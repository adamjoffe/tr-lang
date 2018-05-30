#include "tr_executor.h"

// Convenience macros for profiler
#define PROFILER_START_NODE {if (profiler) { profiler->start_node(ast); }}
#define PROFILER_END_NODE {if (profiler) { profiler->end_node(ast); }}
#define PROFILER_NOTIFY_BEFORE {if (profiler) { profiler->notify_before(); }}
#define PROFILER_NOTIFY_AFTER {if (profiler) { profiler->notify_after(); }}
#define PROFILER_NOTIFY_EXIT {if (profiler) { profiler->notify_exit(); }}

// Convenience macros for debugger
#define DEBUGGER_START_NODE {if (debugger) { debugger->start_node(ast); }}
#define DEBUGGER_END_NODE {if (debugger) { debugger->end_node(ast); }}
#define DEBUGGER_NOTIFY_BEFORE {if (debugger) { debugger->notify_before(); }}
#define DEBUGGER_NOTIFY_AFTER {if (debugger) { debugger->notify_after(); }}
#define DEBUGGER_NOTIFY_EXIT {if (debugger) { debugger->notify_exit(); }}

namespace TR {
	
	TRExecutor::TRExecutor(TRInterpreter &driver) : driver(driver), profiler(nullptr) {}
        
    TRExecutor::~TRExecutor() {
    	delete profiler;
    	delete debugger;
    }

	void TRExecutor::execute() {
		DEBUGGER_NOTIFY_BEFORE;
		PROFILER_NOTIFY_BEFORE;
	    // visit start of program, with visitor and no optional node
	    try {
	    	// evaluate all global variables first
			driver.ast->visit(this,nullptr);
	    	// begin program
	    	driver.start_node->visit(this,nullptr);
	    } catch (ReturnV& v) {
	    	if (v.val->t != Type::VOID_T) {
	    		makeError(driver.start_node,0);
	    	} else {
	    		driver.debug("Execution Success");
	    	}
	    } catch (ExitTR& e) {
	    	// ensure that notification occurs when exiting
	    	PROFILER_NOTIFY_EXIT;
	    	DEBUGGER_NOTIFY_EXIT;
	    	throw;
	    }
	    // notify after completion of executor
		PROFILER_NOTIFY_AFTER;
		DEBUGGER_NOTIFY_AFTER;
	}

	/// Visitor function definitions
	// START INCLUSION POINT
	ASTNode* TRExecutor::visitActionList(ActionList* ast, ASTNode* n) {
		DEBUGGER_START_NODE;
		PROFILER_START_NODE;
		// NOP
        ast->s->visit(this, nullptr);
        ast->al->visit(this, nullptr);
        PROFILER_END_NODE;
        DEBUGGER_END_NODE;
		return nullptr;
	}

	ASTNode* TRExecutor::visitActionStmt(ActionStmt* ast, ASTNode* n) {
		DEBUGGER_START_NODE;
		PROFILER_START_NODE;
		ast->al->visit(this, nullptr);
		ast->rgs->visit(this, nullptr);
		// after completing all actions, return as void
        PROFILER_END_NODE; // have to end profiler before throw
        DEBUGGER_END_NODE;
		throw ReturnV(new GVar(Type::VOID_T));
		return nullptr;
	}

	ASTNode* TRExecutor::visitArg(Arg* ast, ASTNode* n) {
		DEBUGGER_START_NODE;
		PROFILER_START_NODE;
		if (!ast->e->stat_calc) {
			ast->e->visit(this,nullptr);
		}
		// arguments can't be void type so check
		if (ast->e->val->t == Type::VOID_T) {
			makeError(ast,8);
		} else if (GVar* v = MakeCopy(ast->e->val)) {
			delete ast->val;
			ast->val = MakeCopy(ast->e->val);
		} else {
			// errors likely to be caught before here, but just in case
			makeError(ast,1);
		}
        PROFILER_END_NODE;
        DEBUGGER_END_NODE;
		return nullptr;
	}

	ASTNode* TRExecutor::visitArgList(ArgList* ast, ASTNode* n) {
		DEBUGGER_START_NODE;
		PROFILER_START_NODE;
		// NOP
        ast->a->visit(this, nullptr);
        ast->al->visit(this, nullptr);
        PROFILER_END_NODE;
        DEBUGGER_END_NODE;
		return nullptr;
	}

	ASTNode* TRExecutor::visitAssignStmt(AssignStmt* ast, ASTNode* n) {
		DEBUGGER_START_NODE;
		PROFILER_START_NODE;
		// Check symbole table
		std::string vname = dynamic_cast<Ident&>(*(ast->id.get())).name;
		ASTDecl* vdecl = nullptr;
		// attempt to retrieve para table first, then from global scope
		if (vdecl = driver.paratbl->retrieve(vname)) {
			// NOP
		} else if (vdecl = driver.symtbl->retrieve(vname)) {
			// NOP
		} else {
			makeError(ast,0); // shouldn't occur after SA
		}
		ASTVariable* avar = dynamic_cast<ASTVariable*>(vdecl);

		// visit expression if needed
		if (!ast->e->stat_calc) {
			ast->e->visit(this, nullptr);
		}

		// check not void
		if (ast->e->val->t == Type::VOID_T) {
			makeError(ast,6,vname);
		} else if (ast->e->val->t == Type::NULL_T) {
			makeError(ast,1);
		} else {
			if (avar->dt == DeclType::BIVAR_DECL) {
				// Built in var can't change type
				if (avar->t != ast->e->val->t &&
					// allows double to int
					!(avar->t == Type::DOUBLE_T && ast->e->val->t == Type::INT_T)
					) {
					makeError(ast,7,vname);
				} else {
					avar->storeValue(MakeCopy(ast->e->val));
				}
			} else {
				// TR var can change type, but give a warning incase not desired
				if (avar->t != ast->e->val->t) {
					driver.warn(ast, warn_msg[2] + vname);
				}
				avar->storeValue(MakeCopy(ast->e->val));
			}
			driver.debug(ast, "AssignStmt: Name = " + vname + " Type = " + TypeToString(ast->e->val) 
							+ " Value = " + ValToString(ast->e->val));
		}
        PROFILER_END_NODE;
        DEBUGGER_END_NODE;
		return nullptr;
	}

