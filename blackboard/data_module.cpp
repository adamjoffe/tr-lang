#include "data_module.h"

namespace TR {

	DataModule::DataModule() : DataModule("","") {}
	DataModule::DataModule(std::string n) : DataModule(n,"") {}
	DataModule::DataModule(std::string n, std::string d) : name(n), description(d) {}
	
	DataModule::~DataModule() {
		for (auto it = dm.begin(); it != dm.end(); ++it) {
			delete it->second;
		}
	}

	bool DataModule::add_struct(std::string name, DataStruct* dstruct) {
		if (dm.count(name) > 0) {
			return false;
		}

		dm.insert({name, dstruct});

		return true;
	}
	
	bool DataModule::remove_struct(std::string name) {
		if (dm.count(name) > 0) {
			dm.erase(name);
		} else {
			return false;
		}
	}

	DataStruct* DataModule::get(std::string name) {
		if (dm.count(name) > 0) {
			return dm[name];
		}
	}

	DataStruct* DataModule::operator[](std::string name) {
		if (dm.count(name) > 0) {
			return dm[name];
		}
	}

	bool DataModule::exists(std::string name) {
		return dm.count(name) > 0;
	}

	std::string DataModule::structs_to_string() {
		std::string ret;
		size_t i = 0;
		for (auto it = dm.begin(); it != dm.end(); ++it) {
			ret += it->first + " : " + it->second->getName();
			if (i < dm.size() - 1) {
				ret += ", ";
			}
			++i;
		}
		return ret;
	}

	std::ostream& operator<<(std::ostream& os, DataModule& obj) {
		os << obj.name << " : " << obj.description;
		return os;
	}

}