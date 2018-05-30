#ifndef IF_STMT_H
#define IF_STMT_H

namespace TR {

    /**
     * If Statement Node
     *
     * Node of if statement, part of function declaration
     * nodes
     */
    class IfStmt : public ASTStmt {

    public:

        /// Remove default constructor for this
        IfStmt() = delete;

        /**
         * Tree constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param eAST Expr child of this node (should be type ASTExpr)
         * @param sAST Statement child of this node (should be type ASTStmt)
         * @param csAST Otherwise statement child of this node (should be type OtherwiseStmt)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         */
        IfStmt(ASTExpr* eAST, ASTStmt* sAST, ASTStmt* owsAST, const location& l, const std::string& f) :
            e(eAST),
            s(sAST),
            ows(owsAST),
            ASTStmt(l,f) { eAST->parent = sAST->parent = owsAST->parent = this; }

        /**
         * Source code constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param eAST Expr child of this node (should be type ASTExpr)
         * @param sAST Statement child of this node (should be type ASTStmt)
         * @param csAST Otherwise statement child of this node (should be type OtherwiseStmt)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         * @param src Source code of related node
         */
        IfStmt(ASTExpr* eAST, ASTStmt* sAST, ASTStmt* owsAST, const location& l, const std::string& f, const std::string& src) :
            e(eAST),
            s(sAST),
            ows(owsAST),
            ASTStmt(l,f,src) { eAST->parent = sAST->parent = owsAST->parent = this; }

        /**
         * Virtual destructor
         *
         * Doesn't need to delete parent
         */
        virtual ~IfStmt() {}

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

        std::shared_ptr<ASTExpr> e;
        std::shared_ptr<ASTStmt> s;
        std::shared_ptr<ASTStmt> ows;
    };

}

#endif