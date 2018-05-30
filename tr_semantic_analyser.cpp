#include "tr_semantic_analyser.h"

namespace TR {

	TRSemanticAnalyser::TRSemanticAnalyser(TRInterpreter &driver) : driver(driver) {}

	void TRSemanticAnalyser::analyse() {
		// visit start of program, with visitor and no optional node
		driver.ast->visit(this,nullptr);
	}

	/// Visitor function definitions
	// START INCLUSION POINT
	ASTNode* TRSemanticAnalyser::visitActionList(ActionList* ast, ASTNode* n) {
		// NOP
		ast->s->visit(this, nullptr);
		ast->al->visit(this, nullptr);
		return nullptr;
	}

	ASTNode* TRSemanticAnalyser::visitActionStmt(ActionStmt* ast, ASTNode* n) {
		// NOP
		ast->al->visit(this, nullptr);
		ast->rgs->visit(this, nullptr);
		return nullptr;
	}

	ASTNode* TRSemanticAnalyser::visitArg(Arg* ast, ASTNode* n) {
		// add to ptr_args
		if (FCall* fc = dynamic_cast<FCall*>(n)) {
			fc->ptr_args.push_back(ast);
		} else if (BBCall* bbc = dynamic_cast<BBCall*>(n)) {
			bbc->ptr_args.push_back(ast);
		} else {
			driver.error(ast, error_msg[0]);
		}

		// evaluate the expression
		ast->e->visit(this, nullptr);

		// set arg value if possible
		if (ast->e->val->t == Type::VOID_T) {
			driver.error(ast, error_msg[20]);
		} else if (GVar* v = MakeCopy(ast->e->val)) {
			delete ast->val;
			ast->val = v;
			ast->stat_calc = true; // set static calculation to true
			driver.debug(ast,"Arg: Type = " + TypeToString(ast->val) + " Value = " + ValToString(ast->val));
		} else {
			driver.debug(ast,"Arg: can't statically deduce value");
		}
		return nullptr;
	}

	ASTNode* TRSemanticAnalyser::visitArgList(ArgList* ast, ASTNode* n) {
		// NOP
		ast->a->visit(this, n);
		ast->al->visit(this, n);
		return nullptr;
	}

	ASTNode* TRSemanticAnalyser::visitAssignStmt(AssignStmt* ast, ASTNode* n) {
		// Check symbole table
		std::string vname = dynamic_cast<Ident&>(*(ast->id.get())).name;
		if (ASTDecl* vdecl = driver.symtbl->retrieve(vname)) {
			if (vdecl->dt == DeclType::FUNC_DECL || vdecl->dt == DeclType::BIFUNC_DECL) {
				driver.error(ast, error_msg[8] + vname);
			} else if (vdecl->dt == DeclType::TR_DECL) {
				driver.error(ast, error_msg[9] + vname);
			}
			driver.debug(ast, "AssignStmt: Name = " + vname);

			// visit expression
			ast->e->visit(this, nullptr);

			// check not void
			if (ast->e->val->t == Type::VOID_T) {
				driver.error(ast, error_msg[19] + vname);
			} else if (ast->e->val->t != Type::NULL_T) {
				if (vdecl->dt == DeclType::BIVAR_DECL) {
					// Built in var can't change type
					if (vdecl->t != ast->e->val->t &&
						// allows double to int
						!(vdecl->t == Type::DOUBLE_T && ast->e->val->t == Type::INT_T)
						) {
						driver.error(ast, error_msg[21] + vname);
					}
				} else {
					// TR var can change type, but give a warning incase not desired
					// exclude para declarations as they are untyped until execution
					if (vdecl->dt != DeclType::PARA_DECL && vdecl->t != ast->e->val->t) {
						driver.warn(ast, warn_msg[2] + vname);
					}
					vdecl->t = ast->e->val->t;
					driver.debug(ast, vname + ": Type = " + TypeToString(vdecl->t));
				}
			} else {
				driver.debug(ast,vname + ": can't statically deduce value");
			}
		} else {
			// if vdecl nullptr, then it isn't in symbol table
			driver.error(ast, error_msg[5] + vname);
		}
		return nullptr;
	}