	ASTNode* TRExecutor::visitBBCall(BBCall* ast, ASTNode* n) {
		DEBUGGER_START_NODE;
		PROFILER_START_NODE;
		// retrieve table elements
		std::string mod = dynamic_cast<Ident&>(*(ast->mod.get())).name;
		std::string dstruct = dynamic_cast<Ident&>(*(ast->dstruct.get())).name;
		std::string func = dynamic_cast<Ident&>(*(ast->func.get())).name;

		// clear pass_args in case execute was previously run
		for (size_t i = 0; i < ast->pass_args.size(); ++i) {
			// causing some issues when passed second time to functions
			//delete ast->pass_args[i];
		}
		ast->pass_args.clear();

		// evaluate all argument stored in ptr_args, and store in pass_args
		for (size_t i = 0; i < ast->ptr_args.size(); ++i) {
			if (!ast->ptr_args[i]->stat_calc) {
				ast->ptr_args[i]->visit(this,nullptr);
			}
			ast->pass_args.push_back(MakeCopy(ast->ptr_args[i]->val));
			driver.debug(ast,"Name = blackboard." + mod + "." + dstruct + "." + func + " Arg# = " + std::to_string(i) + 
						" Type = " + TypeToString(ast->pass_args[i]) + 
						" Value = " + ValToString(ast->pass_args[i]));
		}

		// make call to blackboard
		delete ast->val;
		ast->val = driver.bbapi.call(mod, dstruct, func, ast->pass_args);

        PROFILER_END_NODE;
    	DEBUGGER_END_NODE;
		return nullptr;
	}

	ASTNode* TRExecutor::visitBIVarDecl(BIVarDecl* ast, ASTNode* n) {
		return nullptr;
	}

