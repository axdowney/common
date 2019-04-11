#pragma once
#include <map>
#include <memory>
#include <string>

/* hdf5 */
#include "H5Cpp.h"
#include "hdf5.h"

class H5Info {
public:
	H5Info() {};
	H5Info(const std::string &sFile, const std::string &sRoot = "/");
	H5Info(H5::Group &g);
	static std::string getStringValue(H5::Attribute &attr);
	const std::map<std::string, std::string> &getAttributes() const;
	const std::map<std::string, std::shared_ptr<H5Info> > &getGroups() const;
	std::map<std::string, std::string> &getAttributes();
	std::map<std::string, std::shared_ptr<H5Info> > &getGroups();
	static H5G_obj_t printObjType(hid_t loc_id, const char *name, std::string &s);

protected:
	std::map<std::string, std::string> mapAttributes;
	std::map<std::string, std::shared_ptr<H5Info> > mapGroups;
};