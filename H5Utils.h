#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>

/* hdf5 */
#include "H5Cpp.h"
#include "hdf5.h"
#include "H5File.h"

class H5DatasetAny {
public:
	void alloc(hid_t iTypeID, hid_t iSpaceID);
	bool alloc(hid_t iType, hsize_t iNumel, hsize_t iBytes);
	void free();
	void *getBuffer();
	const std::vector<hsize_t> &getDims() const;
	hid_t getNativeType() const;
private:
	hid_t iNativeType;

	/*std::shared_ptr<char> spCharBuf;// H5T_NATIVE_CHAR
	std::shared_ptr<short> spShortBuf;// H5T_NATIVE_SHORT
	std::shared_ptr<int> spIntBuf;// H5T_NATIVE_INT
	std::shared_ptr<long> spLongBuf;// H5T_NATIVE_LONG
	std::shared_ptr<long long> spLLongBuf;// H5T_NATIVE_LLONG

	std::shared_ptr<unsigned char> spUCharBuf;// H5T_NATIVE_UCHAR
	std::shared_ptr<unsigned short> spUShortBuf;// H5T_NATIVE_USHORT
	std::shared_ptr<int> spUIntBuf;// H5T_NATIVE_UINT
	std::shared_ptr<long> spULongBuf;// H5T_NATIVE_ULONG
	std::shared_ptr<long long> spULLongBuf;// H5T_NATIVE_ULLONG

	std::shared_ptr<float> spFloatBuf;// H5T_NATIVE_FLOAT
	std::shared_ptr<double> spDoubleBuf;// H5T_NATIVE_DOUBLE
	std::shared_ptr<long double> spLDoubleBuf;// H5T_NATIVE_LDOUBLE

	std::shared_ptr<void> spVoidBuf;*/
	std::vector<hsize_t> dims;

	std::vector<char> vecCharBuf;// H5T_NATIVE_CHAR
	std::vector<short> vecShortBuf;// H5T_NATIVE_SHORT
	std::vector<int> vecIntBuf;// H5T_NATIVE_INT
	std::vector<long> vecLongBuf;// H5T_NATIVE_LONG
	std::vector<long long> vecLLongBuf;// H5T_NATIVE_LLONG

	std::vector<unsigned char> vecUCharBuf;// H5T_NATIVE_UCHAR
	std::vector<unsigned short> vecUShortBuf;// H5T_NATIVE_USHORT
	std::vector<int> vecUIntBuf;// H5T_NATIVE_UINT
	std::vector<long> vecULongBuf;// H5T_NATIVE_ULONG
	std::vector<long long> vecULLongBuf;// H5T_NATIVE_ULLONG

	std::vector<float> vecFloatBuf;// H5T_NATIVE_FLOAT
	std::vector<double> vecDoubleBuf;// H5T_NATIVE_DOUBLE
	std::vector<long double> vecLDoubleBuf;// H5T_NATIVE_LDOUBLE
	void *ptr;

};

class H5Type {
public:
	enum class HType {
		UNKNOWN,

		NATIVE_CHAR,
		NATIVE_SCHAR,
		NATIVE_UCHAR,
		
		NATIVE_SHORT,
		NATIVE_USHORT,

		NATIVE_INT,
		NATIVE_UINT,
		
		NATIVE_LONG,
		NATIVE_ULONG,
		NATIVE_LLONG,
		NATIVE_ULLONG,

		NATIVE_FLOAT,
		NATIVE_DOUBLE,
		NATIVE_LDOUBLE,

		NATIVE_B8,
		NATIVE_B16,
		NATIVE_B32,
		NATIVE_B64,

		NATIVE_OPAQUE,
		NATIVE_HADDR,
		NATIVE_HSIZE,
		NATIVE_HSSIZE,
		NATIVE_HERR,
		NATIVE_HBOOL,

	};
	static const std::map<HType, hid_t> mapTypeEnums;
	static hid_t getNativeType(H5T_class_t ct, hsize_t sz);
	static hid_t getNativeType(hid_t tid);
	static HType getNativeEnum(hid_t tid);
	static hid_t getNativeType(HType eType);
	static const std::pair<HType, hid_t> &getNativePair(hid_t tid);
	void setFromID(hid_t hid);
	static std::shared_ptr<H5Type> createType(hid_t tid);
	virtual hid_t buildType() const;
protected:
	H5T_class_t eClass;
	hsize_t iSize; // Base Type Byte Size
	hid_t typeID;
	static const std::map<H5T_class_t, std::map<hsize_t, hid_t> > mapNativeTypes;
};

class H5CompoundType : public H5Type {
	size_t calcSize();
	void setFromID(hid_t hid);
	virtual hid_t buildType() const;
protected:
	std::vector<std::pair<std::string, std::shared_ptr<H5Type> > > vecMemberTypes;
};