	ASTNode* TRExecutor::visitBinaryExpr(BinaryExpr* ast, ASTNode* n) {
		DEBUGGER_START_NODE;
		PROFILER_START_NODE;
		// eval children based on operation, i.e. "OP::OR" should do left for true then right
		switch(dynamic_cast<Operator&>(*(ast->o)).o) {

			// boolean
			case OP::OR:
				if (!ast->e1->stat_calc) {
					ast->e1->visit(this,nullptr);
				}
				if (ast->e1->val->t == Type::BOOL_T) {
					// check if 1st is true, if so then set to true
					if (dynamic_cast<BoolVar*>(ast->e1->val)->val) {
						delete ast->val;
						ast->val = new BoolVar(true);
					} else {
						if (!ast->e2->stat_calc) {
							ast->e2->visit(this, nullptr);
						}
						// if 1st expr was false, then the binary is the value of the 2nd
						if (ast->e2->val->t == Type::BOOL_T) {
							delete ast->val;
							ast->val = MakeCopy(ast->e2->val);
						} else {
							makeError(ast,4,"\'or\' and " + TypeToString(ast->e2->val));
						}
					}
				} else {
					makeError(ast,4,"\'or\' and " + TypeToString(ast->e1->val));
				}
				break;
			// boolean
			case OP::AND:
				if (!ast->e1->stat_calc) {
					ast->e1->visit(this,nullptr);
				}
				if (ast->e1->val->t == Type::BOOL_T) {
					// check if 1st is false, if so then set to false
					if (!dynamic_cast<BoolVar*>(ast->e1->val)->val) {
						delete ast->val;
						ast->val = new BoolVar(false);
					} else {
						if (!ast->e2->stat_calc) {
							ast->e2->visit(this, nullptr);
						}
						// if 1st expr was true, then the binary is the value of the 2nd
						if (ast->e2->val->t == Type::BOOL_T) {
							delete ast->val;
							ast->val = MakeCopy(ast->e2->val);
						} else {
							makeError(ast,4,"\'or\' and " + TypeToString(ast->e2->val));
						}
					}
				} else {
					makeError(ast,4,"\'or\' and " + TypeToString(ast->e1->val));
				}
				break;

			// int/double/boolean/string/vector
			case OP::EQEQ:
				{ 	// limit scope for initalisation
					// check coercion of variables
					if (!ast->e1->stat_calc) {
						ast->e1->visit(this,nullptr);
					}
					if (!ast->e2->stat_calc) {
						ast->e2->visit(this,nullptr);
					}
					std::pair<GVar*,GVar*> eqVar = doCoercion(ast->e1->val, ast->e2->val);
					GVar* lhs = eqVar.first;
					GVar* rhs = eqVar.second;
					if (lhs->t != Type::NULL_T && rhs->t != Type::NULL_T) {
						delete ast->val;
						if(lhs->t == Type::INT_T) {
							ast->val = new BoolVar(
								dynamic_cast<IntVar*>(lhs)->val == 
								dynamic_cast<IntVar*>(rhs)->val
								);
						} else if (lhs->t == Type::DOUBLE_T) {
							ast->val = new BoolVar(
								dynamic_cast<DoubleVar*>(lhs)->val == 
								dynamic_cast<DoubleVar*>(rhs)->val
								);
						} else if (lhs->t == Type::STRING_T) {
							ast->val = new BoolVar(
								dynamic_cast<StringVar*>(lhs)->val == 
								dynamic_cast<StringVar*>(rhs)->val
								);
						} else if (lhs->t == Type::BOOL_T) {
							ast->val = new BoolVar(
								dynamic_cast<BoolVar*>(lhs)->val == 
								dynamic_cast<BoolVar*>(rhs)->val
								);
						} else if (lhs->t == Type::VECTOR_T) {
							ast->val = new BoolVar(
								dynamic_cast<VectorVar*>(lhs)->val == 
								dynamic_cast<VectorVar*>(rhs)->val
								);
						}
						driver.debug(ast,"BinaryExpr: Type = " + TypeToString(ast->val) + " Value = " + ValToString(ast->val));
					} else {
						makeError(ast,4,"\'==\' and " + TypeToString(ast->e1->val) + ", " + TypeToString(ast->e2->val));
					}
					delete lhs, rhs;
					break;
				}
				break;
			// int/double/boolean/string/vector
			case OP::NOTEQ:
				{ 	// limit scope for initalisation
					// check coercion of variables
					if (!ast->e1->stat_calc) {
						ast->e1->visit(this,nullptr);
					}
					if (!ast->e2->stat_calc) {
						ast->e2->visit(this,nullptr);
					}
					std::pair<GVar*,GVar*> eqVar = doCoercion(ast->e1->val, ast->e2->val);
					GVar* lhs = eqVar.first;
					GVar* rhs = eqVar.second;
					if (lhs->t != Type::NULL_T && rhs->t != Type::NULL_T) {
						delete ast->val;
						if(lhs->t == Type::INT_T) {
							ast->val = new BoolVar(
								dynamic_cast<IntVar*>(lhs)->val != 
								dynamic_cast<IntVar*>(rhs)->val
								);
						} else if (lhs->t == Type::DOUBLE_T) {
							ast->val = new BoolVar(
								dynamic_cast<DoubleVar*>(lhs)->val != 
								dynamic_cast<DoubleVar*>(rhs)->val
								);
						} else if (lhs->t == Type::STRING_T) {
							ast->val = new BoolVar(
								dynamic_cast<StringVar*>(lhs)->val != 
								dynamic_cast<StringVar*>(rhs)->val
								);
						} else if (lhs->t == Type::BOOL_T) {
							ast->val = new BoolVar(
								dynamic_cast<BoolVar*>(lhs)->val != 
								dynamic_cast<BoolVar*>(rhs)->val
								);
						} else if (lhs->t == Type::VECTOR_T) {
							ast->val = new BoolVar(
								dynamic_cast<VectorVar*>(lhs)->val != 
								dynamic_cast<VectorVar*>(rhs)->val
								);
						}
						driver.debug(ast,"BinaryExpr: Type = " + TypeToString(ast->val) + " Value = " + ValToString(ast->val));
					} else {
						makeError(ast,4,"\'!=\' and " + TypeToString(ast->e1->val) + ", " + TypeToString(ast->e2->val));
					}
					delete lhs, rhs;
					break;
				}
				break;

			// int/double
			case OP::LT:
				if (!ast->e1->stat_calc) {
					ast->e1->visit(this,nullptr);
				}
				if (!ast->e2->stat_calc) {
					ast->e2->visit(this,nullptr);
				}
				if ((ast->e1->val->t == Type::INT_T || ast->e1->val->t == Type::DOUBLE_T) &&
					(ast->e2->val->t == Type::INT_T || ast->e2->val->t == Type::DOUBLE_T)) {
					// check coercion of variables
					std::pair<GVar*,GVar*> eqVar = doCoercion(ast->e1->val, ast->e2->val);
					GVar* lhs = eqVar.first;
					GVar* rhs = eqVar.second;
					delete ast->val;
					if(lhs->t == Type::INT_T) {
						ast->val = new BoolVar(
							dynamic_cast<IntVar*>(lhs)->val < 
							dynamic_cast<IntVar*>(rhs)->val
							);
					} else if (lhs->t == Type::DOUBLE_T) {
						ast->val = new BoolVar(
							dynamic_cast<DoubleVar*>(lhs)->val <
							dynamic_cast<DoubleVar*>(rhs)->val
							);
					}
					delete lhs, rhs;
					driver.debug(ast,"BinaryExpr: Type = " + TypeToString(ast->val) + " Value = " + ValToString(ast->val));
				} else {
					makeError(ast,4,"\'<\' and " + TypeToString(ast->e1->val) + ", " + TypeToString(ast->e2->val));
				}
				break;
			// int/double
			case OP::LTEQ:
				if (!ast->e1->stat_calc) {
					ast->e1->visit(this,nullptr);
				}
				if (!ast->e2->stat_calc) {
					ast->e2->visit(this,nullptr);
				}
				if ((ast->e1->val->t == Type::INT_T || ast->e1->val->t == Type::DOUBLE_T) &&
					(ast->e2->val->t == Type::INT_T || ast->e2->val->t == Type::DOUBLE_T)) {
					// check coercion of variables
					std::pair<GVar*,GVar*> eqVar = doCoercion(ast->e1->val, ast->e2->val);
					GVar* lhs = eqVar.first;
					GVar* rhs = eqVar.second;
					delete ast->val;
					if(lhs->t == Type::INT_T) {
						ast->val = new BoolVar(
							dynamic_cast<IntVar*>(lhs)->val <= 
							dynamic_cast<IntVar*>(rhs)->val
							);
					} else if (lhs->t == Type::DOUBLE_T) {
						ast->val = new BoolVar(
							dynamic_cast<DoubleVar*>(lhs)->val <=
							dynamic_cast<DoubleVar*>(rhs)->val
							);
					}
					delete lhs, rhs;
					driver.debug(ast,"BinaryExpr: Type = " + TypeToString(ast->val) + " Value = " + ValToString(ast->val));
				} else {
					makeError(ast,4,"\'<=\' and " + TypeToString(ast->e1->val) + ", " + TypeToString(ast->e2->val));
				}
				break;
			// int/double
			case OP::GT:
				if (!ast->e1->stat_calc) {
					ast->e1->visit(this,nullptr);
				}
				if (!ast->e2->stat_calc) {
					ast->e2->visit(this,nullptr);
				}
				if ((ast->e1->val->t == Type::INT_T || ast->e1->val->t == Type::DOUBLE_T) &&
					(ast->e2->val->t == Type::INT_T || ast->e2->val->t == Type::DOUBLE_T)) {
					// check coercion of variables
					std::pair<GVar*,GVar*> eqVar = doCoercion(ast->e1->val, ast->e2->val);
					GVar* lhs = eqVar.first;
					GVar* rhs = eqVar.second;
					delete ast->val;
					if(lhs->t == Type::INT_T) {
						ast->val = new BoolVar(
							dynamic_cast<IntVar*>(lhs)->val > 
							dynamic_cast<IntVar*>(rhs)->val
							);
					} else if (lhs->t == Type::DOUBLE_T) {
						ast->val = new BoolVar(
							dynamic_cast<DoubleVar*>(lhs)->val >
							dynamic_cast<DoubleVar*>(rhs)->val
							);
					}
					delete lhs, rhs;
					driver.debug(ast,"BinaryExpr: Type = " + TypeToString(ast->val) + " Value = " + ValToString(ast->val));
				} else {
					makeError(ast,4,"\'>\' and " + TypeToString(ast->e1->val) + ", " + TypeToString(ast->e2->val));
				}
				break;
			// int/double
			case OP::GTEQ:
				if (!ast->e1->stat_calc) {
					ast->e1->visit(this,nullptr);
				}
				if (!ast->e2->stat_calc) {
					ast->e2->visit(this,nullptr);
				}
				if ((ast->e1->val->t == Type::INT_T || ast->e1->val->t == Type::DOUBLE_T) &&
					(ast->e2->val->t == Type::INT_T || ast->e2->val->t == Type::DOUBLE_T)) {
					// check coercion of variables
					std::pair<GVar*,GVar*> eqVar = doCoercion(ast->e1->val, ast->e2->val);
					GVar* lhs = eqVar.first;
					GVar* rhs = eqVar.second;
					delete ast->val;
					if(lhs->t == Type::INT_T) {
						ast->val = new BoolVar(
							dynamic_cast<IntVar*>(lhs)->val >=
							dynamic_cast<IntVar*>(rhs)->val
							);
					} else if (lhs->t == Type::DOUBLE_T) {
						ast->val = new BoolVar(
							dynamic_cast<DoubleVar*>(lhs)->val >=
							dynamic_cast<DoubleVar*>(rhs)->val
							);
					}
					delete lhs, rhs;
					driver.debug(ast,"BinaryExpr: Type = " + TypeToString(ast->val) + " Value = " + ValToString(ast->val));
				} else {
					makeError(ast,4,"\'>=\' and " + TypeToString(ast->e1->val) + ", " + TypeToString(ast->e2->val));
				}
				break;

			// int/double/string/vector
			case OP::PLUS:
				if (!ast->e1->stat_calc) {
					ast->e1->visit(this,nullptr);
				}
				if (!ast->e2->stat_calc) {
					ast->e2->visit(this,nullptr);
				}
				if ((ast->e1->val->t != Type::BOOL_T && ast->e1->val->t != Type::VOID_T) || 
					(ast->e2->val->t != Type::BOOL_T && ast->e2->val->t != Type::VOID_T)) {
					// check coercion of variables
					std::pair<GVar*,GVar*> eqVar = doCoercion(ast->e1->val, ast->e2->val,true);
					GVar* lhs = eqVar.first;
					GVar* rhs = eqVar.second;
					if (lhs->t != Type::NULL_T && rhs->t != Type::NULL_T) {
						delete ast->val;
						if(lhs->t == Type::INT_T) {
							ast->val = new IntVar(
								dynamic_cast<IntVar*>(lhs)->val +
								dynamic_cast<IntVar*>(rhs)->val
								);
						} else if (lhs->t == Type::DOUBLE_T) {
							ast->val = new DoubleVar(
								dynamic_cast<DoubleVar*>(lhs)->val +
								dynamic_cast<DoubleVar*>(rhs)->val
								);
						} else if (lhs->t == Type::STRING_T) {
							ast->val = new StringVar(
								dynamic_cast<StringVar*>(lhs)->val + 
								dynamic_cast<StringVar*>(rhs)->val
								);
						} else if (lhs->t == Type::VECTOR_T) {
							ast->val = new VectorVar(
								dynamic_cast<VectorVar*>(lhs)->val + 
								dynamic_cast<VectorVar*>(rhs)->val
								);
						}
						driver.debug(ast,"BinaryExpr: Type = " + TypeToString(ast->val) + " Value = " + ValToString(ast->val));
					} else {
						makeError(ast,4,"\'+\' and " + TypeToString(ast->e1->val) + ", " + TypeToString(ast->e2->val));
					}
					delete lhs, rhs;
				} else {
					makeError(ast,4,"\'+\' and " + TypeToString(ast->e1->val) + ", " + TypeToString(ast->e2->val));
				}
				break;

			// int/double/vector
            case OP::MINUS:
				if (!ast->e1->stat_calc) {
					ast->e1->visit(this,nullptr);
				}
				if (!ast->e2->stat_calc) {
					ast->e2->visit(this,nullptr);
				}
				if ((ast->e1->val->t == Type::INT_T || ast->e1->val->t == Type::DOUBLE_T || ast->e1->val->t == Type::VECTOR_T) &&
					(ast->e2->val->t == Type::INT_T || ast->e2->val->t == Type::DOUBLE_T || ast->e2->val->t == Type::VECTOR_T)) {
					// check coercion of variables
					std::pair<GVar*,GVar*> eqVar = doCoercion(ast->e1->val, ast->e2->val);
					GVar* lhs = eqVar.first;
					GVar* rhs = eqVar.second;
					if (lhs->t != Type::NULL_T && rhs->t != Type::NULL_T) {
						delete ast->val;
						if(lhs->t == Type::INT_T) {
							ast->val = new IntVar(
								dynamic_cast<IntVar*>(lhs)->val -
								dynamic_cast<IntVar*>(rhs)->val
								);
						} else if (lhs->t == Type::DOUBLE_T) {
							ast->val = new DoubleVar(
								dynamic_cast<DoubleVar*>(lhs)->val -
								dynamic_cast<DoubleVar*>(rhs)->val
								);
						} else if (lhs->t == Type::VECTOR_T) {
							ast->val = new VectorVar(
								dynamic_cast<VectorVar*>(lhs)->val - 
								dynamic_cast<VectorVar*>(rhs)->val
								);
						}
						driver.debug(ast,"BinaryExpr: Type = " + TypeToString(ast->val) + " Value = " + ValToString(ast->val));
					} else {
						makeError(ast,4,"\'-\' and " + TypeToString(ast->e1->val) + ", " + TypeToString(ast->e2->val));
					}
					delete lhs, rhs;
				} else {
					makeError(ast,4,"\'-\' and " + TypeToString(ast->e1->val) + ", " + TypeToString(ast->e2->val));
				}
            	break;

			// int/double/vector
            case OP::MULT:
				if (!ast->e1->stat_calc) {
					ast->e1->visit(this,nullptr);
				}
				if (!ast->e2->stat_calc) {
					ast->e2->visit(this,nullptr);
				}
				// Left side Vector scalar mult
				if (ast->e1->val->t == Type::VECTOR_T && 
					(ast->e2->val->t == Type::INT_T || ast->e2->val->t == Type::DOUBLE_T)) {
					delete ast->val;
					VectorVar* lhs = dynamic_cast<VectorVar*>(ast->e1->val);
					if (IntVar* rhs = dynamic_cast<IntVar*>(ast->e2->val)) {
						ast->val = new VectorVar(lhs->val * rhs->val);
					} else if (DoubleVar* rhs = dynamic_cast<DoubleVar*>(ast->e2->val)){
						ast->val = new VectorVar(lhs->val * rhs->val);
					}
					driver.debug(ast,"BinaryExpr: Type = " + TypeToString(ast->val) + " Value = " + ValToString(ast->val));
				// Right side Vector scalar mult
				} else if ((ast->e1->val->t == Type::INT_T || ast->e1->val->t == Type::DOUBLE_T) &&
							ast->e2->val->t == Type::VECTOR_T) {
					delete ast->val;
					VectorVar* rhs = dynamic_cast<VectorVar*>(ast->e2->val);
					if (IntVar* lhs = dynamic_cast<IntVar*>(ast->e1->val)) {
						ast->val = new VectorVar(lhs->val * rhs->val);
					} else if (DoubleVar* lhs = dynamic_cast<DoubleVar*>(ast->e1->val)){
						ast->val = new VectorVar(lhs->val * rhs->val);
					}
					driver.debug(ast,"BinaryExpr: Type = " + TypeToString(ast->val) + " Value = " + ValToString(ast->val));
				} else if ((ast->e1->val->t == Type::INT_T || ast->e1->val->t == Type::DOUBLE_T || ast->e1->val->t == Type::VECTOR_T) &&
					(ast->e2->val->t == Type::INT_T || ast->e2->val->t == Type::DOUBLE_T || ast->e2->val->t == Type::VECTOR_T)) {
					// check coercion of variables
					std::pair<GVar*,GVar*> eqVar = doCoercion(ast->e1->val, ast->e2->val);
					GVar* lhs = eqVar.first;
					GVar* rhs = eqVar.second;
					if (lhs->t != Type::NULL_T && rhs->t != Type::NULL_T) {
						delete ast->val;
						if(lhs->t == Type::INT_T) {
							ast->val = new IntVar(
								dynamic_cast<IntVar*>(lhs)->val *
								dynamic_cast<IntVar*>(rhs)->val
								);
						} else if (lhs->t == Type::DOUBLE_T) {
							ast->val = new DoubleVar(
								dynamic_cast<DoubleVar*>(lhs)->val *
								dynamic_cast<DoubleVar*>(rhs)->val
								);
						} else if (lhs->t == Type::VECTOR_T) {
							// Vector dot product
							ast->val = new DoubleVar(
								dynamic_cast<VectorVar*>(lhs)->val * 
								dynamic_cast<VectorVar*>(rhs)->val
								);
						}
						driver.debug(ast,"BinaryExpr: Type = " + TypeToString(ast->val) + " Value = " + ValToString(ast->val));
					} else {
						makeError(ast,4,"\'*\' and " + TypeToString(ast->e1->val) + ", " + TypeToString(ast->e2->val));
					}
					delete lhs, rhs;
				} else {
					makeError(ast,4,"\'*\' and " + TypeToString(ast->e1->val) + ", " + TypeToString(ast->e2->val));
				}
            	break;

			// int/double/vector(left side)
            case OP::DIV:
				if (!ast->e1->stat_calc) {
					ast->e1->visit(this,nullptr);
				}
				if (!ast->e2->stat_calc) {
					ast->e2->visit(this,nullptr);
				}	
				if (ast->e1->val->t == Type::VECTOR_T &&
					(ast->e2->val->t == Type::INT_T || ast->e2->val->t == Type::DOUBLE_T)) {
					delete ast->val;
					VectorVar* lhs = dynamic_cast<VectorVar*>(ast->e1->val);
					if (IntVar* rhs = dynamic_cast<IntVar*>(ast->e2->val)) {
						ast->val = new VectorVar(lhs->val / rhs->val);
					} else if (DoubleVar* rhs = dynamic_cast<DoubleVar*>(ast->e2->val)){
						ast->val = new VectorVar(lhs->val / rhs->val);
					}
					driver.debug(ast,"BinaryExpr: Type = " + TypeToString(ast->val) + " Value = " + ValToString(ast->val));
				} else if ((ast->e1->val->t == Type::INT_T || ast->e1->val->t == Type::DOUBLE_T) &&
					(ast->e2->val->t == Type::INT_T || ast->e2->val->t == Type::DOUBLE_T)) {
					// check coercion of variables
					std::pair<GVar*,GVar*> eqVar = doCoercion(ast->e1->val, ast->e2->val);
					GVar* lhs = eqVar.first;
					GVar* rhs = eqVar.second;
					if ((lhs->t == Type::INT_T || lhs->t == Type::DOUBLE_T) && 
						(rhs->t == Type::INT_T || rhs->t == Type::DOUBLE_T)) {
						delete ast->val;
						if(lhs->t == Type::INT_T) {
							ast->val = new IntVar(
								dynamic_cast<IntVar*>(lhs)->val /
								dynamic_cast<IntVar*>(rhs)->val
								);
						} else if (lhs->t == Type::DOUBLE_T) {
							ast->val = new DoubleVar(
								dynamic_cast<DoubleVar*>(lhs)->val /
								dynamic_cast<DoubleVar*>(rhs)->val
								);
						}
						driver.debug(ast,"BinaryExpr: Type = " + TypeToString(ast->val) + " Value = " + ValToString(ast->val));
					} else {
						makeError(ast,4,"\'/\' and " + TypeToString(ast->e1->val) + ", " + TypeToString(ast->e2->val));
					}
					delete lhs, rhs;
				} else {
					makeError(ast,4,"\'/\' and " + TypeToString(ast->e1->val) + ", " + TypeToString(ast->e2->val));
				}
            	break;
		}
        PROFILER_END_NODE;
        DEBUGGER_END_NODE;
		return nullptr;
	}

