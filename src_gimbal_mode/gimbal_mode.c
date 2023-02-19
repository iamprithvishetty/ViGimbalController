#include "gimbal_mode.h"
#include "trignometry_pwm.h"

/*
 * Calculates the steps required for gimbal mode set over a second so we have to multiply with the sampling rate
 * after calling the function
 * In LOCK and FOLLOW mode the steps to be moved is 0
 * In PAN mode if the relative yaw is outside dead zone then move wrt to speed and yaw relative angle
 */
float process_mode_yaw(const gimbal_mode_data current_mode, const motor_accessor motor_yaw,const float yaw_relative_angle) {
    
    float feed_cam_mode_yaw = 0;

    switch(current_mode.gimbal_mode) {
        case FOLLOW:
        case PAN:
            if(yaw_relative_angle > current_mode.yaw_dead_zone){
                feed_cam_mode_yaw  = motor_yaw.pole_pair*SIN_ARRAY_SIZE*(10.0f/360.0f)*current_mode.yaw_speed*yaw_relative_angle;
            }
            else if(yaw_relative_angle < -current_mode.yaw_dead_zone){
                feed_cam_mode_yaw  = motor_yaw.pole_pair*SIN_ARRAY_SIZE*(10.0f/360.0f)*current_mode.yaw_speed*yaw_relative_angle;
            }
            break;
        case LOCK:
        default:
            feed_cam_mode_yaw = 0;
            break;
    }

    return feed_cam_mode_yaw;
}

/*
 * Calculates the steps required for gimbal mode set over a second so we have to multiply with the sampling rate
 * after calling the function
 * In PAN and LOCK mode the steps to be moved is 0
 * In FOLLOW mode if the relative pitch is outside dead zone then move wrt to speed and pitch relative angle
 */
float process_mode_pitch(const gimbal_mode_data current_mode, const motor_accessor motor_pitch,const float pitch_relative_angle) {
    
    float feed_cam_mode_pitch = 0;

    switch(current_mode.gimbal_mode) {
        case FOLLOW:
            if(pitch_relative_angle > current_mode.pitch_dead_zone){
                feed_cam_mode_pitch  = -motor_pitch.pole_pair*SIN_ARRAY_SIZE*(10.0f/360.0f)*current_mode.pitch_speed*pitch_relative_angle;
            }
            else if(pitch_relative_angle < -current_mode.pitch_dead_zone){
                feed_cam_mode_pitch  = -motor_pitch.pole_pair*SIN_ARRAY_SIZE*(10.0f/360.0f)*current_mode.pitch_speed*pitch_relative_angle;
            }
            break;
        case PAN:
        case LOCK:
        default:
            feed_cam_mode_pitch = 0;
            break;
    }

    return feed_cam_mode_pitch;
}