#ifndef LITERAL_EXPR_H
#define LITERAL_EXPR_H

namespace TR {

    /**
     * Literal Expression Node
     *
     * Node for literal expressions, part of the general nodes
     */
    class LiteralExpr : public ASTExpr {

    public:

        /// Remove default construtor for this
        LiteralExpr() = delete;

        /**
         * Tree Constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param val Value of literal of TR lang type
         * @param l Location related token in source code
         * @param f File name of related symbol(s) in source code
         */
        LiteralExpr(int val, const location& l, const std::string& f) :
            ASTExpr(new IntVar(val),l,f) {}

        LiteralExpr(double val, const location& l, const std::string& f) :
            ASTExpr(new DoubleVar(val),l,f) {}

        LiteralExpr(bool val, const location& l, const std::string& f) :
            ASTExpr(new BoolVar(val),l,f) {}

        LiteralExpr(std::string val, const location& l, const std::string& f) :
            ASTExpr(new StringVar(val),l,f) {}

        LiteralExpr(Vector val, const location& l, const std::string& f) :
            ASTExpr(new VectorVar(val),l,f) {}

        /**
         * Source code constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param val Value of literal of TR lang type
         * @param l Location related token in source code
         * @param f File name of related symbol(s) in source code
         * @param src Source code of related node
         */
        LiteralExpr(int val, const location& l, const std::string& f, const std::string& src) :
            ASTExpr(new IntVar(val),l,f,src) {}

        LiteralExpr(double val, const location& l, const std::string& f, const std::string& src) :
            ASTExpr(new DoubleVar(val),l,f,src) {}

        LiteralExpr(bool val, const location& l, const std::string& f, const std::string& src) :
            ASTExpr(new BoolVar(val),l,f,src) {}

        LiteralExpr(std::string val, const location& l, const std::string& f, const std::string& src) :
            ASTExpr(new StringVar(val),l,f,src) {}

        LiteralExpr(Vector val, const location& l, const std::string& f, const std::string& src) :
            ASTExpr(new VectorVar(val),l,f,src) {}

        /**
         * Virtual destructor
         *
         * Doesn't need to delete parent
         */
        virtual ~LiteralExpr() {}

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

    };

}

#endif