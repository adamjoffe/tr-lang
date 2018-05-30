#ifndef TR_MAP_STRUCT_H
#define TR_MAP_STRUCT_H

#include <string>
#include <unordered_map>

namespace TR {
	
	template<typename T>
	class MapStruct : public DataStruct {
	public:
		MapStruct() : DataStruct(DStruct::MAP, TypeToEnum<T>::value) {
			// allow only TR supported types in Blackboard
			static_assert(is_valid_TR_type<T>::value,"Blackboard template type must be TR supported type");
			static_assert(!std::is_void<T>::value,"Blackboard template type cannot be void");
			t = TypeToEnum<T>::value; // store the enum type
		}
		
		~MapStruct() {}

		// insert methods for all containers
		void insert(T d) {
            throw std::runtime_error("Unable to use method \'insert(data)\' for DataStruct MAP");
		}
		void insert(T d, size_t i) {
            throw std::runtime_error("Unable to use method \'insert(data, index)\' for DataStruct MAP");
		}
		void insert(std::string k, T v) {
			std::lock_guard<std::mutex> lock(mtx);
			if (data.count(k) == 0) {
				data[k] = v;
				changed = true;
			}
		}
		void insert_front(T d) {
            throw std::runtime_error("Unable to use method \'insert_front(data)\' for DataStruct MAP");
		}
		void insert_back(T d) {
            throw std::runtime_error("Unable to use method \'insert_back(data)\' for DataStruct MAP");
		}

		// get methods for all containers
		T get() {
            throw std::runtime_error("Unable to use method \'get()\' for DataStruct MAP");
		}
		T get(size_t i) {
            throw std::runtime_error("Unable to use method \'get(index)\' for DataStruct MAP");
		}
		T get(std::string k) {
			std::lock_guard<std::mutex> lock(mtx);
			if (data.count(k) > 0) {
				return data[k];
			}
			return T();
		}

		// remove methods for all containers
		void remove() {
            throw std::runtime_error("Unable to use method \'remove()\' for DataStruct MAP");
		}
		void remove(size_t i) {
            throw std::runtime_error("Unable to use method \'remove(index)\' for DataStruct MAP");
		}
		void remove(std::string k) {
			std::lock_guard<std::mutex> lock(mtx);
			if (data.count(k) > 0) {
				changed = true;
				data.erase(k);
			}
		}
		void remove_first(T d) {
            throw std::runtime_error("Unable to use method \'remove_first(data)\' for DataStruct MAP");
		}
		void remove_last(T d) {
            throw std::runtime_error("Unable to use method \'remove_last(data)\' for DataStruct MAP");
		}
		void remove_all(T d) {
			std::lock_guard<std::mutex> lock(mtx);
			for (auto it = data.begin(); it != data.end(); ) {
				if (it->second == d) {
					it = data.erase(it);
				} else {
					++it;
				}
			}
			changed = true;
		}

		// size methods for all containers
		size_t size() {
			std::lock_guard<std::mutex> lock(mtx);
			return data.size();
		}

		// clear methods for all containers
		void clear() {
			std::lock_guard<std::mutex> lock(mtx);
			data.clear();
			changed = true;
		}
		
	private:
		// map can only be indexed by stringified value
		std::unordered_map<std::string, T> data;
	};
	
}

#endif