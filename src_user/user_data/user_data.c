#include "hal.h"
#include "imu_access.h"
#include "madgwick.h"
#include "motor_access.h"
#include "pid_access.h"

imu_accessor imu_cam = {

  .i2c_driver = &I2CD2,
  .id = ID_MPU6050,
  .mount = MOUNT_CAMERA,
  .imu_addr = 0x68,
  .orientation = 1,
  .gyro_scale_factor = 0.0f,
  .accel_scale_factor = 0.0f,
  .gyro_bias_x = 0,
  .gyro_bias_y = 0,
  .gyro_bias_z = 0,
  .accel_bias_x = 0,
  .accel_bias_y = 0,
  .accel_bias_z = 0,
  .is_initialized = false

};
imu_accessor imu_platform = {

  .i2c_driver = &I2CD1,
  .id = ID_MPU6050,
  .mount = MOUNT_PLATFORM,
  .imu_addr = 0x69,
  .orientation = 1,
  .gyro_scale_factor = 0.0f,
  .accel_scale_factor = 0.0f,
  .gyro_bias_x = 0,
  .gyro_bias_y = 0,
  .gyro_bias_z = 0,
  .accel_bias_x = 0,
  .accel_bias_y = 0,
  .accel_bias_z = 0,
  .is_initialized = false

};

madgwick_filter madgwick_cam;
madgwick_filter madgwick_platform;

motor_accessor motor_pitch = {

  .line[0] = {CHANNEL_2, &PWMD3},
  .line[1] = {CHANNEL_3, &PWMD3},
  .line[2] = {CHANNEL_4, &PWMD3},

  .power = 40,
  .pole_pair = 7,
  .direction = CLOCKWISE,

};
motor_accessor motor_roll = {

  .line[0] = {CHANNEL_3, &PWMD2},
  .line[1] = {CHANNEL_4, &PWMD2},
  .line[2] = {CHANNEL_1, &PWMD3},

  .power = 50,
  .pole_pair = 7,
  .direction = CLOCKWISE,

};
motor_accessor motor_yaw = {

  .line[0] = {CHANNEL_2, &PWMD2},
  .line[1] = {CHANNEL_3, &PWMD4},
  .line[2] = {CHANNEL_4, &PWMD4},

  .power = 70,
  .pole_pair = 7,
  .direction = CLOCKWISE,

};



pid_accessor pid_pitch_rotation = {

  .kp = 10.0f,
  .ki = 0.0f,
  .kd = 0.095f,

  .error_cutoff = 0.0f,
  .derivative_cutoff = 0.0f

};
pid_accessor pid_pitch_angle = {

  .kp = 1.0f,
  .ki = 0.0f,
  .kd = 0.0f,

  .error_cutoff = 0.0f,
  .derivative_cutoff = 0.0f

};

pid_accessor pid_roll_rotation = {

  .kp = 15.0f,
  .ki = 0.0f,
  .kd = 0.4f,

  .error_cutoff = 0.0f,
  .derivative_cutoff = 0.0f

};
pid_accessor pid_roll_angle = {

  .kp = 1.0f,
  .ki = 0.0f,
  .kd = 0.0f,

  .error_cutoff = 0.0f,
  .derivative_cutoff = 0.0f

};

pid_accessor pid_yaw_rotation = {

  .kp = 10.0f,
  .ki = 0.0f,
  .kd = 0.3f,

  .error_cutoff = 0.0f,
  .derivative_cutoff = 0.0f

};

float user_pitch_angle = 0.0f;
float user_roll_angle = 0.0f;

int imu_platform_enable = 0;

float resistor_up = 0.0f;
float resistor_down = 0.0f;

float battery_voltage_alpha = 0.8f;
float battery_voltage = 0.0f;

bool debug = false;