class H5ArrayType : public H5Type {
public:
	void setFromID(hid_t hid);
protected:
	int iRank; // ndims -1 for non array
	std::vector<hsize_t> vecDims;
	std::shared_ptr<H5Type> spBase;
};

class H5DataVoid {
public:
	virtual void *data() = 0;
	virtual void *getData(size_t i) = 0;
	virtual void clear() = 0;
	virtual void resize(size_t i) = 0;
	virtual size_t size() const = 0;
	H5Type::HType getType() const;
	static std::unique_ptr<H5DataVoid> createData(H5Type::HType eType);
protected:
	H5Type::HType eType;
};

template<typename T>
class H5Data : public H5DataVoid {
public:
	virtual void *data() { return vec.data(); }
	virtual void *getData(size_t i) { return &vec.at(i); }
	virtual void clear() { vec.clear(); }
	virtual void resize(size_t i) { vec.resize(i); }
	virtual size_t size() const { return vec.size(); }
	T &operator[](size_t i) { return vec[i]; }
protected:
	std::vector<T> vec;
};

class H5EnumType : public H5Type {
public:
	void setFromID(hid_t hid);
	hid_t buildType() const;
protected:
	HType IntType;
	std::shared_ptr<H5DataVoid> spValues;
	std::vector<std::string> vecNames;
};

class H5DatasetBase {
public:
	virtual void *getBuffer() = 0;
	const std::vector<hsize_t> &getDims() const;
	hid_t getNativeType() const;
	hsize_t numel() const;

	static std::shared_ptr<H5DatasetBase> alloc(hid_t iTypeID, hid_t iSpaceID);
	//std::shared_ptr<H5DatasetBase> alloc(hid_t iType, hsize_t iNumel, hsize_t iBytes);
	
protected:
	hid_t iNativeType;
	hsize_t iNumel;
	hsize_t iByte;
	std::vector<hsize_t> dims;
};

template<typename T>
class H5Dataset : public H5DatasetBase {
public:
	H5Dataset() {}
	H5Dataset(size_t iSize) : vec(iSize) {}
	std::vector<T> &getData() {
		return vec;
	}
	const std::vector<T> &getData() const {
		return vec;
	}
	void *getBuffer() {
		return vec.data();
	}
	T at(size_t x, size_t y, size_t z, bool xr = false, bool yr = false, bool zr = false) {
		size_t nz = dims.size() >= 3 ? dims[2] : 1;
		if ((z >= nz)) {
			throw std::out_of_range("z > than max z of " + std::to_string(nz));
		}
		size_t ny = dims.size() >= 2 ? dims[1] : 1;
		if ((y >= ny)) {
			throw std::out_of_range("y > than max y of " + std::to_string(ny));
		}
		size_t nx = dims.size() >= 1 ? dims[0] : 1;
		if ((x >= nx)) {
			throw std::out_of_range("x > than max x of " + std::to_string(nx));
		}
		if (xr) x = nx - 1 - x;
		if (yr) y = ny - 1 - y;
		if (zr) z = nz - 1 - z;
		size_t indx = x * ny * nz + y * nz + z;
		return vec[indx];
	}
protected:
	std::vector<T> vec;
};

class H5Compound {
public:
protected:
	std::vector<std::pair<H5T_class_t, std::string> > values;
	std::map<std::string, unsigned> mapNames;
};

class H5Attribute {
protected:

};

class H5Info {
public:
	H5Info() : bPrint(false) { root = this; };
	H5Info(const std::string &sFile, const std::string &sRoot = "/");
	H5Info(H5::Group &g);
	static std::string getStringValue(H5::Attribute &attr);
	const std::map<std::string, std::string> &getAttributes() const;
	const std::map<std::string, std::shared_ptr<H5Info> > &getGroups() const;
	std::map<std::string, std::string> &getAttributes();
	std::map<std::string, std::shared_ptr<H5Info> > &getGroups();
	std::map<std::string, std::shared_ptr<H5DatasetBase> > &getDatasets();
	static H5G_obj_t printObjType(hid_t loc_id, const char *name, std::string &s);
	bool setPrint(bool b = true);
	bool getPrint() const;
	H5Info *getRoot();
	H5Info *setRoot(H5Info *r);
	bool write(const std::string &s);
	bool write(hid_t parent);

protected:
	std::map<std::string, std::string> mapAttributes;
	std::map<std::string, std::shared_ptr<H5Info> > mapGroups;
	std::map<std::string, std::shared_ptr<H5DatasetBase> > mapDatasets;
	H5Info *root;
	bool bPrint;
};
