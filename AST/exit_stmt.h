#ifndef EXIT_STMT_H
#define EXIT_STMT_H

#include "../exe-components/exit_tr.h"

namespace TR {

    /**
     * Exit Program Node
     *
     * Exit program node to exit program, part of terminal nodes
     * TODO: maybe take in bool literal and string literal nodes
     */
    class ExitStmt : public ASTStmt {

    public:

        /// Remove default constructor for this
        ExitStmt() = delete;

        /**
         * Tree constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param c Boolean exit success code
         * (true = success, false = failure)
         * @param l Location related token in source code
         * @param f File name of related symbol(s) in source code
         */
        ExitStmt(bool c, const location& l, const std::string& f):
            etr(ExitTR(c)), ASTStmt(l,f) {}

        /**
         * Source code constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param c Boolean exit success code
         * (true = success, false = failure)
         * @param l Location related token in source code
         * @param f File name of related symbol(s) in source code
         * @param src Source code of related node
         */
        ExitStmt(bool c, const location& l, const std::string& f, const std::string& src):
            etr(ExitTR(c)), ASTStmt(l,f,src) {}

        /**
         * Tree constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param c Boolean exit success code
         * (true = success, false = failure)
         * @param m Message for reason to exit
         * @param l Location related token in source code
         * @param f File name of related symbol(s) in source code
         */
        ExitStmt(bool c, std::string& m, const location& l, const std::string& f) :
            etr(ExitTR(c,m)), ASTStmt(l,f) {}

        /**
         * Source code constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param c Boolean exit success code
         * (true = success, false = failure)
         * @param m Message for reason to exit
         * @param l Location related token in source code
         * @param f File name of related symbol(s) in source code
         * @param src Source code of related node
         */
        ExitStmt(bool c, std::string& m, const location& l, const std::string& f, const std::string& src) :
            etr(ExitTR(c,m)), ASTStmt(l,f,src) {}

        /**
         * Virtual destructor
         *
         * Doesn't need to delete parent
         */
        virtual ~ExitStmt() {}

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

        ExitTR etr;
    };
}

#endif