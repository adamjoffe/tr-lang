#ifndef TR_DATA_STRUCT_H
#define TR_DATA_STRUCT_H

#include <mutex>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <unordered_map>

#include "../tr_types.h"

namespace TR {
	
	// enum of supported frame types
	enum class DStruct {VAR, STACK, MAP, LIST};

	/// Forward declaration of friend class
	class Interfacer;
	
	/// Provides base frame class containing a data frame of various types
	/// not all provided methods are usable for all frams types
	class DataStruct {
	public:
		// no default constructor, can only be constructed by derived classes
		DataStruct() = delete;
		
		virtual ~DataStruct() {}

		// insert methods for all containers
		template<typename T> void insert(T d);
		template<typename T> void insert(T d, size_t i);
		template<typename T> void insert(std::string k, T v);
		template<typename T> void insert_front(T d);
		template<typename T> void insert_back(T d);

		// get methods for all containers
		template<typename T> T get();
		template<typename T> T get(size_t i);
		template<typename T> T get(std::string k);

		// remove methods for all containers
		template<typename T> void remove();
		template<typename T> void remove(size_t i);
		template<typename T> void remove(std::string k);
		template<typename T> void remove_first(T d); // remove first instance of an item
		template<typename T> void remove_last(T d); // remove last instance of an item
		template<typename T> void remove_all(T d); // remove all instances of an item

		// size methods for all containers
		template<typename T> size_t size();

		// clear methods for all containers
		template<typename T> void clear();

		// gets the name of the frame as a string
		std::string getName() {
			if (dft == DStruct::VAR) {
				return "VAR";
			} else if (dft == DStruct::STACK) {
				return "STACK";
			} else if (dft == DStruct::MAP) {
				return "MAP";
			} else if (dft == DStruct::LIST) {
				return "LIST";
			}
		}

		friend Interfacer;

	protected:
		DataStruct(DStruct df, Type ty) : dft(df), t(ty) {}

		// 1) whenever any data accessing method used, locking must be done
		// for thread safety
		// N.B. size is thread safe, but returned value can change at any time
		// 2) whenever a set method is used, set changed flag to true (high)
		// 3) whenever a read method is used, set changed flag to false (low)
		std::mutex mtx; // lock for this data frame
		bool changed; // change flag
		DStruct dft; // Enum type of data frame
		Type t; // Enum type of TR type
	};

}

// includes templated definitions of all conrete frame types
#include "struct_types.h"

// include template definitions
#include "data_struct.tcc"

#endif