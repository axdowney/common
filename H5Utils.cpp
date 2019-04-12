#include "H5Utils.h"
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "StringUtils.h"
using namespace H5;

herr_t attr_query(hid_t location_id, const char *attr_name, const H5A_info_t *ainfo, void *opdata) {
	if (opdata) {
		try {
			H5Info *parent = static_cast<H5Info *>(opdata);
			H5::Attribute attr = H5Aopen_name(location_id, attr_name);
			std::string sKey = StringUtils::trim(attr_name);
			std::string sVal = StringUtils::trim(H5Info::getStringValue(attr));
			if (parent->getRoot()->getPrint()) {
				printf("Attribute name:'%s', value:'%s'\n", attr_name, sVal.c_str());
			}
			if (sVal == "Water (15 C)") {
				printf("Debug\n");
			}
			parent->getAttributes()[sKey] = sVal;
			attr.close();
		}
		catch (Exception e) {
			e.printError();
			//std::cerr << "Alex Bad " << attr_name << std::endl;
			return -1;
		}
	}
	return 0;
}

std::string dataToString(void *ptr, int ind, hid_t type_id) {
	std::string s;
	char *c = NULL;
	auto eType = H5Tget_class(type_id);
	size_t sz = H5Tget_size(type_id);
	switch (eType) {
	case H5T_INTEGER:
		s = std::to_string(*static_cast<int *>(ptr));
		break;
	case H5T_STRING:
		c = ((char*)ptr);
		s = std::string(((char*)ptr), sz);
		break;
	default:
		break;
	}
	return s;
}

hsize_t getIndex(const hsize_t *point, hid_t type_id, unsigned ndim) {
	hsize_t hz = 0;
	hsize_t *dims = new hsize_t[ndim]();
	H5Sget_simple_extent_dims(type_id, dims, NULL);
	hsize_t points = H5Sget_simple_extent_npoints(type_id);
	for (int i = 0; i < ndim; ++i) {
		points /= dims[i];
		hz += points * point[i];
	}
	delete[] dims;
	return hz;
}

herr_t data_query(void *elem, hid_t type_id, unsigned ndim,
	const hsize_t *point, void *operator_data) {
	void *ptr = elem;
	/*for (unsigned i = 0; i < ndim - 1; ++i) {
		ptr = static_cast<void**>(ptr)[point[i]];
	}*/
	std::string s = dataToString(ptr, ndim, type_id);
	return 0;
}

herr_t group_query(hid_t loc_id, const char *name, void *opdata) {
	if (opdata) {
		try {
			H5Info *parent = static_cast<H5Info *>(opdata);
			
			H5_index_t index = H5_INDEX_NAME;
			H5_iter_order_t order = H5_ITER_INC;
			hsize_t hs = 0;
			
			H5G_stat_t statbuf;
			H5Gget_objinfo(loc_id, name, false, &statbuf);
			Group g;
			switch (statbuf.type) {
			case H5G_GROUP:
			{
				std::shared_ptr<H5Info> node(new H5Info);
				node->setRoot(parent->getRoot());
				if (node->getRoot()->getPrint()) {
					printf(" Object with name %s is a group \n", name);
				}
				g = H5Gopen2(loc_id, name, H5P_DEFAULT);
				H5Aiterate(g.getId(), index, order, &hs, attr_query, node.get());
				g.close();
				H5Giterate(loc_id, name, NULL, group_query, node.get());
				parent->getGroups()[name] = node;
			}
				break;
			case H5G_DATASET:
			{
				//break;
				hid_t dataset_id = H5Dopen1(loc_id, name);
				hid_t dspace_id = 0, dtype_id = 0, plist_id = 0;
				dspace_id = H5Dget_space(dataset_id);
				dtype_id = H5Dget_type(dataset_id);
				/*plist_id = H5Dget_create_plist(dataset_id);
				int ndims = H5Sget_simple_extent_ndims(dspace_id);
				hsize_t *dims = new hsize_t[ndims]();
				H5Sget_simple_extent_dims(dspace_id, dims, NULL);
				hsize_t numel = ndims > 0;
				for (int i = 0; i < ndims; ++i) {
					numel *= dims[i];
				}
				delete[] dims;
				dims = NULL;
				//H5Sget_simple_extent_dims(dspace_id, dims, NULL);
				H5T_class_t h5class = H5Tget_class(dtype_id);
				
				void *buf = NULL;
				char *strings = NULL;
				int *ints = NULL;
				herr_t h5Err = 0;
				hsize_t sz = H5Tget_size(dtype_id);
				hsize_t prec = H5Tget_precision(dtype_id);
				hsize_t sign = H5Tget_sign(dtype_id);
				switch (h5class) {
				case H5T_STRING:
				{
					
					strings = new char[numel * sz];
					buf = strings;
				}
					break;
				case H5T_INTEGER:
				{
					ints = new int[numel]();
					buf = ints;
				}
				default:
					break;
				}*/

				std::shared_ptr<H5DatasetBase> hds = H5DatasetBase::alloc(dtype_id, dspace_id);
				if (!hds) {
					return 0;
				}
				herr_t h5Err = H5Dread(dataset_id, dtype_id, H5S_ALL, H5S_ALL, H5P_DEFAULT, hds->getBuffer());
				//h5Err = H5Diterate(hds->getBuffer(), dtype_id, dspace_id, data_query, NULL);
				//if (ints) delete[]ints;
				//if (strings) delete[]strings;
				H5Tclose(dtype_id);
				H5Dclose(dataset_id);
				parent->getDatasets()[name] = hds;
			}
				break;
			default:
				break;
			}
		}
		catch (Exception e) {
			e.printError();
			return -1;
		}
	}
	return 0;
}









