#include "orientation.h"

void orientation_remap(imu_accessor *current_imu, float *ax, float *ay, float *az, float *gx, float *gy, float *gz){

    float temporary;

    if(current_imu->mount == MOUNT_CAMERA){

        switch(current_imu->orientation){

            // x-> right, y-> back, z-> down
            case 1:
                *ax = -*ax;
                *ay = *ay;
                *az = -*az;
                *gx = -*gx;
                *gy = *gy;
                *gz = -*gz;
                break;

            // x-> back, y-> left, z-> down
            case 2:
                temporary = *ax;
                *ax = *ay;
                *ay = temporary;
                *az = -*az;
                temporary = *gx;
                *gx = *gy;
                *gy = temporary;
                *gz = -*gz;
                break;

            // x-> left, y-> front, z->down
            case 3:
                *ax = *az;
                *ay = -*ay;
                *az = -*az;
                *gx = *gx;
                *gy = -*gy;
                *gz = -*gz;
                break;

            // x-> front, y->right, z->down
            case 4:
                temporary = *ax;
                *ax = -*ay;
                *ay = -temporary;
                *az = -*az;
                temporary = *gx;
                *gx = -*gy;
                *gy = -temporary;
                *gz = -*gz;
                break;

            // x-> right, y->front, z->up
            case 5:
                *ax = -*ax;
                *ay = -*ay;
                *az = *az;
                *gx = -*gx;
                *gy = -*gy;
                *gz = *gz;
                break;

            // x-> back, y->right, z->up
            case 6:
                temporary = *ax;
                *ax = -*ay;
                *ay = temporary;
                *az = *az;
                temporary = *gx;
                *gx = -*gy;
                *gy = temporary;
                *gz = *gz;
                break;

            // x->left, y->back, z->up
            case 7:
                *ax = *ax;
                *ay = *ay;
                *az = *az;
                *gx = *gx;
                *gy = *gy;
                *gz = *gz;
                break;
            
            // x->front, y->left, z->up
            case 8:
                temporary = *ax;
                *ax = *ay;
                *ay = -temporary;
                *az = *az;
                temporary = *gx;
                *gx = *gy;
                *gy = -temporary;
                *gz = *gz;
                break;
        
            case 9:
                break;

            case 10:
                break;
        
            case 11:
                break;
        
            case 12:
                break;

            case 13:
                break;

            case 14:
                break;

            case 15:
                break;

            case 16:
                break;

            case 17:
                break;

            case 18:
                break;

            case 19:
                break;

            case 20:
                break;

            case 21:
                break;

            case 22:
                break;

            case 23:
                break;

            case 24:
                break;


        }

    }
    else{

        switch(current_imu->orientation){

            case 1:
                break;

            case 2:
                break;

            case 3:
                break;

            case 4:
                break;

            case 5:
                break;

            case 6:
                break;

            case 7:
                break;
            
            case 8:
                break;
        
            case 9:
                break;

            case 10:
                break;
        
            case 11:
                break;
        
            case 12:
                break;

            case 13:
                break;

            case 14:
                break;

            case 15:
                break;

            case 16:
                break;

            case 17:
                break;

            case 18:
                break;

            case 19:
                break;

            case 20:
                break;

            case 21:
                break;

            case 22:
                break;

            case 23:
                break;

            case 24:
                break;

        }

    }

}