	ASTNode* TRExecutor::visitBlackboardDecl(BlackboardDecl* ast, ASTNode* n) {
		return nullptr;
	}

	ASTNode* TRExecutor::visitCond(Cond* ast, ASTNode* n) {
		DEBUGGER_START_NODE;
		PROFILER_START_NODE;
		try {
			// only visit if expr true
			if (!ast->e->stat_calc) {
				ast->e->visit(this, nullptr);
			}
			if (ast->e->val->t == Type::BOOL_T) {
				if (dynamic_cast<BoolVar*>(ast->e->val)->val) {
					ast->as->visit(this, nullptr);
				}
			} else {
				makeError(ast,5,TypeToString(ast->e->val));
			}
		} catch (ReturnV& v) {
        	PROFILER_END_NODE;
        	DEBUGGER_END_NODE;
        	throw;
		}
		return nullptr;
	}

	ASTNode* TRExecutor::visitCondStmt(CondStmt* ast, ASTNode* n) {
		DEBUGGER_START_NODE;
		PROFILER_START_NODE;
		// NOP
		try {
			if (ast->as != nullptr) {
				ast->as->visit(this, nullptr);
			} else {
				ast->c->visit(this, nullptr);
				ast->cs->visit(this, nullptr);
			}
		} catch (ReturnV& v) {
        	PROFILER_END_NODE;
        	DEBUGGER_END_NODE;
        	throw;
		}
		return nullptr;
	}

