#ifndef PID_ACCESS_H_
#define PID_ACCESS_H_

#include "math_utils.h"

typedef struct{

    // Pointer to Proportional Gain, Integral Gain and Derivative Gain respectively
    float kp;
    float ki;
    float kd;

    // Pointer to Integral Max and Min to constrain Integral term
    float integral_min;
    float integral_max;

    // Pointer to LPF Cutoff frequency for error and derivative term
    float error_cutoff;
    float derivative_cutoff;

    // Sampling time of pid in seconds
    float dt;

    // Memory of previous error term, derivative term and integral term 
    float previous_error;
    float previous_derivative;
    float previous_integral;

}pid_accessor;

void init_pid(pid_accessor *current_pid, float dt_set);
float update_pid(pid_accessor *current_pid, float error);
float calculate_lowpass_filter(float dt, float cutoff_freq);

#endif