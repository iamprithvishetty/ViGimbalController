/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include <stdio.h>
#include <string.h>

#include "driver_conf.h"
#include "usbcfg.h"

#include "imu_access.h"
#include "madgwick.h"
#include "calibration_gyro.h"
#include "orientation.h"

#include "motor_access.h"
#include "motor_control.h"
#include "trignometry_pwm.h"

#include "pid_access.h"

#include "message_access.h"
#include "user_data.h"


/*
 * gimbal thread
 */

bool gimbal_thread_initialized = false;

// To store imu values for cam
float gyro_x_cam,gyro_y_cam,gyro_z_cam;
float accel_x_cam,accel_y_cam,accel_z_cam;
float angle_cam[3];

// To store imu values for platform
float gyro_x_platform,gyro_y_platform,gyro_z_platform;
float accel_x_platform,accel_y_platform,accel_z_platform;
float angle_platform[3];

static THD_WORKING_AREA(wa_thread_gimbal, 2048);
static __attribute__((noreturn)) THD_FUNCTION(thread_gimbal, arg)
{

  (void)arg;
  chRegSetThreadName("gimbal");

  // sampling time in seconds
  float dt = 0.002;
  // sampling time in microseconds
  int dt_us = (int)(dt*10e6);

  // Initializing the sin array that we'll be using for supplying pwm values
  init_sin_array();

  int pitch_step_memory=0, roll_step_memory=0, yaw_step_memory=0;

  while(true) {

    if(!gimbal_thread_initialized){

      // init the imu
      while(!imu_initialize(&imu_cam)){
        chThdSleepMilliseconds(1);
      }
      imu_cam.is_initialized = true;

      uint8_t max_tries = 10;
      while(!imu_initialize(&imu_platform)){
        if(--max_tries){
          break;
        }
        chThdSleepMilliseconds(1);
      }
      if(max_tries){
        imu_platform.is_initialized = true;
      }

      // init all the pid values
      init_pid(&pid_pitch_rotation, dt);
      init_pid(&pid_roll_rotation, dt);
      init_pid(&pid_yaw_rotation, dt);

      init_pid(&pid_pitch_angle, dt);
      init_pid(&pid_roll_angle, dt);

      // calibrate the gyro values
      if(imu_cam.is_initialized){
        calibrate_gyro(&imu_cam);
      }
      if(imu_platform.is_initialized){
        calibrate_gyro(&imu_platform);
      }

      // init madgwick filter
      if(imu_cam.is_initialized){
        madgwick_init(&madgwick_cam, 10.0, 1.0f/dt);
      }
      if(imu_platform.is_initialized){
        madgwick_init(&madgwick_platform, 10.0, 1.0f/dt);
      }

      //update madgwick value and retrieve angle values
      if(imu_cam.is_initialized){
        imu_get_all(&imu_cam, &accel_x_cam, &accel_y_cam, &accel_z_cam, &gyro_x_cam, &gyro_y_cam, &gyro_z_cam);
        madgwick_update(&madgwick_cam , gyro_x_cam, gyro_y_cam, gyro_z_cam, accel_x_cam, accel_y_cam, accel_z_cam);
        madgwick_compute_angle(&madgwick_cam, angle_cam);
      }
      if(imu_platform.is_initialized){
        imu_get_all(&imu_platform, &accel_x_platform, &accel_y_platform, &accel_z_platform, &gyro_x_platform, &gyro_y_platform, &gyro_z_platform);
        madgwick_update(&madgwick_platform , gyro_x_platform, gyro_y_platform, gyro_z_platform, accel_x_platform, accel_y_platform, accel_z_platform);
        madgwick_compute_angle(&madgwick_platform, angle_platform);
      }

      madgwick_cam.beta = 0.01;
      madgwick_platform.beta = 0.01;

      gimbal_thread_initialized = 1;
    
    }
    else {

      // system time start
      systime_t systemtime_begin = chVTGetSystemTime();

    
      // Get the imu values
      imu_get_all(&imu_cam, &accel_x_cam, &accel_y_cam, &accel_z_cam, &gyro_x_cam, &gyro_y_cam, &gyro_z_cam);
      madgwick_update(&madgwick_cam , gyro_x_cam, gyro_y_cam, gyro_z_cam, accel_x_cam, accel_y_cam, accel_z_cam);
      madgwick_compute_angle(&madgwick_cam, angle_cam);

      if(imu_platform.is_initialized){
        imu_get_all(&imu_platform, &accel_x_platform, &accel_y_platform, &accel_z_platform, &gyro_x_platform, &gyro_y_platform, &gyro_z_platform);
        madgwick_update(&madgwick_platform , gyro_x_platform, gyro_y_platform, gyro_z_platform, accel_x_platform, accel_y_platform, accel_z_platform);
        madgwick_compute_angle(&madgwick_platform, angle_platform);
      }

      // Only update the yaw angle if gyro value exceeds a certain threshold
      if(gyro_z_cam > 15.0 || gyro_z_cam < -15.0) {
        angle_cam[YAW] += gyro_z_cam*dt;
      }
      if(gyro_z_platform > 15.0 || gyro_z_platform < -15.0) {
        angle_platform[YAW] += gyro_z_cam*dt;
      }
  

    
      // calculate the value to be feeded for angle correction
      float feed_cam_angle_pitch = update_pid(&pid_pitch_angle, angle_cam[PITCH]-user_pitch_angle);
      
      // factor for converting angle to steps
      float to_steps = (float)SIN_ARRAY_SIZE*(float)motor_pitch.pole_pair/360.0;
      // calculate the value to be feeded for gyro correction
      float feed_cam_rotation_pitch = update_pid(&pid_pitch_rotation, gyro_x_cam * dt * to_steps);

      float step_pitch;
      if(imu_platform_enable && imu_platform.is_initialized){
        
      }
      else {
        step_pitch = feed_cam_angle_pitch + feed_cam_rotation_pitch;
      }

      // current step to be given based on motor direction
      float feed_step = (int)step_pitch*motor_pitch.direction;

      pitch_step_memory += feed_step;
      set_pwm_direct(&motor_pitch, &pitch_step_memory);




      // calculate the value to be feeded for angle correction
      float feed_cam_angle_roll = update_pid(&pid_roll_angle, angle_cam[ROLL]-user_roll_angle);
      
      // factor for converting angle to steps
      to_steps = (float)SIN_ARRAY_SIZE*(float)motor_roll.pole_pair/360.0;
      // calculate the value to be feeded for gyro correction
      float feed_cam_rotation_roll = update_pid(&pid_roll_rotation, gyro_y_cam * dt * to_steps);

      float step_roll;
      if(imu_platform_enable && imu_platform.is_initialized){
        
      }
      else {
        step_roll = feed_cam_angle_roll + feed_cam_rotation_roll;
      }

      // current step to be given based on motor direction
      feed_step = (int)step_roll*motor_roll.direction;

      roll_step_memory += feed_step;
      set_pwm_direct(&motor_roll, &roll_step_memory);

    

      // factor for converting angle to steps
      to_steps = (float)SIN_ARRAY_SIZE*(float)motor_yaw.pole_pair/360.0;
      // calculate the value to be feeded for gyro correction
      float feed_cam_rotation_yaw = update_pid(&pid_yaw_rotation, gyro_z_cam * dt * to_steps);

      float step_yaw;
      if(imu_platform_enable && imu_platform.is_initialized){
        
      }
      else {
        step_yaw = feed_cam_rotation_yaw;
      }

      // current step to be given based on motor direction
      feed_step = (int)step_yaw*motor_yaw.direction;

      yaw_step_memory += feed_step;
      set_pwm_direct(&motor_yaw, &yaw_step_memory);

      // system time end
      systime_t systemtime_end = chVTGetSystemTime();
      // loop execution time
      int32_t time_loop_execution = systemtime_end - systemtime_begin;

      // if system time has reached maximum value then reset
      if(time_loop_execution < 0){
        time_loop_execution += 65536;
      }

      // Wait for 2000us but also taking into account the time taken for the execution of the process in the loop
      chThdSleepMicroseconds(dt_us - TIME_I2US(time_loop_execution));

    }
  }
}

