#ifndef TR_BLACKBOARD_H
#define TR_BLACKBOARD_H

#include <string>
#include <unordered_map>

#include "data_module.h"

// TR-module name
#define TRMODULE "trmodule"

namespace TR {
	
	/// This class provides modular thread safe shared memory accessible
	/// from TR-Lang and C++
	/// this class stores data in C++ types
	class Blackboard {
	public: 
		// include a TR data module by default ("trmodule")
		Blackboard();
		
		~Blackboard();
		
		/// adds modules into blackboard
		bool add_module(std::string name);
		bool add_module(std::string name, std::string description);
		bool add_module(std::string name, DataModule& module);
		
		/// remove module from blackboard
		bool remove_module(std::string name);

		/// get reference to module object
		DataModule& get(std::string name);
		DataModule& operator[](std::string name);

		/// check module exists
		bool exists(std::string name);

		friend std::ostream& operator<<(std::ostream& os, Blackboard& obj);

	private:
		std::unordered_map< std::string, DataModule > bb;
	};
	
}

#endif