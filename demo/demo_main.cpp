#include <exception>
#include <iostream>

#include "../tr_interpreter.h"
#include "drive_control.h"
#include "sensor_control.h"

int main(int argc, char **argv) {

    int interpArgc = 4;
    char** interpArgv = new char*[interpArgc];

    // set debug
    interpArgv[0] = (char*)"-x";
    interpArgv[1] = (char*)"-l";
    interpArgv[2] = (char*)"0";
    interpArgv[3] = (char*)"demo.tr";

  	TR::TRInterpreter* interp;
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

    DriveControl mcontroller(ev3dev::OUTPUT_C,ev3dev::OUTPUT_B,ev3dev::OUTPUT_A);

    REGISTER_BIND_FUNC(*interp,"drive",void(int,int),&DriveControl::drive,&mcontroller,plh::_1,0);
    REGISTER_BIND_FUNC(*interp,"drive_time",void(int,int),&DriveControl::drive,&mcontroller,plh::_1,plh::_2);
    REGISTER_BIND_FUNC(*interp,"turn",void(int),&DriveControl::turn,&mcontroller,plh::_1);
    REGISTER_BIND_FUNC(*interp,"turn_head",void(int),&DriveControl::turn_head,&mcontroller,plh::_1);
    REGISTER_BIND_FUNC(*interp,"stop_drive",void(void),&DriveControl::stop_drive,&mcontroller);
    REGISTER_BIND_FUNC(*interp,"stop_head",void(void),&DriveControl::stop_head,&mcontroller);
    REGISTER_BIND_FUNC(*interp,"reset",void(void),&DriveControl::reset,&mcontroller);

    SensorControl scontroller(ev3dev::INPUT_2,ev3dev::INPUT_1,ev3dev::INPUT_4,ev3dev::INPUT_3);

    REGISTER_BIND_FUNC(*interp,"is_left_touched",bool(void),&SensorControl::is_left_touched,&scontroller);
    REGISTER_BIND_FUNC(*interp,"is_right_touched",bool(void),&SensorControl::is_right_touched,&scontroller);
    REGISTER_BIND_FUNC(*interp,"distance_from",float(void),&SensorControl::distance,&scontroller);
    REGISTER_BIND_FUNC(*interp,"distance_from",bool(void),&SensorControl::is_alone,&scontroller);
    REGISTER_BIND_FUNC(*interp,"rot_angle",int(void),&SensorControl::rot_angle,&scontroller);
    REGISTER_BIND_FUNC(*interp,"rot_rate",int(void),&SensorControl::rot_rate,&scontroller);

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
