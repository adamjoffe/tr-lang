#ifndef TR_RUNTIME_EXCEPTION_H
#define TR_RUNTIME_EXCEPTION_H

#include <cstring>
#include <exception>
#include <string>

namespace TR {
	class TR_Runtime_Exception : public std::exception {
	public:

		explicit TR_Runtime_Exception (const std::string& what_arg) : TR_Runtime_Exception(what_arg.c_str()) {}
		explicit TR_Runtime_Exception (const char* what_arg) { strcat(m,"TR Runtime Exception - "); strcat(m,what_arg); }

	    virtual ~TR_Runtime_Exception() {}

	    virtual const char* what() const noexcept {
	        return m;
	    }

	private:
		char m[1024];
	};
}

#endif