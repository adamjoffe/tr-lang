#include <fstream>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>

#include <boost/program_options.hpp>

// Base include and AST
#include "tr_interpreter.h"
#include "AST/abstract_visitor.h"

// debug printing
#include "tools/print_tree.h"

// tr hierarchy display
#include "tools/tr_hierarchy.h"

/// Execution attachables
// tr profiler
#include "tools/tr_profiler.h"
// tr debugger
#include "tools/tr_debugger.h"

// includes for TR libs
#include <cmath>
#include <cstdlib>
#include <ctime>

// convert for short name spacing
namespace po = boost::program_options;

namespace TR {

    TRInterpreter::TRInterpreter() : TRInterpreter(0, nullptr) {}

    TRInterpreter::TRInterpreter(int const& argc, char** const& argv) : 
        TRInterpreter(argc, argv, std::cout, std::cerr) {}

    TRInterpreter::TRInterpreter(int const& argc, char** const& argv, std::ostream& out, std::ostream& err) :
        scanner(*this), parser(scanner, *this), executor(new TRExecutor(*this)),
        ast(nullptr), start_node(nullptr), bbapi(bb),
        symtbl(new SymbolTable()), rgrtbl(new RegressionTable()), paratbl(new ParameterTable()),
        interp_out(out), interp_err(err),
        non_default_print(false), internalise_throws(false),
        draw_tr_structure(false), execution_profiler(false), tr_debugger(false),
        trace_scanning(false), trace_parsing(false), display_ast_tree(false),
        warnings(false), silent(false), verbose(false), debug_printing(false),
        success(true), has_pre_processed(false) {

        /** Generic options **/
        po::options_description generic_options("Generic Options");
        generic_options.add_options()
                ("help,h", "Display help message")
                ("starting-node,e", po::value<std::string>(&start_node_name)->default_value("main"), 
                    "TR-Node name used as entrance to program.\n"
                    "Default is \'main\'")  
                ("non-default-print,n", "Turns off default printing function for TR Lang.\n"
                    "User required to supply own printing function.")
                ("intern-throw,T", "Internalize error and exit throws to the driver");

        /** Tools options **/
        po::options_description tools_options("Tools Options");
        tools_options.add_options()
                ("draw-tree,t", "Draws the structure of the TR tree implied by TR code")
                ("execution-profiler,l", po::value<int>()->implicit_value(0),
                    "Profiles execution time and number of executions for TR code.\n"
                    "Optionally, a number for the yield rate of the profiler can be given\n"
                    "Default is \'0\', meaning only yields after final execution")
                ("tr-debugger,X", "Activates TR-Debugger output which provides information for debugging");

        /** Debug options **/
        po::options_description debug_options("Debug Options");
        debug_options.add_options()
                ("scanner-trace,S", "Allows debugging trace for scanner")
                ("parser-trace,P", "Allows debugging trace for parser")
                ("display-ast-tree,D", "Prints the AST tree after parsing.\n"
                    "Warning: for large files output will be verbose")
                ("warnings,W", "Turns on additional warnings")
                ("silent,s", "Allows silencing of interpreter output")
                ("verbose,v", "Allows verbose output of interpreter")
                ("debug,x", "Allows debug output of interpreter");

        /** Hidden options **/
        po::options_description hidden_options("Hidden Options");
        hidden_options.add_options()
                ("input-file", po::value<std::string>(), "Input files to run")
                ("execution-profiler-outloc", po::value<std::string>(), "Execution profiler output location")
                ("tr-debugger-outloc", po::value<std::string>(), "TR debugger output location")
                ("tr-structure-drawer-outloc", po::value<std::string>(&draw_tr_structure_outloc)->default_value("./"), "TR hierarchy drawer output location");

        // All options available
        po::options_description all("Options");
        all.add(generic_options).add(tools_options).add(debug_options).add(hidden_options);

        // Options visible to user
        po::options_description visible("Options");
        visible.add(generic_options).add(tools_options).add(debug_options);

        // positional argument for input file
        po::positional_options_description p;
        p.add("input-file", -1);

        po::variables_map vm;
        // store commmand line options
        po::store(po::command_line_parser(argc, argv).
                options(all).positional(p).run(), vm);
        // store config file options
        std::ifstream cfgfile("user-customisation/out_files.cfg");
        po::store(po::parse_config_file(cfgfile, all), vm);
        cfgfile.close();
        // notify the variable map
        po::notify(vm);

        /** Help Handling **/
        if (vm.count("help")) {
            interp_out << "Usage: TR-Lang <filename> [generic-options] [tool-options] [debug-options]" 
                        << std::endl << std::endl;
            interp_out << visible << std::endl;
            // hard exit with success since only "help" display was wanted
            exit(EXIT_SUCCESS);
        }

        /** Generic Option Handling **/
        if (vm.count("non-default-print")) {
            non_default_print = true;
        }
        if (vm.count("intern-throw")) {
            internalise_throws = true;
        }

        /** Tools Option Handling **/
        if (vm.count("draw-tree")) {
            draw_tr_structure = true;
            // default outloc if blank
            if (draw_tr_structure_outloc == "") {
                draw_tr_structure_outloc = "./";
            }
        }
        // profiler setup if chosen
        if (vm.count("execution-profiler")) {
            execution_profiler = true;
            TRProfiler* prof = nullptr;
            // make profiler from cfg file
            std::string loc;
            if (vm.count("execution-profiler-outloc") && vm["execution-profiler-outloc"].as<std::string>() != "") {
                loc = vm["execution-profiler-outloc"].as<std::string>();
            // if profiler output wasn't specified, default to same as interpreter
            } else {
                loc = "./";
            }
            prof = new TRProfiler(*this, loc, vm["execution-profiler"].as<int>());
            executor->attach_profiler(prof);
        }
        // debugger setup if chosen
        if (vm.count("tr-debugger")) {
            tr_debugger = true;
            TRDebugger* dbg = nullptr;
            // make debugger from cfg file
            std::string loc;
            if (vm.count("tr-debugger-outloc") && vm["tr-debugger-outloc"].as<std::string>() != "") {
                loc = vm["tr-debugger-outloc"].as<std::string>();
            // if debugger output wasn't specified, default to same as interpreter
            } else {
                loc = "./";
            }
            dbg = new TRDebugger(*this, loc);
            executor->attach_debugger(dbg);
        }

        /** Debug Option Handling **/
        if (vm.count("scanner-trace")) {
            trace_scanning = true;
        }
        if (vm.count("parse-trace")) {
            trace_parsing = true;
        }
        if (vm.count("display-ast-tree")) {
            display_ast_tree = true;
            debug_printing = true; // has to be enabled to display tree
        }
        if (vm.count("warnings")) {
            warnings = true;
        }
        if (vm.count("silent")) {
            silent = true;
        }
        if (vm.count("verbose")) {
            verbose = true;
        }
        if (vm.count("debug")) {
            debug_printing = true;
        }

        // check for source file if given
        if (vm.count("input-file")) {
            scanner.init_file(vm["input-file"].as<std::string>());
        }

        // set scanner/parser debug state
        scanner.set_debug(trace_scanning);
        parser.set_debug_level(trace_parsing);

        // set source code capture if needed
        scanner.set_source_code_capture(execution_profiler||tr_debugger);

        // return succes status from parser
        info("Parsing file: " + scanner.currentFile());
        success = !parser.parse(); // inverse cause success = 0

        // debug use for importing
        debug("import list: " + scanner.disp_imports());

        // check error success
        if(!success) {
            this->error("TRInterpreter has failed during parsing! See above errors.");
            throw std::runtime_error("TRInterpreter has failed during parsing! See above errors.");
        }

        // check AST tree
        if (display_ast_tree) {
            info("===========AST TREE===========");
            PrintTree pt(*this);
            pt.print_tree();
        }
    }

