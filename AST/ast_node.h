#ifndef AST_NODE_H
#define AST_NODE_H

#include <ctime> // used for profiler
#include <memory> // used for all other nodes
#include <time.h>

#include "../location.hh"

// forward declaration of Visitor
namespace TR { 
    class Visitor;
}

namespace TR {

    /**
     * Abstract Node Class
     *
     * Abstract node class for all nodes to implement
     * visitor pattern for tree walking
     */
    class ASTNode {

    public:

        /// Remove default constructor for this
        ASTNode() = delete;

        /**
         * Location constructor
         *
         * Constructs AST node with a location in the source code
         *
         * @param l Location of related symbol(s) in source code
         * @param f File name of related symbol(s) in source code
         */
        ASTNode(const location& l, const std::string& f) : loc(l), file(f) {}

        /**
         * Source code constructor
         *
         * Constructs AST node with a location and file to retrieve source
         *
         * @param l Location of related symbol(s) in source code
         * @param f File name of related symbol(s) in source code
         * @param src Source code of related node
         */
        ASTNode(const location& l, const std::string& f, const std::string& src) : loc(l), file(f), src_code(src) {}

        /**
         * Virtual destructor
         *
         * Doesn't need to delete parent
         */
        virtual ~ASTNode() {};

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

        /// Parent of this node
        ASTNode* parent; // use raw pointer for this since destruction not required
        const location loc; // parser location of related token
        const std::string file; // scanner file of related token

        /// Tool components
        std::string src_code; // stores the related source code for this node

        // profiler components
        int count = 0; // number of times node executed
        clock_t exe_time = 0; // accumilative time node has executed for
        clock_t tmp_c; // temp clock count to use for timing

        // debug components
    };

}

#endif