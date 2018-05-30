#ifndef TR_INTERPRETER_H
#define TR_INTERPRETER_H

#include <exception>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "tr_scanner.h"
#include "tr_parser.h"
#include "tr_semantic_analyser.h"
#include "tr_executor.h"

#include "AST/ast_node.h"
#include "tr_symbol_table.h"

// blackboard structure
#include "blackboard/blackboard.h"
#include "blackboard/interfacer.h"

// runtime components
#include "exe-components/exit_tr.h"
#include "exe-components/tr_runtime_exception.h"

// built-in components
#include "AST/ident.h"
#include "AST/bi_var_decl.h"
#include "AST/bi_func_decl.h"

namespace plh = std::placeholders; // namespace shortening for placeholders
    
/**
 * Register function macro
 *
 * Used for convenience to simplify arguments given
 *
 * @param driver Reference to Interpreter object to insert into it's symbol table
 * Note: pointers to interpreter objects must be de-referenced first
 * @param name String literal name of the function as it will be used
 * in TR lang
 * @param types Type signature of the function as C++ type
 * @param ptr Function pointer of callable free function in C++
 * @throws runtime_error if it has an invalid type
 */
#define REGISTER_FUNC(driver,name,types,ptr)                    \
{                                                               \
    (driver).register_built_in(                                 \
        std::string(name),                                      \
        new TR::BIFuncDecl<types>(                              \
            new TR::Ident(std::string(name),                    \
                            TR::location(),                     \
                            std::string()                       \
                        ),                                      \
            std::function<types>(ptr)                           \
        )                                                       \
    );                                                          \
}

/**
 * Register bind function macro
 *
 * Used for member function registering and when wanting to bind
 * function parameters to a fixed variable/value. This can be usedful
 * when wanting to use a function that requires non TR Lang types.
 *
 * @param driver Reference to Interpreter object to insert into it's symbol table
 * Note: pointers to interpreter objects must be de-referenced first
 * @param name String literal name of the function as it will be used
 * in TR lang
 * @param types Type signature of the function as C++ type, for parameters
 * that are bound (i.e. not using placeholders) exclude them from the type
 * signature. All return types and placeholder types should be TR Lang types.
 * @param binders Functions, objects and parameters to bind into a TR Lang
 * function.
 * - For free functions, it requires (in order):
 *      1) function pointer
 *      2) parameter(s), fixed or placeholders
 * - For member functions, it requires (in order):
 *      1) function pointer (with scoping)
 *      2) object to call it on (pointer/reference)
 *      3) parameter(s), fixed or placeholders
 * Placeholder params are specified using unique placeholder names
 *      plh::_1, plh::_2, ..., plh::_N (limit based on compiler implementation)
 * Note: for member functions, the bound function will retain its reference
 * even after the object related to the member function is deleted, and will
 * attempt to still call it
 */
#define REGISTER_BIND_FUNC(driver,name,types,binders...)        \
{                                                               \
    (driver).register_built_in(                                 \
        std::string(name),                                      \
        new TR::BIFuncDecl<types>(                              \
            new TR::Ident(std::string(name),                    \
                            TR::location(),                     \
                            std::string()                       \
                        ),                                      \
            std::function<types>(std::bind(binders))            \
        )                                                       \
    );                                                          \
}

/**
 * Register variable macro
 *
 * Used for convenience to simplify arguments given
 *
 * @param driver Reference to Interpreter object to insert into it's symbol table
 * Note: pointers to interpreter objects must be de-referenced first
 * @param name String literal name of the variable as it will be used
 * in TR lang
 * @param type Type of the variable as C++ type
 * @param ptr Variable pointer of the memory location of the variable
 * as it is stored in C++
 * @throws runtime_error if it has an invalid type
 */
#define REGISTER_VAR(driver,name,type,ptr)                      \
{                                                               \
    (driver).register_built_in(                                 \
        std::string(name),                                      \
        new TR::BIVarDecl(                                      \
            new TR::Ident(std::string(name),                    \
                            TR::location(),                     \
                            std::string()                       \
                        ),                                      \
            TR::TypeToEnum<type>::value,                        \
            static_cast<void*>(ptr)                             \
        )                                                       \
    );                                                          \
}

