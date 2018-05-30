/*----Copied C/C++ code----*/
%{
    #include <sys/stat.h>

	#include <cstdlib>
    #include <fstream>
    #include <iostream>
    #include <string>

	#include "tr_scanner.h"
	#include "tr_interpreter.h"
	#include "tr_parser.h"
	#include "location.hh"

    // macros for token location
    #define TOKEN_LOC loc_stack[import_stack_idx]
    #define TOKEN_PROGRESS TOKEN_LOC.step()
    #define LINE_PROGRESS TOKEN_LOC.lines(yyleng);TOKEN_LOC.step()

    // Return end token on termination instead of 0
	#define yyterminate() return TR::TRParser::make_END(TOKEN_LOC);

	// Update location with current token length after matching
	#define YY_USER_ACTION TOKEN_LOC.columns(yyleng);

%}

/*----Flex Options----*/
%option c++
%option yyclass="TRScanner"
%option prefix="TR"
/*%option nodefault*/
%option noyywrap nounput
%option stack

/*----States----*/
%x BLOCKCOMMENT
%x LINECOMMENT
%x SQ_STRING
%x DQ_STRING
%x IMPORT

/*----abbreviations----*/
digit               [0-9]
letter              [A-Za-z_]
fraction            ("."{digit}+)
exponent            (E|e)("+"|"-")?{digit}+
space               [ \t]

%%

"/*"                            { BEGIN(BLOCKCOMMENT); }
<BLOCKCOMMENT>"*/"              { BEGIN(INITIAL); }
<BLOCKCOMMENT>\n                { LINE_PROGRESS; }
<BLOCKCOMMENT>.                 { TOKEN_PROGRESS; }

"//"|"#"                        { BEGIN(LINECOMMENT); }
<LINECOMMENT>\n                 { LINE_PROGRESS; BEGIN(INITIAL); }
<LINECOMMENT>.                  { TOKEN_PROGRESS; }

