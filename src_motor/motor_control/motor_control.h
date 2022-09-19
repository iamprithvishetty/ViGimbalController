#ifndef MOTOR_CONTROL_H_
#define MOTOR_CONTROL_H_

#include "motor_access.h"

#define PWM_PERIOD 1000

void set_pwm_fast_table_direct(motor_accessor *current_motor, int *step, int *pwm);
void set_pwm_fast_table(motor_accessor *current_motor, float phi, int *pwm);
void set_pwm_data(motor_accessor *current_motor ,int *pwm);
void set_pwm(motor_accessor *current_motor, float phi);
void set_pwm_direct(motor_accessor *current_motor, int *step);


#endif