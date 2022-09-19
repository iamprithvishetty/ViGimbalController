#include <math.h>

#include "ch.h"
#include "hal.h"

#include "motor_control.h"
#include "motor_access.h"
#include "trignometry_pwm.h"
#include "math_utils.h"
#include "misc_utils.h"

/*
 * Calculates the pwm value based on the steps directly
 * param1 : *current_motor -> motor_accessor with configuration parameters
 * param2 : step -> direct step
 * param3 : *pwm -> Calculates the value of pwm based on the step given
 */
void set_pwm_fast_table_direct(motor_accessor *current_motor, int *step, int *pwm)
{

    if (*step < 0)
    {
        *step = SIN_ARRAY_SIZE + *step;
    }
    int i_power = 5 * current_motor->power;
    pwm[0] = (sin_data_16bit[*step                          % SIN_ARRAY_SIZE] * i_power + SIN_ARRAY_SCALE / 2) / SIN_ARRAY_SCALE + (PWM_PERIOD / 2);
    pwm[1] = (sin_data_16bit[(*step + 1 * SIN_ARRAY_SIZE / 3)     % SIN_ARRAY_SIZE] * i_power + SIN_ARRAY_SCALE / 2) / SIN_ARRAY_SCALE + (PWM_PERIOD / 2);
    pwm[2] = (sin_data_16bit[(*step + (2 * SIN_ARRAY_SIZE + 1) / 3) % SIN_ARRAY_SIZE] * i_power + SIN_ARRAY_SCALE / 2) / SIN_ARRAY_SCALE + (PWM_PERIOD / 2);

}

/*
 * Calculates the pwm value based on the angle
 * param1 : *current_motor -> motor_accessor with configuration parameters
 * param2 : phi -> angle for the motor
 * param3 : *pwm -> Calculates the value of pwm based on the angle given
 */
void set_pwm_fast_table(motor_accessor *current_motor, float phi, int *pwm)
{
    int phi_to_step = (int)Round((phi / (M_2PI)) * SIN_ARRAY_SIZE);
    phi_to_step = phi_to_step % SIN_ARRAY_SIZE;

    if (phi_to_step < 0)
    {
        phi_to_step = SIN_ARRAY_SIZE + phi_to_step;
    }

    int i_power = 5 * current_motor->power;
    pwm[0] = (sin_data_16bit[phi_to_step                          % SIN_ARRAY_SIZE] * i_power + SIN_ARRAY_SCALE / 2) / SIN_ARRAY_SCALE + (PWM_PERIOD / 2);
    pwm[1] = (sin_data_16bit[(phi_to_step + 1 * SIN_ARRAY_SIZE / 3)     % SIN_ARRAY_SIZE] * i_power + SIN_ARRAY_SCALE / 2) / SIN_ARRAY_SCALE + (PWM_PERIOD / 2);
    pwm[2] = (sin_data_16bit[(phi_to_step + (2 * SIN_ARRAY_SIZE + 1) / 3) % SIN_ARRAY_SIZE] * i_power + SIN_ARRAY_SCALE / 2) / SIN_ARRAY_SCALE + (PWM_PERIOD / 2);
}

/*
 * Sets the desired PWM values into the PWM Channel
 */
void set_pwm_data(motor_accessor *current_motor ,int *pwm)
{
        pwmEnableChannel(current_motor->line[0].pwm_driver, current_motor->line[0].channel, pwm[0]);
        pwmEnableChannel(current_motor->line[1].pwm_driver, current_motor->line[1].channel, pwm[1]);
        pwmEnableChannel(current_motor->line[2].pwm_driver, current_motor->line[2].channel, pwm[2]);
}

/*
 * Calculates PWM values for certain angle with certain power 
 * and writes it to the PWM Channel
 */
void set_pwm(motor_accessor *current_motor, float phi)
{
    int pwm[3];
    set_pwm_fast_table(current_motor, phi, pwm);
    set_pwm_data(current_motor, pwm);
}

/*
 * Calculates PWM values for certain step with certain power 
 * and writes it to the PWM Channel
 */
void set_pwm_direct(motor_accessor *current_motor, int *step)
{
    int pwm[3];
    set_pwm_fast_table_direct(current_motor, step, pwm);
    set_pwm_data(current_motor, pwm);
}