namespace TR {

    class TRInterpreter {
    public:
        /**
         * Default constructor
         *
         * @throws runtime_error if interpreter fails
         */
        TRInterpreter();

        /**
         * Command line constructor
         *
         * Initialises the interpreter using command line options
         *
         * Output stream defaults to std::cout
         * Error stream defaults to std::cerr
         *
         * @param argc Number of command line arguments
         * @param argv Command line argument vector
         * @throws runtime_error if interpreter fails
         */
        TRInterpreter(int const& argc, char** const& argv);

        /**
         * Command line with stream constructor
         *
         * Initialises the interpreter using command line options
         * with specification of output streams to print to
         *
         * @param argc Number of command line arguments
         * @param argv Command line argument vector
         * @param out Output stream to print to
         * @param err Error stream to print to
         * @throws runtime_error if interpreter fails
         */
        TRInterpreter(int const& argc, char** const& argv, std::ostream& out, std::ostream& err);
        
        /**
         * Driver deconstructor
         */
        ~TRInterpreter();

        /**
         * Pre-processes TR Code
         *
         * Statically checks and optimises the code
         * before executing it.
         *
         * All built-in functions and variables should
         * be added prior to running the pre-process
         *
         * NOTE: This must be run before execution
         *
         * @throws runtime_error if interpreter fails, unless internalize throws enabled
         */
        bool pre_process();

        /**
         * Executes TR Code
         *
         * Executres stored TR code
         *
         * @throws TR_Runtime_Exception if interpreter fails, unless internalize throws enabled
         * @throws ExitTR if interpreter reaches exit statement, unless internalize throws enabled
         */
        bool execute();

        /**
         * Registers a built-in
         *
         * Registers a built-in function for the TR language
         *
         * @param name Name of the variable as will be referenced in TR lang
         * @param dAST Declaration AST node of the built in (should be type BIFuncDecl or BIVarDecl)
         */
        void register_built_in(const std::string& name, ASTDecl* dAST);
        
        /** Friend class definition to use private data/functions **/
        /// Core components
        friend class TRParser;
        friend class TRScanner;
        friend class TRSemanticAnalyser;
        friend class TRExecutor;
        /// Tools/Debug components
        friend class PrintTree;
        friend class TRHierarchy;
        friend class TRProfiler;
        friend class TRDebugger;

        /// Store the blackboard publically so can be accessed from C++
        Blackboard bb;

    private:

        // helper function for checking if a dir exists and making it if it doesn't
        void existAndMake(std::string s);

        /// Interpreter Messaging

        /**
         * Error Reporting
         *
         * Reporting error caused by a token
         *
         * @param loc Token location
         * @param reason Reason for error
         * @param token Token that caused error
         */
        inline void error(const location& loc,
                          const std::string& reason,
                          const std::string& token) {
            if (!silent) {
                interp_err << "\033[1;31m[ERROR]:" << scanner.currentFile() 
                           << ":" << loc << ": - " << reason 
                           << " - \'" << token 
                           << "\'\033[0m" << std::endl;
                success = false;
            }
        }

        /**
         * Error Reporting
         *
         * Reporting error without a token
         *
         * @param loc Token location
         * @param reason Reason for error
         */
        inline void error(const location& loc,
                          const std::string& reason) {
            if (!silent) {
                interp_err << "\033[1;31m[ERROR]:" << scanner.currentFile()
                           << ":" << loc << ": - " << reason
                           << "\033[0m" << std::endl;
                success = false;
            }
        }

        /**
         * Error Reporting
         *
         * Report an error without location or token
         *
         * @param reason Reason for error
         */
        inline void error(const std::string& reason) {
            if (!silent) {
                interp_err << "\033[1;31m[ERROR]:" << scanner.currentFile()
                           << ": - " << reason 
                           << "\033[0m" << std::endl;
                success = false;
            }
        }

