#ifndef EXIT_TR_H
#define EXIT_TR_H

namespace TR {
	
	/**
	 * Throw object to exit gracefully
	 */
	struct ExitTR {
		ExitTR(bool c) : code(c), msg("") {}
		ExitTR(bool c, std::string& m) : code(c), msg(m) {}

	    bool code; /**Success code, true if success, false if failure**/
	    std::string msg; /**Message related to exit**/
	};
}

#endif