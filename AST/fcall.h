#ifndef FCALL_H
#define FCALL_H

namespace TR {

    /**
     * FCall Expression Node
     *
     * Node for FCall for funcion and tr-node calls, part of
     * general nodes
     */
    class FCall : public ASTExpr {

    public:

        /// Remove default constructor for this
        FCall() = delete;

        /**
         * Tree constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param idAST Id child of this node (should be type Ident)
         * @param alAST Argument List child of this node (should be type ArgList)
         * @param l Location related token in source code
         * @param f File name of related symbol(s) in source code
         */
        FCall(ASTTerminal* idAST, ASTList* alAST, const location& l, const std::string& f) :
                id(idAST),
                al(alAST),
                ASTExpr(l,f) { idAST->parent = alAST->parent = this; }

        /**
         * Source code constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param idAST Id child of this node (should be type Ident)
         * @param alAST Argument List child of this node (should be type ArgList)
         * @param l Location related token in source code
         * @param f File name of related symbol(s) in source code
         * @param src Source code of related node
         */
        FCall(ASTTerminal* idAST, ASTList* alAST, const location& l, const std::string& f, const std::string& src) :
                id(idAST),
                al(alAST),
                ASTExpr(l,f,src) { idAST->parent = alAST->parent = this; }

        /**
         * Virtual destructor
         *
         * Doesn't need to delete parent
         */
        virtual ~FCall() {}

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
        std::shared_ptr<ASTList> al;
        std::vector<ASTExpr*> ptr_args; /**list of pointers to args, populated only during SA**/
        std::vector<GVar*> pass_args; /**args to pass to any call, populated only during E**/ // should be new objects
    };

}

#endif