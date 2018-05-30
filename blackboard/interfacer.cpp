#include "interfacer.h"

namespace TR {

	Interfacer::Interfacer(Blackboard& b) : bb(b) {}

	bool Interfacer::exists(std::string& mod) {
		return bb.exists(mod);
	}

	bool Interfacer::exists(std::string& mod, std::string& dstruct) {
		return bb[mod].exists(dstruct);
	}

	bool Interfacer::exists(std::string& mod, std::string& dstruct, std::string& func, int nargs) {
		// shared functions that work for all
		if (func == "size" && nargs == 0) {
			return true;
		} else if (func == "clear" && nargs == 0) {
			return true;
		} else if (func == "remove_all" && nargs == 1) {
			return true;


		// specific functions that work for some
		} else if (bb[mod][dstruct]->dft == DStruct::VAR || bb[mod][dstruct]->dft == DStruct::STACK) {
			if (func == "insert" && (nargs == 1 || nargs == 2)) {
				return true;
			} else if ((func == "insert_front" || func == "insert_back") && nargs == 1) {
				return true;
			} else if (func == "get" && (nargs == 0 || nargs == 1)) {
				return true;
			} else if (func == "remove" && (nargs == 0 || nargs == 1)) {
				return true;
			} else if ((func == "remove_first" || func == "remove_last") && nargs == 1) {
				return true;
			}
		} else if (bb[mod][dstruct]->dft == DStruct::MAP) {
			if (func == "insert" && nargs == 2) {
				return true;
			} else if (func == "get" && nargs == 1) {
				return true;
			} else if (func == "remove" && nargs == 1) {
				return true;
			}
		} else if (bb[mod][dstruct]->dft == DStruct::LIST) {
			if (func == "insert" && (nargs == 1 || nargs == 2)) {
				return true;
			} else if ((func == "insert_front" || func == "insert_back") && nargs == 1) {
				return true;
			} else if (func == "get" && nargs == 1) {
				return true;
			} else if (func == "remove" && nargs == 1) {
				return true;
			} else if ((func == "remove_first" || func == "remove_last") && nargs == 1) {
				return true;
			}
		}
		return false;
	}

	bool Interfacer::void_return(std::string& mod, std::string& dstruct, std::string& func) {
		if (func == "get" || func == "size") {
			return false;
		}
		return true;
	}

	GVar* Interfacer::call(std::string& mod, std::string& dstruct, std::string& func, std::vector<GVar*>& args) {
		if (func == "insert") {
			if (args.size() == 1) {
				insert(mod, dstruct, args[0]);
				return new GVar(Type::VOID_T);
			} else {
				insert(mod, dstruct, args[0], args[1]);
				return new GVar(Type::VOID_T);
			}
		} else if (func == "insert_front") {
			insert_front(mod, dstruct, args[0]);
			return new GVar(Type::VOID_T);
		} else if (func == "insert_back") {
			insert_back(mod, dstruct, args[0]);
			return new GVar(Type::VOID_T);
		} else if (func == "get") {
			if (args.size() == 0) {
				return get(mod, dstruct);
			} else {
				return get(mod, dstruct, args[0]);
			}
			// after getting from TR-Lang, set to unchanged
			std::lock_guard<std::mutex> lock(bb[mod][dstruct]->mtx);
			bb[mod][dstruct]->changed = false;
		} else if (func == "remove") {
			if (args.size() == 0) {
				remove(mod, dstruct);
				return new GVar(Type::VOID_T);
			} else {
				remove(mod, dstruct, args[0]);
				return new GVar(Type::VOID_T);
			}
		} else if (func == "remove_first") {
			remove_first(mod, dstruct, args[0]);
			return new GVar(Type::VOID_T);
		} else if (func == "remove_last") {
			remove_last(mod, dstruct, args[0]);
			return new GVar(Type::VOID_T);
		} else if (func == "size") {
			return size(mod, dstruct);
		} else if (func == "clear") {
			clear(mod, func);
			return new GVar(Type::VOID_T);
		}
	}

