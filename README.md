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