        /**
         * Error Reporting
         *
         * Reporting error with AST node
         *
         * @param ast AST node related to error
         * @param reason Reason for error
         */
        inline void error(const ASTNode* ast,
                          const std::string& reason) {
            if (!silent) {
                interp_err << "\033[1;31m[ERROR]:" << ast->file
                           << ":" << ast->loc << ": - " << reason
                           << "\033[0m" << std::endl;
                success = false;
            }
        }

        /**
         * Warning Reporting
         *
         * Reporting warning with AST node
         *
         * @param ast AST node related to error
         * @param reason Reason for error
         */
        inline void warn(const ASTNode* ast,
                         const std::string& reason) {
            if ((debug_printing || verbose || warnings) && !silent) {
                interp_out << "\033[1;33m[WARNING]:" << ast->file
                           << ":" << ast->loc << ": - " << reason
                           << "\033[0m" << std::endl;
            }
        }

        /**
         * Info Output
         *
         * Outputs an information message
         *
         * @param msg Message to output
         */
        inline void info(const std::string& msg) {
            if ((debug_printing || verbose) && !silent) {
                interp_out << "[INFO]: " << msg << std::endl;
            }
        }

        /**
         * Debug Output
         *
         * Output a debug message
         *
         * @param ast AST node related to debug output
         * @param msg Message to output
         */
        inline void debug(const ASTNode* ast,
                          const std::string& msg) {
            if (debug_printing && !silent) {
                interp_out << "[DEBUG]:" << ast->file
                           << ":" << ast->loc << ": "
                           << msg << std::endl;
            }
        }

        /**
         * Debug Output
         *
         * Output a debug message
         *
         * @param l Location of related token
         * @param msg Message to output
         */
        inline void debug(const location& loc,
                          const std::string& msg) {
            if (debug_printing && !silent) {
                interp_out << "[DEBUG]:" 
                           << loc << ": "
                           << msg << std::endl;
            }
        }

        /**
         * Debug Output
         *
         * Output a debug message
         *
         * @param msg Message to output
         */
        inline void debug(const std::string& msg) {
            if (debug_printing && !silent) {
                interp_out << "[DEBUG]: " << msg << std::endl;
            }
        }
        
    private:
        /** Assosciated Components **/
        /// Scanner
        TRScanner scanner;
        /// Parser
        TRParser parser;
        /// Executer
        class TRExecutor* executor;
        /// Intermediate Representation
        ASTNode* ast;
        /// Start Node Name
        std::string start_node_name;
        /// Start Node
        ASTNode* start_node;
        /// Interfacer between blackboard on TR types
        Interfacer bbapi;

        /// Symbol Table, retains global declarations after SA
        SymbolTable* symtbl;
        /// Regression Table - used for checking regression statements
        RegressionTable* rgrtbl;
        /// Parameter table - used for 
        ParameterTable* paratbl;

        /// Reporting output streams
        std::ostream& interp_out;
        std::ostream& interp_err;

        /** Option flags **/
        /// Flag for default print, true by default
        bool non_default_print;
        /// Flag for internalising runtime errors and exit throws to driver,
        /// false by default
        bool internalise_throws;

        /** Tool flags **/
        /// Flag for drawing TR tree structure
        bool draw_tr_structure;
        /// Name of outfile for drawing
        std::string draw_tr_structure_outloc;
        /// Flag for execution profiler
        bool execution_profiler;
        /// Flag for debugger
        bool tr_debugger;

        /** Debug flags **/
        /// Debug output for scanner
        bool trace_scanning;
        /// Debug output for parser
        bool trace_parsing;
        /// Displays AST tree
        bool display_ast_tree;
        /// Flag for warnings
        bool warnings;
        /// Flag to suppress all output
        bool silent;
        /// Flag for verbose mode, if debug on, then verbose by default
        bool verbose;
        /// Allow debug printing by interpreter
        bool debug_printing;

        /// Success flag
        bool success;

        /// Pre-process flag
        bool has_pre_processed;

        /// TR library map
        std::unordered_map< std::string, bool > lib_set = {
            {"math.lib", false}, // C/C++ Math functions
            {"utility.lib", false} // Misc components and system calls
        };
    };

}

#endif
