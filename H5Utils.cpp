#include "H5Utils.h"
#include <sstream>
#include <iostream>
#include "StringUtils.h"
using namespace H5;

herr_t attr_query(hid_t location_id, const char *attr_name, const H5A_info_t *ainfo, void *opdata) {
	if (opdata) {
		try {
			H5Info *parent = static_cast<H5Info *>(opdata);
			H5::Attribute attr = H5Aopen_name(location_id, attr_name);
			std::string sKey = StringUtils::trim(attr_name);
			std::string sVal = StringUtils::trim(H5Info::getStringValue(attr));
			//printf("Attribute name:'%s', value:'%s'\n", attr_name, sVal.c_str());
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

herr_t group_query(hid_t loc_id, const char *name, void *opdata) {
	if (opdata) {
		try {
			H5Info *parent = static_cast<H5Info *>(opdata);
			std::shared_ptr<H5Info> node(new H5Info);
			H5_index_t index = H5_INDEX_NAME;
			H5_iter_order_t order = H5_ITER_INC;
			hsize_t hs = 0;
			Group g = H5Gopen2(loc_id, name, H5P_DEFAULT);
			H5Aiterate(g.getId(), index, order, &hs, attr_query, node.get());
			g.close();
			H5G_stat_t statbuf;
			H5Gget_objinfo(loc_id, name, false, &statbuf);
			switch (statbuf.type) {
			case H5G_GROUP:
				printf(" Object with name %s is a group \n", name);
				H5Giterate(loc_id, name, NULL, group_query, node.get());
				break;
			default:
				break;
			}
			parent->getGroups()[name] = node;
		}
		catch (Exception e) {
			e.printError();
			return -1;
		}
	}
	return 0;
}









H5Info::H5Info(const std::string & sFile, const std::string &sRoot)
{
	H5File hfile(sFile, H5F_ACC_RDONLY);
	H5Giterate(hfile.getId(), sRoot.c_str(), NULL, group_query, this);
	hfile.close();
}

H5Info::H5Info(H5::Group & g)
{
	H5Giterate(g.getId(), g.getObjName().c_str(), NULL, group_query, this);
}

std::string H5Info::getStringValue(H5::Attribute & attr)
{
	std::stringstream ss;
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
