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

            // x->right, y->down, z->front
            case 9:
                *ax = -*ax;
                temporary = *ay;
                *ay = -*az;
                *az = -temporary;
                *gx = -*gx;
                temporary = *gy;
                *gy = -*gz;
                *gz = -temporary;
                break;

            // x->back, y->down, z->right
            case 10:
                temporary = *ax;
                *ax = -*az;
                *az = -*ay;
                *ay = temporary;
                temporary = *gx;
                *gx = -*gz;
                *gz = -*gy;
                *gy = temporary;
                break;

            // x->left, y->down, z->back
            case 11:
                *ax = *ax;
                temporary = *ay;
                *ay = *az;
                *az = -temporary;
                *gx = *gx;
                temporary = *gy;
                *gy = *gz;
                *gz = -temporary;
                break;

            // x->back, y->down, z->left
            case 12:
                temporary = *ax;
                *ax = *az;
                *az = -*ay;
                *ay = -temporary;
                temporary = *gx;
                *gx = *gz;
                *gz = -*gy;
                *gy = -temporary;
                break;
            
            // x->right, y->up, z->back
            case 13:
                temporary = *ay;
                *ax = -*ax;
                *ay = *az;
                *az = temporary;
                temporary = *gy;
                *gx = - *gx;
                *gy = *gz;
                *gz = temporary;
                break;

            // x->front, y->up, z->right
            case 14:
                temporary = *ax;
                *ax = -*az;
                *az = *ay;
                *ay = -temporary;
                temporary = *gx;
                *gx = -*gz;
                *gz = *gy;
                *gy = -temporary;
                break;

            // x->left, y->up, z->front
            case 15:
                temporary = *ay;
                *ax = *ax;
                *ay = -*az;
                *az = temporary;
                temporary = *gy;
                *gx = *gx;
                *gy = -*gz;
                *gz = temporary;
                break;

            // x->back, y->up, z->left
            case 16:
                temporary = *ax;
                *ax = *az;
                *az = *ay;
                *ay = temporary;
                temporary = *gx;
                *gx = *gz;
                *gz = *gy;
                *gy = temporary;
                break;
            
            // x->down, y->front , z->right
            case 17:
                temporary = *ax;
                *ax = -*az;
                *ay = -*ay;
                *az = -temporary;
                temporary = *gx;
                *gx = -*gz;
                *gy = -*gy;
                *gz = -temporary;
                break;

            // x->down, y->right , z->back
            case 18:
                temporary = *ax;
                *ax = -*ay;
                *ay = *az;
                *az = -temporary;
                temporary = *gx;
                *gx = -*gy;
                *gy = -*gz;
                *gz = -temporary;
                break;

            // x->down, y->back , z->left
            case 19:
                temporary = *ax;
                *ax = *az;
                *ay = *ay;
                *az = -temporary;
                temporary = *gx;
                *gx = *gz;
                *gy = *gy;
                *gz = -temporary;
                break;

            // x->down, y->left , z->front
            case 20:
                temporary = *ax;
                *ax = *ay;
                *ay = -*az;
                *az = -temporary;
                temporary = *gx;
                *gx = *gy;
                *gy = -*gz;
                *gz = -temporary;
                break;

            // x->up, y->back, z->right
            case 21:
                temporary = *ax;
                *ax = -*az;
                *ay = *ay;
                *az = temporary;
                temporary = *gx;
                *gx = -*gz;
                *gy = *gy;
                *gz = temporary;
                break;
            
            // x->up, y->left, z->back
            case 22:
                temporary = *ax;
                *ax = *ay;
                *ay = *az;
                *az = temporary;
                temporary = *gx;
                *gx = *gy;
                *gy = *gz;
                *gz = temporary;
                break;

            // x->up, y->front, z->left
            case 23:
                temporary = *ax;
                *ax = *az;
                *ay = -*ay;
                *az = temporary;
                temporary = *gx;
                *gx = *gz;
                *gy = -*gy;
                *gz = temporary;
                break;

            // x->up, y->right, z->front
            case 24:
                temporary = *ax;
                *ax = -*ay;
                *ay = -*az;
                *az = temporary;
                temporary = *gx;
                *gx = -*gy;
                *gy = -*gz;
                *gz = temporary;
                break;


        }

    }
    else{

        switch(current_imu->orientation){
            
            // x->left, y->back, z->up
            case 1:
                *ax = *ax;
                *ay = *ay;
                *az = *az;
                *gx = *gx;
                *gy = *gy;
                *gz = *gz;
                break;

            // x->front, y->left, z->up
            case 2:
                temporary = *ax;
                *ax = *ay;
                *ay = -temporary;
                *az = *az;
                temporary = *gx;
                *gx = *gy;
                *gy = -temporary;
                *gz = *gz;
                break;

            // x->right, y->front, z->up
            case 3:
                *ax = -*ax;
                *ay = -*ay;
                *az = *az;
                *gx = -*gx;
                *gy = -*gy;
                *gz = *gz;
                break;

            // x->back, y->right, z->up
            case 4:
                temporary = *ax;
                *ax = -*ay;
                *ay = temporary;
                *az = *az;
                temporary = *gx;
                *gx = -*gy;
                *gy = temporary;
                *gz = *gz;
                break;

            // x->left, y->front, z->down
            case 5:
                *ax = *ax;
                *ay = -*ay;
                *az = -*az;
                *gx = *gx;
                *gy = -*gy;
                *gz = -*gz;
                break;

            // x->front, y->right, z->down 
            case 6:
                temporary = *ax;
                *ax = -*ay;
                *ay = -temporary;
                *az = -*az;
                temporary = *gx;
                *gx = -*gy;
                *gy = -temporary;
                *gz = -*gz;                
                break;
            
            // x->right, y->back, z->down
            case 7:
                *ax = -*ax;
                *ay = *ay;
                *az = -*az;
                *gx = -*gx;
                *gy = *gy;
                *gz = -*gz;
                break;
            
            // x->back, y->left, z->down
            case 8:
                temporary = *ax;
                *ax = *ay;
                *ay = temporary;
                *az = -*az;
                temporary = *gx;
                *gx = *gy;
                *gy = temporary;
                *gz = -*gz;
                break;
        
            // x->left, y->down, z->back
            case 9:
                temporary = *az;
                *ax = *ax;
                *az = -*ay;
                *ay = *az;
                temporary = *gz;
                *gx = *gx;
                *gz = -*gy;
                *gy = *gz;
                break;

            // x->front, y->down, z->left
            case 10:
                temporary = *ax;
                *ax = *az;
                *az = -*ay;
                *ay = -temporary;
                temporary = *gx;
                *gx = *gz;
                *gz = -*gy;
                *gy = -temporary;
                break;
        
            //  x->right, y->down, z->front
            case 11:
                temporary = *ay;
                *ax = -*ax;
                *ay = -*az;
                *az = -*ay;
                temporary = *gy;
                *gx = -*gx;
                *gy = -*gz;
                *gz = -*gy;
                break;

            // x->back, y->down, z->right
            case 12:
                temporary = *ax;
                *ax = -*az;
                *az = -*ay;
                *ay = temporary;
                temporary = *gx;
                *gx = -*gz;
                *gz = -*gy;
                *gy = temporary;
                break;

            // x->left, y->up, z->front
            case 13:
                temporary = *ay;
                *ax = *ax;
                *ay = -*az;
                *az = temporary;
                temporary = *gy;
                *gx = *gx;
                *gy = -*gz;
                *gz = temporary;
                break;

            // x->front, y->up, z->right
            case 14:
                temporary = *ax;
                *ax = -*az;
                *az = *ay;
                *ay = -temporary;
                temporary = *gx;
                *gx = -*gz;
                *gz = *gy;
                *gy = -temporary;
                break;

            // x->right, y->up, z->back
            case 15:
                temporary = *ay;
                *ax = -*ax;
                *ay = *az;
                *az = temporary;
                temporary = *gy;
                *gx = -*gx;
                *gy = *gz;
                *gz = temporary;
                break;

            // x->back, y->up, z->left
            case 16:
                temporary = *ax;
                *ax = *az;
                *az = *ay;
                *ay = temporary;
                temporary = *gx;
                *gx = *gz;
                *gz = *gy;
                *gy = temporary;
                break;

            // x->up, y->back, z->right
            case 17:
                temporary = *ax;
                *ax = -*az;
                *ay = *ay;
                *az = temporary;
                temporary = *gx;
                *gx = -*gz;
                *gy = *gy;
                *gz = temporary;
                break;

            // x->up, y->left, z->back
            case 18:
                temporary = *ax;
                *ax = *ay;
                *ay = *az;
                *az = temporary;
                temporary = *gx;
                *gx = *gy;
                *gy = *gz;
                *gz = temporary;
                break;

            // x->up, y->front, z->left
            case 19:
                temporary = *ax;
                *ax = *az;
                *ay = -*ay;
                *az = temporary;
                temporary = *ax;
                *gx = *gz;
                *gy = -*gy;
                *gz = temporary;
                break;

            // x->up, y->right, z->front
            case 20:
                temporary = *ax;
                *ax = -*ay;
                *ay = -*az;
                *az = temporary;
                temporary = *gx;
                *gx = -*gy;
                *gy = -*gz;
                *gz = temporary;
                break;

            // x->down, y->back, z->left
            case 21:
                temporary = *ax;
                *ax = *az;
                *ay = *ay;
                *az = -temporary;
                temporary = *gx;
                *gx = *gz;
                *gy = *gy;
                *gz = -temporary;
                break;

            // x->down, y->left, z->front
            case 22:
                temporary = *ax;
                *ax = *ay;
                *ay = -*az;
                *az = -temporary;
                temporary = *gx;
                *gx = *gy;
                *gy = -*gz;
                *gz = -temporary;
                break;

            // x->down, y->front, z->right
            case 23:
                temporary = *ax;
                *ax = -*az;
                *ay = -*ay;
                *az = -temporary;
                temporary = *gx;
                *gx = -*gz;
                *gy = -*gy;
                *gz = -temporary;
                break;

            // x->down, y->right, z->back
            case 24:
                temporary = *ax;
                *ax = -*ay;
                *ay = *az;
                *az = -temporary;
                temporary = *gx;
                *gx = -*gy;
                *gy = *gz;
                *gz = -temporary;
                break;

        }

    }

}