H5Info::H5Info(const std::string & sFile, const std::string &sRoot) : bPrint(false)
{
	root = this;
	H5File hfile(sFile.c_str(), H5F_ACC_RDONLY);
	H5Giterate(hfile.getId(), sRoot.c_str(), NULL, group_query, this);
	hfile.close();
}

H5Info::H5Info(H5::Group & g) : bPrint(false)
{
	root = this;
	H5Giterate(g.getId(), g.getObjName().c_str(), NULL, group_query, this);
}

template <typename T>
std::ostream &operator<<(std::ostream &out, std::vector<T> &vec) {
	for (int i = 0; i < vec.size(); ++i) {
		if (i > 0) {
			out << ",";
		}
		out << vec[i];
	}
	return out;
}

std::string H5Info::getStringValue(H5::Attribute & attr)
{
	std::stringstream ss;
	ss.precision(17);

	hid_t atype = H5Aget_type(attr.getId());
	hid_t aspace = H5Aget_space(attr.getId());
	size_t tElem = H5Sget_simple_extent_npoints(aspace);
	auto eType = H5Tget_class(atype);
#define H5_ATTR_LOOP(type) \
	type *arr = new type[tElem + 1](); \
	H5Aread(attr.getId(), atype, arr); \
	for (size_t i = 0; i < tElem; ++i) {\
		if (i > 0) {\
			ss << ","; \
		} \
		ss << arr[i]; \
	} \
	delete [] arr;

	switch (eType) {
	case H5T_INTEGER:
	{
		H5_ATTR_LOOP(int);
		H5::Attribute attr2(attr);
		std::vector<int> ints2(tElem);
		for (int i = 0; i < tElem; ++i) {
			ints2[i] = i + 1;
		}
		//H5::DataType dt(atype);
		IntType int_type(PredType::STD_I32LE);
		//attr2.write(int_type, ints2.data());
		int ia = H5Tget_array_ndims(atype);
		//attr2.write(int_type, &ia);
		H5Awrite(attr2.getId(), atype, ints2.data());
		std::vector<long long int> ints1(tElem, 0);
		//ints2 = ints1;
		attr.read(atype, ints1.data());
		attr2.read(atype, ints2.data());
		std::cout << ints1 << std::endl << ints2 << std::endl;
		auto i = H5T_NATIVE_CHAR;
	}
	break;
	case H5T_FLOAT:
	{
		H5_ATTR_LOOP(double);
	}
	break;
	case H5T_STRING:
	{
		std::string strg;
		attr.read(atype, strg);
		ss << strg;
	}
	break;
	default:
		break;
	}
	H5Tclose(atype);
	H5Sclose(aspace);

	return ss.str();
}