	// insert methodes for all containers
	void Interfacer::insert(std::string& mod, std::string& dstruct, GVar* d) {
		if (bb[mod][dstruct]->t == Type::INT_T) {
			bb[mod][dstruct]->insert<int>(get_gvar_as<int>(d));
		} else if (bb[mod][dstruct]->t == Type::FLOAT_T) {
			bb[mod][dstruct]->insert<float>(get_gvar_as<float>(d));
		} else if (bb[mod][dstruct]->t == Type::DOUBLE_T) {
			bb[mod][dstruct]->insert<double>(get_gvar_as<double>(d));
		} else if (bb[mod][dstruct]->t == Type::STRING_T) {
			bb[mod][dstruct]->insert<std::string>(get_gvar_as<std::string>(d));
		} else if (bb[mod][dstruct]->t == Type::BOOL_T) {
			bb[mod][dstruct]->insert<bool>(get_gvar_as<bool>(d));
		} else if (bb[mod][dstruct]->t == Type::VECTOR_T) {
			bb[mod][dstruct]->insert<Vector>(get_gvar_as<Vector>(d));
		} else {
			// shouldn't occur
			throw std::runtime_error("Unknown/Invalid TR Type");
		}
	}
	void Interfacer::insert(std::string& mod, std::string& dstruct, GVar* dk, GVar* iv) {
		// check for MAP and LIST special cases
		if (bb[mod][dstruct]->dft == DStruct::MAP) {
			if (bb[mod][dstruct]->t == Type::INT_T) {
				bb[mod][dstruct]->insert<int>(get_gvar_as<std::string>(dk), get_gvar_as<int>(iv));
			} else if (bb[mod][dstruct]->t == Type::FLOAT_T) {
				bb[mod][dstruct]->insert<float>(get_gvar_as<std::string>(dk), get_gvar_as<float>(iv));
			} else if (bb[mod][dstruct]->t == Type::DOUBLE_T) {
				bb[mod][dstruct]->insert<double>(get_gvar_as<std::string>(dk), get_gvar_as<double>(iv));
			} else if (bb[mod][dstruct]->t == Type::STRING_T) {
				bb[mod][dstruct]->insert<std::string>(get_gvar_as<std::string>(dk), get_gvar_as<std::string>(iv));
			} else if (bb[mod][dstruct]->t == Type::BOOL_T) {
				bb[mod][dstruct]->insert<bool>(get_gvar_as<std::string>(dk), get_gvar_as<bool>(iv));
			} else if (bb[mod][dstruct]->t == Type::VECTOR_T) {
				bb[mod][dstruct]->insert<Vector>(get_gvar_as<std::string>(dk), get_gvar_as<Vector>(iv));
			} else {
				// shouldn't occur
				throw std::runtime_error("Unknown/Invalid TR Type");
			}
		} else if (bb[mod][dstruct]->dft == DStruct::LIST) {
			if (bb[mod][dstruct]->t == Type::INT_T) {
				bb[mod][dstruct]->insert<int>(get_gvar_as<int>(dk), get_gvar_as<int>(iv));
			} else if (bb[mod][dstruct]->t == Type::FLOAT_T) {
				bb[mod][dstruct]->insert<float>(get_gvar_as<float>(dk), get_gvar_as<int>(iv));
			} else if (bb[mod][dstruct]->t == Type::DOUBLE_T) {
				bb[mod][dstruct]->insert<double>(get_gvar_as<double>(dk), get_gvar_as<int>(iv));
			} else if (bb[mod][dstruct]->t == Type::STRING_T) {
				bb[mod][dstruct]->insert<std::string>(get_gvar_as<std::string>(dk), get_gvar_as<int>(iv));
			} else if (bb[mod][dstruct]->t == Type::BOOL_T) {
				bb[mod][dstruct]->insert<bool>(get_gvar_as<bool>(dk), get_gvar_as<int>(iv));
			} else if (bb[mod][dstruct]->t == Type::VECTOR_T) {
				bb[mod][dstruct]->insert<Vector>(get_gvar_as<Vector>(dk), get_gvar_as<int>(iv));
			} else {
				// shouldn't occur
				throw std::runtime_error("Unknown/Invalid TR Type");
			}
		} else {
			// fail here, incorrect insert function for dstruct
			throw TR_Runtime_Exception("Unable to use method \'insert(data, index)\' or \'insert(key, data)\' for DataStruct VAR/STACK");
		}
	}
	void Interfacer::insert_front(std::string& mod, std::string& dstruct, GVar* d) {
		if (bb[mod][dstruct]->t == Type::INT_T) {
	        bb[mod][dstruct]->insert_front<int>(get_gvar_as<int>(d));
		} else if (bb[mod][dstruct]->t == Type::FLOAT_T) {
	        bb[mod][dstruct]->insert_front<float>(get_gvar_as<float>(d));
		} else if (bb[mod][dstruct]->t == Type::DOUBLE_T) {
	        bb[mod][dstruct]->insert_front<double>(get_gvar_as<double>(d));
		} else if (bb[mod][dstruct]->t == Type::STRING_T) {
	        bb[mod][dstruct]->insert_front<std::string>(get_gvar_as<std::string>(d));
		} else if (bb[mod][dstruct]->t == Type::BOOL_T) {
	        bb[mod][dstruct]->insert_front<bool>(get_gvar_as<bool>(d));
		} else if (bb[mod][dstruct]->t == Type::VECTOR_T) {
	        bb[mod][dstruct]->insert_front<Vector>(get_gvar_as<Vector>(d));
		} else {
			// shouldn't occur
			throw std::runtime_error("Unknown/Invalid TR Type");
		}
	}
	void Interfacer::insert_back(std::string& mod, std::string& dstruct, GVar* d) {
		if (bb[mod][dstruct]->t == Type::INT_T) {
	        bb[mod][dstruct]->insert_back<int>(get_gvar_as<int>(d));
		} else if (bb[mod][dstruct]->t == Type::FLOAT_T) {
	        bb[mod][dstruct]->insert_back<float>(get_gvar_as<float>(d));
		} else if (bb[mod][dstruct]->t == Type::DOUBLE_T) {
	        bb[mod][dstruct]->insert_back<double>(get_gvar_as<double>(d));
		} else if (bb[mod][dstruct]->t == Type::STRING_T) {
	        bb[mod][dstruct]->insert_back<std::string>(get_gvar_as<std::string>(d));
		} else if (bb[mod][dstruct]->t == Type::BOOL_T) {
	        bb[mod][dstruct]->insert_back<bool>(get_gvar_as<bool>(d));
		} else if (bb[mod][dstruct]->t == Type::VECTOR_T) {
	        bb[mod][dstruct]->insert_back<Vector>(get_gvar_as<Vector>(d));
		} else {
			// shouldn't occur
			throw std::runtime_error("Unknown/Invalid TR Type");
		}
	}

