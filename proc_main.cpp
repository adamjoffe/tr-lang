#include <exception>
#include <iostream>
#include <mutex>

#include "tr_interpreter.h"

// flag to check that process is still healthy
bool healthy = true;
// mutex lock on healthy
std::mutex healthy_mutex;

// global interpreter
TR::TRInterpreter* interp;
// mutex lock on interp
std::mutex interp_mutex;

bool executeInterp();
void welcomeSocket();
void commHandler();

int main(int argc, char **argv) {

    int interpArgc;
    char** interpArgv = new char*[interpArgc];

    // if args are given already, otherwise use hard coded set
    if (argc) {
    	interpArgc = argc;
    	interpArgv = argv;
    } else {
    	interpArgc = 4;

	    // set debug
	    interpArgv[0] = (char*)"-x";
	    interpArgv[1] = (char*)"-l";
	    interpArgv[2] = (char*)"0";
	    interpArgv[3] = (char*)"demo/demo.tr";
    }

    // Construction (AST creation)
   	try {
   		interp = new TR::TRInterpreter(interpArgc, interpArgv);
   	} catch (std::exception& e) {
        std::cerr << "ERROR: " << e.what()
                  << std::endl << std::endl;
        return -1;
   	}

    /**#################################################**/
    /** BUILT IN SECTION **/
    /**#################################################**/

    /**#################################################**/
    /** BLACKBOARD SECTION **/
    /**#################################################**/

    // Pre-process (Static analysis and optimisation)
    try {
        interp->pre_process();
    } catch (std::exception& e) {
        std::cerr << "ERROR: " << e.what()
                  << std::endl << std::endl;
        return -1;
    }

    // initial execution
    bool is_success = executeInterp();

    // if initial execution succeded, then fork the welcome thread, otherwise exit
    if (is_success) {
    	// call welcome socket
    	welcomeSocket();
    }

	return 0;
}

// trigger execution
bool executeInterp() {
	try {
		return interp->execute();
	}  catch (TR::ExitTR& e) {
        std::cout << "[EXIT]: TR program has exited with success code: "
                  << (e.code ? "SUCCESS" : "FAILURE")
                  << (e.msg == "" ? "" : " - \'" + e.msg + "\'")
                  << std::endl;
        return false;
    } catch (TR::TR_Runtime_Exception& e) {
        std::cerr << "[ERROR]: " << e.what()
                  << std::endl << std::endl;
        return false;
    } catch (std::exception& e) {
        std::cerr << "UNCAUGHT ERROR!: " << e.what()
                  << std::endl << std::endl;
        return false;
    }
}

// welcome thread
void welcomeSocket() {
	// start welcome socket

	// loop until finished
	while (true) {
		// check healthy, break loop if its not healthy
		{
			std::lock_guard<std::mutex> lock(healthy_mutex);
			if (!healthy) {
				break; // stop loop
			}
		}

		// when new socket opened, fork into new thread
	}

	// join threads and return
}

// read/write blackboard thread
void commHandler() {

	while (true) {
		// wait for set/request message

		// if set message, update blackboard and executre TR again
		{
			// lock the mutex
			std::lock_guard<std::mutex> lock(interp_mutex);

			// execute TR after the change
			bool is_success = executeInterp();

			// if fail, trigger all other threads to send exit messages to other processes and 
			if (!is_success) {
				std::lock_guard<std::mutex> lock(healthy_mutex);
				healthy = false;
				break; // stop loop
			}
		}

		// if request, send requested data to other process
	}

	// send exit message and return
}