const std::map<std::string, std::string>& H5Info::getAttributes() const
{
	return mapAttributes;
}

const std::map<std::string, std::shared_ptr<H5Info>>& H5Info::getGroups() const
{
	return mapGroups;
}

std::map<std::string, std::string>& H5Info::getAttributes()
{
	return mapAttributes;
}

std::map<std::string, std::shared_ptr<H5Info>>& H5Info::getGroups()
{
	return mapGroups;
}

std::map<std::string, std::shared_ptr<H5DatasetBase> >& H5Info::getDatasets()
{
	return mapDatasets;
}

H5G_obj_t H5Info::printObjType(hid_t loc_id, const char * name, std::string & s)
{
	char *lname = nullptr;
	H5G_stat_t statbuf;
	H5Gget_objinfo(loc_id, name, false, &statbuf);
	switch (statbuf.type) {
	case H5G_GROUP:
		StringUtils::sprintf(s, " Object with name %s is a group \n", name);
		break;
	case H5G_DATASET:
		StringUtils::sprintf(s, " Object with name %s is a dataset \n", name);
		break;
	case H5G_TYPE:
		StringUtils::sprintf(s, " Object with name %s is a named datatype \n", name);
		break;
	case H5G_LINK:
		lname = (char *)malloc(statbuf.linklen);
		H5Gget_linkval(loc_id, name, statbuf.linklen, lname);
		StringUtils::sprintf(s, " Object with name %s is a link to %s \n", name, lname);
		H5Gget_objinfo(loc_id, name, true, &statbuf);
		switch (statbuf.type) {
		case H5G_GROUP:
			StringUtils::sprintf(s, " Target of link name %s is a group \n", name);
			break;
		case H5G_DATASET:
			StringUtils::sprintf(s, " Target of link name %s is a dataset \n", name);
			break;
		case H5G_TYPE:
			StringUtils::sprintf(s, " Target of link name %s is a named datatype \n", name);
			break;
		case H5G_LINK:
			StringUtils::sprintf(s, " Target of link name %s is a soft link \n", name);
			break;
		default:
			StringUtils::sprintf(s, " Unable to identify target ");
		}
		break;
	default:
		StringUtils::sprintf(s, " Unable to identify an object ");
		break;
	}
	return statbuf.type;
}

bool H5Info::setPrint(bool b)
{
	return this->bPrint = b;
}

bool H5Info::getPrint() const
{
	return bPrint;
}

H5Info * H5Info::getRoot()
{
	return root;
}

H5Info * H5Info::setRoot(H5Info * r)
{
	return root = r;
}

