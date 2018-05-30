#ifndef TR_LIST_STRUCT_H
#define TR_LIST_STRUCT_H

#include <vector>

namespace TR {
	
	template<typename T>
	class ListStruct : public DataStruct {
	public:
		ListStruct() : DataStruct(DStruct::LIST, TypeToEnum<T>::value) {
			// allow only TR supported types in Blackboard
			static_assert(is_valid_TR_type<T>::value,"Blackboard template type must be TR supported type");
			static_assert(!std::is_void<T>::value,"Blackboard template type cannot be void");
		}
		
		~ListStruct() {}
		
		// insert methods for all containers
		void insert(T d) {
            insert_back(d);
		}
		void insert(T d, size_t i) {
			std::lock_guard<std::mutex> lock(mtx);
			data.insert(data.begin()+i, d);
			changed = false;
		}
		void insert(std::string k, T v) {
            throw std::runtime_error("Unable to use method \'insert(key, data)\' for DataStruct LIST");
		}
		void insert_front(T d) {
			std::lock_guard<std::mutex> lock(mtx);
			data.insert(data.begin(), d);
			changed = false;
		}
		void insert_back(T d) {
			std::lock_guard<std::mutex> lock(mtx);
			data.push_back(d);
			changed = false;
		}

		// get methods for all containers
		T get() {
            throw std::runtime_error("Unable to use method \'get()\' for DataStruct LIST");
		}
		T get(size_t i) {
			std::lock_guard<std::mutex> lock(mtx);
			changed = true;
			return data[i];
		}
		T get(std::string k) {
            throw std::runtime_error("Unable to use method \'get(key)\' for DataStruct LIST");
		}

		// remove methods for all containers
		void remove() {
            throw std::runtime_error("Unable to use method \'remove()\' for DataStruct LIST");
		}
		void remove(size_t i) {
			data.erase(data.begin()+i);
		}
		void remove(std::string k) {
            throw std::runtime_error("Unable to use method \'remove(key)\' for DataStruct LIST");
		}
		void remove_first(T d) {
			std::lock_guard<std::mutex> lock(mtx);
			data.erase(data.begin());
			changed = true;
		}
		void remove_last(T d) {
			std::lock_guard<std::mutex> lock(mtx);
			data.pop_back();
			changed = true;
		}
		void remove_all(T d) {
			std::lock_guard<std::mutex> lock(mtx);
			for (auto it = data.begin(); it != data.end(); ) {
				if (*it == d) {
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
		std::vector<T> data;
	};
	
}

#endif