	// get methods for all containers
	GVar* Interfacer::get(std::string& mod, std::string& dstruct) {
		if (bb[mod][dstruct]->t == Type::INT_T) {
			return new IntVar(bb[mod][dstruct]->get<int>());
		} else if (bb[mod][dstruct]->t == Type::FLOAT_T) {
			return new DoubleVar(bb[mod][dstruct]->get<float>());
		} else if (bb[mod][dstruct]->t == Type::DOUBLE_T) {
			return new DoubleVar(bb[mod][dstruct]->get<double>());
		} else if (bb[mod][dstruct]->t == Type::STRING_T) {
			return new StringVar(bb[mod][dstruct]->get<std::string>());
		} else if (bb[mod][dstruct]->t == Type::BOOL_T) {
			return new BoolVar(bb[mod][dstruct]->get<bool>());
		} else if (bb[mod][dstruct]->t == Type::VECTOR_T) {
			return new VectorVar(bb[mod][dstruct]->get<Vector>());
		} else {
			// shouldn't occur
			throw std::runtime_error("Unknown/Invalid TR Type");
		}
	}
	GVar* Interfacer::get(std::string& mod, std::string& dstruct, GVar* ik) {
		// check for MAP and LIST special cases
		if (bb[mod][dstruct]->dft == DStruct::MAP) {
			if (bb[mod][dstruct]->t == Type::INT_T) {
				return new IntVar(bb[mod][dstruct]->get<int>(get_gvar_as<std::string>(ik)));
			} else if (bb[mod][dstruct]->t == Type::FLOAT_T) {
				return new DoubleVar(bb[mod][dstruct]->get<float>(get_gvar_as<std::string>(ik)));
			} else if (bb[mod][dstruct]->t == Type::DOUBLE_T) {
				return new DoubleVar(bb[mod][dstruct]->get<double>(get_gvar_as<std::string>(ik)));
			} else if (bb[mod][dstruct]->t == Type::STRING_T) {
				return new StringVar(bb[mod][dstruct]->get<std::string>(get_gvar_as<std::string>(ik)));
			} else if (bb[mod][dstruct]->t == Type::BOOL_T) {
				return new BoolVar(bb[mod][dstruct]->get<bool>(get_gvar_as<std::string>(ik)));
			} else if (bb[mod][dstruct]->t == Type::VECTOR_T) {
				return new VectorVar(bb[mod][dstruct]->get<Vector>(get_gvar_as<std::string>(ik)));
			} else {
				// shouldn't occur
				throw std::runtime_error("Unknown/Invalid TR Type");
			}
		} else if (bb[mod][dstruct]->dft == DStruct::LIST) {
			if (bb[mod][dstruct]->t == Type::INT_T) {
				return new IntVar(bb[mod][dstruct]->get<int>(get_gvar_as<int>(ik)));
			} else if (bb[mod][dstruct]->t == Type::FLOAT_T) {
				return new DoubleVar(bb[mod][dstruct]->get<float>(get_gvar_as<int>(ik)));
			} else if (bb[mod][dstruct]->t == Type::DOUBLE_T) {
				return new DoubleVar(bb[mod][dstruct]->get<double>(get_gvar_as<int>(ik)));
			} else if (bb[mod][dstruct]->t == Type::STRING_T) {
				return new StringVar(bb[mod][dstruct]->get<std::string>(get_gvar_as<int>(ik)));
			} else if (bb[mod][dstruct]->t == Type::BOOL_T) {
				return new BoolVar(bb[mod][dstruct]->get<bool>(get_gvar_as<int>(ik)));
			} else if (bb[mod][dstruct]->t == Type::VECTOR_T) {
				return new VectorVar(bb[mod][dstruct]->get<Vector>(get_gvar_as<int>(ik)));
			} else {
				// shouldn't occur
				throw std::runtime_error("Unknown/Invalid TR Type");
			}
		} else {
			// fail here, incorrect insert function for dstruct
			throw TR_Runtime_Exception("Unable to use method \'get(index)\' or \'get(key)\' for DataStruct VAR/STACK");
		}
	}

