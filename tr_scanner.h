#ifndef SCANNER_H
#define SCANNER_H

#include <fstream>
#include <string>
#include <unordered_set>

/* buffer stack for importing support */
// max depth of import nesting
#define MAX_IMPORT_DEPTH 10 //TODO: find appropriate size for this

/**
 * Generated Flex class name is yyFlexLexer by default. If we want to use more flex-generated
 * classes we should name them differently. See scanner.l prefix option.
 * 
 * Unfortunately the implementation relies on this trick with redefining class name
 * with a preprocessor macro. See GNU Flex manual, "Generating C++ Scanners" section
 */
#ifndef yyFlexLexerOnce
#undef yyFlexLexer
#define yyFlexLexer TRFlexLexer
#include <FlexLexer.h>
#endif


#undef YY_DECL
#define YY_DECL TR::TRParser::symbol_type TR::TRScanner::get_next_token()

#include "tr_parser.h"

namespace TR {

	// Forward declare interpreter to avoid include
	class TRInterpreter; 
	    
	class TRScanner : public yyFlexLexer {
	public:
	    TRScanner(TRInterpreter& dvr) : driver(dvr), import_stack_idx(0), code_capture(false) {
	    	// initial inputs from std::cin
	    	fn_stack[0] = "std::cin";
	    	path_stack[0] = "";
	    	loc_stack[0] = location();
	    }

		virtual ~TRScanner() {
			for (size_t i = 0; i < clean_stream.size(); ++i) {
				delete clean_stream[i];
			}
		}

		virtual TR::TRParser::symbol_type get_next_token();

		void init_file(std::string fn);

		void set_source_code_capture(bool f) { code_capture = f; }

		inline const std::string& currentFile() {
			return fn_stack[import_stack_idx];
		}

		inline const bool is_capturing() {
			return code_capture;
		}

		// Debug
	    inline std::string disp_imports() {
	    	std::string s;
	    	int i = 0;
	    	for (auto it = import_set.begin(); it != import_set.end(); ++it) {
	    		s += *it;
	    		++i;
	    		if (i < import_set.size()) {
	    			s += ", ";
	    		}
	    	}
	    	return s;
	    }

	private:
		/**
		 * Imports a File
		 *
		 * Takes a relative path and switches stream to read new file while 
		 * storing previous read files, streams and locations
		 *
		 * @param rel_path Relative path of file to import
		 */
		void import_file(std::string rel_path);

		/**
		 * Ends Import
		 *
		 * Finishes an import, if one exists, restoring previous state of
		 * files, streams and locations
		 *
		 * @return Returns false if no more files to pop
		 */
		bool end_import();

		/**
		 * Sets Up New Read Stream
		 * 
		 * Takes an absolute file path and sets up a read stream for the scanner
		 * to start reading from instead of previous. Also stores previous stack in stack
		 *
		 * @param fn Absolute file path of file to switch stream from
		 */
		void setup_stream(std::string& fn);

		/**
		 * Stores Previous File and Location
		 * 
		 * Takes an absolute file path and stores previous files, path and location 
		 * in stack for after import finished
		 *
		 * @param fn Absolute file path of file to switch stream from
		 */
		void store_file(std::string& fp);

		/**
		 * Checks if a File Exists
		 *
		 * @param fn Full path to file
		 * @return True if file exists
		 */
		bool file_exists(std::string& fn);

		/**
		 * Extracts filename from path
		 *
		 * @param fp Relative/Full path to file
		 * @return Filename
		 */
	    inline std::string get_fn(std::string& fp) {
	        return fp.substr(fp.find_last_of("/\\")+1);
	    }

	    /**
	     * Gets file extension
	     *
	     * @param fp Relative/Full path to file
	     * @param File extension
	     */
	    inline std::string get_ext(std::string& fp) {
	    	return fp.substr(fp.find_last_of(".")+1);
	    }
	        
	private:
	    TRInterpreter& driver;

	    /** Used for tracking import stack **/
	    size_t import_stack_idx;
	    std::istream* stream_stack[MAX_IMPORT_DEPTH]; // streams will need to be allocated heap memory
	    location loc_stack[MAX_IMPORT_DEPTH];
		std::string fn_stack[MAX_IMPORT_DEPTH];
		std::string path_stack[MAX_IMPORT_DEPTH];

		/// Used for cleaning heap allocated to import files
		std::vector<std::istream*> clean_stream;

		/// Source capturing
		bool code_capture;

		/// Import guard map
		// Stores filename of all imported files to avoid double import
		std::unordered_set< std::string > import_set;
	};
}

#endif