	ASTNode* TRExecutor::visitElifStmt(ElifStmt* ast, ASTNode* n) {
		DEBUGGER_START_NODE;
		PROFILER_START_NODE;
		// assumed that after visiting statment, returnV is called,
		// otherwise, else statement will be visited
		if (!ast->e->stat_calc) {
			ast->e->visit(this, nullptr);
		}
		if (ast->e->val->t == Type::BOOL_T) {
			if (dynamic_cast<BoolVar*>(ast->e->val)->val) {
        		ast->s->visit(this, nullptr);
			}
		} else {
			makeError(ast,5,TypeToString(ast->e->val));
		}
        PROFILER_END_NODE;
    	DEBUGGER_END_NODE;
		return nullptr;
	}

	ASTNode* TRExecutor::visitElseStmt(ElseStmt* ast, ASTNode* n) {
		DEBUGGER_START_NODE;
		PROFILER_START_NODE;
		// NOP
        ast->s->visit(this, nullptr);
        PROFILER_END_NODE;
    	DEBUGGER_END_NODE;
		return nullptr;
	}

	ASTNode* TRExecutor::visitEmptyActionList(EmptyActionList* ast, ASTNode* n) {
		DEBUGGER_START_NODE;
		PROFILER_START_NODE;
		// NOP
        PROFILER_END_NODE;
		return nullptr;
	}

