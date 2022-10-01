#ifndef ORIENTATION_H_
#define ORIENTATION_H_

#include "imu_access.h"

void orientation_remap(imu_accessor *current_imu, float *ax, float *ay, float *az, float *gx, float *gy, float *gz);

#endif