/*
 * serial communication thread
 */

static THD_WORKING_AREA(wa_thread_serial_com, 128);
static __attribute__((noreturn)) THD_FUNCTION(thread_serial_com, arg)
{

  (void)arg;
  chRegSetThreadName("serial_com");

  message_decoder decoder_gc = {
    .start = "GC",
    .command_seperator = '+',
    .return_seperator = '?',
    .set_seperator = '='
  };

  char message_received[64];
  int16_t incoming_character;
  uint8_t incoming_character_counter;

  while (true)
  {

    incoming_character_counter = 0;
    while(true) {
      incoming_character = chnGetTimeout(&SDU1,TIME_IMMEDIATE);
      if(incoming_character == Q_TIMEOUT) {
        break;
      }
      else{
        message_received[incoming_character_counter] = (char)incoming_character;
        incoming_character_counter++;
        if(incoming_character_counter==64) {
          break;
        }
      }
    }

    if(incoming_character_counter > 0){
      process(message_received,incoming_character_counter,&decoder_gc);
    }  
    chThdSleepMilliseconds(10);
  }
}

/*
 * blink thread
 */

static THD_WORKING_AREA(wa_thread_blink, 128);
static __attribute__((noreturn)) THD_FUNCTION(thread_blink, arg)
{

  (void)arg;
  chRegSetThreadName("blink");
  while (true)
  {
    // Blink Red if IMU is not initialized
    if(!imu_cam.is_initialized){
      palClearLine(LED_1);
      palSetLine(LED_2);
      chThdSleepMilliseconds(500);
      palClearLine(LED_2);
      chThdSleepMilliseconds(500);
    }

    // Check if IMU is initialized
    else if(imu_cam.is_initialized){

      // If Gimbal Thread is initialized then blink green
      if(gimbal_thread_initialized){
        palClearLine(LED_2);
        palSetLine(LED_1);
        chThdSleepMilliseconds(200);
        palClearLine(LED_1);
        chThdSleepMilliseconds(200);
      }
      // If Gimbal Thread is not initialized then blink green and red alternately
      else {
        palClearLine(LED_1);
        palSetLine(LED_2);
        chThdSleepMilliseconds(200);
        palSetLine(LED_1);
        palClearLine(LED_2);
        chThdSleepMilliseconds(200);
      }

    }

  }
}


