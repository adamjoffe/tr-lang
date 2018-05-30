#ifndef REGRESSION_STMT_H
#define REGRESSION_STMT_H

namespace TR {

    /**
     * Regression Statment Node
     *
     * Node of regression statment, part of TR Node nodes
     */
    class RegressionStmt : public ASTStmt {

    public:

        /// Remove default constructor for this
        RegressionStmt() = delete;

        /**
         * Tree constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param idAST Id child of this node (should be type Ident)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         */
        RegressionStmt(ASTTerminal* idAST, const location& l, const std::string& f) :
                id(idAST),
                ASTStmt(l,f) { idAST->parent = this; }

        /**
         * Source code constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param idAST Id child of this node (should be type Ident)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         * @param src Source code of related node
         */
        RegressionStmt(ASTTerminal* idAST, const location& l, const std::string& f, const std::string& src) :
                id(idAST),
                ASTStmt(l,f,src) { idAST->parent = this; }

        /**
         * Virtual destructor
         *
         * Doesn't need to delete parent
         */
        virtual ~RegressionStmt() {}

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

        std::shared_ptr<ASTTerminal> id;
    };

}

#endif