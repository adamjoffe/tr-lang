#ifndef VAR_DECL_H
#define VAR_DECL_H

namespace TR {

    /**
     * Variable Declaration Node
     *
     * Node for variable declarations, part of TR declaration
     * nodes
     */
    class VarDecl : public ASTVariable {

    public:

        /// Remove default constructor for this
        VarDecl() = delete;

        /**
         * Tree constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param idAST Id child of this node (should be type Ident)
         * @param eAST Init expression child of this node (should be type ASTExpr)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         */
        VarDecl(ASTTerminal* idAST, ASTExpr* eAST, const location& l, const std::string& f) :
                e(eAST),
                val(nullptr),
                ASTVariable(idAST, DeclType::VAR_DECL, l, f) {
            idAST->parent = eAST->parent = this;
        }

        /**
         * Source code constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param idAST Id child of this node (should be type Ident)
         * @param eAST Init expression child of this node (should be type ASTExpr)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         * @param src Source code of related node
         */
        VarDecl(ASTTerminal* idAST, ASTExpr* eAST, const location& l, const std::string& f, const std::string& src) :
                e(eAST),
                val(nullptr),
                ASTVariable(idAST, DeclType::VAR_DECL, l, f, src) {
            idAST->parent = eAST->parent = this;
        }

        /**
         * Virtual destructor
         *
         * Doesn't need to delete parent
         */
        virtual ~VarDecl() {}

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
            return val;
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
            // remove previous value and overwrite
            delete val;
            val = v;
        }

        std::shared_ptr<ASTExpr> e;
        GVar* val; // value stored in this declaration used
                    // by symbol table during execution
    };

}

#endif