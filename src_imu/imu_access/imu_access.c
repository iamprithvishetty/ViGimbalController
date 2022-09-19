#include "imu_access.h"
#include "mpu6050.h"

/*
 * Initializes IMU as per user defined functions
 * @param1 : imu_accessor to get ID, I2C_Driver and I2C_Address
 * @return : determines whether the initialization was successful 
 */
bool imu_initialize(imu_accessor *current_imu){

    switch(current_imu->id){

        case ID_MPU6050 :

            return imu_initialize_mpu6050(current_imu);
            break;

    }

    return false;

}

/*
 * To get acceleration values in m/s
 * @param1 : imu_accessor to get ID, I2C_Driver and I2C_Address
 * @param2 : container for storing accel_x value
 * @param3 : container for storing accel_y value
 * @param4 : container for storing accel_z value
 */
void imu_get_accel(imu_accessor *current_imu, float *ax, float *ay, float *az){

    switch(current_imu->id){

        case ID_MPU6050 :

            return imu_get_accel_mpu6050(current_imu, ax, ay, az);
            break;

    }

}

/*
 * To get gyroscope values in degrees/s
 * @param1 : imu_accessor to get ID, I2C_Driver and I2C_Address
 * @param2 : container for storing gyro_x value
 * @param3 : container for storing gyro_y value
 * @param4 : container for storing gyro_z value
 */
void imu_get_gyro(imu_accessor *current_imu, float *gx, float *gy, float *gz){

    switch(current_imu->id){

        case ID_MPU6050 :

            return imu_get_gyro_mpu6050(current_imu, gx, gy, gz);
            break;

    }

}

/*
 * To get accleration values in m/s and gyroscope values in degrees/s
 * @param1 : imu_accessor to get ID, I2C_Driver and I2C_Address
 * @param2 : container for storing accel_x value
 * @param3 : container for storing accel_y value
 * @param4 : container for storing accel_z value
 * @param5 : container for storing gyro_x value
 * @param6 : container for storing gyro_y value
 * @param7 : container for storing gyro_z value
 */
void imu_get_all(imu_accessor *current_imu, float *ax, float *ay, float *az, float *gx, float *gy, float *gz){

    switch(current_imu->id){

        case ID_MPU6050 :

            return imu_get_all_mpu6050(current_imu, ax, ay, az, gx, gy, gz);
            break;

    }

}


/*
 * To get raw acceleration values
 * @param1 : imu_accessor to get ID, I2C_Driver and I2C_Address
 * @param2 : container for storing accel_x value
 * @param3 : container for storing accel_y value
 * @param4 : container for storing accel_z value
 */
void imu_get_accel_raw(imu_accessor *current_imu, int16_t *ax, int16_t *ay, int16_t *az){

    switch(current_imu->id){

        case ID_MPU6050 :

            return imu_get_accel_raw_mpu6050(current_imu, ax, ay, az);
            break;

    }

}

/*
 * To get raw gyroscope values
 * @param1 : imu_accessor to get ID, I2C_Driver and I2C_Address
 * @param2 : container for storing gyro_x value
 * @param3 : container for storing gyro_y value
 * @param4 : container for storing gyro_z value
 */
void imu_get_gyro_raw(imu_accessor *current_imu, int16_t *gx, int16_t *gy, int16_t *gz){

    switch(current_imu->id){

        case ID_MPU6050 :

            return imu_get_gyro_raw_mpu6050(current_imu, gx, gy, gz);
            break;

    }

}

/*
 * To get raw accleration values and gyroscope values in degrees/s
 * @param1 : imu_accessor to get ID, I2C_Driver and I2C_Address
 * @param2 : container for storing accel_x value
 * @param3 : container for storing accel_y value
 * @param4 : container for storing accel_z value
 * @param5 : container for storing gyro_x value
 * @param6 : container for storing gyro_y value
 * @param7 : container for storing gyro_z value
 */
void imu_get_all_raw(imu_accessor *current_imu, int16_t *ax, int16_t *ay, int16_t *az, int16_t *gx, int16_t *gy, int16_t *gz){

    switch(current_imu->id){

        case ID_MPU6050 :

            return imu_get_all_raw_mpu6050(current_imu, ax, ay, az, gx, gy, gz);
            break;

    }

}