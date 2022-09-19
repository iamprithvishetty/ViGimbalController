#include "calibration_gyro.h"
#include "math.h"

/*
 * Calibration for calculating IMU Gyroscope Bias
 * param1 : imu_accessor to access imu configuration data
 */
void calibrate_gyro(imu_accessor *current_imu) {

  //To temporarily store accel and gyro data
  int16_t ax,ay,az,gx,gy,gz;

  // To keep a check if the gyro bias average has converged
  bool converged_gyro_bias_x = false, converged_gyro_bias_y = false , converged_gyro_bias_z = false;

  // To save the summed values of gyro reading for specific time interval
  int gyro_x_sum, gyro_y_sum, gyro_z_sum;
  
  // To save the average value of gyro reading 
  int gyro_x_avg, gyro_y_avg, gyro_z_avg;
  int gyro_x_avg_prev, gyro_y_avg_prev, gyro_z_avg_prev;

  // To save the best average
  int gyro_x_avg_best, gyro_y_avg_best, gyro_z_avg_best;

  // To save the difference between the average of previous gyro and new gyro reading
  int gyro_x_avg_diff, gyro_y_avg_diff, gyro_z_avg_diff;

  // To save the best difference we have got so far
  int gyro_x_avg_diff_best = -1, gyro_y_avg_diff_best = -1, gyro_z_avg_diff_best = -1;

  // To keep a check if the IMU moved while calibration or was kept on a moving platform
  float accel_start_x, accel_diff_x, accel_start_y, accel_diff_y, accel_start_z, accel_diff_z;

  int counter;

  // To keep a check of how much time is passed inside the loop
  int time_passed_count = 0;

  // Ignore the initial readings
  for(counter=0; counter<5; counter++) {
  
    imu_get_all_raw(current_imu, &ax, &ay, &az, &gx, &gy, &gz);
    chThdSleepMilliseconds(5);

  }

  // Stay in the loop until all the values are not converged
  while(!converged_gyro_bias_x || !converged_gyro_bias_y || !converged_gyro_bias_z){

    // Reset the sum values
    gyro_x_sum = 0;
    gyro_y_sum = 0;
    gyro_z_sum = 0;


     // Calculate the raw imu values
    imu_get_all_raw(current_imu, &ax, &ay, &az, &gx, &gy, &gz);

    accel_start_x = current_imu->accel_scale_factor*ax;
    accel_start_y = current_imu->accel_scale_factor*ay;
    accel_start_z = current_imu->accel_scale_factor*az;

    for(counter=0; counter<50; counter++) {

      // Calculate the raw imu values
      imu_get_all_raw(current_imu, &ax, &ay, &az, &gx, &gy, &gz);

      // Calculate the sum for individual Gyro
      gyro_x_sum += gx;
      gyro_y_sum += gy;
      gyro_z_sum += gz;

      chThdSleepMilliseconds(5);

      time_passed_count++;
    }

     // Calculate the raw imu values
    imu_get_all_raw(current_imu, &ax, &ay, &az, &gx, &gy, &gz);

    // Calculate the absolute value of accleration difference wrt before starting the Summing
    accel_diff_x = fabs(current_imu->accel_scale_factor*ax - accel_start_x);
    accel_diff_y = fabs(current_imu->accel_scale_factor*ay - accel_start_y);
    accel_diff_z = fabs(current_imu->accel_scale_factor*az - accel_start_z);
    
    // If waited for more than 20s break out of the loop
    if(time_passed_count > 20/0.005){
      break;
    }

    // Check if Difference in Accleration values exceed 0.2 if yes then skip this reading
    if(accel_diff_x > 0.2f || accel_diff_y > 0.2f || accel_diff_z > 0.2f) {
      continue;
    }

    // Calculate the average
    gyro_x_avg = gyro_x_sum/counter;
    gyro_y_avg = gyro_y_sum/counter;
    gyro_z_avg = gyro_z_sum/counter;

    // Calculate the absolute difference between previous and current average
    gyro_x_avg_diff = abs(gyro_x_avg_prev - gyro_x_avg);
    gyro_y_avg_diff = abs(gyro_y_avg_prev - gyro_y_avg);
    gyro_z_avg_diff = abs(gyro_z_avg_prev - gyro_z_avg);

    // Check if it's the first time and save the gyro_x_avg_best as current gyro reading
    if(gyro_x_avg_diff_best < 0){
      gyro_x_avg_diff_best = gyro_x_avg_diff;
      gyro_x_avg_best = gyro_x_avg;
    }
    // If the absolute difference is less than 2 then converged
    else if(gyro_x_avg_diff <= 2 && converged_gyro_bias_x != true){
      gyro_x_avg_prev = gyro_x_avg*0.5 + gyro_x_avg_prev*0.5;
      gyro_x_avg_best = gyro_x_avg_prev;
      converged_gyro_bias_x = true;
    }
    // Check if current difference is less than best difference
    else if(gyro_x_avg_diff < gyro_x_avg_diff_best){
      gyro_x_avg_diff_best = gyro_x_avg_diff;
      gyro_x_avg_best = gyro_x_avg*0.5 + gyro_x_avg_prev*0.5;
    }
    gyro_x_avg_prev = gyro_x_avg;

    if(gyro_y_avg_diff_best < 0){
      gyro_y_avg_diff_best = gyro_y_avg_diff;
      gyro_y_avg_best = gyro_y_avg;
    }
    else if(gyro_y_avg_diff <= 2 && converged_gyro_bias_y != true){
      gyro_y_avg_prev = gyro_y_avg*0.5 + gyro_y_avg_prev*0.5;
      gyro_y_avg_best = gyro_y_avg_prev;
      converged_gyro_bias_y = true;
    }
    else if(gyro_y_avg_diff < gyro_y_avg_diff_best){
      gyro_y_avg_diff_best = gyro_y_avg_diff;
      gyro_y_avg_best = gyro_y_avg*0.5 + gyro_y_avg_prev*0.5;
    }
    gyro_y_avg_prev = gyro_y_avg;

    if(gyro_z_avg_diff_best < 0){
      gyro_z_avg_diff_best = gyro_z_avg_diff;
      gyro_z_avg_best = gyro_z_avg;
    }
    else if(gyro_z_avg_diff <= 2 && converged_gyro_bias_z != true){
      gyro_z_avg_prev = gyro_z_avg*0.5 + gyro_z_avg_prev*0.5;
      gyro_z_avg_best = gyro_z_avg_prev;
      converged_gyro_bias_z = true;
    }
    else if(gyro_z_avg_diff < gyro_z_avg_diff_best){
      gyro_z_avg_diff_best = gyro_z_avg_diff;
      gyro_z_avg_best = gyro_z_avg*0.5 + gyro_z_avg_prev*0.5;
    }
    gyro_z_avg_prev = gyro_z_avg;

  }

  // Change the Main Gyro Bias with Current Best Gyro Bias 
  current_imu->gyro_bias_x = gyro_x_avg_best;
  current_imu->gyro_bias_y = gyro_y_avg_best;
  current_imu->gyro_bias_z = gyro_z_avg_best;

}