#ifndef DRIVE_CONTROL_H
#define DRIVE_CONTROL_H

#include <chrono>
#include <thread>

#include "ev3dev-lang-cpp/ev3dev.h"

class DriveControl {
public:
	DriveControl() = delete;
	DriveControl(const char mleft[], const char mright[], const char mhead[]) :
		_motor_left(mleft), _motor_right(mright), _motor_head(mhead) {}
	~DriveControl() { reset(); }

	// drive forward at speed, for X time
	void drive(int speed, int time=0);
	// turn a relative fixed direction
	void turn(int direction);
	// turn head a relative fixed direction
	void turn_head(int direction);
	// stop driving
	void stop_drive();
	// stop head rotation
	void stop_head();
	// reset motors
	void reset();

private:
	ev3dev::large_motor     _motor_left;
	ev3dev::large_motor     _motor_right;
	ev3dev::medium_motor	_motor_head;

};

#endif