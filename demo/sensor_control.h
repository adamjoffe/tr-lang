#ifndef SENSOR_CONTROL_H
#define SENSOR_CONTROL_H

#include "ev3dev-lang-cpp/ev3dev.h"

class SensorControl {
public:
	SensorControl() = delete;
	SensorControl(const char tleft[], const char tright[], const char usonic[], const char gyro[]) :
		_touch_left(tleft), _touch_right(tright), _ultrasonic_sensor(usonic), _gyro_sensor(gyro) {}
	~SensorControl() { }

	// whether sensors are triggered or not
	bool is_left_touched();
	bool is_right_touched();
	// distance from object in cm
	float distance();
	// if any other ultrasonic sensors nearby
	bool is_alone();
	// robot rotational angle
	int rot_angle();
	// robot rotational rate
	int rot_rate();

private:
	ev3dev::touch_sensor     	_touch_left;
	ev3dev::touch_sensor     	_touch_right;
	ev3dev::ultrasonic_sensor	_ultrasonic_sensor;
	ev3dev::gyro_sensor			_gyro_sensor;

};

#endif