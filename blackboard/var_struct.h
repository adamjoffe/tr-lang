#ifndef TR_VAR_STRUCT_H
#define TR_VAR_STRUCT_H

namespace TR {
	
	template<typename T>
	class VarStruct : public DataStruct {
	public:
		VarStruct() : DataStruct(DStruct::VAR, TypeToEnum<T>::value) {
			// allow only TR supported types in Blackboard
			static_assert(is_valid_TR_type<T>::value,"Blackboard template type must be TR supported type");
			static_assert(!std::is_void<T>::value,"Blackboard template type cannot be void");
			t = TypeToEnum<T>::value; // store the enum type
		}
		
		~VarStruct() {}

		// insert methods for all containers
		void insert(T d) {
			std::lock_guard<std::mutex> lock(mtx);
			if (data != d) {
				data = d;
				changed = true;
			}
		}
		void insert(T d, size_t i) {
			insert(d);
		}
		void insert(std::string k, T v) {
			insert(v);
		}
		void insert_front(T d) {
			insert(d);
		}
		void insert_back(T d) {
			insert(d);
		}

		// get methods for all containers
		T get() {
			std::lock_guard<std::mutex> lock(mtx);
			return data; // data is copied on return, to keep internal state
		}
		T get(size_t i) {
			return get();
		}
		T get(std::string k) {
			return get();
		}

		// remove methods for all containers
		void remove() {
			std::lock_guard<std::mutex> lock(mtx);
			if (data != T()) {
				data = T(); // default back to value default constructor
				changed = true;
			}
		}
		void remove(size_t i) {
			remove();
		}
		void remove(std::string k) {
			remove();
		}
		void remove_first(T d) {
			remove();
		}
		void remove_last(T d) {
			remove();
		}
		void remove_all(T d) {
			remove();
		}

		// size methods for all containers
		size_t size() {
			return 1;
		}

		// clear methods for all containers
		void clear() {
			remove();
		}
		
	private:
		T data;
	};
	
}

#endif