#ifndef COND_STMT_H
#define COND_STMT_H

namespace TR {

    /**
     * Condition Statment Node
     *
     * Node of condition statement, part of TR Node nodes
     */
    class CondStmt : public ASTStmt {

    public:

        /// Remove default constructor for this
        CondStmt() = delete;

        /**
         * True Tree Constructor
         *
         * Constructs true node of this tree given child node(s)
         *
         * @param asAST Action statement child of this node (should be type ActionStmt)
         * @param l Location of related token in source node
         * @param f File name of related symbol(s) in source code
         */
        CondStmt(ASTStmt* asAST, const location& l, const std::string& f) :
                as(asAST),
                c(nullptr),
                cs(nullptr),
                ASTStmt(l,f) { asAST->parent = this; }

        /**
         * Source code constructor
         *
         * Constructs true node of this tree given child node(s)
         *
         * @param asAST Action statement child of this node (should be type ActionStmt)
         * @param l Location of related token in source node
         * @param f File name of related symbol(s) in source code
         * @param src Source code of related node
         */
        CondStmt(ASTStmt* asAST, const location& l, const std::string& f, const std::string& src) :
                as(asAST),
                c(nullptr),
                cs(nullptr),
                ASTStmt(l,f,src) { asAST->parent = this; }

        /**
         * Cond Tree Constructor
         *
         * Constructs cond statement child of this node(s)
         *
         * @param cAST Condition statement child of this node (should be type Cond)
         * @param csAST Condition statement statement of this node (should be type CondStmt)
         * @param l Location of related token in source code
         */
        CondStmt(ASTStmt* cAST, ASTStmt* csAST, const location& l, const std::string& f) :
                as(nullptr),
                c(cAST),
                cs(csAST),
                ASTStmt(l,f) { cAST->parent = csAST->parent = this; }

        /**
         * Source code constructor
         *
         * Constructs cond statement child of this node(s)
         *
         * @param cAST Condition statement child of this node (should be type Cond)
         * @param csAST Condition statement statement of this node (should be type CondStmt)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         * @param src Source code of related node
         */
        CondStmt(ASTStmt* cAST, ASTStmt* csAST, const location& l, const std::string& f, const std::string& src) :
                as(nullptr),
                c(cAST),
                cs(csAST),
                ASTStmt(l,f,src) { cAST->parent = csAST->parent = this; }

        /**
         * Virtual destructor
         *
         * Doesn't need to delete parent
         */
        virtual ~CondStmt() {}

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

        std::shared_ptr<ASTStmt> as;
        std::shared_ptr<ASTStmt> c;
        std::shared_ptr<ASTStmt> cs;
    };

}

#endif