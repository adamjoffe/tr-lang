#include "drive_control.h"

void DriveControl::DriveControl::drive(int speed, int time) {
  	_motor_left.set_speed_sp(-speed);

  	_motor_right.set_speed_sp(-speed);

  	if (time > 0) {
		_motor_left .set_time_sp(time).run_timed();
		_motor_right.set_time_sp(time).run_timed();

		while (_motor_left.state().count("running") || _motor_right.state().count("running"))
			std::this_thread::sleep_for(std::chrono::milliseconds(10));

  	} else {
		_motor_left.run_forever();
		_motor_right.run_forever();
  	}
}

void DriveControl::turn(int direction) {

	stop_drive();

	if (direction == 0)
	return;

	_motor_left. set_position_sp( direction).set_speed_sp(500).run_to_rel_pos();
	_motor_right.set_position_sp(-direction).set_speed_sp(500).run_to_rel_pos();

	while (_motor_left.state().count("running") || _motor_right.state().count("running"))
		std::this_thread::sleep_for(std::chrono::milliseconds(10));

}

void DriveControl::turn_head(int direction) {

	stop_head();

	if (direction == 0)
	return;

	_motor_head.set_position_sp(direction).set_speed_sp(500).run_to_rel_pos();

	while (_motor_head.state().count("running"))
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void DriveControl::stop_drive() {

	_motor_left .stop();
	_motor_right.stop();

}

void DriveControl::stop_head() {

	_motor_head.stop();

}

void DriveControl::reset() {
	if (_motor_left.connected()) {
		_motor_left.reset();
	}

	if (_motor_right.connected()) {
		_motor_right.reset();
	}

	if (_motor_head.connected()) {
		_motor_head.reset();
	}
}