#ifndef MOTOR_ACCESS_H_
#define MOTOR_ACCESS_H_

#include "hal.h"
#include "misc_utils.h"

typedef enum{

    CLOCKWISE = 1,
    ANTICLOCKWISE = -1

}motor_direction;

typedef enum{

    CHANNEL_1 = 0,
    CHANNEL_2 = 1,
    CHANNEL_3 = 2,
    CHANNEL_4 = 3

}pwm_channel;

typedef struct{

    pwm_channel channel;
    PWMDriver *pwm_driver;
    
}pwm_channel_driver;

typedef struct{

    pwm_channel_driver line[3];
      
    int power;
    int pole_pair;
    motor_direction direction;

}motor_accessor;

#endif