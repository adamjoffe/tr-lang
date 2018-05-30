#include "blackboard.h"

namespace TR {

	Blackboard::Blackboard() {
		add_module(TRMODULE,"Basic module as part of TR language");
	}
	
	Blackboard::~Blackboard() {}
	
	bool Blackboard::add_module(std::string name) {
		DataModule dm(name);
		add_module(name,dm);
	}
	bool Blackboard::add_module(std::string name, std::string description) {
		DataModule dm(name, description);
		add_module(name,dm);
	}
	bool Blackboard::add_module(std::string name, DataModule& module) {
		if (bb.count(name) > 0) {
			return false;
		}

		bb.insert({name, module});

		return true;
	}
	
	bool Blackboard::remove_module(std::string name) {
		if (bb.count(name) > 0) {
			bb.erase(name);
			return true;
		}
		return false;
	}

	DataModule& Blackboard::get(std::string name) {
		if (bb.count(name) > 0) {
			return bb[name];
		}
	}

	DataModule& Blackboard::operator[](std::string name) {
		if (bb.count(name) > 0) {
			return bb[name];
		}
	}

	bool Blackboard::exists(std::string name) {
		return bb.count(name) > 0;
	}

	std::ostream& operator<<(std::ostream& os, Blackboard& obj) {
		os << "{";
		size_t i = 0;
		for (auto it = obj.bb.begin(); it != obj.bb.end(); ++it) {
			os << it->second;
			if (i < obj.bb.size() - 1) {
				os << ", ";
			}
		}
		os << "}";
		return os;
	}

}