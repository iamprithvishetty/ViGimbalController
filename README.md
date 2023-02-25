# ✨ViGimbalController
## _3-axis Camera Stabilizer for Stom32 Gimbal Board_

ViGimbalController is an *Open Source* software for 3-axis camera stabilizer built on [ChibiOS](https://www.chibios.org/dokuwiki/doku.php) 

## Hardware Used

Strom32 BGC - ***STM32F103RCT6***


## Features

- Configurable UART Communication
- Support for IMU2 (Better Performance)
- Auto Gyro Claibration
- Data storage in the FLASH Memory
- Data Debugging


## Setting Up The Project

1) **Install Ubuntu** - [Guide](https://ubuntu.com/tutorials/install-ubuntu-desktop#1-overview)
2) **After installation**
    ```sh
    sudo apt update
    sudo apt upgrade
    ```
3) **Install ST-Link v2**
    1) Install Necessary Librarires
        ```sh
        sudo apt install git make cmake libusb-1.0-0-dev
        sudo apt install gcc build-essential
        ```
    2) Build the ST-Link Utilities
        ```sh
        cd username
        mkdir stm32
        cd stm32
        git clone https://github.com/stlink-org/stlink
        cd stlink
        cmake .
        make
        ```    
    3) Copying the Built Binaries
        ```sh
        cd bin
        sudo cp st-* /usr/local/bin
        cd ../lib
        sudo cp *.so* /lib32
        ```
    4) Copying the udev Rules
        ```sh
        cd ../../../../
        sudo cp stlink/config/udev/rules.d/49-stlinkv* /etc/udev/rules.d/
        ```    
    5) Plug the ST-Link device into the USB port and verify if ST-Link is detected
        ```sh
        lsusb
        ```
4) **Install gcc-arm-none-eabi** 
    ```sh
    sudo apt update
    sudo apt install gcc-arm-none-eabi
    ```
5) **Install openocd**
    ```sh
    sudo apt install openocd
    ```
    
## Building and Uploading the Code
1) **Clone the project**
    ```sh
    git clone https://github.com/iamprithvishetty/ViGimbalController.git
    ```
2) **Go into the project**
    ```sh
    cd ViGimbalController
    ```
3) **Build the code**
    ```sh
    make 
    ```
4) **Build and upload the code**
    ```sh
    make upload
    ```

## Gimbal USB Commands

**How to Use**
- Retrieve the data ***GC+Command?*** Eg :- ***GC+PWR_PITCH?***
- Set the data ***GC+Command=Value*** Eg :- ***GC+PWR+PITCH=35***
- Min value is the minimum it can be set to
- Max value is the maximum it can be set to
- If Min and Max both are 0 then the data is only readable
- Default value is the initial setting of the attribute
- The data is either Integer i.e -2, -1, 0, 1, 2 etc or Float i.e 1.5, 1.2, 0.5,-0.2, -1.3 etc



| Attribute                            | Command          | Min | Max  | Default | Type     |
|--------------------------------------|------------------|-----|------|---------|----------|
| Pitch Power                          | PWR_PITCH        | 0   | 100  | 40      | INTEGER  |
| Pitch Pole Pair                      | PP_PITCH         | 0   | 20   | 7       | INTEGER  |
| Pitch Motor Direction                | DIR_PITCH        | -1  | 1    | 1       | INTEGER  |
| Proportional Gain Angle Pitch        | P_ANG_PITCH      | 0   | 1000 | 1.0     | FLOATING |
| Proportional Gain Rotation Pitch     | P_ROT_PITCH      | 0   | 1000 | 20.0    | FLOATING |
| Integral Gain Rotation Pitch         | I_ROT_PITCH      | 0   | 1000 | 0.0     | FLOATING |
| Derivative Gain Rotation Pitch       | D_ROT_PITCH      | 0   | 1000 | 0.1     | FLOATING |
| Pitch User Angle                     | ANGLE_PITCH      | -90 | 90   | 0.0     | FLOATING |
| Roll Power                           | PWR_ROLL         | 0   | 100  | 50      | INTEGER  |
| Roll Pole Pair                       | PP_ROLL          | 0   | 20   | 7       | INTEGER  |
| Roll Motor Direction                 | DIR_ROLL         | -1  | 1    | 1       | INTEGER  |
| Proportional Gain Angle Roll         | P_ANG_ROLL       | 0   | 1000 | 1.0     | FLOATING |
| Proportional Gain Rotation Roll      | P_ROT_ROLL       | 0   | 1000 | 30.0    | FLOATING |
| Integral Gain Rotation Roll          | I_ROT_ROLL       | 0   | 1000 | 0.0     | FLOATING |
| Derivative Gain Rotation Roll        | D_ROT_ROLL       | 0   | 1000 | 0.45    | FLOATING |
| Yaw Power                            | PWR_YAW          | 0   | 100  | 30      | INTEGER  |
| Yaw Pole Pair                        | PP_YAW           | 0   | 20   | 7       | INTEGER  |
| Yaw Motor Direction                  | DIR_YAW          | -1  | 1    | 1       | INTEGER  |
| Proportional Gain Rotation Yaw       | P_ROT_YAW        | 0   | 1000 | 20.0    | FLOATING |
| Integral Gain Rotation Yaw           | I_ROT_YAW        | 0   | 1000 | 0.0     | FLOATING |
| Derivative Gain Rotation Yaw         | D_ROT_YAW        | 0   | 1000 | 0.1     | FLOATING |
| Debug via USB                        | DEBUG            | 0   | 1    | 0       | INTEGER  |
| R1 Resistor Voltage Divider in kOhms | RESISTOR_UP      | 0   | 1000 | 0.0     | FLOATING |
| R2 Resistor Voltage Divider in kOhms | RESISTOR_DOWN    | 0   | 1000 | 0.0     | FLOATING |
| Battery Voltage in V                 | BATT_VOLT        | 0   | 0    |         | FLOATING |
| Battery LPF Gain                     | BATT_ALPHA       | 0   | 1    | 0.0     | FLOATING |
| Enable IMU 2                         | ENABLE_IMU2      | 0   | 1    | 0       | INTEGER  |
| IMU 1 Orientation                    | IMU1_ORIENTATION | 1   | 24   | 1       | INTEGER  |
| Gimbal Mode                          | MODE             | 1   | 3    | 1       | INTEGER  |
| Yaw Dead Zone                        | YAW_DEAD_ZONE    | 4   | 15   | 4       | FLOATING |
| Yaw Speed                            | YAW_SPEED        | 1   | 5    | 3       | INTEGER  |
| Pitch Dead Zone                      | PITCH_DEAD_ZONE  | 4   | 15   | 4       | FLOATING |
| Pitch Speed                          | PITCH_SPEED      | 1   | 5    | 3       | INTEGER  |

