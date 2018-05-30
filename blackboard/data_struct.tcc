namespace TR {

	// insert methods for all containers
	template<typename T> void DataStruct::insert(T d) {
		if (dft == DStruct::VAR) {
			return dynamic_cast<VarStruct<T>&>(*this).insert(d);
		} else if (dft == DStruct::STACK) {
			return dynamic_cast<StackStruct<T>&>(*this).insert(d);
		} else if (dft == DStruct::MAP) {
			return dynamic_cast<MapStruct<T>&>(*this).insert(d);
		} else if (dft == DStruct::LIST) {
			return dynamic_cast<ListStruct<T>&>(*this).insert(d);
		} else {
			throw std::runtime_error("Incorrect datastruct type");
		}
	}
	template<typename T> void DataStruct::insert(T d, size_t i) {
		if (dft == DStruct::VAR) {
			return dynamic_cast<VarStruct<T>&>(*this).insert(d,i);
		} else if (dft == DStruct::STACK) {
			return dynamic_cast<StackStruct<T>&>(*this).insert(d,i);
		} else if (dft == DStruct::MAP) {
			return dynamic_cast<MapStruct<T>&>(*this).insert(d,i);
		} else if (dft == DStruct::LIST) {
			return dynamic_cast<ListStruct<T>&>(*this).insert(d,i);
		} else {
			throw std::runtime_error("Incorrect datastruct type");
		}
	}
	template<typename T> void DataStruct::insert(std::string k, T v) {
		if (dft == DStruct::VAR) {
			return dynamic_cast<VarStruct<T>&>(*this).insert(k,v);
		} else if (dft == DStruct::STACK) {
			return dynamic_cast<StackStruct<T>&>(*this).insert(k,v);
		} else if (dft == DStruct::MAP) {
			return dynamic_cast<MapStruct<T>&>(*this).insert(k,v);
		} else if (dft == DStruct::LIST) {
			return dynamic_cast<ListStruct<T>&>(*this).insert(k,v);
		} else {
			throw std::runtime_error("Incorrect datastruct type");
		}
	}
	template<typename T> void DataStruct::insert_front(T d) {
		if (dft == DStruct::VAR) {
			return dynamic_cast<VarStruct<T>&>(*this).insert_front(d);
		} else if (dft == DStruct::STACK) {
			return dynamic_cast<StackStruct<T>&>(*this).insert_front(d);
		} else if (dft == DStruct::MAP) {
			return dynamic_cast<MapStruct<T>&>(*this).insert_front(d);
		} else if (dft == DStruct::LIST) {
			return dynamic_cast<ListStruct<T>&>(*this).insert_front(d);
		} else {
			throw std::runtime_error("Incorrect datastruct type");
		}
	}
	template<typename T> void DataStruct::insert_back(T d) {
		if (dft == DStruct::VAR) {
			return dynamic_cast<VarStruct<T>&>(*this).insert_back(d);
		} else if (dft == DStruct::STACK) {
			return dynamic_cast<StackStruct<T>&>(*this).insert_back(d);
		} else if (dft == DStruct::MAP) {
			return dynamic_cast<MapStruct<T>&>(*this).insert_back(d);
		} else if (dft == DStruct::LIST) {
			return dynamic_cast<ListStruct<T>&>(*this).insert_back(d);
		} else {
			throw std::runtime_error("Incorrect datastruct type");
		}
	}

	// get methods for all containers
	template<typename T> T DataStruct::get() {
		if (dft == DStruct::VAR) {
			return dynamic_cast<VarStruct<T>&>(*this).get();
		} else if (dft == DStruct::STACK) {
			return dynamic_cast<StackStruct<T>&>(*this).get();
		} else if (dft == DStruct::MAP) {
			return dynamic_cast<MapStruct<T>&>(*this).get();
		} else if (dft == DStruct::LIST) {
			return dynamic_cast<ListStruct<T>&>(*this).get();
		} else {
			throw std::runtime_error("Incorrect datastruct type");
		}
	}
	template<typename T> T DataStruct::get(size_t i) {
		if (dft == DStruct::VAR) {
			return dynamic_cast<VarStruct<T>&>(*this).get(i);
		} else if (dft == DStruct::STACK) {
			return dynamic_cast<StackStruct<T>&>(*this).get(i);
		} else if (dft == DStruct::MAP) {
			return dynamic_cast<MapStruct<T>&>(*this).get(i);
		} else if (dft == DStruct::LIST) {
			return dynamic_cast<ListStruct<T>&>(*this).get(i);
		} else {
			throw std::runtime_error("Incorrect datastruct type");
		}
	}
	template<typename T> T DataStruct::get(std::string k) {
		if (dft == DStruct::VAR) {
			return dynamic_cast<VarStruct<T>&>(*this).get(k);
		} else if (dft == DStruct::STACK) {
			return dynamic_cast<StackStruct<T>&>(*this).get(k);
		} else if (dft == DStruct::MAP) {
			return dynamic_cast<MapStruct<T>&>(*this).get(k);
		} else if (dft == DStruct::LIST) {
			return dynamic_cast<ListStruct<T>&>(*this).get(k);
		} else {
			throw std::runtime_error("Incorrect datastruct type");
		}
	}

	// remove methods for all containers
	template<typename T> void DataStruct::remove() {
		if (dft == DStruct::VAR) {
			return dynamic_cast<VarStruct<T>&>(*this).remove();
		} else if (dft == DStruct::STACK) {
			return dynamic_cast<StackStruct<T>&>(*this).remove();
		} else if (dft == DStruct::MAP) {
			return dynamic_cast<MapStruct<T>&>(*this).remove();
		} else if (dft == DStruct::LIST) {
			return dynamic_cast<ListStruct<T>&>(*this).remove();
		} else {
			throw std::runtime_error("Incorrect datastruct type");
		}
	}
	template<typename T> void DataStruct::remove(size_t i) {
		if (dft == DStruct::VAR) {
			return dynamic_cast<VarStruct<T>&>(*this).remove(i);
		} else if (dft == DStruct::STACK) {
			return dynamic_cast<StackStruct<T>&>(*this).remove(i);
		} else if (dft == DStruct::MAP) {
			return dynamic_cast<MapStruct<T>&>(*this).remove(i);
		} else if (dft == DStruct::LIST) {
			return dynamic_cast<ListStruct<T>&>(*this).remove(i);
		} else {
			throw std::runtime_error("Incorrect datastruct type");
		}
	}
	template<typename T> void DataStruct::remove(std::string k) {
		if (dft == DStruct::VAR) {
			return dynamic_cast<VarStruct<T>&>(*this).remove(k);
		} else if (dft == DStruct::STACK) {
			return dynamic_cast<StackStruct<T>&>(*this).remove(k);
		} else if (dft == DStruct::MAP) {
			return dynamic_cast<MapStruct<T>&>(*this).remove(k);
		} else if (dft == DStruct::LIST) {
			return dynamic_cast<ListStruct<T>&>(*this).remove(k);
		} else {
			throw std::runtime_error("Incorrect datastruct type");
		}
	}
	template<typename T> void DataStruct::remove_first(T d) {
		if (dft == DStruct::VAR) {
			return dynamic_cast<VarStruct<T>&>(*this).remove_first(d);
		} else if (dft == DStruct::STACK) {
			return dynamic_cast<StackStruct<T>&>(*this).remove_first(d);
		} else if (dft == DStruct::MAP) {
			return dynamic_cast<MapStruct<T>&>(*this).remove_first(d);
		} else if (dft == DStruct::LIST) {
			return dynamic_cast<ListStruct<T>&>(*this).remove_first(d);
		} else {
			throw std::runtime_error("Incorrect datastruct type");
		}
	}

	template<typename T> void DataStruct::remove_last(T d) {
		if (dft == DStruct::VAR) {
			dynamic_cast<VarStruct<T>&>(*this).remove_last(d);
		} else if (dft == DStruct::STACK) {
			return dynamic_cast<StackStruct<T>&>(*this).remove_last(d);
		} else if (dft == DStruct::MAP) {
			return dynamic_cast<MapStruct<T>&>(*this).remove_last(d);
		} else if (dft == DStruct::LIST) {
			return dynamic_cast<ListStruct<T>&>(*this).remove_last(d);
		} else {
			throw std::runtime_error("Incorrect datastruct type");
		}
	}
	template<typename T> void DataStruct::remove_all(T d) {
		if (dft == DStruct::VAR) {
			return dynamic_cast<VarStruct<T>&>(*this).remove_all(d);
		} else if (dft == DStruct::STACK) {
			return dynamic_cast<StackStruct<T>&>(*this).remove_all(d);
		} else if (dft == DStruct::MAP) {
			return dynamic_cast<MapStruct<T>&>(*this).remove_all(d);
		} else if (dft == DStruct::LIST) {
			return dynamic_cast<ListStruct<T>&>(*this).remove_all(d);
		} else {
			throw std::runtime_error("Incorrect datastruct type");
		}
	}

	// size methods for all containers
	template<typename T> size_t DataStruct::size() {
		if (dft == DStruct::VAR) {
			return dynamic_cast<VarStruct<T>&>(*this).size();
		} else if (dft == DStruct::STACK) {
			return dynamic_cast<StackStruct<T>&>(*this).size();
		} else if (dft == DStruct::MAP) {
			return dynamic_cast<MapStruct<T>&>(*this).size();
		} else if (dft == DStruct::LIST) {
			return dynamic_cast<ListStruct<T>&>(*this).size();
		} else {
			throw std::runtime_error("Incorrect datastruct type");
		}
	}

	// clear methods for all containers
	template<typename T> void DataStruct::clear() {
		if (dft == DStruct::VAR) {
			return dynamic_cast<VarStruct<T>&>(*this).clear();
		} else if (dft == DStruct::STACK) {
			return dynamic_cast<StackStruct<T>&>(*this).clear();
		} else if (dft == DStruct::MAP) {
			return dynamic_cast<MapStruct<T>&>(*this).clear();
		} else if (dft == DStruct::LIST) {
			return dynamic_cast<ListStruct<T>&>(*this).clear();
		} else {
			throw std::runtime_error("Incorrect datastruct type");
		}
	}

}