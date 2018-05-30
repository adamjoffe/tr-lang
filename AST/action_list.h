#ifndef ACTION_LIST_H
#define ACTION_LIST_H

namespace TR {

    /**
     * Action List
     *
     * List for actions, part of the TR Node node
     */
    class ActionList : public ASTList {

    public:

        /// Remove default constructor for this
        ActionList() = delete;

        /**
         * Tree constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param sAST Expression of the child node (should by type ASTStmt)
         * @param alAST Action list child of this node (should be type ASTList)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         */
        ActionList(ASTStmt* sAST, ASTList* alAST, const location& l, const std::string& f) :
                s(sAST),
                al(alAST),
                ASTList(l,f) { sAST->parent = alAST->parent = this; }

        /**
         * Source code constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param sAST Expression of the child node (should by type ASTStmt)
         * @param alAST Action list child of this node (should be type ASTList)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         * @param src Source code of related node
         */
        ActionList(ASTStmt* sAST, ASTList* alAST, const location& l, const std::string& f, const std::string& src) :
                s(sAST),
                al(alAST),
                ASTList(l,f,src) { sAST->parent = alAST->parent = this; }

        /**
         * Virtual destructor
         *
         * Doesn't need to delete parent
         */
        virtual ~ActionList() {}

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
         * Empty Check
         *
         * Checks if this instance of the list is empty
         * Always returns false since this is a non empty implementation
         *
         * @return True if the list is empty
         */
        virtual bool isEmpty() { return false; }

        std::shared_ptr<ASTStmt> s;
        std::shared_ptr<ASTList> al;
    };

}

#endif