## Command Description

***Pitch Power, Roll Power and Yaw Power***
- Voltage supplied to the motor, ranges from 0-100%

***Pitch Pole Pair, Roll Pole Pair and Yaw Pole Pair***
- The number of pole pairs for each motor

***Pitch Motor Direction, Roll Motor Direction and Yaw Motor Direction***
- The direction can either be -1 or +1, 0 means the motor won't move
- The motor direction needs to be set based on it default rotation direction

***Proporitonal Gain Angle Pitch, Proportional Gain Angle Roll and Proportional Gain Angle Yaw***
- This is the proportional gain component for the angle correction
- Higher the gain the faster the angle will get corrected but it'll be more unstable
- Try finding the sweet spot, 1.0 normally works fine

***Proportional Gain Rotation Pitch, Proportional Gain Rotation Roll and Proportional Gain Rotation Yaw***
- This is the proportional gain component for the rotation correction
- Higher the gain better the response but it's prone to be unstable at very high values
- Try finding the sweet spot, normally greater than 10.0

***Integral Gain Rotation Pitch, Integeral Gain Rotation Roll and Integral Gain Rotation Yaw***
- This is the integral gain component for the rotation component
- There's a provision given for integral but it's better to not use it here as it doesn't help much

***Derivative Gain Rotation Pitch, Derivative Gain Rotation Roll and Derivative Gain Rotation Yaw***
- This is the derivative gain component for the rotation correction
- Higher the value more unstable the response will be, keep the values lower initially and then try increasing

***Pitch User Angle***
- The default angle for camera pitch, the camera will try to be at that angle

***Debug via USB***
- This starts printing out the raw value for accel, gyro and angle
- The data are in order accel_x_cam, accel_y_cam, accel_z_cam, gyro_x_cam, gyro_y_cam, gyro_z_cam, angle_cam[PITCH], angle_cam[ROLL], angle_cam[YAW], accel_x_platform, accel_y_platform, accel_z_platform, gyro_x_platform, gyro_y_platform, gyro_z_platform, angle_platform[PITCH], angle_platform[ROLL], angle_platform[YAW], relative_yaw, relative_pitch

***Battery Functionalities***
- Yet to be added

***Enable IMU2***
- Enables the IMU2 if present, and uses the IMU2 for better stabilization
- Currently the IMU2 is supported only for one orientation (x-> left, y-> back, z-> up) wrt camera pov
- Here it is important to ensure that the inital position of the camera is facing the one mentioned above, after that IMU2 should be enabled

***IMU 1 Orientation***
- There are 16 IMU1 orientations supported currently
- The Camera POV is always front, the IMU orientation is wrt the camera

| Value     | Orientation IMU                   |
|-----------|-----------------------------------|
| 1         |   x-> right, y-> back, z-> down   |
| 2         |   x-> back, y-> left, z-> down    |
| 3         |   x-> left, y-> front, z->down    |
| 4         |   x-> front, y->right, z->down    |
| 5         |   x-> right, y->front, z->up      |
| 6         |   x-> back, y->right, z->up       |
| 7         |   x->left, y->back, z->up         |
| 8         |   x->front, y->left, z->up        |
| 9         |   x->right, y->down, z->front     |
| 10        |   x->back, y->down, z->right      |
| 11        |   x->left, y->down, z->back       |
| 12        |   x->back, y->down, z->left       |
| 13        |   x->right, y->up, z->back        |
| 14        |   x->front, y->up, z->right       |
| 15        |   x->left, y->up, z->front        |
| 16        |   x->back, y->up, z->left         |

***Gimbal Modes***
- There are three Gimbal Modes
- Gimbal Modes are only active when IMU2 is enabled
1) Lock Mode - The Gimbal will lock itself at that postion
2) Pan Mode - The Yaw will pan based on the movement
3) Follow Mode - The Pitch and Yaw will pan based on the movement

***Yaw and Pitch Dead Zone***
- The pitch and yaw dead zone can be set for pan and follow mode
- This is to restrict the movement for certain angle threhsold

***Yaw and Pitch Speed***
- This is the speed it should move at in pan and follow mode