/*
 * application entry point.
 */

int main(void)
{

  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();

  /*
   * Initializes a serial-over-USB CDC driver.
   */
  sduObjectInit(&SDU1);
  sduStart(&SDU1, &serusbcfg);

  /*
   * Activates the USB driver and then the USB bus pull-up on D+.
   * Note, a delay is inserted in order to not have to disconnect the cable
   * after a reset.
   */
  usbDisconnectBus(serusbcfg.usbp);
  chThdSleepMilliseconds(1500);
  usbStart(serusbcfg.usbp, &usbcfg);
  usbConnectBus(serusbcfg.usbp);

  /*
   * Initializes the I2C Driver
   */
  i2cObjectInit(imu_cam.i2c_driver);
  i2cStart(imu_cam.i2c_driver, &i2ccfg);

  i2cObjectInit(imu_platform.i2c_driver);
  i2cStart(imu_platform.i2c_driver, &i2ccfg);

  /*
   * Initializes a PWM driver.
   */
  pwmStart(&PWMD3, &pwmcfg_tim3);
  pwmStart(&PWMD2, &pwmcfg_tim2);
  pwmStart(&PWMD4, &pwmcfg_tim4);

  pwmEnableChannel(motor_pitch.line[0].pwm_driver, motor_pitch.line[0].channel, 0);
  pwmEnableChannel(motor_pitch.line[1].pwm_driver, motor_pitch.line[1].channel, 0);
  pwmEnableChannel(motor_pitch.line[2].pwm_driver, motor_pitch.line[2].channel, 0);

  pwmEnableChannel(motor_roll.line[0].pwm_driver, motor_roll.line[0].channel, 0);
  pwmEnableChannel(motor_roll.line[1].pwm_driver, motor_roll.line[1].channel, 0);
  pwmEnableChannel(motor_roll.line[2].pwm_driver, motor_roll.line[2].channel, 0);

  pwmEnableChannel(motor_yaw.line[0].pwm_driver, motor_yaw.line[0].channel, 0);
  pwmEnableChannel(motor_yaw.line[1].pwm_driver, motor_yaw.line[1].channel, 0);
  pwmEnableChannel(motor_yaw.line[2].pwm_driver, motor_yaw.line[2].channel, 0);


  /*
   * Initializes a ICU driver.
   */
  icuStart(&ICUD1, &icucfgTim1);
  icuStart(&ICUD8, &icucfgTim8);

  /*
   * Starting ICU capture and enabling the notifications.
   */
  icuStartCapture(&ICUD1);
  icuEnableNotifications(&ICUD1);

  icuStartCapture(&ICUD8);
  icuEnableNotifications(&ICUD8);

  /*
   * Activates the ADC1 driver
   */
  adcStart(&ADCD1, NULL);

  /*
   * Creating different threads
   */

  chThdCreateStatic(wa_thread_blink, sizeof(wa_thread_blink), NORMALPRIO, thread_blink, NULL);
  chThdCreateStatic(wa_thread_serial_com, sizeof(wa_thread_serial_com), NORMALPRIO + 1, thread_serial_com, NULL);
  chThdCreateStatic(wa_thread_gimbal, sizeof(wa_thread_gimbal), NORMALPRIO + 2, thread_gimbal, NULL);

  /*
   * Normal main() thread activity
   */

  while (true)
  { 
    if(debug){
      print("%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n",accel_x_cam, accel_y_cam, accel_z_cam, gyro_x_cam, gyro_y_cam, gyro_z_cam, angle_cam[PITCH], angle_cam[ROLL], angle_cam[YAW], accel_x_platform, accel_y_platform, accel_z_platform, gyro_x_platform, gyro_y_platform, gyro_z_platform, angle_platform[PITCH], angle_platform[ROLL], angle_cam[YAW]);
    }
    chThdSleepMilliseconds(40);
  }
}