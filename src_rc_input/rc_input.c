#include "rc_input.h"
#include "trignometry_pwm.h"

/*
 * Process the duty cycle and give the output to move for pitch 
 */
int process_pitch_input(motor_accessor pitch_motor, rc_accessor pitch_rc_conf, 
                        int duty_cycle, float dt){
    
    // Return zero if duty cycle is zero
    if(duty_cycle == 0){
        return 0;
    }

    // Return zero if inside the threshold range
    if(duty_cycle <= (pitch_rc_conf.center + pitch_rc_conf.dead_zone)
    && duty_cycle >= (pitch_rc_conf.center - pitch_rc_conf.dead_zone)) {
        return 0;
    }

    int output_value = 0;

    // Check if the duty cycle is above the dead zone cap
    if(duty_cycle > pitch_rc_conf.center + pitch_rc_conf.dead_zone) {

        // Set the duty cycle to max if above upper threshold
        if(duty_cycle > pitch_rc_conf.upper_threshold) {
            duty_cycle = pitch_rc_conf.upper_threshold;
        }
        // Calculate the ratio of diff of duty cycle to center with upper thresold to center 
        float ratio_duty_cycle = (float)(duty_cycle - pitch_rc_conf.center)/(float)(pitch_rc_conf.upper_threshold - pitch_rc_conf.center);
        
        // Output value is Total Steps to complete one rev * 720/360(Max speed 720deg/s) * ratio * direction * time 
        output_value = pitch_motor.pole_pair*SIN_ARRAY_SIZE*(720.0f/360.0f)*ratio_duty_cycle*pitch_rc_conf.direction*dt;
    } else if (duty_cycle < pitch_rc_conf.center - pitch_rc_conf.dead_zone) {
        if(duty_cycle < pitch_rc_conf.lower_threshold) {
            duty_cycle = pitch_rc_conf.lower_threshold;
        }
        float ratio_duty_cycle = (float)(pitch_rc_conf.center - duty_cycle)/(float)(pitch_rc_conf.center - pitch_rc_conf.lower_threshold);
        output_value = pitch_motor.pole_pair*SIN_ARRAY_SIZE*(720.0f/360.0f)*ratio_duty_cycle*pitch_rc_conf.direction*-1*dt;
    }

    return output_value;
}

/*
 * Process the duty cycle and give the output to move for yaw 
 */
int process_yaw_input(motor_accessor yaw_motor, rc_accessor yaw_rc_conf, 
                       int duty_cycle, float dt){
    
    // Return zero if duty cycle is zero
    if(duty_cycle == 0){
        return 0;
    }

    // Return zero if inside the threshold range
    if(duty_cycle <= (yaw_rc_conf.center + yaw_rc_conf.dead_zone)
    && duty_cycle >= (yaw_rc_conf.center - yaw_rc_conf.dead_zone)) {
        return 0;
    }

    int output_value = 0;

    // Check if the duty cycle is above the dead zone cap
    if(duty_cycle > yaw_rc_conf.center + yaw_rc_conf.dead_zone) {

        // Set the duty cycle to max if above upper threshold
        if(duty_cycle > yaw_rc_conf.upper_threshold) {
            duty_cycle = yaw_rc_conf.upper_threshold;
        }
        // Calculate the ratio of diff of duty cycle to center with upper thresold to center 
        float ratio_duty_cycle = (float)(duty_cycle - yaw_rc_conf.center)/(float)(yaw_rc_conf.upper_threshold - yaw_rc_conf.center);
        // Output value is Total Steps to complete one rev * 720/360(Max speed 720deg/s) * ratio * direction * time 
        output_value = yaw_motor.pole_pair*SIN_ARRAY_SIZE*(720.0f/360.0f)*ratio_duty_cycle*yaw_rc_conf.direction*dt;
    } else if (duty_cycle < yaw_rc_conf.center - yaw_rc_conf.dead_zone) {
        if(duty_cycle < yaw_rc_conf.lower_threshold) {
            duty_cycle = yaw_rc_conf.lower_threshold;
        }
        float ratio_duty_cycle = (float)(yaw_rc_conf.center - duty_cycle)/(float)(yaw_rc_conf.center - yaw_rc_conf.lower_threshold);
        output_value = yaw_motor.pole_pair*SIN_ARRAY_SIZE*(720.0f/360.0f)*ratio_duty_cycle*yaw_rc_conf.direction*-1*dt;
    }

    return output_value;   
}