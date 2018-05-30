#include "sensor_control.h"

bool SensorControl::is_left_touched() {
	return _touch_left.is_pressed();
}

bool SensorControl::is_right_touched() {
	return _touch_right.is_pressed();
}

float SensorControl::distance() {
	return _ultrasonic_sensor.distance_centimeters();
}

bool SensorControl::is_alone() {
	return !_ultrasonic_sensor.other_sensor_present();
}

int SensorControl::rot_angle() {
	return _gyro_sensor.angle();
}

int SensorControl::rot_rate() {
	return _gyro_sensor.rate();
}