    TRInterpreter::~TRInterpreter() {
        delete ast;
        delete start_node; // not necissarily required
        delete symtbl;
        delete rgrtbl;
        delete paratbl;
        delete executor;
    }

    bool TRInterpreter::pre_process() {

        if (has_pre_processed) {
            throw std::runtime_error("TR Interpreter has already pre-processed, shouldn't do it again.");
        }

        // Default printing
        if (!non_default_print) {
            info("Using default printing function");
            REGISTER_BIND_FUNC(*this,"print",void(std::string),
                [](TRInterpreter* interp, std::string s){ interp->interp_out << s << std::endl; },
                this,
                plh::_1);
        }

        // Include TR math
        if (lib_set.find("math.lib")->second) {
            debug("math.lib has been included");
            #include "libs/tr_lib.math.h"
        }

        // Include TR utility
        if (lib_set.find("utility.lib")->second) {
            debug("utility.lib has been included");
            #include "libs/tr_lib.utility.h"
        }

        info("Statically checking code");
        TRSemanticAnalyser semanticAnalyser(*this);
        semanticAnalyser.analyse();

        if (!success) {
            if (internalise_throws) {
                error("TR Interpreter has failed during static analysis! See above errors.");
                return false;
            } else {
                throw std::runtime_error("TR Interpreter has failed during static analysis! See above errors.");
            }
        }
        
        // check tables are valid
        info((symtbl->validate() ? "Symbol table validated" : "Symbol table not validated"));
        info((rgrtbl->validate() ? "Regression table validated" : "Regression table not validated"));

        has_pre_processed = true;

        if (draw_tr_structure) {
            info("Outputting TR tree structure");
            TRHierarchy hierarchy(*this, draw_tr_structure_outloc);
            hierarchy.print_hierarchy();
        }

        return true;
    }

    bool TRInterpreter::execute() {

        if (!has_pre_processed) {
            throw std::runtime_error("TR Interpreter has not pre-processed, it must be run first");
        }

        try {
            executor->execute();
            // done as debug since otherwise it would occur every loop/execution call
            debug((paratbl->validate() ? "Parameter table validated" : "Parameter table not validated"));
            return true;
        } catch (ExitTR& e) {
            if (internalise_throws) {
                interp_out << "[EXIT]: TR program has exited with success code: "
                          << (e.code ? "SUCCESS" : "FAILURE")
                          << (e.msg == "" ? "" : " - \'" + e.msg + "\'")
                          << std::endl;
                return false;
            } else {
                throw;
            }
        } catch (TR_Runtime_Exception& e) {
            if (internalise_throws) {
                error(e.what());
                return false;
            } else {
                throw;
            }
        }
    }
    
    void TRInterpreter::register_built_in(const std::string& name, ASTDecl* dAST) {
        symtbl->insert(name, dAST);
    }

    void TRInterpreter::existAndMake(std::string s) {
        struct stat info;
        std::size_t found = s.find_last_of("/\\");
        std::string path;
        if (found == std::string::npos) {
            path = "";
        } else {
            path = s.substr(0, found) + '/';
        }
        // make the directory if it doesn't exist
        if ( stat( path.c_str(), &info ) != 0 || !(info.st_mode & S_IFDIR)) {
            // mkdir, using linux specific
            if (system(("mkdir " + path).c_str()) != 0) {
                throw std::runtime_error("TRInterpreter failed, no directory: " + path);
            }
        }
    }
}
