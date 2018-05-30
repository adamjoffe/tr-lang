#ifndef ASSIGN_STMT_H
#define ASSIGN_STMT_H

namespace TR {

    /**
     * Assignment Statement Node
     *
     * Node of assignment statement, part of general nodes
     */
    class AssignStmt : public ASTStmt {

    public:

        /// Remove default constructor for this
        AssignStmt() = delete;

        /**
         * Tree constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param idAST ASTTerminal child of this node (should be type Ident)
         * @param eAST Expr child of this node (should be type ASTExpr)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         */
        AssignStmt(ASTTerminal* idAST, ASTExpr* eAST, const location& l, const std::string& f) :
                id(idAST),
                e(eAST),
                ASTStmt(l,f) { idAST->parent = eAST->parent = this; }

        /**
         * Source code constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param idAST ASTTerminal child of this node (should be type Ident)
         * @param eAST Expr child of this node (should be type ASTExpr)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         * @param src Source code of related node
         */
        AssignStmt(ASTTerminal* idAST, ASTExpr* eAST, const location& l, const std::string& f, const std::string& src) :
                id(idAST),
                e(eAST),
                ASTStmt(l,f,src) { idAST->parent = eAST->parent = this; }

        /**
         * Virtual destructor
         *
         * Doesn't need to delete parent
         */
        virtual ~AssignStmt() {}

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
        std::shared_ptr<ASTExpr> e;
    };

}

#endif