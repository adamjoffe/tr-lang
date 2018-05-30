#ifndef BLACKBOARD_DECL_H
#define BLACKBOARD_DECL_H

namespace TR {

    /**
     * Blackboard Declaration Node
     *
     * Node for variable declarations, part of TR declaration
     * nodes
     */
    class BlackboardDecl : public ASTDecl {

    public:

        /// Remove default constructor for this
        BlackboardDecl() = delete;

        /**
         * Tree constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param idAST Id child of this node (should be type Ident)
         * @param eAST Init expression child of this node (should be type ASTExpr)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         */
        BlackboardDecl(ASTTerminal* idAST, std::string struct_typeAST, std::string tr_typeAST, const location& l, const std::string& f) :
                struct_type(struct_typeAST),
                tr_type(tr_typeAST),
                ASTDecl(idAST, DeclType::BLACKBOARD_DECL, l, f) {
            idAST->parent = this;
        }

        /**
         * Source code constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param idAST Id child of this node (should be type Ident)
         * @param eAST Init expression child of this node (should be type ASTExpr)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         * @param src Source code of related node
         */
        BlackboardDecl(ASTTerminal* idAST, std::string struct_typeAST, std::string tr_typeAST, const location& l, const std::string& f, const std::string& src) :
                struct_type(struct_typeAST),
                tr_type(tr_typeAST),
                ASTDecl(idAST, DeclType::BLACKBOARD_DECL, l, f, src) {
            idAST->parent = this;
        }

        /**
         * Virtual destructor
         *
         * Doesn't need to delete parent
         */
        virtual ~BlackboardDecl() {}

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

        std::string struct_type;
        std::string tr_type;
    };

}

#endif