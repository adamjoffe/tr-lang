#ifndef TR_DATA_MODULE_H
#define TR_DATA_MODULE_H

#include <ostream>
#include <string>
#include <unordered_map>

// included first as is base class
#include "data_struct.h"

namespace TR{

	/// Blackboard data module, indexed by name and contains description of module
	class DataModule {
	public:
		DataModule();
		DataModule(std::string n);
		DataModule(std::string n, std::string d);
		
		~DataModule();
		
		/// add a data struct to this data module
		bool add_struct(std::string name, DataStruct* dstruct);
		
		/// remove a data struct from this module
		bool remove_struct(std::string name);

		/// gets a pointer to a stored data module
		DataStruct* get(std::string name);
		DataStruct* operator[](std::string name);

		/// checks struct exists
		bool exists(std::string name);

		/// converts structs stored to a string format
		std::string structs_to_string();

		friend std::ostream& operator<<(std::ostream& os, DataModule& obj);
		
	private:
		std::string name;
		std::string description;
		
		std::unordered_map< std::string, DataStruct* > dm;
	};

}

#endif