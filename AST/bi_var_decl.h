#ifndef BI_VAR_DECL_H
#define BI_VAR_DECL_H

#include <exception>
#include <stdexcept>
#include <string>

// have to include required parts, as won't be included as part of regular AST
#include "ast_variable.h"

// require inclusion first for erroring
#include "ident.h"

// error functions
#include "../exe-components/tr_runtime_exception.h"

namespace TR {

    /**
     * Built-in Variable Declaration Class
     *
     * Variable declaration node for built-in variables. Since
     * built-in variables have a different method of initialising
     * and storing values than TR variables.
     */
    class BIVarDecl : public ASTVariable {

    public:

        /// Remove default constructor for this
        BIVarDecl() = delete;

        /**
         * Single node constructor
         *
         * Constructs single AST node with no child or parents
         *
         * @param idAST ASTTerminal child of this node (should be type Ident)
         * @param ty Type enum of the variable type
         * @param fptr Variable pointer to stored value of C++ variable
         */
        BIVarDecl(ASTTerminal* idAST, const Type ty, void* v) :
                val(v),
                dummy(nullptr),
                ASTVariable(idAST, DeclType::BIVAR_DECL, location(), std::string()) {
            idAST->parent = this;
            // if the type is null, then it was made with an incorrect type
            t = ty; // initialised after ASTDecl created
            if (t == Type::NULL_T) {
                throw std::runtime_error("Invalid type used for built-in: " + (dynamic_cast<Ident*>(idAST))->name); 
            } else if (t == Type::FLOAT_T) {
                t = Type::DOUBLE_T;
                isFloat = true;
            }
        }

        /**
         * Virtual destructor
         *
         * Doesn't need to delete C++ reference, as assumed
         * it's done by C++
         */
        virtual ~BIVarDecl() {}

        /**
         * Visit Function
         *
         * Calls the abstracted visitor function
         * See Visitor Pattern
         *
         * @param v Pointer to the visitor object
         * @param n Optional pointer to AST node
         * @return Optionally returns a pointer to an AST node
         */
        virtual ASTNode* visit(Visitor* v, ASTNode* n);

        /**
         * Get Variable Value
         *
         * Provides a pointer to a GVar with the value of the variable
         * stored in this variable
         *
         * @return Pointer to GVar containing value of variable
         */
        GVar* getValue() {
            delete dummy; // delete previous dummy value incase something is there
            switch(t) {
                case Type::INT_T:
                    dummy = new IntVar(*static_cast<int*>(val));
                    break;
                case Type::DOUBLE_T:
                    if (isFloat) { // store float as TR Lang double
                        dummy = new DoubleVar(*static_cast<float*>(val));
                    } else {
                        dummy = new DoubleVar(*static_cast<double*>(val));
                    }
                    break;
                case Type::STRING_T:
                    dummy = new StringVar(*static_cast<std::string*>(val));
                    break;
                case Type::BOOL_T:
                    dummy = new BoolVar(*static_cast<bool*>(val));
                    break;
                case Type::VECTOR_T:
                    dummy = new VectorVar(*static_cast<Vector*>(val));
                    break;
                default:
                    // this shouldn't happen
                    dummy = new GVar();
                    break;
            }
            return dummy;
        }

        /**
         * Store Variable Value
         *
         * Stores a value in the variable given by a pointer to a GVar with the
         * same type as this variable.
         *
         * @param v Pointer to a GVar with value to store in this variable
         */
        void storeValue(GVar* v) {
            // for built-in var, can just store directly in pointer value
            switch(t) {
                case Type::INT_T:
                    *(static_cast<int*>(val)) = dynamic_cast<IntVar*>(v)->val;
                    break;
                case Type::DOUBLE_T:
                    if (isFloat) { // store float as TR Lang double
                        *(static_cast<double*>(val)) = static_cast<float>(dynamic_cast<DoubleVar*>(v)->val);
                    } else {
                        *(static_cast<double*>(val)) = dynamic_cast<DoubleVar*>(v)->val;
                    }
                    break;
                case Type::STRING_T:
                    *(static_cast<std::string*>(val)) = dynamic_cast<StringVar*>(v)->val;
                    break;
                case Type::BOOL_T:
                    *(static_cast<bool*>(val)) = dynamic_cast<BoolVar*>(v)->val;
                    break;
                case Type::VECTOR_T:
                    *(static_cast<Vector*>(val)) = dynamic_cast<VectorVar*>(v)->val;
                    break;
                default:
                    throw TR_Runtime_Exception("Unable to store type in built-in variable");
                    break;
            }
        }

        bool isFloat = false; // if the actual C++ type is float, then this is true
        GVar* dummy; // dummy generic variable that wraps the C++ variable when using getValue
        void* val;  // value pointed to in C++ is cast to type (t) when required during execution
    };

}

#endif