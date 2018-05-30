#ifndef TR_PROGRAM_H
#define TR_PROGRAM_H

namespace TR {

    /**
     * TR Program Node
     *
     * Top level node of the TR program
     */
    class TRProgram : public ASTNode {

    public:

        /// Remove default constructor for this
        TRProgram() = delete;

        /**
         * Tree Constructor
         *
         * Constructs nodes of the tree given the child node(s)
         *
         * @param plAST List child of this node (should be type TRProgList)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         */
        TRProgram(ASTList* plAST, const location& l, const std::string& f) :
                pl(plAST),
                ASTNode(l,f) { plAST->parent = this; }

        /**
         * Source code constructor
         *
         * Constructs nodes of the tree given the child node(s)
         *
         * @param plAST List child of this node (should be type TRProgList)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         * @param src Source code of related node
         */
        TRProgram(ASTList* plAST, const location& l, const std::string& f, const std::string& src) :
                pl(plAST),
                ASTNode(l,f,src) { plAST->parent = this; }

        /**
         * Virtual destructor
         *
         * Doesn't need to delete parent
         */
        virtual ~TRProgram() {}

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

        std::shared_ptr<ASTList> pl;
    };
}

#endif
