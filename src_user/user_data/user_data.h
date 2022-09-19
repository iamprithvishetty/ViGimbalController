#ifndef USER_DATA_H_
#define USER_DATA_H_

#include "imu_access.h"
#include "madgwick.h"
#include "motor_access.h"
#include "pid_access.h"

extern imu_accessor imu_cam;
extern imu_accessor imu_platform;

extern madgwick_filter madgwick_cam;
extern madgwick_filter madgwick_platform;

extern motor_accessor motor_pitch;
extern motor_accessor motor_roll;
extern motor_accessor motor_yaw;

extern pid_accessor pid_pitch_rotation;
extern pid_accessor pid_roll_rotation;
extern pid_accessor pid_yaw_rotation;

extern pid_accessor pid_pitch_angle;
extern pid_accessor pid_roll_angle;

extern float user_pitch_angle;
extern float user_roll_angle;

extern int imu_platform_enable;

extern float resistor_up;
extern float resistor_down;

extern float battery_voltage_alpha;
extern float battery_voltage;

extern bool debug;

#endif

