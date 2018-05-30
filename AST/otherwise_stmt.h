#ifndef OTHERWISE_STMT_H
#define OTHERWISE_STMT_H

namespace TR {

    /**
     * Otherwise Statement Node
     *
     * Node of otherwise statement, part of function declaration
     * nodes
     */
    class OtherwiseStmt : public ASTStmt {

    public:

        /// Remove default constructor for this
        OtherwiseStmt() = delete;

        /**
         * Else Tree constructor
         *
         * Constructs else node of this tree given the child node(s)
         *
         * @param elsAST Else statement child of this node (should be type ElseStmt)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         */
        OtherwiseStmt(ASTStmt* elsAST, const location& l, const std::string& f) :
                els(elsAST),
                efs(nullptr),
                ows(nullptr),
                ASTStmt(l,f) { elsAST->parent = this; }

        /**
         * Else Source code constructor
         *
         * Constructs else node of this tree given the child node(s)
         *
         * @param elsAST Else statement child of this node (should be type ElseStmt)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         * @param src Source code of related node
         */
        OtherwiseStmt(ASTStmt* elsAST, const location& l, const std::string& f, const std::string& src) :
                els(elsAST),
                efs(nullptr),
                ows(nullptr),
                ASTStmt(l,f,src) { elsAST->parent = this; }

        /**
         * Elif Tree constructor
         *
         * Constructs elif node of this tree given the child node(s)
         *
         * @param efsAST Elif statement child of this node (should be type ElifStmt)
         * @parma owsAST Otherwise statement child of this node (should be type OtherwsieStmt)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         */
        OtherwiseStmt(ASTStmt* efsAST, ASTStmt* owsAST, const location& l, const std::string& f) :
                els(nullptr),
                efs(efsAST),
                ows(owsAST),
                ASTStmt(l,f) { efsAST->parent = owsAST->parent = this; }

        /**
         * Elif Source code constructor
         *
         * Constructs elif node of this tree given the child node(s)
         *
         * @param efsAST Elif statement child of this node (should be type ElifStmt)
         * @parma owsAST Otherwise statement child of this node (should be type OtherwsieStmt)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         * @param src Source code of related node
         */
        OtherwiseStmt(ASTStmt* efsAST, ASTStmt* owsAST, const location& l, const std::string& f, const std::string& src) :
                els(nullptr),
                efs(efsAST),
                ows(owsAST),
                ASTStmt(l,f,src) { efsAST->parent = owsAST->parent = this; }

        /**
         * Virtual destructor
         *
         * Doesn't need to delete parent
         */
        virtual ~OtherwiseStmt() {}

        /**
         * Visit Function
         *
         * Calls the abstracted visitor function
         * See Visitor Pattern
         *
         * @param v Pointer to the visitor object
         * @param n Optional pointer to AST node
         * @return Optionally returns pointer to an AST node
         */
        virtual ASTNode* visit(Visitor* v, ASTNode* n);

        std::shared_ptr<ASTStmt> els;
        std::shared_ptr<ASTStmt> efs;
        std::shared_ptr<ASTStmt> ows;
    };

}

#endif