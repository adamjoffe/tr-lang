#ifndef BBCALL_H
#define BBCALL_H

namespace TR {

    /**
     * FCall Expression Node
     *
     * Node for FCall for funcion and tr-node calls, part of
     * general nodes
     */
    class BBCall : public ASTExpr {

    public:

        /// Remove default constructor for this
        BBCall() = delete;

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
        BBCall(ASTTerminal* modAST, ASTTerminal* structAST, ASTTerminal* funcAST, ASTList* alAST, const location& l, const std::string& f) :
                mod(modAST),
                dstruct(structAST),
                func(funcAST),
                al(alAST),
                ASTExpr(l,f) { 
                    modAST->parent = structAST->parent = funcAST->parent = alAST->parent = this; 
                }

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
        BBCall(ASTTerminal* modAST, ASTTerminal* structAST, ASTTerminal* funcAST, ASTList* alAST, const location& l, const std::string& f, const std::string& src) :
                mod(modAST),
                dstruct(structAST),
                func(funcAST),
                al(alAST),
                ASTExpr(l,f,src) {
                    modAST->parent = structAST->parent = funcAST->parent = alAST->parent = this; 
                }

        /**
         * Virtual destructor
         *
         * Doesn't need to delete parent
         */
        virtual ~BBCall() {}

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

        std::shared_ptr<ASTTerminal> mod;
        std::shared_ptr<ASTTerminal> dstruct;
        std::shared_ptr<ASTTerminal> func;
        std::shared_ptr<ASTList> al;
        std::vector<ASTExpr*> ptr_args; /**list of pointers to args, populated only during SA**/
        std::vector<GVar*> pass_args; /**args to pass to any call, populated only during E**/ // should be new objects
    };

}

#endif