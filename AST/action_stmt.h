#ifndef ACTION_STMT_H
#define ACTION_STMT_H

namespace TR {

    /**
     * Action Statement Node
     *
     * Node of action statement, part of TR Node nodes
     */
    class ActionStmt : public ASTStmt {

    public:

        /// Remove default constructor for this
        ActionStmt() = delete;

        /**
         * Tree constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param alAST Action list child of this node (should be type ASTList)
         * @param rgsAST Regression statement child of this node (should be type RegressionStmt)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         */
        ActionStmt(ASTList* alAST, ASTStmt* rgsAST, const location& l, const std::string& f) :
                al(alAST),
                rgs(rgsAST),
                ASTStmt(l,f) { alAST->parent = rgsAST->parent = this; }

        /**
         * Source code constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param alAST Action list child of this node (should be type ASTList)
         * @param rgsAST Regression statement child of this node (should be type RegressionStmt)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         * @param src Source code of related node
         */
        ActionStmt(ASTList* alAST, ASTStmt* rgsAST, const location& l, const std::string& f, const std::string& src) :
                al(alAST),
                rgs(rgsAST),
                ASTStmt(l,f,src) { alAST->parent = rgsAST->parent = this; }

        /**
         * Virtual destructor
         *
         * Doesn't need to delete parent
         */
        virtual ~ActionStmt() {}

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

        std::shared_ptr<ASTList> al;
        std::shared_ptr<ASTStmt> rgs;
    };

}

#endif