	ASTNode* TRExecutor::visitEmptyArgList(EmptyArgList* ast, ASTNode* n) {
		DEBUGGER_START_NODE;
		PROFILER_START_NODE;
		// NOP
        PROFILER_END_NODE;
    	DEBUGGER_END_NODE;
		return nullptr;
	}

	ASTNode* TRExecutor::visitEmptyParaList(EmptyParaList* ast, ASTNode* n) {
		DEBUGGER_START_NODE;
		PROFILER_START_NODE;
		// NOP
        PROFILER_END_NODE;
    	DEBUGGER_END_NODE;
		return nullptr;
	}

	ASTNode* TRExecutor::visitEmptyTRProgList(EmptyTRProgList* ast, ASTNode* n) {
		DEBUGGER_START_NODE;
		PROFILER_START_NODE;
		// NOP
        PROFILER_END_NODE;
    	DEBUGGER_END_NODE;
		return nullptr;
	}

	ASTNode* TRExecutor::visitExitStmt(ExitStmt* ast, ASTNode* n) {
		DEBUGGER_START_NODE;
		PROFILER_START_NODE;
		// throw to exit
        PROFILER_END_NODE;
    	DEBUGGER_END_NODE;
		throw ast->etr;
		return nullptr;
	}

	ASTNode* TRExecutor::visitExprStmt(ExprStmt* ast, ASTNode* n) {
		DEBUGGER_START_NODE;
		PROFILER_START_NODE;
		// no point re-evaluating if it has been done once
		if (!ast->e->stat_calc) {
        	ast->e->visit(this,nullptr);
        	// give warning about not used value
        	if (ast->e->val->t != Type::VOID_T) {
				driver.warn(ast, warn_msg[1]);
        	}
        }
        PROFILER_END_NODE;
    	DEBUGGER_END_NODE;
		return nullptr;
	}

	ASTNode* TRExecutor::visitFCall(FCall* ast, ASTNode* n) {
		DEBUGGER_START_NODE;
		PROFILER_START_NODE;
		// retrieve from table
		std::string vname = dynamic_cast<Ident&>(*(ast->id.get())).name;
		if (ASTDecl* vdecl = driver.symtbl->retrieve(vname)) {
			if (vdecl->dt == DeclType::VAR_DECL 
				|| vdecl->dt == DeclType::BIVAR_DECL 
				|| vdecl->dt == DeclType::PARA_DECL) {
				makeError(ast,0);
			} else {
				// clear pass_args in case execute was previously run
				for (size_t i = 0; i < ast->pass_args.size(); ++i) {
					// causing some issues when passed second time to functions
					//delete ast->pass_args[i];
				}
				ast->pass_args.clear();

				// evaluate all argument stored in ptr_args, and store in pass_args
				for (size_t i = 0; i < ast->ptr_args.size(); ++i) {
					if (!ast->ptr_args[i]->stat_calc) {
						ast->ptr_args[i]->visit(this,nullptr);
					}
					ast->pass_args.push_back(MakeCopy(ast->ptr_args[i]->val));
					driver.debug(ast,"Name = " + vname + " Arg# = " + std::to_string(i) + 
								" Type = " + TypeToString(ast->pass_args[i]) + 
								" Value = " + ValToString(ast->pass_args[i]));
				}

				// call function, try/catch return object
				try {
					driver.debug(ast, "Calling: " + vname);
					ASTCallable* callee = dynamic_cast<ASTCallable*>(vdecl);
					callee->call(this,ast); // pass this and FCall ast that contains args
					// error check since all returns should be throws, so this shouldn't get executed
					makeError(ast,0,vname);
				} catch (ReturnV& ret) {
					// set value of FCall from return value
					if (ret.val->t == Type::NULL_T) {
						makeError(ast,2,vname);
					} else {
						delete ast->val;
						ast->val = ret.val;
						if (ast->val->t == Type::VOID_T) {
							driver.debug(ast,"FCall: Type = " + TypeToString(ast->val));
						} else {
							driver.debug(ast,"FCall: Type = " + TypeToString(ast->val) + " Value = " + ValToString(ast->val));
						}
					}
				}
			}
		} else {
			// if vdecl nullptr, then it isn't in symbol table
			makeError(ast,0);
		}
        PROFILER_END_NODE;
    	DEBUGGER_END_NODE;
		return nullptr;
	}