\'\'                            { return TR::TRParser::make_STRING(std::string(), TOKEN_LOC); }
\'                              { BEGIN(SQ_STRING); }
<SQ_STRING>[^\']*               { return TR::TRParser::make_STRING(yytext, TOKEN_LOC); }
<SQ_STRING>\'                   { BEGIN(INITIAL); }

\"\"                            { return TR::TRParser::make_STRING(std::string(), TOKEN_LOC); }
\"                              { BEGIN(DQ_STRING); }
<DQ_STRING>[^\"]*               { return TR::TRParser::make_STRING(yytext, TOKEN_LOC); }
<DQ_STRING>\"                   { BEGIN(INITIAL); }

import                          { BEGIN(IMPORT); }
<IMPORT>{space}+                { TOKEN_PROGRESS; }
<IMPORT>[^ \t\n]+               {
                                    if(import_stack_idx >= MAX_IMPORT_DEPTH) {
                                        driver.error(TOKEN_LOC, "Import nested too deep, won't import any further", yytext);
                                    } else {
                                        import_file(yytext);
                                        BEGIN(INITIAL);
                                    }
                                }
<IMPORT>\n                      { driver.error(TOKEN_LOC, "No import file was given"); LINE_PROGRESS; BEGIN(INITIAL); }

or                              { return TR::TRParser::make_OR(TOKEN_LOC); }
and                             { return TR::TRParser::make_AND(TOKEN_LOC); }
not                             { return TR::TRParser::make_NOT(TOKEN_LOC); }
if                              { return TR::TRParser::make_IF(TOKEN_LOC); }
elif                            { return TR::TRParser::make_ELIF(TOKEN_LOC); }
else                            { return TR::TRParser::make_ELSE(TOKEN_LOC); }
achieves                        { return TR::TRParser::make_ACHIEVES(TOKEN_LOC); }
exit                            { return TR::TRParser::make_EXIT(TOKEN_LOC); }
blackboard                      { return TR::TRParser::make_BLACKBOARD(TOKEN_LOC); }
init                            { return TR::TRParser::make_INIT(TOKEN_LOC); }
once                            { return TR::TRParser::make_ONCE(TOKEN_LOC); }

VAR                             { return TR::TRParser::make_VAR(TOKEN_LOC); }
STACK                           { return TR::TRParser::make_STACK(TOKEN_LOC); }
MAP                             { return TR::TRParser::make_MAP(TOKEN_LOC); }
LIST                            { return TR::TRParser::make_LIST(TOKEN_LOC); }

INT                             { return TR::TRParser::make_INT_T(TOKEN_LOC); }
DOUBLE                          { return TR::TRParser::make_DOUBLE_T(TOKEN_LOC); }
BOOL                            { return TR::TRParser::make_BOOL_T(TOKEN_LOC); }
STRING                          { return TR::TRParser::make_STRING_T(TOKEN_LOC); }
VECTOR                          { return TR::TRParser::make_VECTOR_T(TOKEN_LOC); }

"+"                             { return TR::TRParser::make_PLUS(TOKEN_LOC); }
"-"                             { return TR::TRParser::make_MINUS(TOKEN_LOC); }
"*"                             { return TR::TRParser::make_MULT(TOKEN_LOC); }
"/"                             { return TR::TRParser::make_DIV(TOKEN_LOC); }
"<"                             { return TR::TRParser::make_LT(TOKEN_LOC); }
"<="                            { return TR::TRParser::make_LTEQ(TOKEN_LOC); }
">"                             { return TR::TRParser::make_GT(TOKEN_LOC); }
">="                            { return TR::TRParser::make_GTEQ(TOKEN_LOC); }
"=="                            { return TR::TRParser::make_EQEQ(TOKEN_LOC); }
"!="                            { return TR::TRParser::make_NOTEQ(TOKEN_LOC); }
"="                             { return TR::TRParser::make_EQ(TOKEN_LOC); }

";"                             { return TR::TRParser::make_SEMICOL(TOKEN_LOC); }
","                             { return TR::TRParser::make_COMMA(TOKEN_LOC); } 
"->"                            { return TR::TRParser::make_ARROW(TOKEN_LOC); }
":"                             { return TR::TRParser::make_COL(TOKEN_LOC); }
":-"                            { return TR::TRParser::make_BLOCK(TOKEN_LOC); }
"."                             { return TR::TRParser::make_DOT(TOKEN_LOC); }

"{"                             { return TR::TRParser::make_LCURL(TOKEN_LOC); }
"}"                             { return TR::TRParser::make_RCURL(TOKEN_LOC); }
"("                             { return TR::TRParser::make_LPAREN(TOKEN_LOC); }
")"                             { return TR::TRParser::make_RPAREN(TOKEN_LOC); }

true                            { return TR::TRParser::make_BOOL(true,TOKEN_LOC); }
false                           { return TR::TRParser::make_BOOL(false,TOKEN_LOC); }
"0x"({digit}|[a-f])+            { return TR::TRParser::make_INT(static_cast<int>(strtol(yytext, 0, 16)),TOKEN_LOC); }
{digit}({digit})*               { return TR::TRParser::make_INT(atoi(yytext),TOKEN_LOC); }
{digit}*{fraction}{exponent}?   { return TR::TRParser::make_DOUBLE(strtod(yytext,nullptr),TOKEN_LOC); }
{digit}+"."                     { return TR::TRParser::make_DOUBLE(strtod(yytext,nullptr),TOKEN_LOC); }
{digit}+"."?{exponent}          { return TR::TRParser::make_DOUBLE(strtod(yytext,nullptr),TOKEN_LOC); }
{letter}({letter}|{digit})*     { return TR::TRParser::make_ID(std::string(yytext),TOKEN_LOC); }

{space}+                        { TOKEN_PROGRESS; }
\n                              { LINE_PROGRESS; }

<<EOF>>                         { 
                                    // try go back to files if they exist
                                    if(!end_import()) {
                                        yyterminate(); 
                                    }
                                    LINE_PROGRESS; // also need to progress line if there was an import
                                }

.                               { 
                                    driver.error(TOKEN_LOC,"Unknown Token",yytext); TOKEN_PROGRESS;
                                    return TR::TRParser::make_ERROR(TOKEN_LOC); 
                                }

%%

/** Scanner Function Definitions **/

namespace TR {

    void TRScanner::init_file(std::string fn) {
        if (get_ext(fn) == "tr") {
            if (file_exists(fn)) {
                import_set.insert(get_fn(fn)); // store file in set
                setup_stream(fn);
                store_file(fn);
            } else {
                driver.error(TOKEN_LOC,"Could not find input file! Defaulting to std::cin",fn);
            }
        } else {
            driver.error(TOKEN_LOC,"Input file must be a TR source code file (\'.tr\')! Defaulting to std::cin",fn);
        }
    }

    void TRScanner::import_file(std::string rel_path) {
        // create a full path from the relative import and current path
        std::string full_path = path_stack[import_stack_idx] + rel_path;
        std::string file_name = get_fn(rel_path);
        std::string file_ext = get_ext(rel_path);
        if (import_set.count(file_name)>0) { // check set if already included
            driver.info("File already imported: \'" + file_name + "\', import will be ignored");
        } else {
            // if lib, setup to import it
            if (file_ext == "lib") {
                std::unordered_map< std::string, bool >::iterator it = driver.lib_set.find(file_name);
                if (it != driver.lib_set.end()) {
                    import_set.insert(file_name); // store file in set
                    it->second = true;
                } else {
                    driver.error(TOKEN_LOC,"Could not find TR library",full_path);
                }
            // otherwise check for tr source
            } else if (file_ext == "tr") {
                driver.debug("Trying to import: " + full_path);
                if (file_exists(full_path) && (import_stack_idx + 1) < MAX_IMPORT_DEPTH) {
                    ++import_stack_idx;
                    import_set.insert(file_name); // store file in set
                    setup_stream(full_path);
                    store_file(full_path);
                } else {
                    driver.error(TOKEN_LOC,"Could not find TR source code import file",full_path);
                }
            // otherwise error
            } else {
                driver.error(TOKEN_LOC,
                    "Could not import file extension, must be \'lib\' for TR libraries or \'tr\' for TR source code",
                    file_name);
            }
        }
    }

    bool TRScanner::end_import() {
        if (import_stack_idx == 0) {
            return false; // no more files left
        } else {
            --import_stack_idx;
            switch_streams(stream_stack[import_stack_idx],&driver.interp_out);
        }
        return true;
    }


    void TRScanner::setup_stream(std::string& fn) {
        std::istream* tmp = new std::ifstream(fn.c_str());
        clean_stream.push_back(tmp); // add created ifstream into buffer for later cleaning up
        stream_stack[import_stack_idx] = tmp;
        switch_streams(tmp,&driver.interp_out);
    }

    void TRScanner::store_file(std::string& fp) {
        std::size_t found = fp.find_last_of("/\\");
        if (found == std::string::npos) {
            path_stack[import_stack_idx] = "";
        } else {
            path_stack[import_stack_idx] = fp.substr(0, found) + '/';
        }
        fn_stack[import_stack_idx] = fp.substr(found+1);
        loc_stack[import_stack_idx] = location();
    }

    bool TRScanner::file_exists(std::string& fn) {
        struct stat buffer;   
        return (stat (fn.c_str(), &buffer) == 0); 
    }
}   