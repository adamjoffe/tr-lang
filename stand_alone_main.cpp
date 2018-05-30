#include <exception>
#include <iostream>

#include "tr_interpreter.h"

int main(int argc, char **argv) {

  	TR::TRInterpreter* interp;
    // Construction (AST creation)
   	try {
   		interp = new TR::TRInterpreter(argc, argv);
   	} catch (std::exception& e) {
        std::cerr << "ERROR: " << e.what()
                  << std::endl << std::endl;
        return -1;
   	}

    /**#################################################**/
    /** BUILT IN SECTION **/
    /**
     * Examples:
     *
     * +-+-+ FUNCTIONS +-+-+
     *
     * // Basic function registering
     * REGISTER_FUNC(*interp,"sin",double(double),&sin);
     * REGISTER_FUNC(*interp,"tan2",double(double,double),&tan2);
     *
     * // placeholder binding
     * REGISTER_BIND_FUNC(*interp,"cos",double(double),&cos,plh::_1);
     *
     * // fix 1 parameter, placeholder for other
     * REGISTER_BIND_FUNC(*interp,"tan2",double(double),&tan2,1.1,plh::_1);
     *
     * // member function binding
     * class A {
     * public:
     *  void display(int val) { std::cout << "My number = " << val << std::endl; }
     * };
     * A displayer;
     * REGISTER_BIND_FUNC(*interp,"display",void(int),&A::display,&displayer,plh::_1);
     * !!!Note: deleting the related object will make the function unusable!!!
     *
     * // lambda wrapping, allows using vector from TR Lang
     * //(Note: can't use captures, as current context irrelevent)
     * std::vector<int> vec;
     * REGISTER_BIND_FUNC(*interp,"vec_push_back",void(int),
     *  [](std::vector<int>* vec, int val){ vec->push_back(val); },
     *  &vec,plh::_1);
     * REGISTER_BIND_FUNC(*interp,"vec_get",int(int),
     *  [](std::vector<int>* vec, int idx){ return vec->at(idx); },
     *  &vec,plh::_1);
     *
     *  ############################################################
     *
     * +-+-+ VARIABLES +-+-+
     *
     * // Variable registering
     * int alpha = 0;
     * REGISTER_VAR(*interp,"alpha",int,&alpha);
     * double beta = 1.2;
     * REGISTER_VAR(*interp,"beta",double,&beta);
     *
     * // Member data
     * // Note: have to be careful with deleting objects
     * // that contain variables used as built-ins
     * class D {
     * public:
     *  D() : val(7) {}
     *  int val;
     * };
     * D data;
     * REGISTER_VAR(*interp,"data",int,&data.val);
     */
    /**#################################################**/

    double alpha = 0;
    REGISTER_VAR(*interp,"alpha",double,&alpha);

    int myCount = 0;
    REGISTER_VAR(*interp,"myCount",int,&myCount);

    REGISTER_BIND_FUNC(*interp,"getVal",int(void),[](){ return 14; });

    REGISTER_BIND_FUNC(*interp,"myBool",bool(void),[](){ return false; });

    REGISTER_BIND_FUNC(*interp,"useFloat",float(float),[](float f){ std::cout << f << std::endl; return f; }, plh::_1);

    /**#################################################**/
    /** BLACKBOARD SECTION **/
    /**
     * Examples:
     *
     * // Add new modules
     * interp->bb.add_module("visionmodule","Stores vision data take from the camera");
     * OR
     * DataModule dm("visionmodule","Stores vision data take from the camera");
     * interp->bb.add_module("visionmodule",dm);
     *
     * // Add new frames
     * interp->bb[TRMODULE].add_struct("prevlocation", new StackFrame<int>());
     * 
     * // Using frames
     * interp->bb[TRMODULE]["prevlocation"]->insert<int>(1);
     * std::cout << interp->bb[TRMODULE]["prevlocation"]->get<int>() std::endl;
     */
    /**#################################################**/

    // Pre-process (Static analysis and optimisation)
    try {
        interp->pre_process();
    } catch (std::exception& e) {
        std::cerr << "ERROR: " << e.what()
                  << std::endl << std::endl;
        return -1;
    }

    // Execute (Run the TR code)
    bool is_success = true;
    while (is_success) {
        try {
            is_success = interp->execute();
        } catch (TR::ExitTR& e) {
            std::cout << "[EXIT]: TR program has exited with success code: "
                      << (e.code ? "SUCCESS" : "FAILURE")
                      << (e.msg == "" ? "" : " - \'" + e.msg + "\'")
                      << std::endl;
            is_success = false;
        } catch (TR::TR_Runtime_Exception& e) {
            std::cerr << "[ERROR]: " << e.what()
                      << std::endl << std::endl;
            return -1;
        } catch (std::exception& e) {
            std::cerr << "UNCAUGHT ERROR!: " << e.what()
                      << std::endl << std::endl;
            return -1;
        }
    }

   	//delete interp; // this causes failure on long exit statment messages for some reason

    return 0;
}