	ASTNode* TRSemanticAnalyser::visitBBCall(BBCall* ast, ASTNode* n) {
		std::string mod = dynamic_cast<Ident&>(*(ast->mod.get())).name;
		// check mod exists
		if (driver.bbapi.exists(mod)) {
			std::string dstruct = dynamic_cast<Ident&>(*(ast->dstruct.get())).name;
			// check struct exists
			if (driver.bbapi.exists(mod, dstruct)) {
				std::string func = dynamic_cast<Ident&>(*(ast->func.get())).name;
				// get number of arguments first
				ast->al->visit(this, ast); // pass BBCall to fill its arguments
				driver.debug(ast, "BBCall: blackboard." + mod + "." + dstruct + "." + func + " : Number of args = " + std::to_string(ast->ptr_args.size()));
				// check function exists
				if (!driver.bbapi.exists(mod, dstruct, func, ast->ptr_args.size())) {
					driver.error(ast, error_msg[26] + "\'" + dstruct + "\' has no function \'" + func + "(" + std::to_string(ast->ptr_args.size()) + " args)\'");
				} else {
					// check return to void it its a void return
					if (driver.bbapi.void_return(mod, dstruct, func)) {
						ast->val->t = Type::VOID_T;
					}
				}
			} else {
				driver.error(ast, error_msg[25] + "\'" + mod + "\' has no \'" + dstruct + "\'");
			}
		} else {
			driver.error(ast, error_msg[24] + "\'" + mod + "\'");
		}
	}

	ASTNode* TRSemanticAnalyser::visitBIVarDecl(BIVarDecl* ast, ASTNode* n) {
		return nullptr;
	}