bool H5Info::write(const std::string & s)
{
	bool bOK = false;
	hid_t hidFile = H5Fcreate(s.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
	if (hidFile > 0) {
		bOK = write(hidFile);
		H5Fclose(hidFile);
	}
	return bOK;
}

bool H5Info::write(hid_t parent)
{
	bool bOK = true;
	for (auto iter : mapGroups) {
		hid_t gid = H5Gcreate2(parent, iter.first.c_str(), H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
		if (gid > 0) {
			bOK = iter.second->write(gid);
			H5Gclose(gid);
		}
		else {
			bOK = false;
		}

		if (!bOK) break;
	}
	return bOK;
}

void H5DatasetAny::alloc(hid_t iTypeID, hid_t iSpaceID)
{
	int ndims = H5Sget_simple_extent_ndims(iSpaceID);
	//hsize_t *dims = new hsize_t[ndims]();
	dims.resize(ndims);
	H5Sget_simple_extent_dims(iSpaceID, dims.data(), NULL);
	hsize_t numel = ndims > 0;
	for (int i = 0; i < ndims; ++i) {
		numel *= dims[i];
	}
	hsize_t sz = H5Tget_size(iTypeID);
	hid_t iType = H5Tget_native_type(iTypeID, H5T_DIR_ASCEND);
	alloc(iType, numel, sz);
}

bool H5DatasetAny::alloc(hid_t iType, hsize_t iNumel, hsize_t iBytes)
{
	bool bOK = true;
	if (iNumel > 0 && iBytes > 0) {
		if (iType == H5T_NATIVE_CHAR) {
			//spCharBuf.reset(new char[iNumel * iBytes]);
			//spVoidBuf = spCharBuf;
			vecCharBuf.resize(iNumel * iBytes);
			ptr = vecCharBuf.data();
        } else if (iType == H5T_NATIVE_SHORT) {
			//spShortBuf.reset(new short[iNumel]);
			//spVoidBuf = spShortBuf;
			vecShortBuf.resize(iNumel);
			ptr = vecShortBuf.data();
		} else if (iType == H5T_NATIVE_INT) {
			//spIntBuf.reset(new int[iNumel]);
			//spVoidBuf = spIntBuf;
			vecIntBuf.resize(iNumel);
			ptr = vecIntBuf.data();
        } else if (iType == H5T_NATIVE_LONG) {
			//spLongBuf.reset(new long[iNumel]);
			//spVoidBuf = spLongBuf;
			vecLongBuf.resize(iNumel);
			ptr = vecLongBuf.data();
        } else if (iType == H5T_NATIVE_LLONG) {
			//spLLongBuf.reset(new long long[iNumel]);
			//spVoidBuf = spLLongBuf;
			vecLLongBuf.resize(iNumel);
			ptr = vecLLongBuf.data();
        } else if (iType == H5T_NATIVE_UCHAR) {
			//spUCharBuf.reset(new unsigned char[iNumel * iBytes]);
			//spVoidBuf = spUCharBuf;
			vecUCharBuf.resize(iNumel * iBytes);
			ptr = vecUCharBuf.data();
        } else if (iType == H5T_NATIVE_USHORT) {
			//spUShortBuf.reset(new unsigned short[iNumel]);
			//spVoidBuf = spUShortBuf;
			vecUShortBuf.resize(iNumel);
			ptr = vecUShortBuf.data();
        } else if (iType == H5T_NATIVE_UINT) {
			//spUIntBuf.reset(new unsigned int [iNumel]);
			//spVoidBuf = spUIntBuf;
			vecUIntBuf.resize(iNumel);
			ptr = vecUIntBuf.data();
        } else if (iType == H5T_NATIVE_ULONG) {
			//spULongBuf.reset(new unsigned long[iNumel]);
			//spVoidBuf = spULongBuf;
			vecULongBuf.resize(iNumel);
			ptr = vecULongBuf.data();
        } else if (iType == H5T_NATIVE_ULLONG) {
			//spULLongBuf.reset(new unsigned long long[iNumel]);
			//spVoidBuf = spULLongBuf;
			vecULLongBuf.resize(iNumel);
			ptr = vecULLongBuf.data();
        } else if (iType == H5T_NATIVE_FLOAT) {
			//spFloatBuf.reset(new float[iNumel]);
			//spVoidBuf = spFloatBuf;
			vecFloatBuf.resize(iNumel);
			ptr = vecFloatBuf.data();
        } else if (iType == H5T_NATIVE_DOUBLE) {
			//spDoubleBuf.reset(new double[iNumel]);
			//spVoidBuf = spDoubleBuf;
			vecDoubleBuf.resize(iNumel);
			ptr = vecDoubleBuf.data();
        } else if (iType == H5T_NATIVE_LDOUBLE) {
			//spLDoubleBuf.reset(new long double[iNumel]);
			//spVoidBuf = spLDoubleBuf;
			vecLDoubleBuf.resize(iNumel);
			ptr = vecLDoubleBuf.data();
		}
		else {
			bOK = false;
		}
	}
	else {
		bOK = false;
	}
	return bOK;
}

void H5DatasetAny::free()
{
	/*spCharBuf.reset();// H5T_NATIVE_CHAR
	spShortBuf.reset();// H5T_NATIVE_SHORT
	spIntBuf.reset();// H5T_NATIVE_INT
	spLongBuf.reset();// H5T_NATIVE_LONG
	spLLongBuf.reset();// H5T_NATIVE_LLONG

	spUCharBuf.reset();// H5T_NATIVE_UCHAR
	spUShortBuf.reset();// H5T_NATIVE_USHORT
	spUIntBuf.reset();// H5T_NATIVE_UINT
	spULongBuf.reset();// H5T_NATIVE_ULONG
	spULLongBuf.reset();// H5T_NATIVE_ULLONG

	spFloatBuf.reset();// H5T_NATIVE_FLOAT
	spDoubleBuf.reset();// H5T_NATIVE_DOUBLE
	spLDoubleBuf.reset();// H5T_NATIVE_LDOUBLE

	spVoidBuf.reset();*/
	vecCharBuf.clear();// H5T_NATIVE_CHAR
	vecShortBuf.clear();// H5T_NATIVE_SHORT
	vecIntBuf.clear();// H5T_NATIVE_INT
	vecLongBuf.clear();// H5T_NATIVE_LONG
	vecLLongBuf.clear();// H5T_NATIVE_LLONG

	vecUCharBuf.clear();// H5T_NATIVE_UCHAR
	vecUShortBuf.clear();// H5T_NATIVE_USHORT
	vecUIntBuf.clear();// H5T_NATIVE_UINT
	vecULongBuf.clear();// H5T_NATIVE_ULONG
	vecULLongBuf.clear();// H5T_NATIVE_ULLONG

	vecFloatBuf.clear();// H5T_NATIVE_FLOAT
	vecDoubleBuf.clear();// H5T_NATIVE_DOUBLE
	vecLDoubleBuf.clear();// H5T_NATIVE_LDOUBLE
}


void *H5DatasetAny::getBuffer()
{
	return ptr;
}

const std::vector<hsize_t>& H5DatasetAny::getDims() const
{
	return dims;
}

hid_t H5DatasetAny::getNativeType() const
{
	return iNativeType;
}

const std::vector<hsize_t>& H5DatasetBase::getDims() const
{
	return dims;
}

hid_t H5DatasetBase::getNativeType() const
{
	return iNativeType;
}

hsize_t H5DatasetBase::numel() const
{
	return iNumel;
}

std::shared_ptr<H5DatasetBase> H5DatasetBase::alloc(hid_t iTypeID, hid_t iSpaceID)
{
	int ndims = H5Sget_simple_extent_ndims(iSpaceID);
	//hsize_t *dims = new hsize_t[ndims]();
	std::vector<hsize_t> dims(ndims);
	H5Sget_simple_extent_dims(iSpaceID, dims.data(), NULL);
	hsize_t numel = ndims > 0;
	for (int i = 0; i < ndims; ++i) {
		numel *= dims[i];
	}
	int ndimsa = H5Tget_array_ndims(iTypeID);
	std::vector<hsize_t> dimsa;
	if (ndimsa > 0) {
		dimsa.resize(ndimsa);
		H5Tget_array_dims(iTypeID, dimsa.data());
	}
	hsize_t sz = H5Tget_size(iTypeID);
	hid_t iType = H5Tget_native_type(iTypeID, H5T_DIR_DESCEND);
	H5T_class_t tclass = H5Tget_class(iTypeID);
	std::shared_ptr<H5DatasetBase> sp;
	htri_t cmpr = H5Tequal(iType, H5T_NATIVE_FLOAT);
	cmpr = H5Tequal(iType, H5T_NATIVE_DOUBLE);
	cmpr = H5Tequal(iType, H5T_NATIVE_LDOUBLE);
	cmpr = H5Tequal(iTypeID, H5T_NATIVE_FLOAT);
	switch (tclass) {
	case H5T_STRING:
		if (H5Tequal(iTypeID, H5T_NATIVE_CHAR) > 0) {
			sp.reset(new H5Dataset<char>(sz * numel));
		}
		else if (H5Tequal(iTypeID, H5T_NATIVE_UCHAR) > 0) {
			sp.reset(new H5Dataset<unsigned char>(sz * numel));
		}
		break;
	case H5T_INTEGER:
		if (H5Tequal(iTypeID, H5T_NATIVE_CHAR) > 0) {
			sp.reset(new H5Dataset<char>(numel));
		}
		else if (H5Tequal(iTypeID, H5T_NATIVE_UCHAR) > 0) {
			sp.reset(new H5Dataset<unsigned char>(numel));
		}
		else if (H5Tequal(iTypeID, H5T_NATIVE_SHORT) > 0) {
			sp.reset(new H5Dataset<short>(numel));
		}
		else if (H5Tequal(iTypeID, H5T_NATIVE_INT) > 0) {
			sp.reset(new H5Dataset<int>(numel));
		}
		else if (H5Tequal(iTypeID, H5T_NATIVE_LONG) > 0) {
			sp.reset(new H5Dataset<long>(numel));
		}
		else if (H5Tequal(iTypeID, H5T_NATIVE_LLONG) > 0) {
			sp.reset(new H5Dataset<long long>(numel));
		}
		else if (H5Tequal(iTypeID, H5T_NATIVE_USHORT) > 0) {
			sp.reset(new H5Dataset<unsigned short>(numel));
		}
		else if (H5Tequal(iTypeID, H5T_NATIVE_UINT) > 0) {
			sp.reset(new H5Dataset<unsigned int>(numel));
		}
		else if (H5Tequal(iTypeID, H5T_NATIVE_ULONG) > 0) {
			sp.reset(new H5Dataset<unsigned long>(numel));
		}
		else if (H5Tequal(iTypeID, H5T_NATIVE_ULLONG) > 0) {
			sp.reset(new H5Dataset<unsigned long long>(numel));
		}
		break;
	case H5T_FLOAT:
		if (H5Tequal(iTypeID, H5T_NATIVE_FLOAT) > 0) {
			sp.reset(new H5Dataset<float>(numel));
		}
		else if (H5Tequal(iTypeID, H5T_NATIVE_DOUBLE) > 0) {
			sp.reset(new H5Dataset<double>(numel));
		}
		else if (H5Tequal(iTypeID, H5T_NATIVE_LDOUBLE) > 0) {
			sp.reset(new H5Dataset<long double>(numel));
		}
	default:
		break;
	}
	std::vector<hid_t> vecTypes = {
		H5T_NATIVE_CHAR,
		H5T_NATIVE_SHORT,
		H5T_NATIVE_INT,
		H5T_NATIVE_LONG,
		H5T_NATIVE_LLONG,

		H5T_NATIVE_UCHAR,
		H5T_NATIVE_USHORT,
		H5T_NATIVE_UINT,
		H5T_NATIVE_ULONG,
		H5T_NATIVE_ULLONG,

		H5T_NATIVE_FLOAT,
		H5T_NATIVE_DOUBLE,
		H5T_NATIVE_LDOUBLE,
		H5T_NATIVE_B8,
		H5T_NATIVE_B16,
		H5T_NATIVE_B32,
		H5T_NATIVE_B64
	};
	if (sp) {
		sp->iByte = sz;
		sp->iNumel = numel;
		sp->dims = dims;
		sp->iNativeType = iType;
	}
	return sp;
}

const std::map<H5T_class_t, std::map<hsize_t, hid_t> > H5Type::mapNativeTypes = {
	{ H5T_class_t::H5T_INTEGER , {  } },
	{ H5T_class_t::H5T_FLOAT , { {4 , H5T_NATIVE_FLOAT_g}, {8, H5T_NATIVE_LDOUBLE_g } } }
};

const std::map<H5Type::HType, hid_t> H5Type::mapTypeEnums = {
	{ H5Type::HType::UNKNOWN, -1},
	{ H5Type::HType::NATIVE_CHAR, H5T_NATIVE_SCHAR_g },
	{ H5Type::HType::NATIVE_SCHAR, H5T_NATIVE_SCHAR_g },
	{ H5Type::HType::NATIVE_UCHAR, H5T_NATIVE_UCHAR_g },

	{ H5Type::HType::NATIVE_SHORT, H5T_NATIVE_SHORT_g },
	{ H5Type::HType::NATIVE_USHORT, H5T_NATIVE_USHORT_g },

	{ H5Type::HType::NATIVE_INT, H5T_NATIVE_INT_g },
	{ H5Type::HType::NATIVE_UINT, H5T_NATIVE_UINT_g },

	{ H5Type::HType::NATIVE_LONG, H5T_NATIVE_LONG_g },
	{ H5Type::HType::NATIVE_ULONG, H5T_NATIVE_ULONG_g },
	{ H5Type::HType::NATIVE_LLONG, H5T_NATIVE_LLONG_g },
	{ H5Type::HType::NATIVE_ULLONG, H5T_NATIVE_ULLONG_g },

	{ H5Type::HType::NATIVE_FLOAT, H5T_NATIVE_FLOAT_g },
	{ H5Type::HType::NATIVE_DOUBLE, H5T_NATIVE_DOUBLE_g },
	{ H5Type::HType::NATIVE_LDOUBLE, H5T_NATIVE_LDOUBLE_g },

	{ H5Type::HType::NATIVE_B8, H5T_NATIVE_B8_g },
	{ H5Type::HType::NATIVE_B16, H5T_NATIVE_B16_g },
	{ H5Type::HType::NATIVE_B32, H5T_NATIVE_B32_g },
	{ H5Type::HType::NATIVE_B64, H5T_NATIVE_B64_g },

	{ H5Type::HType::NATIVE_OPAQUE, H5T_NATIVE_OPAQUE_g },
	{ H5Type::HType::NATIVE_HADDR, H5T_NATIVE_HADDR_g },
	{ H5Type::HType::NATIVE_HSIZE, H5T_NATIVE_HSIZE_g },
	{ H5Type::HType::NATIVE_HSSIZE, H5T_NATIVE_HSSIZE_g },
	{ H5Type::HType::NATIVE_HERR, H5T_NATIVE_HERR_g },
	{ H5Type::HType::NATIVE_HBOOL, H5T_NATIVE_HBOOL_g },
};

hid_t H5Type::getNativeType(H5T_class_t ct, hsize_t sz)
{
	hid_t hid = -1;
	
	return hid;
}

hid_t H5Type::getNativeType(hid_t tid)
{
	return H5Type::getNativePair(tid).second;
}

H5Type::HType H5Type::getNativeEnum(hid_t tid)
{
	return H5Type::getNativePair(tid).first;
}

hid_t H5Type::getNativeType(H5Type::HType eType)
{
	hid_t hid = -1;
	auto iter = mapTypeEnums.find(eType);
	if (iter != mapTypeEnums.end()) {
		hid = iter->second;
	}
	return hid;
}

const std::pair<H5Type::HType, hid_t>& H5Type::getNativePair(hid_t tid)
{
	auto iter = mapTypeEnums.find(HType::UNKNOWN);
	for (const auto &iter : mapTypeEnums) {
		htri_t eq = H5Tequal(tid, iter.second);
		if (eq > 0) {
			return iter;
		}
		else if (eq < 0) {
			break;
		}
	}
	return *iter;
}

void H5Type::setFromID(hid_t hid)
{
	eClass = H5Tget_class(hid);
	iSize = H5Tget_size(hid);
	
	switch (eClass) {
	case H5T_class_t::H5T_INTEGER:
	case H5T_class_t::H5T_FLOAT:
	case H5T_class_t::H5T_BITFIELD:
		typeID = getNativeType(hid);
		break;
	default:
		typeID = 0;
	}
}

std::shared_ptr<H5Type> H5Type::createType(hid_t tid)
{
	std::shared_ptr<H5Type> sp;
	H5T_class_t eClass = H5Tget_class(tid);
	switch (eClass) {
	case H5T_class_t::H5T_ARRAY:
	case H5T_class_t::H5T_VLEN:
		sp.reset(new H5ArrayType());
		sp->setFromID(tid);
		break;
	case H5T_class_t::H5T_COMPOUND:
		sp.reset(new H5CompoundType());
		sp->setFromID(tid);
		break;
	case H5T_class_t::H5T_ENUM:
		sp.reset(new H5EnumType());
		sp->setFromID(tid);
		break;
	case H5T_class_t::H5T_NO_CLASS:
		break;
	default:
		sp.reset(new H5Type());
		sp->setFromID(tid);
		break;
	}
	return sp;
}

void H5ArrayType::setFromID(hid_t hid)
{
	H5Type::setFromID(hid);
	if (eClass == H5T_class_t::H5T_ARRAY) {
		iRank = H5Tget_array_ndims(hid);
		if (iRank > 0) {
			vecDims.resize(iRank);
		}
		else {
			vecDims.clear();
		}
	}
	else {
		iRank = 0;
		vecDims.clear();
	}
	hid_t tidBase = H5Tget_super(hid);
	spBase = createType(tidBase);
	H5Tclose(tidBase);
}

void H5CompoundType::setFromID(hid_t hid)
{
	H5Type::setFromID(hid);
	if (eClass == H5T_class_t::H5T_COMPOUND) {
		int iRank = H5Tget_nmembers(hid);
		if (iRank > 0) {
			vecMemberTypes.resize(iRank);
			for (int i = 0; i < iRank; ++i) {
				char *sz = H5Tget_member_name(hid, i);
				vecMemberTypes[i].first = sz ? sz : "";
				H5free_memory(sz);
				sz = NULL;
				hid_t tidMem = H5Tget_member_type(hid, 0);
				vecMemberTypes[i].second = createType(tidMem);
				H5Tclose(tidMem);
			}
		}
		else {
			vecMemberTypes.clear();
		}
	}
	else {
		vecMemberTypes.clear();
	}
}

hid_t H5CompoundType::buildType() const
{
	hid_t hid = -1;
	size_t t = 0;
	hid = H5Tcreate(H5T_COMPOUND, t);
	return hid;
}

H5Type::HType H5DataVoid::getType() const
{
	return eType;
}

std::unique_ptr<H5DataVoid> H5DataVoid::createData(H5Type::HType eType)
{
	std::unique_ptr<H5DataVoid> up;
	switch (eType) {
	case H5Type::HType::NATIVE_CHAR:
		up.reset(new H5Data<char>());
		break;
	case H5Type::HType::NATIVE_UCHAR:
		up.reset(new H5Data<unsigned char>());		
		break;
	case H5Type::HType::NATIVE_SHORT:
		up.reset(new H5Data<short>());
		break;
	case H5Type::HType::NATIVE_INT:
		up.reset(new H5Data<int>());
		break;
	case H5Type::HType::NATIVE_LONG:
		up.reset(new H5Data<long>());
		break;
	case H5Type::HType::NATIVE_LLONG:
		up.reset(new H5Data<long long>);
		break;
	case H5Type::HType::NATIVE_USHORT:
		up.reset(new H5Data<unsigned short>());
		break;
	case H5Type::HType::NATIVE_UINT:
		up.reset(new H5Data<unsigned int>());
		break;
	case H5Type::HType::NATIVE_ULONG:
		up.reset(new H5Data<unsigned long>());
		break;
	case H5Type::HType::NATIVE_ULLONG:
		up.reset(new H5Data<unsigned long long>);
		break;
	case H5Type::HType::NATIVE_FLOAT:
		up.reset(new H5Data<float>());
		break;
	case H5Type::HType::NATIVE_DOUBLE:
		up.reset(new H5Data<double>());
		break;
	case H5Type::HType::NATIVE_LDOUBLE:
		up.reset(new H5Data<long double>());
		break;
	default:
		break;
	}
	return up;
}

void H5EnumType::setFromID(hid_t hid)
{
	spValues.reset();
	vecNames.clear();
	H5Type::setFromID(hid);
	if (eClass == H5T_class_t::H5T_ENUM) {
		hid_t tid = H5Tget_super(hid);
		spValues = H5DataVoid::createData(H5Type::getNativeEnum(tid));
		if (spValues) {
			spValues->resize(H5Tget_nmembers(hid));
			vecNames.resize(spValues->size());
			for (size_t i = 0; i < spValues->size(); ++i) {
				H5Tget_member_value(hid, i, spValues->getData(i));
				char * sz = H5Tget_member_name(hid, i);
				vecNames[i] = sz ? sz : "";
				H5free_memory(sz);
			}
		}
		H5Tclose(tid);
	}
}
/*!
 * Opens a type for the enum.
 * Must be closed by caller to prevent leaks.
 * \return an id for the enum type or -1 on error
 */
hid_t H5EnumType::buildType() const
{
	hid_t hid = -1;
	if (spValues) {
		hid = H5Tenum_create(H5Type::getNativeType(spValues->getType()));
		size_t iSize = std::min(spValues->size(), vecNames.size());
		for (size_t i = 0; i < iSize; ++i) {
			H5Tenum_insert(hid,vecNames[i].c_str(), spValues->getData(i));
		}
	}
	return hid;
}