	ASTNode* TRExecutor::visitFuncDecl(FuncDecl* ast, ASTNode* n) {
		PROFILER_START_NODE;
		// open scope
		driver.paratbl->openScope();

		// set all parameter values from args and insert into symbol table
		FCall* caller = dynamic_cast<FCall*>(n);
		driver.debug(ast,"FuncDecl: ParamNum = " + std::to_string(ast->arity));
		for (size_t i = 0; i < ast->params.size(); ++i) {
			// param name from list
			std::string vname = dynamic_cast<Ident&>(*(ast->params[i]->id.get())).name;
			ast->params[i]->storeValue(caller->pass_args[i]);
			driver.paratbl->insert(vname,ast->params[i]);
			driver.debug(ast,"Name = " + vname + " Param# = " + std::to_string(i) + 
							" Type = " + TypeToString(caller->pass_args[i]) + 
							" Value = " + ValToString(caller->pass_args[i]));
		}
		// done after parameter unpacking
		DEBUGGER_START_NODE;

		try {
			ast->s->visit(this, nullptr);
		} catch (ReturnV& v) {
			// close scope
			driver.paratbl->closeScope();
	        PROFILER_END_NODE;
    		DEBUGGER_END_NODE;
	        throw;
	    }
		return nullptr;
	}

	ASTNode* TRExecutor::visitIdent(Ident* ast, ASTNode* n) {
		DEBUGGER_START_NODE;
		PROFILER_START_NODE;
		// NOP
        PROFILER_END_NODE;
		DEBUGGER_END_NODE;
		return nullptr;
	}

	ASTNode* TRExecutor::visitIfStmt(IfStmt* ast, ASTNode* n) {
		DEBUGGER_START_NODE;
		PROFILER_START_NODE;
		if (!ast->e->stat_calc) {
        	ast->e->visit(this, nullptr);
		}
		if (ast->e->val->t == Type::BOOL_T) {
			if (dynamic_cast<BoolVar*>(ast->e->val)->val) {
				ast->s->visit(this, nullptr);
			} else {
				ast->ows->visit(this, nullptr);
			}
		} else {
			makeError(ast,5,TypeToString(ast->e->val));
		}
        PROFILER_END_NODE;
		DEBUGGER_END_NODE;
		return nullptr;
	}

	ASTNode* TRExecutor::visitInitExpr(InitExpr* ast, ASTNode* n) {
		DEBUGGER_START_NODE;
		PROFILER_START_NODE;
		// if it has been statically calculated no need to evaluate it
		if (!ast->e->stat_calc) {
			ast->e->visit(this, nullptr);
		}

		// if it has value, update variable with type
		// if its void, pass the type up so it can error on var decl
		if (GVar* v = MakeCopy(ast->e->val)) {
			delete ast->val;
			ast->val = v;
			driver.debug(ast,"IntExpr: Type = " + TypeToString(ast->val) + " Value = " + ValToString(ast->val));
		} else {
			// errors likely to be caught before here, but just in case
			makeError(ast,1);
		}
        PROFILER_END_NODE;
		DEBUGGER_END_NODE;
		return nullptr;
	}

	ASTNode* TRExecutor::visitLiteralExpr(LiteralExpr* ast, ASTNode* n) {
		DEBUGGER_START_NODE;
		PROFILER_START_NODE;
		// NOP
        PROFILER_END_NODE;
		DEBUGGER_END_NODE;
		return nullptr;
	}

	ASTNode* TRExecutor::visitLogicStmt(LogicStmt* ast, ASTNode* n) {
		DEBUGGER_START_NODE;
		PROFILER_START_NODE;
		// NOP
        ast->ifs->visit(this, nullptr);
        PROFILER_END_NODE;
		DEBUGGER_END_NODE;
		return nullptr;
	}

	ASTNode* TRExecutor::visitOnceDecl(OnceDecl* ast, ASTNode* n) {
		DEBUGGER_START_NODE;
		PROFILER_START_NODE;
		if (!ast->isComplete) {
			ast->al->visit(this, nullptr);
			ast->isComplete = true;
		}
        PROFILER_END_NODE;
		DEBUGGER_END_NODE;
		return nullptr;
	}

	ASTNode* TRExecutor::visitOperator(Operator* ast, ASTNode* n) {
		DEBUGGER_START_NODE;
		PROFILER_START_NODE;
		// NOP
        PROFILER_END_NODE;
		DEBUGGER_END_NODE;
		return nullptr;
	}

	ASTNode* TRExecutor::visitOtherwiseStmt(OtherwiseStmt* ast, ASTNode* n) {
		DEBUGGER_START_NODE;
		PROFILER_START_NODE;
		// NOP
        if (ast->els != nullptr) {
            ast->els->visit(this, nullptr);
        } else {
            ast->efs->visit(this, nullptr);
            ast->ows->visit(this, nullptr);
        }
        PROFILER_END_NODE;
		DEBUGGER_END_NODE;
		return nullptr;
	}

	ASTNode* TRExecutor::visitParaDecl(ParaDecl* ast, ASTNode* n) {
		DEBUGGER_START_NODE;
		PROFILER_START_NODE;
		// NOP
        PROFILER_END_NODE;
		DEBUGGER_END_NODE;
		return nullptr;
	}

	ASTNode* TRExecutor::visitParaList(ParaList* ast, ASTNode* n) {
		DEBUGGER_START_NODE;
		PROFILER_START_NODE;
		// NOP
        ast->pd->visit(this, nullptr);
        ast->pl->visit(this, nullptr);
        PROFILER_END_NODE;
		DEBUGGER_END_NODE;
		return nullptr;
	}

	ASTNode* TRExecutor::visitRegressionStmt(RegressionStmt* ast, ASTNode* n) {
		DEBUGGER_START_NODE;
		PROFILER_START_NODE;
		// NOP
        PROFILER_END_NODE;
		DEBUGGER_END_NODE;
		return nullptr;
	}

	ASTNode* TRExecutor::visitReturnStmt(ReturnStmt* ast, ASTNode* n) {
		DEBUGGER_START_NODE;
		PROFILER_START_NODE;
		if(!ast->e->stat_calc) {
        	ast->e->visit(this, nullptr);
		}
		// if void don't need to copy
		if (ast->e->val->t == Type::VOID_T) {
        	PROFILER_END_NODE;
			DEBUGGER_END_NODE;
			throw ReturnV(new GVar(Type::VOID_T));
		} else {
        	PROFILER_END_NODE;
			DEBUGGER_END_NODE;
			throw ReturnV(MakeCopy(ast->e->val));
		}
		return nullptr;
	}