	ASTNode* TRSemanticAnalyser::visitBinaryExpr(BinaryExpr* ast, ASTNode* n) {
		// evaluate children first
		ast->e1->visit(this, nullptr);
		ast->e2->visit(this, nullptr);

		if (ast->e1->val->t != Type::NULL_T && ast->e2->val->t != Type::NULL_T) {
			switch (dynamic_cast<Operator&>(*(ast->o)).o) {
				// boolean
				case OP::OR:
					if (ast->e1->val->t == Type::BOOL_T && ast->e2->val->t == Type::BOOL_T) {
						delete ast->val;
						ast->val = new BoolVar(
							(dynamic_cast<BoolVar*>(ast->e1->val)->val) ||
							(dynamic_cast<BoolVar*>(ast->e2->val)->val)
							);
						ast->stat_calc = true; // set static calculation to true
						driver.debug(ast,"BinaryExpr: Type = " + TypeToString(ast->val) + " Value = " + ValToString(ast->val));
					} else {
						driver.error(ast, error_msg[12] + "\'or\' and " + TypeToString(ast->e1->val) + ", " + TypeToString(ast->e2->val));
					}
					break;
				// boolean
				case OP::AND:
					if (ast->e1->val->t == Type::BOOL_T && ast->e2->val->t == Type::BOOL_T) {
						delete ast->val;
						ast->val = new BoolVar(
							(dynamic_cast<BoolVar*>(ast->e1->val)->val) &&
							(dynamic_cast<BoolVar*>(ast->e2->val)->val)
							);
						ast->stat_calc = true; // set static calculation to true
						driver.debug(ast,"BinaryExpr: Type = " + TypeToString(ast->val) + " Value = " + ValToString(ast->val));
					} else {
						driver.error(ast, error_msg[12] + "\'and\' and " + TypeToString(ast->e1->val) + ", " + TypeToString(ast->e2->val));
					}
					break;

				// int/double/boolean/string/vector
				case OP::EQEQ:
					{ // limit scope for initalisation
						// check coercion of variables
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
							ast->stat_calc = true; // set static calculation to true
							driver.debug(ast,"BinaryExpr: Type = " + TypeToString(ast->val) + " Value = " + ValToString(ast->val));
						} else {
							driver.error(ast, error_msg[12] + "\'==\' and " + TypeToString(ast->e1->val) + ", " + TypeToString(ast->e2->val));
						}
						delete lhs, rhs;
						break;
					}
				// int/double/boolean/string/vector
				case OP::NOTEQ:
					{ // limit scope for initalisation
						// check coercion of variables
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
							ast->stat_calc = true; // set static calculation to true
							driver.debug(ast,"BinaryExpr: Type = " + TypeToString(ast->val) + " Value = " + ValToString(ast->val));
						} else {
							driver.error(ast, error_msg[12] + "\'!=\' and " + TypeToString(ast->e1->val) + ", " + TypeToString(ast->e2->val));
						}
						delete lhs, rhs;
						break;
					}
					break;

				// int/double
				case OP::LT:
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
						ast->stat_calc = true; // set static calculation to true
						driver.debug(ast,"BinaryExpr: Type = " + TypeToString(ast->val) + " Value = " + ValToString(ast->val));
					} else {
						driver.error(ast, error_msg[12] + "\'<\' and " + TypeToString(ast->e1->val) + ", " + TypeToString(ast->e2->val));
					}
					break;
				// int/double
				case OP::LTEQ:
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
						ast->stat_calc = true; // set static calculation to true
						driver.debug(ast,"BinaryExpr: Type = " + TypeToString(ast->val) + " Value = " + ValToString(ast->val));
					} else {
						driver.error(ast, error_msg[12] + "\'<=\' and " + TypeToString(ast->e1->val) + ", " + TypeToString(ast->e2->val));
					}
					break;
				// int/double
				case OP::GT:
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
						ast->stat_calc = true; // set static calculation to true
						driver.debug(ast,"BinaryExpr: Type = " + TypeToString(ast->val) + " Value = " + ValToString(ast->val));
					} else {
						driver.error(ast, error_msg[12] + "\'>\' and " + TypeToString(ast->e1->val) + ", " + TypeToString(ast->e2->val));
					}
					break;
				// int/double
				case OP::GTEQ:
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
						ast->stat_calc = true; // set static calculation to true
						driver.debug(ast,"BinaryExpr: Type = " + TypeToString(ast->val) + " Value = " + ValToString(ast->val));
					} else {
						driver.error(ast, error_msg[12] + "\'>=\' and " + TypeToString(ast->e1->val) + ", " + TypeToString(ast->e2->val));
					}
					break;

				// int/double/string/vector
				case OP::PLUS:
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
							ast->stat_calc = true; // set static calculation to true
							driver.debug(ast,"BinaryExpr: Type = " + TypeToString(ast->val) + " Value = " + ValToString(ast->val));
						} else {
							driver.error(ast, error_msg[12] + "\'+\' and " + TypeToString(ast->e1->val) + ", " + TypeToString(ast->e2->val));
						}
						delete lhs, rhs;
					} else {
						driver.error(ast, error_msg[12] + "\'+\' and " + TypeToString(ast->e1->val) + ", " + TypeToString(ast->e2->val));
					}
					break;

				// int/double/vector
				case OP::MINUS:
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
							ast->stat_calc = true; // set static calculation to true
							driver.debug(ast,"BinaryExpr: Type = " + TypeToString(ast->val) + " Value = " + ValToString(ast->val));
						} else {
							driver.error(ast, error_msg[12] + "\'-\' and " + TypeToString(ast->e1->val) + ", " + TypeToString(ast->e2->val));
						}
						delete lhs, rhs;
					} else {
						driver.error(ast, error_msg[12] + "\'-\' and " + TypeToString(ast->e1->val) + ", " + TypeToString(ast->e2->val));
					}
					break;

				// int/double/vector
				case OP::MULT:
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
						ast->stat_calc = true; // set static calculation to true
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
						ast->stat_calc = true; // set static calculation to true
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
							ast->stat_calc = true; // set static calculation to true
							driver.debug(ast,"BinaryExpr: Type = " + TypeToString(ast->val) + " Value = " + ValToString(ast->val));
						} else {
							driver.error(ast, error_msg[12] + "\'*\' and " + TypeToString(ast->e1->val) + ", " + TypeToString(ast->e2->val));
						}
						delete lhs, rhs;
					} else {
						driver.error(ast, error_msg[12] + "\'*\' and " + TypeToString(ast->e1->val) + ", " + TypeToString(ast->e2->val));
					}
					break;

				// int/double/vector(left side)
				case OP::DIV:
					if (ast->e1->val->t == Type::VECTOR_T &&
						(ast->e2->val->t == Type::INT_T || ast->e2->val->t == Type::DOUBLE_T)) {
						delete ast->val;
						VectorVar* lhs = dynamic_cast<VectorVar*>(ast->e1->val);
						if (IntVar* rhs = dynamic_cast<IntVar*>(ast->e2->val)) {
							ast->val = new VectorVar(lhs->val / rhs->val);
						} else if (DoubleVar* rhs = dynamic_cast<DoubleVar*>(ast->e2->val)){
							ast->val = new VectorVar(lhs->val / rhs->val);
						}
						ast->stat_calc = true; // set static calculation to true
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
							ast->stat_calc = true; // set static calculation to true
							driver.debug(ast,"BinaryExpr: Type = " + TypeToString(ast->val) + " Value = " + ValToString(ast->val));
						} else {
							driver.error(ast, error_msg[12] + "\'/\' and " + TypeToString(ast->e1->val) + ", " + TypeToString(ast->e2->val));
						}
						delete lhs, rhs;
					} else {
						driver.error(ast, error_msg[12] + "\'/\' and " + TypeToString(ast->e1->val) + ", " + TypeToString(ast->e2->val));
					}
					break;
			}
		} else {
			driver.debug(ast,"BinaryExpr: can't statically deduce value");
		}
		return nullptr;
	}

	ASTNode* TRSemanticAnalyser::visitBlackboardDecl(BlackboardDecl* ast, ASTNode* n) {
		std::string vname = dynamic_cast<Ident&>(*(ast->id.get())).name;
		// check if its already exists in the blackboard
		if (!driver.bb[TRMODULE].exists(vname)) {
			// if not then make struct of desired type
			DataStruct* ds = nullptr;
			if (ast->struct_type == "VAR") {
				if (ast->tr_type == "INT") {
					ds = new VarStruct<int>();
				} else if (ast->tr_type == "DOUBLE") {
					ds = new VarStruct<double>();
				} else if (ast->tr_type == "STRING") {
					ds = new VarStruct<std::string>();
				} else if (ast->tr_type == "BOOL") {
					ds = new VarStruct<bool>();
				} else if (ast->tr_type == "VECTOR") {
					ds = new VarStruct<Vector>();
				}
			} else if (ast->struct_type == "STACK") {
				if (ast->tr_type == "INT") {
					ds = new StackStruct<int>();
				} else if (ast->tr_type == "DOUBLE") {
					ds = new StackStruct<double>();
				} else if (ast->tr_type == "STRING") {
					ds = new StackStruct<std::string>();
				} else if (ast->tr_type == "BOOL") {
					ds = new StackStruct<bool>();
				} else if (ast->tr_type == "VECTOR") {
					ds = new StackStruct<Vector>();
				}
			} else if (ast->struct_type == "MAP") {
				if (ast->tr_type == "INT") {
					ds = new MapStruct<int>();
				} else if (ast->tr_type == "DOUBLE") {
					ds = new MapStruct<double>();
				} else if (ast->tr_type == "STRING") {
					ds = new MapStruct<std::string>();
				} else if (ast->tr_type == "BOOL") {
					ds = new MapStruct<bool>();
				} else if (ast->tr_type == "VECTOR") {
					ds = new MapStruct<Vector>();
				}
			} else if (ast->struct_type == "LIST") {
				if (ast->tr_type == "INT") {
					ds = new ListStruct<int>();
				} else if (ast->tr_type == "DOUBLE") {
					ds = new ListStruct<double>();
				} else if (ast->tr_type == "STRING") {
					ds = new ListStruct<std::string>();
				} else if (ast->tr_type == "BOOL") {
					ds = new ListStruct<bool>();
				} else if (ast->tr_type == "VECTOR") {
					ds = new ListStruct<Vector>();
				}
			}
			// add struct of that name
			if (ds) {
				driver.bb[TRMODULE].add_struct(vname, ds);
			} else {
				driver.error(ast, error_msg[0] + vname);
			}
		} else {
			driver.error(ast, error_msg[23] + vname);
		}
		return nullptr;
	}

	ASTNode* TRSemanticAnalyser::visitCond(Cond* ast, ASTNode* n) {
		// Check regression table if already exists and store
		std::string vname = dynamic_cast<Ident&>(*(ast->id.get())).name;
		if (!driver.rgrtbl->insert(vname)) {
			driver.error(ast, error_msg[13] + vname);
		}
		ast->e->visit(this, nullptr);
		if (ast->e->val->t != Type::NULL_T) {
			if (ast->e->val->t != Type::BOOL_T) {
				driver.error(ast, error_msg[18] + TypeToString(ast->e->val));
			}
		} else {
			driver.debug(ast,"Cond: can't statically deduce value");
		}

		ast->as->visit(this, nullptr);
		return nullptr;
	}

	ASTNode* TRSemanticAnalyser::visitCondStmt(CondStmt* ast, ASTNode* n) {
		// NOP	
		if (ast->as != nullptr) {
			ast->as->visit(this, nullptr);
		} else {
			ast->c->visit(this, nullptr);
			ast->cs->visit(this, nullptr);
		}
		return nullptr;
	}

	ASTNode* TRSemanticAnalyser::visitElifStmt(ElifStmt* ast, ASTNode* n) {
		ast->e->visit(this, nullptr);
		if (ast->e->val->t != Type::NULL_T) {
			if (ast->e->val->t != Type::BOOL_T) {
				driver.error(ast, error_msg[18] + TypeToString(ast->e->val));
			}
		} else {
			driver.debug(ast,"ElifStmt: can't statically deduce value");
		}
		ast->s->visit(this, nullptr);
		return nullptr;
	}

	ASTNode* TRSemanticAnalyser::visitElseStmt(ElseStmt* ast, ASTNode* n) {
		// NOP
		ast->s->visit(this, nullptr);
		return nullptr;
	}

	ASTNode* TRSemanticAnalyser::visitEmptyActionList(EmptyActionList* ast, ASTNode* n) {
		// NOP
		return nullptr;
	}

	ASTNode* TRSemanticAnalyser::visitEmptyArgList(EmptyArgList* ast, ASTNode* n) {
		// NOP
		return nullptr;
	}

	ASTNode* TRSemanticAnalyser::visitEmptyParaList(EmptyParaList* ast, ASTNode* n) {
		// NOP
		return nullptr;
	}

	ASTNode* TRSemanticAnalyser::visitEmptyTRProgList(EmptyTRProgList* ast, ASTNode* n) {
		// NOP
		return nullptr;
	}

	ASTNode* TRSemanticAnalyser::visitExitStmt(ExitStmt* ast, ASTNode* n) {
		// NOP
		return nullptr;
	}

	ASTNode* TRSemanticAnalyser::visitExprStmt(ExprStmt* ast, ASTNode* n) {
		// NOP
		ast->e->visit(this,nullptr);
		driver.debug(ast, "ExprStmt Child: Type = " + TypeToString(ast->e->val));
		if (ast->e->val->t != Type::NULL_T && ast->e->val->t != Type::VOID_T) {
			driver.warn(ast, warn_msg[1]);
		}
		return nullptr;
	}

	ASTNode* TRSemanticAnalyser::visitFCall(FCall* ast, ASTNode* n) {
		// check if it exists
		std::string vname = dynamic_cast<Ident&>(*(ast->id.get())).name;
		if (ASTDecl* vdecl = driver.symtbl->retrieve(vname)) {
			if (vdecl->dt == DeclType::VAR_DECL || vdecl->dt == DeclType::BIVAR_DECL) {
				driver.error(ast, error_msg[10] + vname);
			} else if (vdecl->dt == DeclType::PARA_DECL) {
				driver.error(ast, error_msg[7] + vname);
			} else if (vdecl->dt == DeclType::TR_DECL && 
				(dynamic_cast<ExprStmt*>(ast->parent) == nullptr)) {
				driver.error(ast, error_msg[22] + vname);
			} else {
				ast->al->visit(this, ast); // pass FCall to fill its arguments

				// compare arity to make sure it matches
				driver.debug(ast,vname + " : Number of args = " + std::to_string(ast->ptr_args.size()));
				if (ASTCallable* acall = dynamic_cast<ASTCallable*>(vdecl)) {
					if (acall->arity < ast->ptr_args.size()) {
						driver.error(ast, error_msg[15] + vname + " expects " + std::to_string(acall->arity) + " arguments");
					} else if (acall->arity > ast->ptr_args.size()) {
						driver.error(ast, error_msg[16] + vname + " expects " + std::to_string(acall->arity) + " arguments");
					}
					driver.debug(ast, "FCall: Name = " + vname + " NumParams = " + std::to_string(acall->arity));
				} else {
					driver.error(ast, error_msg[0] + vname);
				}

				// if void type (bi-func only), set type so we can do some checks
				if (vdecl->t == Type::VOID_T) {
					ast->val->t = vdecl->t;
				}
			}
		} else {
			// if vdecl nullptr, then it isn't in symbol table
			driver.error(ast, error_msg[6] + vname);
		}
		return nullptr;
	}

	ASTNode* TRSemanticAnalyser::visitFuncDecl(FuncDecl* ast, ASTNode* n) {
		// check if variable already exists
		std::string vname = dynamic_cast<Ident&>(*(ast->id.get())).name;
		if(!driver.symtbl->insert(vname,ast)) {
			driver.error(ast, error_msg[3] + vname);
		}
		// open scope
		driver.symtbl->openScope();

		ast->pl->visit(this, ast); // pass FuncDecl to fill its arity
		driver.debug(ast,vname + " : Number of params = " + std::to_string(ast->arity));

		ast->s->visit(this, nullptr);

		// close scope
		driver.symtbl->closeScope();
		return nullptr;
	}

	ASTNode* TRSemanticAnalyser::visitIdent(Ident* ast, ASTNode* n) {
		// NOP
	}

	ASTNode* TRSemanticAnalyser::visitIfStmt(IfStmt* ast, ASTNode* n) {
		ast->e->visit(this, nullptr);
		if (ast->e->val->t != Type::NULL_T) {
			if (ast->e->val->t != Type::BOOL_T) {
				driver.error(ast, error_msg[18] + TypeToString(ast->e->val));
			}
		} else {
			driver.debug(ast,"IfStmt: can't statically deduce value");
		}
		ast->s->visit(this, nullptr);
		ast->ows->visit(this, nullptr);
		return nullptr;
	}

	ASTNode* TRSemanticAnalyser::visitInitExpr(InitExpr* ast, ASTNode* n) {
		ast->e->visit(this, nullptr);

		// if it has value, update variable with type
		// if its void, pass the type up so it can error on var decl
		if (ast->e->val->t == Type::VOID_T) {
			ast->val->t = Type::VOID_T;
		} else if (GVar* v = MakeCopy(ast->e->val)) {
			delete ast->val;
			ast->val = v;
			ast->stat_calc = true; // set static calculation to true
			driver.debug(ast,"IntExpr: Type = " + TypeToString(ast->val) + " Value = " + ValToString(ast->val));
		} else {
			driver.debug(ast,"IntExpr: can't statically deduce value");
		}
		return nullptr;
	}

	ASTNode* TRSemanticAnalyser::visitLiteralExpr(LiteralExpr* ast, ASTNode* n) {
			driver.debug(ast,"LiteralExpr: Type = " + TypeToString(ast->val) + " Value = " + ValToString(ast->val));
		return nullptr;
	}

	ASTNode* TRSemanticAnalyser::visitLogicStmt(LogicStmt* ast, ASTNode* n) {
		// NOP
		ast->ifs->visit(this, nullptr);
		return nullptr;
	}

	ASTNode* TRSemanticAnalyser::visitOnceDecl(OnceDecl* ast, ASTNode* n) {
		// NOP
		ast->al->visit(this, nullptr);
		return nullptr;
	}

	ASTNode* TRSemanticAnalyser::visitOperator(Operator* ast, ASTNode* n) {
		// NOP
		return nullptr;
	}

	ASTNode* TRSemanticAnalyser::visitOtherwiseStmt(OtherwiseStmt* ast, ASTNode* n) {
		// NOP
		if (ast->els != nullptr) {
			ast->els->visit(this, nullptr);
		} else {
			ast->efs->visit(this, nullptr);
			ast->ows->visit(this, nullptr);
		}
		return nullptr;
	}

	ASTNode* TRSemanticAnalyser::visitParaDecl(ParaDecl* ast, ASTNode* n) {
		std::string vname = dynamic_cast<Ident&>(*(ast->id.get())).name;
		if (ASTCallable* acall = dynamic_cast<ASTCallable*>(n)) {
			// increment arity
			driver.debug(ast,"ParaDecl: Name = " + vname + " Index = " + std::to_string(acall->arity));
			++(acall->arity);
			acall->params.push_back(ast); // add params to vector

			// insert para name into table
			if (!driver.symtbl->insert(vname,ast)) {
				driver.error(ast, error_msg[0] + vname);
			}
		} else {
			driver.error(ast,error_msg[0] + vname);
		}
		return nullptr;
	}

	ASTNode* TRSemanticAnalyser::visitParaList(ParaList* ast, ASTNode* n) {
		// NOP
		ast->pd->visit(this, n);
		ast->pl->visit(this, n);
		return nullptr;
	}

	ASTNode* TRSemanticAnalyser::visitRegressionStmt(RegressionStmt* ast, ASTNode* n) {
		// check regression table to ensure it exists
		std::string vname = dynamic_cast<Ident&>(*(ast->id.get())).name;
		if (!driver.rgrtbl->retrieve(vname)) {
			driver.error(ast, error_msg[14] + vname);
		} else {
			driver.debug(ast,"RegressionStmt: Name = " + vname);
		}
		return nullptr;
	}

	ASTNode* TRSemanticAnalyser::visitReturnStmt(ReturnStmt* ast, ASTNode* n) {
		ast->e->visit(this, nullptr);
		if (ast->e->val->t != Type::NULL_T) {
			// allowed to be void
		} else {
			driver.debug(ast,"ReturnStmt: can't statically deduce value");
		}
		return nullptr;
	}

	ASTNode* TRSemanticAnalyser::visitTRNode(TRNode* ast, ASTNode* n) {
		// check symbol table duplication
		std::string vname = dynamic_cast<Ident&>(*(ast->id.get())).name;
		if (!driver.symtbl->insert(vname,ast)) {
			driver.error(ast, error_msg[4] + vname);
		}

		// if main, then set in interpreter
		if (vname == driver.start_node_name) {
			driver.start_node = ast;
		}

		// open scope
		driver.symtbl->openScope();

		// add the TR Node name into the regression table
		if(!driver.rgrtbl->insert(vname)) {
			driver.error(ast, error_msg[0] + vname);
		}

		ast->pl->visit(this, ast); // pass TRNode to fill its arity
		driver.debug(ast,vname + " : Number of params = " + std::to_string(ast->arity));

		// if main not, arity needs to be 0
		if (vname == driver.start_node_name && ast->arity != 0) {
			driver.error(ast, error_msg[17] + "Number of parameters = " + std::to_string(ast->arity));
		}

		ast->cs->visit(this, nullptr);

		// reset table afterwards, as scope restricted to each TR Node
		driver.rgrtbl->reset();

		// close scope
		driver.symtbl->closeScope();
		return nullptr;

	}

	ASTNode* TRSemanticAnalyser::visitTRProgList(TRProgList* ast, ASTNode* n) {
		// NOP
		ast->d->visit(this, nullptr);
		ast->pl->visit(this, nullptr);
		return nullptr;
	}

	ASTNode* TRSemanticAnalyser::visitTRProgram(TRProgram* ast, ASTNode* n) {
		ast->pl->visit(this, nullptr);
		// after program has been visited, check that main_node exists
		if (driver.start_node == nullptr) {
			driver.error(ast, error_msg[1] + driver.start_node_name);
		}
		return nullptr;
	}

	ASTNode* TRSemanticAnalyser::visitUnaryExpr(UnaryExpr* ast, ASTNode* n) {
		// evaluate child first
		ast->e->visit(this, nullptr);

		if (ast->e->val->t != Type::NULL_T) {
			switch (dynamic_cast<Operator&>(*(ast->o)).o) {
				// int/double/vector
				case OP::PLUS:
					if (ast->e->val->t == Type::INT_T
							|| ast->e->val->t == Type::DOUBLE_T
							|| ast->e->val->t == Type::VECTOR_T) {
						delete ast->val;
						ast->val = MakeCopy(ast->e->val);
						ast->stat_calc = true; // set static calculation to true
						driver.debug(ast,"UnaryExpr: Type = " + TypeToString(ast->val) + " Value = " + ValToString(ast->val));
					} else {
						driver.error(ast, error_msg[11] + "\'+\' and " + TypeToString(ast->e->val));
					}
					break;

				// int/double/vector
				case OP::MINUS:
					switch (ast->e->val->t) {
						case Type::INT_T:
							delete ast->val;
							ast->val = new IntVar(-(dynamic_cast<IntVar*>(ast->e->val)->val));
							ast->stat_calc = true; // set static calculation to true
							break;
						case Type::DOUBLE_T:
							delete ast->val;
							ast->val = new DoubleVar(-(dynamic_cast<DoubleVar*>(ast->e->val)->val));
							ast->stat_calc = true; // set static calculation to true
							break;
						case Type::VECTOR_T:
							delete ast->val;
							ast->val = new VectorVar(
								Vector(
									-dynamic_cast<VectorVar*>(ast->e->val)->val.get(0),
									-dynamic_cast<VectorVar*>(ast->e->val)->val.get(1)
									)
								);
							ast->stat_calc = true; // set static calculation to true
							driver.debug(ast,"UnaryExpr: Type = " + TypeToString(ast->val) + " Value = " + ValToString(ast->val));
							break;
						default:
							driver.error(ast, error_msg[11] + "\'+\' and " + TypeToString(ast->e->val));
					}
					break;

				// boolean
				case OP::NOT:
					if (ast->e->val->t == Type::BOOL_T) {
						delete ast->val;
						ast->val = new BoolVar(!(dynamic_cast<BoolVar*>(ast->e->val)->val));
						ast->stat_calc = true; // set static calculation to true
						driver.debug(ast,"UnaryExpr: Type = " + TypeToString(ast->val) + " Value = " + ValToString(ast->val));
					} else {
						driver.error(ast, error_msg[11] + "\'not\' and " + TypeToString(ast->e->val));
					}
					break;
			}
		} else {
			driver.debug(ast,"UnaryExpr: can't statically deduce value");
		}
		return nullptr;
	}

	ASTNode* TRSemanticAnalyser::visitVarDecl(VarDecl* ast, ASTNode* n) {
		// visit expr first to avoid using var to declare itself
		ast->e->visit(this, nullptr);

		// check if variable already exists
		std::string vname = dynamic_cast<Ident&>(*(ast->id.get())).name;
		if (!driver.symtbl->insert(vname,ast)) {
			driver.error(ast, error_msg[2] + vname);
		}

		// if it has type, update variable with type and check not void
		if (ast->e->val->t == Type::VOID_T) {
			driver.error(ast, error_msg[19] + vname);
		} else if (ast->e->val->t != Type::NULL_T) {
			ast->t = ast->e->val->t;
			driver.debug(vname + ": Type = " + TypeToString(ast->t));
		} else {
			driver.debug(vname + ": can't statically deduce type");
		}
		return nullptr;
	}

	ASTNode* TRSemanticAnalyser::visitVarExpr(VarExpr* ast, ASTNode* n) {
		std::string vname = dynamic_cast<Ident&>(*(ast->id.get())).name;
		if (ASTDecl* vdecl = driver.symtbl->retrieve(vname)) {
			if (vdecl->dt == DeclType::FUNC_DECL || vdecl->dt == DeclType::BIFUNC_DECL) {
				driver.error(ast, error_msg[8] + vname);
			} else if (vdecl->dt == DeclType::TR_DECL) {
				driver.error(ast, error_msg[9] + vname);
			}
			if (vdecl->dt == DeclType::BIVAR_DECL) {
				ASTVariable* avar = dynamic_cast<ASTVariable*>(vdecl);
				driver.debug(ast, "VarExpr: Name = " + vname + " Type = " + TypeToString(avar->t) 
								+ " Value = " + ValToString(avar->getValue()));
				// don't set value of expression here since the built-in variable can change
				// so isn't static
			} else {
				driver.debug(ast, "VarExpr: Name = " + vname);
			}
		} else {
			// if vdecl nullptr, then it isn't in symbol table
			driver.error(ast, error_msg[5] + vname);
		}
		return nullptr;
	}

	// END INCLUSION POINT
	
}