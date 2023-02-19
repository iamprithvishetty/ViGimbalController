#ifndef GIMBAL_MODE_H_
#define GIMBAL_MODE_H_

#include "motor_access.h"

typedef enum {
    LOCK   = 1,
    PAN    = 2,
    FOLLOW = 3,
}mode;

typedef struct{
    mode gimbal_mode;
    float yaw_dead_zone;
    int yaw_speed;
    float pitch_dead_zone;
    int pitch_speed;
}gimbal_mode_data;

float process_mode_yaw(const gimbal_mode_data current_mode, const motor_accessor motor_yaw,const float yaw_relative_angle);
float process_mode_pitch(const gimbal_mode_data current_mode, const motor_accessor motor_pitch,const float pitch_relative_angle);

#endif