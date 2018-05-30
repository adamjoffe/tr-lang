#ifndef ELSE_STMT_H
#define ELSE_STMT_H

namespace TR {

    /**
     * Else Statement Node
     *
     * Node of else statement, part of function declaration
     * nodes
     */
    class ElseStmt : public ASTStmt {

    public:

        /// Remove default constructor for this
        ElseStmt() = delete;

        /**
         * Tree constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param sAST Statement child of this node (should be type ASTStmt)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         */
        ElseStmt(ASTStmt* sAST, const location& l, const std::string& f) :
                s(sAST),
                ASTStmt(l,f) { sAST->parent = this; }

        /**
         * Source code constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param sAST Statement child of this node (should be type ASTStmt)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         * @param src Source code of related node
         */
        ElseStmt(ASTStmt* sAST, const location& l, const std::string& f, const std::string& src) :
                s(sAST),
                ASTStmt(l,f,src) { sAST->parent = this; }

        /**
         * Virtual destructor
         *
         * Doesn't need to delete parent
         */
        virtual ~ElseStmt() {}

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

        std::shared_ptr<ASTStmt> s;
    };

}

#endif