	ASTNode* TRExecutor::visitTRNode(TRNode* ast, ASTNode* n) {
		PROFILER_START_NODE;

		// open scope
		driver.paratbl->openScope();

		// set all parameter values from args and insert into symbol table
		if (n != nullptr) { // only nullptr for main node
			FCall* caller = dynamic_cast<FCall*>(n);
			driver.debug(ast,"TRNode: ParamNum = " + std::to_string(ast->arity));
			for (size_t i = 0; i < ast->params.size(); ++i) {
				// param name from list
				std::string vname = dynamic_cast<Ident&>(*(ast->params[i]->id.get())).name;
				ast->params[i]->storeValue(caller->pass_args[i]);
				driver.paratbl->insert(vname,ast->params[i]);
				driver.debug(ast,"Name = " + vname + " Param# = " + std::to_string(i) + 
								" Type = " + TypeToString(caller->pass_args[i]) + 
								" Value = " + ValToString(caller->pass_args[i]));
			}
		}
		// done after parameter unpacking
		DEBUGGER_START_NODE;

		try {
			ast->cs->visit(this, nullptr);
		} catch (ReturnV& v) {
			// close scope
			driver.paratbl->closeScope();
	        PROFILER_END_NODE;
			DEBUGGER_END_NODE;
	        throw;
		}
		return nullptr;
	}

	ASTNode* TRExecutor::visitTRProgList(TRProgList* ast, ASTNode* n) {
		DEBUGGER_START_NODE;
		PROFILER_START_NODE;
		// only visit if its a variable declaration, for global var evaluation or once declaration
		if (ast->d->dt == DeclType::VAR_DECL || ast->d->dt == DeclType::ONCE_DECL) {
        	ast->d->visit(this, nullptr);
		}
        ast->pl->visit(this, nullptr);
        PROFILER_END_NODE;
		DEBUGGER_END_NODE;
		return nullptr;
	}

	ASTNode* TRExecutor::visitTRProgram(TRProgram* ast, ASTNode* n) {
		DEBUGGER_START_NODE;
		PROFILER_START_NODE;
		// NOP
        ast->pl->visit(this, nullptr);
        PROFILER_END_NODE;
		DEBUGGER_END_NODE;
		return nullptr;
	}

	ASTNode* TRExecutor::visitUnaryExpr(UnaryExpr* ast, ASTNode* n) {
		DEBUGGER_START_NODE;
		PROFILER_START_NODE;
		if (!ast->e->stat_calc) {
        	ast->e->visit(this, nullptr);
		}

		switch (dynamic_cast<Operator&>(*(ast->o)).o) {
			// int/double/vector
			case OP::PLUS:
				if (ast->e->val->t == Type::INT_T
						|| ast->e->val->t == Type::DOUBLE_T
						|| ast->e->val->t == Type::VECTOR_T) {
					delete ast->val;
					ast->val = MakeCopy(ast->e->val);
					driver.debug(ast,"UnaryExpr: Type = " + TypeToString(ast->val) + " Value = " + ValToString(ast->val));
				} else {
					makeError(ast,3,"\'+\' and " + TypeToString(ast->e->val));
				}
				break;

			// int/double/vector
			case OP::MINUS:
				switch (ast->e->val->t) {
					case Type::INT_T:
						delete ast->val;
						ast->val = new IntVar(-(dynamic_cast<IntVar*>(ast->e->val)->val));
						break;
					case Type::DOUBLE_T:
						delete ast->val;
						ast->val = new DoubleVar(-(dynamic_cast<DoubleVar*>(ast->e->val)->val));
						break;
					case Type::VECTOR_T:
						delete ast->val;
						ast->val = new VectorVar(
							Vector(
								-dynamic_cast<VectorVar*>(ast->e->val)->val.get(0),
								-dynamic_cast<VectorVar*>(ast->e->val)->val.get(1)
								)
							);
						driver.debug(ast,"UnaryExpr: Type = " + TypeToString(ast->val) + " Value = " + ValToString(ast->val));
						break;
					default:
						makeError(ast,3,"\'+\' and " + TypeToString(ast->e->val));
				}
				break;

			// boolean
			case OP::NOT:
				if (ast->e->val->t == Type::BOOL_T) {
					delete ast->val;
					ast->val = new BoolVar(!(dynamic_cast<BoolVar*>(ast->e->val)->val));
					driver.debug(ast,"UnaryExpr: Type = " + TypeToString(ast->val) + " Value = " + ValToString(ast->val));
				} else {
					makeError(ast,3,"\'not\' and " + TypeToString(ast->e->val));
				}
				break;
		}
        PROFILER_END_NODE;
		DEBUGGER_END_NODE;
		return nullptr;
	}

	ASTNode* TRExecutor::visitVarDecl(VarDecl* ast, ASTNode* n) {
		DEBUGGER_START_NODE;
		PROFILER_START_NODE;
		if (!ast->e->stat_calc) {
        	ast->e->visit(this, nullptr);
		}
		if (GVar* v = MakeCopy(ast->e->val)) {
			ast->storeValue(v);
		} else {
			// errors likely to be caught before here, but just in case
			makeError(ast,1);
		}
        PROFILER_END_NODE;
		DEBUGGER_END_NODE;
		return nullptr;
	}

	ASTNode* TRExecutor::visitVarExpr(VarExpr* ast, ASTNode* n) {
		DEBUGGER_START_NODE;
		PROFILER_START_NODE;
		std::string vname = dynamic_cast<Ident&>(*(ast->id.get())).name;
		ASTDecl* vdecl = nullptr;
		// attempt to retrieve para table first, then from global scope
		if (vdecl = driver.paratbl->retrieve(vname)) {
			// NOP
		} else if (vdecl = driver.symtbl->retrieve(vname)) {
			// NOP
		} else {
			makeError(ast,0); // shouldn't occur after SA
		}
		ASTVariable* avar = dynamic_cast<ASTVariable*>(vdecl);
		// update expression value
		if (GVar* v = MakeCopy(avar->getValue())) {
			delete ast->val;
			ast->val = v;
			driver.debug(ast, "VarExpr: Name = " + vname + " Type = " + TypeToString(ast->val) 
						+ " Value = " + ValToString(ast->val));
		} else {
			// errors likely to be caught before here, but just in case
			makeError(ast,1);
		}
        PROFILER_END_NODE;
		DEBUGGER_END_NODE;
		return nullptr;
	}

	// END INCLUSION POINT

}