	// remove methods for all containers
	void Interfacer::remove(std::string& mod, std::string& dstruct) {
		if (bb[mod][dstruct]->t == Type::INT_T) {
			bb[mod][dstruct]->remove<int>();
		} else if (bb[mod][dstruct]->t == Type::FLOAT_T) {
			bb[mod][dstruct]->remove<float>();
		} else if (bb[mod][dstruct]->t == Type::DOUBLE_T) {
			bb[mod][dstruct]->remove<double>();
		} else if (bb[mod][dstruct]->t == Type::STRING_T) {
			bb[mod][dstruct]->remove<std::string>();
		} else if (bb[mod][dstruct]->t == Type::BOOL_T) {
			bb[mod][dstruct]->remove<bool>();
		} else if (bb[mod][dstruct]->t == Type::VECTOR_T) {
			bb[mod][dstruct]->remove<Vector>();
		} else {
			// shouldn't occur
			throw std::runtime_error("Unknown/Invalid TR Type");
		}
	}
	void Interfacer::remove(std::string& mod, std::string& dstruct, GVar* ik) {
		// check for MAP and LIST special cases
		if (bb[mod][dstruct]->dft == DStruct::MAP) {
			if (bb[mod][dstruct]->t == Type::INT_T) {
				bb[mod][dstruct]->remove<int>(get_gvar_as<std::string>(ik));
			} else if (bb[mod][dstruct]->t == Type::FLOAT_T) {
				bb[mod][dstruct]->remove<float>(get_gvar_as<std::string>(ik));
			} else if (bb[mod][dstruct]->t == Type::DOUBLE_T) {
				bb[mod][dstruct]->remove<double>(get_gvar_as<std::string>(ik));
			} else if (bb[mod][dstruct]->t == Type::STRING_T) {
				bb[mod][dstruct]->remove<std::string>(get_gvar_as<std::string>(ik));
			} else if (bb[mod][dstruct]->t == Type::BOOL_T) {
				bb[mod][dstruct]->remove<bool>(get_gvar_as<std::string>(ik));
			} else if (bb[mod][dstruct]->t == Type::VECTOR_T) {
				bb[mod][dstruct]->remove<Vector>(get_gvar_as<std::string>(ik));
			} else {
				// shouldn't occur
				throw std::runtime_error("Unknown/Invalid TR Type");
			}
		} else if (bb[mod][dstruct]->dft == DStruct::LIST) {
			if (bb[mod][dstruct]->t == Type::INT_T) {
				bb[mod][dstruct]->remove<int>(get_gvar_as<int>(ik));
			} else if (bb[mod][dstruct]->t == Type::FLOAT_T) {
				bb[mod][dstruct]->remove<float>(get_gvar_as<int>(ik));
			} else if (bb[mod][dstruct]->t == Type::DOUBLE_T) {
				bb[mod][dstruct]->remove<double>(get_gvar_as<int>(ik));
			} else if (bb[mod][dstruct]->t == Type::STRING_T) {
				bb[mod][dstruct]->remove<std::string>(get_gvar_as<int>(ik));
			} else if (bb[mod][dstruct]->t == Type::BOOL_T) {
				bb[mod][dstruct]->remove<bool>(get_gvar_as<int>(ik));
			} else if (bb[mod][dstruct]->t == Type::VECTOR_T) {
				bb[mod][dstruct]->remove<Vector>(get_gvar_as<int>(ik));
			} else {
				// shouldn't occur
				throw std::runtime_error("Unknown/Invalid TR Type");
			}
		} else {
			// fail here, incorrect insert function for dstruct
			throw TR_Runtime_Exception("Unable to use method \'get(index)\' or \'get(key)\' for DataStruct VAR/STACK");
		}
	}
	void Interfacer::remove_first(std::string& mod, std::string& dstruct, GVar* d) {
		if (bb[mod][dstruct]->t == Type::INT_T) {
	        bb[mod][dstruct]->remove_first<int>(get_gvar_as<int>(d));
		} else if (bb[mod][dstruct]->t == Type::FLOAT_T) {
	        bb[mod][dstruct]->remove_first<float>(get_gvar_as<float>(d));
		} else if (bb[mod][dstruct]->t == Type::DOUBLE_T) {
	        bb[mod][dstruct]->remove_first<double>(get_gvar_as<double>(d));
		} else if (bb[mod][dstruct]->t == Type::STRING_T) {
	        bb[mod][dstruct]->remove_first<std::string>(get_gvar_as<std::string>(d));
		} else if (bb[mod][dstruct]->t == Type::BOOL_T) {
	        bb[mod][dstruct]->remove_first<bool>(get_gvar_as<bool>(d));
		} else if (bb[mod][dstruct]->t == Type::VECTOR_T) {
	        bb[mod][dstruct]->remove_first<Vector>(get_gvar_as<Vector>(d));
		} else {
			// shouldn't occur
			throw std::runtime_error("Unknown/Invalid TR Type");
		}
	}
	void Interfacer::remove_last(std::string& mod, std::string& dstruct, GVar* d) {
		if (bb[mod][dstruct]->t == Type::INT_T) {
	        bb[mod][dstruct]->remove_last<int>(get_gvar_as<int>(d));
		} else if (bb[mod][dstruct]->t == Type::FLOAT_T) {
	        bb[mod][dstruct]->remove_last<float>(get_gvar_as<float>(d));
		} else if (bb[mod][dstruct]->t == Type::DOUBLE_T) {
	        bb[mod][dstruct]->remove_last<double>(get_gvar_as<double>(d));
		} else if (bb[mod][dstruct]->t == Type::STRING_T) {
	        bb[mod][dstruct]->remove_last<std::string>(get_gvar_as<std::string>(d));
		} else if (bb[mod][dstruct]->t == Type::BOOL_T) {
	        bb[mod][dstruct]->remove_last<bool>(get_gvar_as<bool>(d));
		} else if (bb[mod][dstruct]->t == Type::VECTOR_T) {
	        bb[mod][dstruct]->remove_last<Vector>(get_gvar_as<Vector>(d));
		} else {
			// shouldn't occur
			throw std::runtime_error("Unknown/Invalid TR Type");
		}
	}
	void Interfacer::remove_all(std::string& mod, std::string& dstruct, GVar* d) {
		if (bb[mod][dstruct]->t == Type::INT_T) {
	        bb[mod][dstruct]->remove_all<int>(get_gvar_as<int>(d));
		} else if (bb[mod][dstruct]->t == Type::FLOAT_T) {
	        bb[mod][dstruct]->remove_all<float>(get_gvar_as<float>(d));
		} else if (bb[mod][dstruct]->t == Type::DOUBLE_T) {
	        bb[mod][dstruct]->remove_all<double>(get_gvar_as<double>(d));
		} else if (bb[mod][dstruct]->t == Type::STRING_T) {
	        bb[mod][dstruct]->remove_all<std::string>(get_gvar_as<std::string>(d));
		} else if (bb[mod][dstruct]->t == Type::BOOL_T) {
	        bb[mod][dstruct]->remove_all<bool>(get_gvar_as<bool>(d));
		} else if (bb[mod][dstruct]->t == Type::VECTOR_T) {
	        bb[mod][dstruct]->remove_all<Vector>(get_gvar_as<Vector>(d));
		} else {
			// shouldn't occur
			throw std::runtime_error("Unknown/Invalid TR Type");
		}
	}

