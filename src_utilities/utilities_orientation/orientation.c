#include "orientation.h"

void orientation_remap(imu_accessor *current_imu, float *ax, float *ay, float *az, float *gx, float *gy, float *gz){

    if(current_imu->mount == MOUNT_CAMERA){

        switch(current_imu->orientation){

            // x-> left, y-> front, z-> down
            case 1:
                *ax = -*ax;
                *ay = *ay;
                *az = -*az;
                *gx = -*gx;
                *gy = *gy;
                *gz = -*gz;
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