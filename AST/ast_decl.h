#ifndef AST_DECL_H
#define AST_DECL_H

// only included here for symbol table and built-ins
#include "ast_node.h" 
#include "ast_terminal.h"

#include "../tr_types.h"

namespace TR {

    /// Enum for type of declaration
    //TODO: potentially remove this in favour of dynamic casting
    enum class DeclType { VAR_DECL, FUNC_DECL, TR_DECL, PARA_DECL,
                    BIFUNC_DECL, BIVAR_DECL, BLACKBOARD_DECL, ONCE_DECL };

    /**
     * Abstract Declaration Class
     *
     * Abstract declaration implements nodes that declare parts
     * of the program
     */
    class ASTDecl : public ASTNode {

    public:

        /// Remove default constructor for this
        ASTDecl() = delete;

        /**
         * Location constructor
         *
         * Constructs AST node with a location in the source code
         *
         * @param idAST Identifier related to declaration (should be type Ident)
         * @param declT Declaration type enum of the declaration
         * @param l Location of related symbol(s) in source code
         * @param f File name of related symbol(s) in source code
         */
        ASTDecl(ASTTerminal* idAST, DeclType declT, const location& l, const std::string& f) :
                t(Type::NULL_T),
                id(idAST),
                dt(declT),
                ASTNode(l,f) {}

        /**
         * Source code constructor
         *
         * Constructs AST node with a location and file to retrieve source
         *
         * @param idAST Identifier related to declaration (should be type Ident)
         * @param declT Declaration type enum of the declaration
         * @param l Location of related symbol(s) in source code
         * @param f File name of related symbol(s) in source code
         * @param src Source code of related node
         */
        ASTDecl(ASTTerminal* idAST, DeclType declT, const location& l, const std::string& f, const std::string& src) :
                t(Type::NULL_T),
                id(idAST),
                dt(declT),
                ASTNode(l,f,src) {}

        /**
         * Virtual destructor
         *
         * Doesn't need to delete parent
         */
        virtual ~ASTDecl() {}

        /**
         * Visit Function
         *
         * All nodes must implement this function
         * See Visitor Pattern
         *
         * @param v Pointer to the visitor object
         * @param n Optional pointer to AST node
         * @return Optionally returns a pointer to an AST node
         */
        virtual ASTNode* visit(Visitor* v, ASTNode* n) = 0;

        Type t; /// Not defined until after semantic pass done
                /// except for built ins
        std::shared_ptr<ASTTerminal> id;
        DeclType dt;
    };

}

#endif