	// size methods for all containers
	GVar* Interfacer::size(std::string& mod, std::string& dstruct) {
		if (bb[mod][dstruct]->t == Type::INT_T) {
			return new IntVar(bb[mod][dstruct]->size<int>());
		} else if (bb[mod][dstruct]->t == Type::FLOAT_T) {
			return new IntVar(bb[mod][dstruct]->size<float>());
		} else if (bb[mod][dstruct]->t == Type::DOUBLE_T) {
			return new IntVar(bb[mod][dstruct]->size<double>());
		} else if (bb[mod][dstruct]->t == Type::STRING_T) {
			return new IntVar(bb[mod][dstruct]->size<std::string>());
		} else if (bb[mod][dstruct]->t == Type::BOOL_T) {
			return new IntVar(bb[mod][dstruct]->size<bool>());
		} else if (bb[mod][dstruct]->t == Type::VECTOR_T) {
			return new IntVar(bb[mod][dstruct]->size<Vector>());
		} else {
			// shouldn't occur
			throw std::runtime_error("Unknown/Invalid TR Type");
		}
	}

	// clear methods for all containers
	void Interfacer::clear(std::string& mod, std::string& dstruct) {
		if (bb[mod][dstruct]->t == Type::INT_T) {
			bb[mod][dstruct]->clear<int>();
		} else if (bb[mod][dstruct]->t == Type::FLOAT_T) {
			bb[mod][dstruct]->clear<float>();
		} else if (bb[mod][dstruct]->t == Type::DOUBLE_T) {
			bb[mod][dstruct]->clear<double>();
		} else if (bb[mod][dstruct]->t == Type::STRING_T) {
			bb[mod][dstruct]->clear<std::string>();
		} else if (bb[mod][dstruct]->t == Type::BOOL_T) {
			bb[mod][dstruct]->clear<bool>();
		} else if (bb[mod][dstruct]->t == Type::VECTOR_T) {
			bb[mod][dstruct]->clear<Vector>();
		} else {
			// shouldn't occur
			throw std::runtime_error("Unknown/Invalid TR Type");
		}
	}
}
