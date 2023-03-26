#ifndef RC_INPUT_H_
#define RC_INPUT_H_

#include "motor_access.h"

typedef struct{
    int upper_threshold;
    int lower_threshold;
    int center;
    int dead_zone;
    int direction;
}rc_accessor;

int process_pitch_input(motor_accessor pitch_motor, rc_accessor pitch_rc_conf, int duty_cycle, float dt);
int process_yaw_input(motor_accessor yaw_motor, rc_accessor yaw_rc_conf, int duty_cycle, float dt);

#endif