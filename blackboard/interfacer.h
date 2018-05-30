#ifndef TR_INTERFACER_H
#define TR_INTERFACER_H

#include "blackboard.h"
#include "../exe-components/tr_runtime_exception.h"

namespace TR{
	
	/// This class provides an interface between C++ types stored in the blackboard
	/// and the GVar type used by Interpreter
	class Interfacer {
	public:
		// remove default constructor, has to be constructed with reference to a Blackboard
		Interfacer() = delete;

		Interfacer(Blackboard& b);

		// checks if a components exist within blackboard
		bool exists(std::string& mod);
		bool exists(std::string& mod, std::string& dstruct);
		bool exists(std::string& mod, std::string& dstruct, std::string& func, int nargs);

		// gets function return type
		bool void_return(std::string& mod, std::string& dstruct, std::string& func);

		// function caller
		GVar* call(std::string& mod, std::string& dstruct, std::string& func, std::vector<GVar*>& args);

		friend std::ostream& operator<<(std::ostream& os, Interfacer& obj) {
			os << obj.bb;
			return os;
		}

	private:
		/// Private data struct methods

		/// Same methods as data structs, but additionally require the module name
		/// and the struct name
		// insert methodes for all containers
		void insert(std::string& mod, std::string& dstruct, GVar* d);
		// covers both list and map use
		void insert(std::string& mod, std::string& dstruct, GVar* dk, GVar* iv);
		void insert_front(std::string& mod, std::string& dstruct, GVar* d);
		void insert_back(std::string& mod, std::string& dstruct, GVar* d);

		// get methods for all containers
		GVar* get(std::string& mod, std::string& dstruct);
		// covers both list and map use
		GVar* get(std::string& mod, std::string& dstruct, GVar* ik);

		// remove methods for all containers
		void remove(std::string& mod, std::string& dstruct);
		// covers both list and map use
		void remove(std::string& mod, std::string& dstruct, GVar* ik);
		void remove_first(std::string& mod, std::string& dstruct, GVar* d); // remove first instance of an item
		void remove_last(std::string& mod, std::string& dstruct, GVar* d); // remove last instance of an item
		void remove_all(std::string& mod, std::string& dstruct, GVar* d); // remove all instances of an item

		// size methods for all containers
		GVar* size(std::string& mod, std::string& dstruct);

		// clear methods for all containers
		void clear(std::string& mod, std::string& dstruct);

	private:
		Blackboard& bb;
	};
	
}

#endif