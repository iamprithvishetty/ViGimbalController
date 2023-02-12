#ifndef IMU_ACCESS_H_
#define IMU_ACCESS_H_

#include "hal.h"

// The specific id is used to call the low level driver for the imu
typedef enum{

    ID_MPU6050

}imu_id;

// This is to define if the imu is camera mounted or pcb mounted
typedef enum{

    MOUNT_CAMERA,
    MOUNT_PLATFORM

}imu_mount;

// This accessor is used to setup an imu with all required configuration params that will be used
typedef struct{

    I2CDriver *i2c_driver;
    imu_id id;
    imu_mount mount;
    int orientation;
    union{
        uint8_t imu_addr;
        struct{
            uint8_t accel_addr;
            uint8_t gyro_addr;
        };
    };
    double gyro_scale_factor;
    double accel_scale_factor;

    int gyro_bias_x, gyro_bias_y, gyro_bias_z;
    int accel_bias_x, accel_bias_y, accel_bias_z;

    bool is_initialized;

}imu_accessor;

bool imu_initialize(imu_accessor *current_imu);
void imu_get_accel(imu_accessor *current_imu, float *ax, float *ay, float *az);
void imu_get_gyro(imu_accessor *current_imu, float *gx, float *gy, float *gz);
void imu_get_all(imu_accessor *current_imu, float *ax, float *ay, float *az, float *gx, float *gy, float *gz);
void imu_get_accel_raw(imu_accessor *current_imu, int16_t *ax, int16_t *ay, int16_t *az);
void imu_get_gyro_raw(imu_accessor *current_imu, int16_t *gx, int16_t *gy, int16_t *gz);
void imu_get_all_raw(imu_accessor *current_imu, int16_t *ax, int16_t *ay, int16_t *az, int16_t *gx, int16_t *gy, int16_t *gz);

#endif