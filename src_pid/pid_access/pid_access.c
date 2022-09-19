#include "pid_access.h"
#include "hal.h"

/*
 * Init the pid_accessor instance to default values
 * param1 : address of instance of pid_accessor used
 * param2 : update time of pid in seconds
 */
void init_pid(pid_accessor *current_pid, float dt_set) {

    current_pid->dt = dt_set;

    //Initialize the value to zero
    current_pid->previous_error = 0;
    current_pid->previous_derivative = 0;
    current_pid->previous_integral = 0;

}

/*
 * Update Pid funtion with error
 * param1 : address of instance of pid_accessor used
 * param2 : value of error
 */
float update_pid(pid_accessor *current_pid, float error) {

    float p_output = 0, d_output = 0, i_output = 0;
    
    // Applying LPF to the error 
    error = current_pid->previous_error + calculate_lowpass_filter(current_pid->dt, current_pid->error_cutoff)*(error - current_pid->previous_error);


    // Check id sampling time is valid
    if(current_pid->dt > 0.0f) {


        // Calculating the derivative value i.e (Current_error-previous_error)/dt;
        float derivative = (error - current_pid->previous_error)/(current_pid->dt);

        // Applying LPF to the derivative
        current_pid->previous_derivative += calculate_lowpass_filter(current_pid->dt, current_pid->derivative_cutoff)*(derivative-current_pid->previous_derivative);  


        d_output = (current_pid->previous_derivative)*(current_pid->kd);


        // This is to make sure that integral comes into play only when the integral term and error are in opp direction
        if((current_pid->previous_integral<0 && error>=0) || (current_pid->previous_integral>=0 && error<0)) {

            // Calculating the integral term
            current_pid->previous_integral += error*(current_pid->ki)*(current_pid->dt);

            // Check if min and max value for integral is not null
            if(current_pid->integral_min == 0 && current_pid->integral_max == 0) {

                // Constrain the integral value for avoiding integral windup
                current_pid->previous_integral = constrain_float(current_pid->previous_integral, (current_pid->integral_min), (current_pid->integral_max));
            }
        }
        

        i_output = current_pid->previous_integral;


    }


    //Proporitonal Op = error*Kp
    p_output =  (error)*(current_pid->kp);

    // Update previous error value
    current_pid->previous_error = error;

    // Final Op
    return (p_output+i_output+d_output);

}

/*
 * Calculates constant in order to apply LPF
 * param1 : sampling time
 * param2 : cutoff frequency
 * Reference Link: https://youtu.be/MrbffdimDts
 */
float calculate_lowpass_filter(float dt, float cutoff_freq) {

    if (dt <= 0.0f || cutoff_freq <= 0.0f) {
        return 1.0;
    }

    float rc = 1.0f/(M_2PI*cutoff_freq);

    return constrain_float(dt/(dt+rc), 0.0f, 1.0f);

}