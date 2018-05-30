#ifndef TR_NODE_H
#define TR_NODE_H

namespace TR {

    /**
     * TR Node Node
     *
     * Node for TR Node, part of TR declaration nodes
     */
    class TRNode : public ASTCallable {

    public:

        /// Remove default constructor for this
        TRNode() = delete;

        /**
         * Tree constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param idAST Id child of this node (should be type Ident)
         * @param plAST Parameter list of this node (should be type ParaList)
         * @param csAST Condition statement statment child of this node (should be type CondStmt)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         */
        TRNode(ASTTerminal* idAST, ASTList* plAST, ASTStmt* csAST, const location& l, const std::string& f) :
                pl(plAST),
                cs(csAST),
                ASTCallable(idAST, DeclType::TR_DECL, l, f) {
            idAST->parent = plAST->parent = csAST->parent = this;
        }

        /**
         * Source code constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param idAST Id child of this node (should be type Ident)
         * @param plAST Parameter list of this node (should be type ParaList)
         * @param csAST Condition statement statment child of this node (should be type CondStmt)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         * @param src Source code of related node
         */
        TRNode(ASTTerminal* idAST, ASTList* plAST, ASTStmt* csAST, const location& l, const std::string& f, const std::string& src) :
                pl(plAST),
                cs(csAST),
                ASTCallable(idAST, DeclType::TR_DECL, l, f, src) {
            idAST->parent = plAST->parent = csAST->parent = this;
        }

        /**
         * Virtual destructor
         *
         * Doesn't need to delete parent
         */
        virtual ~TRNode() {}

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
         * FCallable Override
         *
         * Call function for calling a TR Function
         *
         * @param v Visitor passed to call to walk tree
         * @param n Reference to the FCall node that called
         * @throws ReturnV Return value object of callable
         */
        void call(Visitor* v, ASTNode* n);

        std::shared_ptr<ASTList> pl;
        std::shared_ptr<ASTStmt> cs;
    };

}

#endif