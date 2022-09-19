/* ============================================
ChibiOS I2Cdev MPU6050 device class code is placed under the MIT license
Copyright (c) 2012 Jan Schlemminger

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
===============================================
*/

#ifndef MPU6050_H_
#define MPU6050_H_

#include "hal.h"
#include "imu_access.h"

#define MPU6050_ADDRESS_AD0_LOW     0x68 // address pin low (GND), default for InvenSense evaluation board
#define MPU6050_ADDRESS_AD0_HIGH    0x69 // address pin high (VCC)
#define MPU6050_DEFAULT_ADDRESS     MPU6050_ADDRESS_AD0_LOW

#define MPU6050_RA_XG_OFFS_TC       0x00 //[7] PWR_MODE, [6:1] XG_OFFS_TC, [0] OTP_BNK_VLD
#define MPU6050_RA_YG_OFFS_TC       0x01 //[7] PWR_MODE, [6:1] YG_OFFS_TC, [0] OTP_BNK_VLD
#define MPU6050_RA_ZG_OFFS_TC       0x02 //[7] PWR_MODE, [6:1] ZG_OFFS_TC, [0] OTP_BNK_VLD
#define MPU6050_RA_X_FINE_GAIN      0x03 //[7:0] X_FINE_GAIN
#define MPU6050_RA_Y_FINE_GAIN      0x04 //[7:0] Y_FINE_GAIN
#define MPU6050_RA_Z_FINE_GAIN      0x05 //[7:0] Z_FINE_GAIN
#define MPU6050_RA_XA_OFFS_H        0x06 //[15:0] XA_OFFS
#define MPU6050_RA_XA_OFFS_L_TC     0x07
#define MPU6050_RA_YA_OFFS_H        0x08 //[15:0] YA_OFFS
#define MPU6050_RA_YA_OFFS_L_TC     0x09
#define MPU6050_RA_ZA_OFFS_H        0x0A //[15:0] ZA_OFFS
#define MPU6050_RA_ZA_OFFS_L_TC     0x0B
#define MPU6050_RA_XG_OFFS_USRH     0x13 //[15:0] XG_OFFS_USR
#define MPU6050_RA_XG_OFFS_USRL     0x14
#define MPU6050_RA_YG_OFFS_USRH     0x15 //[15:0] YG_OFFS_USR
#define MPU6050_RA_YG_OFFS_USRL     0x16
#define MPU6050_RA_ZG_OFFS_USRH     0x17 //[15:0] ZG_OFFS_USR
#define MPU6050_RA_ZG_OFFS_USRL     0x18
#define MPU6050_RA_SMPLRT_DIV       0x19
#define MPU6050_RA_CONFIG           0x1A
#define MPU6050_RA_GYRO_CONFIG      0x1B
#define MPU6050_RA_ACCEL_CONFIG     0x1C
#define MPU6050_RA_FF_THR           0x1D
#define MPU6050_RA_FF_DUR           0x1E
#define MPU6050_RA_MOT_THR          0x1F
#define MPU6050_RA_MOT_DUR          0x20
#define MPU6050_RA_ZRMOT_THR        0x21
#define MPU6050_RA_ZRMOT_DUR        0x22
#define MPU6050_RA_FIFO_EN          0x23
#define MPU6050_RA_I2C_MST_CTRL     0x24
#define MPU6050_RA_I2C_SLV0_ADDR    0x25
#define MPU6050_RA_I2C_SLV0_REG     0x26
#define MPU6050_RA_I2C_SLV0_CTRL    0x27
#define MPU6050_RA_I2C_SLV1_ADDR    0x28
#define MPU6050_RA_I2C_SLV1_REG     0x29
#define MPU6050_RA_I2C_SLV1_CTRL    0x2A
#define MPU6050_RA_I2C_SLV2_ADDR    0x2B
#define MPU6050_RA_I2C_SLV2_REG     0x2C
#define MPU6050_RA_I2C_SLV2_CTRL    0x2D
#define MPU6050_RA_I2C_SLV3_ADDR    0x2E
#define MPU6050_RA_I2C_SLV3_REG     0x2F
#define MPU6050_RA_I2C_SLV3_CTRL    0x30
#define MPU6050_RA_I2C_SLV4_ADDR    0x31
#define MPU6050_RA_I2C_SLV4_REG     0x32
#define MPU6050_RA_I2C_SLV4_DO      0x33
#define MPU6050_RA_I2C_SLV4_CTRL    0x34
#define MPU6050_RA_I2C_SLV4_DI      0x35
#define MPU6050_RA_I2C_MST_STATUS   0x36
#define MPU6050_RA_INT_PIN_CFG      0x37
#define MPU6050_RA_INT_ENABLE       0x38
#define MPU6050_RA_DMP_INT_STATUS   0x39
#define MPU6050_RA_INT_STATUS       0x3A
#define MPU6050_RA_ACCEL_XOUT_H     0x3B
#define MPU6050_RA_ACCEL_XOUT_L     0x3C
#define MPU6050_RA_ACCEL_YOUT_H     0x3D
#define MPU6050_RA_ACCEL_YOUT_L     0x3E
#define MPU6050_RA_ACCEL_ZOUT_H     0x3F
#define MPU6050_RA_ACCEL_ZOUT_L     0x40
#define MPU6050_RA_TEMP_OUT_H       0x41
#define MPU6050_RA_TEMP_OUT_L       0x42
#define MPU6050_RA_GYRO_XOUT_H      0x43
#define MPU6050_RA_GYRO_XOUT_L      0x44
#define MPU6050_RA_GYRO_YOUT_H      0x45
#define MPU6050_RA_GYRO_YOUT_L      0x46
#define MPU6050_RA_GYRO_ZOUT_H      0x47
#define MPU6050_RA_GYRO_ZOUT_L      0x48
#define MPU6050_RA_EXT_SENS_DATA_00 0x49
#define MPU6050_RA_EXT_SENS_DATA_01 0x4A
#define MPU6050_RA_EXT_SENS_DATA_02 0x4B
#define MPU6050_RA_EXT_SENS_DATA_03 0x4C
#define MPU6050_RA_EXT_SENS_DATA_04 0x4D
#define MPU6050_RA_EXT_SENS_DATA_05 0x4E
#define MPU6050_RA_EXT_SENS_DATA_06 0x4F
#define MPU6050_RA_EXT_SENS_DATA_07 0x50
#define MPU6050_RA_EXT_SENS_DATA_08 0x51
#define MPU6050_RA_EXT_SENS_DATA_09 0x52
#define MPU6050_RA_EXT_SENS_DATA_10 0x53
#define MPU6050_RA_EXT_SENS_DATA_11 0x54
#define MPU6050_RA_EXT_SENS_DATA_12 0x55
#define MPU6050_RA_EXT_SENS_DATA_13 0x56
#define MPU6050_RA_EXT_SENS_DATA_14 0x57
#define MPU6050_RA_EXT_SENS_DATA_15 0x58
#define MPU6050_RA_EXT_SENS_DATA_16 0x59
#define MPU6050_RA_EXT_SENS_DATA_17 0x5A
#define MPU6050_RA_EXT_SENS_DATA_18 0x5B
#define MPU6050_RA_EXT_SENS_DATA_19 0x5C
#define MPU6050_RA_EXT_SENS_DATA_20 0x5D
#define MPU6050_RA_EXT_SENS_DATA_21 0x5E
#define MPU6050_RA_EXT_SENS_DATA_22 0x5F
#define MPU6050_RA_EXT_SENS_DATA_23 0x60
#define MPU6050_RA_MOT_DETECT_STATUS    0x61
#define MPU6050_RA_I2C_SLV0_DO      0x63
#define MPU6050_RA_I2C_SLV1_DO      0x64
#define MPU6050_RA_I2C_SLV2_DO      0x65
#define MPU6050_RA_I2C_SLV3_DO      0x66
#define MPU6050_RA_I2C_MST_DELAY_CTRL   0x67
#define MPU6050_RA_SIGNAL_PATH_RESET    0x68
#define MPU6050_RA_MOT_DETECT_CTRL      0x69
#define MPU6050_RA_USER_CTRL        0x6A
#define MPU6050_RA_PWR_MGMT_1       0x6B
#define MPU6050_RA_PWR_MGMT_2       0x6C
#define MPU6050_RA_BANK_SEL         0x6D
#define MPU6050_RA_MEM_START_ADDR   0x6E
#define MPU6050_RA_MEM_R_W          0x6F
#define MPU6050_RA_DMP_CFG_1        0x70
#define MPU6050_RA_DMP_CFG_2        0x71
#define MPU6050_RA_FIFO_COUNTH      0x72
#define MPU6050_RA_FIFO_COUNTL      0x73
#define MPU6050_RA_FIFO_R_W         0x74
#define MPU6050_RA_WHO_AM_I         0x75

#define MPU6050_TC_PWR_MODE_BIT     7
#define MPU6050_TC_OFFSET_BIT       6
#define MPU6050_TC_OFFSET_LENGTH    6
#define MPU6050_TC_OTP_BNK_VLD_BIT  0

#define MPU6050_VDDIO_LEVEL_VLOGIC  0
#define MPU6050_VDDIO_LEVEL_VDD     1

#define MPU6050_CFG_EXT_SYNC_SET_BIT    5
#define MPU6050_CFG_EXT_SYNC_SET_LENGTH 3
#define MPU6050_CFG_DLPF_CFG_BIT    2
#define MPU6050_CFG_DLPF_CFG_LENGTH 3

#define MPU6050_EXT_SYNC_DISABLED       0x0
#define MPU6050_EXT_SYNC_TEMP_OUT_L     0x1
#define MPU6050_EXT_SYNC_GYRO_XOUT_L    0x2
#define MPU6050_EXT_SYNC_GYRO_YOUT_L    0x3
#define MPU6050_EXT_SYNC_GYRO_ZOUT_L    0x4
#define MPU6050_EXT_SYNC_ACCEL_XOUT_L   0x5
#define MPU6050_EXT_SYNC_ACCEL_YOUT_L   0x6
#define MPU6050_EXT_SYNC_ACCEL_ZOUT_L   0x7

#define MPU6050_DLPF_BW_256         0x00
#define MPU6050_DLPF_BW_188         0x01
#define MPU6050_DLPF_BW_98          0x02
#define MPU6050_DLPF_BW_42          0x03
#define MPU6050_DLPF_BW_20          0x04
#define MPU6050_DLPF_BW_10          0x05
#define MPU6050_DLPF_BW_5           0x06

#define MPU6050_GCONFIG_FS_SEL_BIT      4
#define MPU6050_GCONFIG_FS_SEL_LENGTH   2

#define MPU6050_GYRO_FS_250         0x00
#define MPU6050_GYRO_FS_500         0x01
#define MPU6050_GYRO_FS_1000        0x02
#define MPU6050_GYRO_FS_2000        0x03

#define MPU6050_ACONFIG_XA_ST_BIT           7
#define MPU6050_ACONFIG_YA_ST_BIT           6
#define MPU6050_ACONFIG_ZA_ST_BIT           5
#define MPU6050_ACONFIG_AFS_SEL_BIT         4
#define MPU6050_ACONFIG_AFS_SEL_LENGTH      2
#define MPU6050_ACONFIG_ACCEL_HPF_BIT       2
#define MPU6050_ACONFIG_ACCEL_HPF_LENGTH    3

#define MPU6050_ACCEL_FS_2          0x00
#define MPU6050_ACCEL_FS_4          0x01
#define MPU6050_ACCEL_FS_8          0x02
#define MPU6050_ACCEL_FS_16         0x03

#define MPU6050_DHPF_RESET          0x00
#define MPU6050_DHPF_5              0x01
#define MPU6050_DHPF_2P5            0x02
#define MPU6050_DHPF_1P25           0x03
#define MPU6050_DHPF_0P63           0x04
#define MPU6050_DHPF_HOLD           0x07

#define MPU6050_TEMP_FIFO_EN_BIT    7
#define MPU6050_XG_FIFO_EN_BIT      6
#define MPU6050_YG_FIFO_EN_BIT      5
#define MPU6050_ZG_FIFO_EN_BIT      4
#define MPU6050_ACCEL_FIFO_EN_BIT   3
#define MPU6050_SLV2_FIFO_EN_BIT    2
#define MPU6050_SLV1_FIFO_EN_BIT    1
#define MPU6050_SLV0_FIFO_EN_BIT    0

#define MPU6050_MULT_MST_EN_BIT     7
#define MPU6050_WAIT_FOR_ES_BIT     6
#define MPU6050_SLV_3_FIFO_EN_BIT   5
#define MPU6050_I2C_MST_P_NSR_BIT   4
#define MPU6050_I2C_MST_CLK_BIT     3
#define MPU6050_I2C_MST_CLK_LENGTH  4

#define MPU6050_CLOCK_DIV_348       0x0
#define MPU6050_CLOCK_DIV_333       0x1
#define MPU6050_CLOCK_DIV_320       0x2
#define MPU6050_CLOCK_DIV_308       0x3
#define MPU6050_CLOCK_DIV_296       0x4
#define MPU6050_CLOCK_DIV_286       0x5
#define MPU6050_CLOCK_DIV_276       0x6
#define MPU6050_CLOCK_DIV_267       0x7
#define MPU6050_CLOCK_DIV_258       0x8
#define MPU6050_CLOCK_DIV_500       0x9
#define MPU6050_CLOCK_DIV_471       0xA
#define MPU6050_CLOCK_DIV_444       0xB
#define MPU6050_CLOCK_DIV_421       0xC
#define MPU6050_CLOCK_DIV_400       0xD
#define MPU6050_CLOCK_DIV_381       0xE
#define MPU6050_CLOCK_DIV_364       0xF

#define MPU6050_I2C_SLV_RW_BIT      7
#define MPU6050_I2C_SLV_ADDR_BIT    6
#define MPU6050_I2C_SLV_ADDR_LENGTH 7
#define MPU6050_I2C_SLV_EN_BIT      7
#define MPU6050_I2C_SLV_BYTE_SW_BIT 6
#define MPU6050_I2C_SLV_REG_DIS_BIT 5
#define MPU6050_I2C_SLV_GRP_BIT     4
#define MPU6050_I2C_SLV_LEN_BIT     3
#define MPU6050_I2C_SLV_LEN_LENGTH  4

#define MPU6050_I2C_SLV4_RW_BIT         7
#define MPU6050_I2C_SLV4_ADDR_BIT       6
#define MPU6050_I2C_SLV4_ADDR_LENGTH    7
#define MPU6050_I2C_SLV4_EN_BIT         7
#define MPU6050_I2C_SLV4_INT_EN_BIT     6
#define MPU6050_I2C_SLV4_REG_DIS_BIT    5
#define MPU6050_I2C_SLV4_MST_DLY_BIT    4
#define MPU6050_I2C_SLV4_MST_DLY_LENGTH 5

#define MPU6050_MST_PASS_THROUGH_BIT    7
#define MPU6050_MST_I2C_SLV4_DONE_BIT   6
#define MPU6050_MST_I2C_LOST_ARB_BIT    5
#define MPU6050_MST_I2C_SLV4_NACK_BIT   4
#define MPU6050_MST_I2C_SLV3_NACK_BIT   3
#define MPU6050_MST_I2C_SLV2_NACK_BIT   2
#define MPU6050_MST_I2C_SLV1_NACK_BIT   1
#define MPU6050_MST_I2C_SLV0_NACK_BIT   0

#define MPU6050_INTCFG_INT_LEVEL_BIT        7
#define MPU6050_INTCFG_INT_OPEN_BIT         6
#define MPU6050_INTCFG_LATCH_INT_EN_BIT     5
#define MPU6050_INTCFG_INT_RD_CLEAR_BIT     4
#define MPU6050_INTCFG_FSYNC_INT_LEVEL_BIT  3
#define MPU6050_INTCFG_FSYNC_INT_EN_BIT     2
#define MPU6050_INTCFG_I2C_BYPASS_EN_BIT    1
#define MPU6050_INTCFG_CLKOUT_EN_BIT        0

#define MPU6050_INTMODE_ACTIVEHIGH  0x00
#define MPU6050_INTMODE_ACTIVELOW   0x01

#define MPU6050_INTDRV_PUSHPULL     0x00
#define MPU6050_INTDRV_OPENDRAIN    0x01

#define MPU6050_INTLATCH_50USPULSE  0x00
#define MPU6050_INTLATCH_WAITCLEAR  0x01

#define MPU6050_INTCLEAR_STATUSREAD 0x00
#define MPU6050_INTCLEAR_ANYREAD    0x01

#define MPU6050_INTERRUPT_FF_BIT            7
#define MPU6050_INTERRUPT_MOT_BIT           6
#define MPU6050_INTERRUPT_ZMOT_BIT          5
#define MPU6050_INTERRUPT_FIFO_OFLOW_BIT    4
#define MPU6050_INTERRUPT_I2C_MST_INT_BIT   3
#define MPU6050_INTERRUPT_PLL_RDY_INT_BIT   2
#define MPU6050_INTERRUPT_DMP_INT_BIT       1
#define MPU6050_INTERRUPT_DATA_RDY_BIT      0

// TODO: figure out what these actually do
// UMPL source code is not very obivous
#define MPU6050_DMPINT_5_BIT            5
#define MPU6050_DMPINT_4_BIT            4
#define MPU6050_DMPINT_3_BIT            3
#define MPU6050_DMPINT_2_BIT            2
#define MPU6050_DMPINT_1_BIT            1
#define MPU6050_DMPINT_0_BIT            0

#define MPU6050_MOTION_MOT_XNEG_BIT     7
#define MPU6050_MOTION_MOT_XPOS_BIT     6
#define MPU6050_MOTION_MOT_YNEG_BIT     5
#define MPU6050_MOTION_MOT_YPOS_BIT     4
#define MPU6050_MOTION_MOT_ZNEG_BIT     3
#define MPU6050_MOTION_MOT_ZPOS_BIT     2
#define MPU6050_MOTION_MOT_ZRMOT_BIT    0

#define MPU6050_DELAYCTRL_DELAY_ES_SHADOW_BIT   7
#define MPU6050_DELAYCTRL_I2C_SLV4_DLY_EN_BIT   4
#define MPU6050_DELAYCTRL_I2C_SLV3_DLY_EN_BIT   3
#define MPU6050_DELAYCTRL_I2C_SLV2_DLY_EN_BIT   2
#define MPU6050_DELAYCTRL_I2C_SLV1_DLY_EN_BIT   1
#define MPU6050_DELAYCTRL_I2C_SLV0_DLY_EN_BIT   0

#define MPU6050_PATHRESET_GYRO_RESET_BIT    2
#define MPU6050_PATHRESET_ACCEL_RESET_BIT   1
#define MPU6050_PATHRESET_TEMP_RESET_BIT    0

#define MPU6050_DETECT_ACCEL_ON_DELAY_BIT       5
#define MPU6050_DETECT_ACCEL_ON_DELAY_LENGTH    2
#define MPU6050_DETECT_FF_COUNT_BIT             3
#define MPU6050_DETECT_FF_COUNT_LENGTH          2
#define MPU6050_DETECT_MOT_COUNT_BIT            1
#define MPU6050_DETECT_MOT_COUNT_LENGTH         2

#define MPU6050_DETECT_DECREMENT_RESET  0x0
#define MPU6050_DETECT_DECREMENT_1      0x1
#define MPU6050_DETECT_DECREMENT_2      0x2
#define MPU6050_DETECT_DECREMENT_4      0x3

#define MPU6050_USERCTRL_DMP_EN_BIT             7
#define MPU6050_USERCTRL_FIFO_EN_BIT            6
#define MPU6050_USERCTRL_I2C_MST_EN_BIT         5
#define MPU6050_USERCTRL_I2C_IF_DIS_BIT         4
#define MPU6050_USERCTRL_DMP_RESET_BIT          3
#define MPU6050_USERCTRL_FIFO_RESET_BIT         2
#define MPU6050_USERCTRL_I2C_MST_RESET_BIT      1
#define MPU6050_USERCTRL_SIG_COND_RESET_BIT     0

#define MPU6050_PWR1_DEVICE_RESET_BIT   7
#define MPU6050_PWR1_SLEEP_BIT          6
#define MPU6050_PWR1_CYCLE_BIT          5
#define MPU6050_PWR1_TEMP_DIS_BIT       3
#define MPU6050_PWR1_CLKSEL_BIT         2
#define MPU6050_PWR1_CLKSEL_LENGTH      3

#define MPU6050_CLOCK_INTERNAL          0x00
#define MPU6050_CLOCK_PLL_XGYRO         0x01
#define MPU6050_CLOCK_PLL_YGYRO         0x02
#define MPU6050_CLOCK_PLL_ZGYRO         0x03
#define MPU6050_CLOCK_PLL_EXT32K        0x04
#define MPU6050_CLOCK_PLL_EXT19M        0x05
#define MPU6050_CLOCK_KEEP_RESET        0x07

#define MPU6050_PWR2_LP_WAKE_CTRL_BIT       7
#define MPU6050_PWR2_LP_WAKE_CTRL_LENGTH    2
#define MPU6050_PWR2_STBY_XA_BIT            5
#define MPU6050_PWR2_STBY_YA_BIT            4
#define MPU6050_PWR2_STBY_ZA_BIT            3
#define MPU6050_PWR2_STBY_XG_BIT            2
#define MPU6050_PWR2_STBY_YG_BIT            1
#define MPU6050_PWR2_STBY_ZG_BIT            0

#define MPU6050_WAKE_FREQ_1P25      0x0
#define MPU6050_WAKE_FREQ_2P5       0x1
#define MPU6050_WAKE_FREQ_5         0x2
#define MPU6050_WAKE_FREQ_10        0x3

#define MPU6050_BANKSEL_PRFTCH_EN_BIT       6
#define MPU6050_BANKSEL_CFG_USER_BANK_BIT   5
#define MPU6050_BANKSEL_MEM_SEL_BIT         4
#define MPU6050_BANKSEL_MEM_SEL_LENGTH      5

#define MPU6050_WHO_AM_I_BIT        6
#define MPU6050_WHO_AM_I_LENGTH     6

#define MPU6050_DMP_MEMORY_BANKS        8
#define MPU6050_DMP_MEMORY_BANK_SIZE    256
#define MPU6050_DMP_MEMORY_CHUNK_SIZE   16

/*      User Defined */
bool imu_initialize_mpu6050(imu_accessor *current_imu);
void imu_get_accel_raw_mpu6050(imu_accessor *current_imu, int16_t *ax, int16_t *ay, int16_t *az);
void imu_get_gyro_raw_mpu6050(imu_accessor *current_imu, int16_t *gx, int16_t *gy, int16_t *gz);
void imu_get_all_raw_mpu6050(imu_accessor *current_imu, int16_t *ax, int16_t *ay, int16_t *az, int16_t *gx, int16_t *gy, int16_t *gz);
void imu_get_accel_mpu6050(imu_accessor *current_imu, float *ax, float *ay, float *az);
void imu_get_gyro_mpu6050(imu_accessor *current_imu, float *gx, float *gy, float *gz);
void imu_get_all_mpu6050(imu_accessor *current_imu, float *ax, float *ay, float *az, float *gx, float *gy, float *gz);


// note: DMP code memory blocks defined at end of header file

/*        MPU6050(); */
        void MPU6050(uint8_t address_camera, uint8_t address_board);

        void MPUinitialize(imu_accessor *current_imu, uint8_t gyro_setting, uint8_t acclerometer_setting);
        bool MPUtestConnection(imu_accessor *current_imu);

        // AUX_VDDIO register
        uint8_t MPUgetAuxVDDIOLevel(imu_accessor *current_imu);
        void MPUsetAuxVDDIOLevel(imu_accessor *current_imu, uint8_t level);

        // SMPLRT_DIV register
        uint8_t MPUgetRate(imu_accessor *current_imu);
        void MPUsetRate(imu_accessor *current_imu, uint8_t rate);

        // CONFIG register
        uint8_t MPUgetExternalFrameSync(imu_accessor *current_imu);
        void MPUsetExternalFrameSync(imu_accessor *current_imu, uint8_t sync);
        uint8_t MPUgetDLPFMode(imu_accessor *current_imu);
        void MPUsetDLPFMode(imu_accessor *current_imu, uint8_t bandwidth);

        // GYRO_CONFIG register
        uint8_t MPUgetFullScaleGyroRange(imu_accessor *current_imu);
        void MPUsetFullScaleGyroRange(imu_accessor *current_imu, uint8_t range);

        // ACCEL_CONFIG register
        bool MPUgetAccelXSelfTest(imu_accessor *current_imu);
        void MPUsetAccelXSelfTest(imu_accessor *current_imu, bool enabled);
        bool MPUgetAccelYSelfTest(imu_accessor *current_imu);
        void MPUsetAccelYSelfTest(imu_accessor *current_imu, bool enabled);
        bool MPUgetAccelZSelfTest(imu_accessor *current_imu);
        void MPUsetAccelZSelfTest(imu_accessor *current_imu, bool enabled);
        uint8_t MPUgetFullScaleAccelRange(imu_accessor *current_imu);
        void MPUsetFullScaleAccelRange(imu_accessor *current_imu, uint8_t range);
        uint8_t MPUgetDHPFMode(imu_accessor *current_imu);
        void MPUsetDHPFMode(imu_accessor *current_imu, uint8_t mode);

        // FF_THR register
        uint8_t MPUgetFreefallDetectionThreshold(imu_accessor *current_imu);
        void MPUsetFreefallDetectionThreshold(imu_accessor *current_imu, uint8_t threshold);

        // FF_DUR register
        uint8_t MPUgetFreefallDetectionDuration(imu_accessor *current_imu);
        void MPUsetFreefallDetectionDuration(imu_accessor *current_imu, uint8_t duration);

        // MOT_THR register
        uint8_t MPUgetMotionDetectionThreshold(imu_accessor *current_imu);
        void MPUsetMotionDetectionThreshold(imu_accessor *current_imu, uint8_t threshold);

        // MOT_DUR register
        uint8_t MPUgetMotionDetectionDuration(imu_accessor *current_imu);
        void MPUsetMotionDetectionDuration(imu_accessor *current_imu, uint8_t duration);

        // ZRMOT_THR register
        uint8_t MPUgetZeroMotionDetectionThreshold(imu_accessor *current_imu);
        void MPUsetZeroMotionDetectionThreshold(imu_accessor *current_imu, uint8_t threshold);

        // ZRMOT_DUR register
        uint8_t MPUgetZeroMotionDetectionDuration(imu_accessor *current_imu);
        void MPUsetZeroMotionDetectionDuration(imu_accessor *current_imu, uint8_t duration);

        // FIFO_EN register
        bool MPUgetTempFIFOEnabled(imu_accessor *current_imu);
        void MPUsetTempFIFOEnabled(imu_accessor *current_imu, bool enabled);
        bool MPUgetXGyroFIFOEnabled(imu_accessor *current_imu);
        void MPUsetXGyroFIFOEnabled(imu_accessor *current_imu, bool enabled);
        bool MPUgetYGyroFIFOEnabled(imu_accessor *current_imu);
        void MPUsetYGyroFIFOEnabled(imu_accessor *current_imu, bool enabled);
        bool MPUgetZGyroFIFOEnabled(imu_accessor *current_imu);
        void MPUsetZGyroFIFOEnabled(imu_accessor *current_imu, bool enabled);
        bool MPUgetAccelFIFOEnabled(imu_accessor *current_imu);
        void MPUsetAccelFIFOEnabled(imu_accessor *current_imu, bool enabled);
        bool MPUgetSlave2FIFOEnabled(imu_accessor *current_imu);
        void MPUsetSlave2FIFOEnabled(imu_accessor *current_imu, bool enabled);
        bool MPUgetSlave1FIFOEnabled(imu_accessor *current_imu);
        void MPUsetSlave1FIFOEnabled(imu_accessor *current_imu, bool enabled);
        bool MPUgetSlave0FIFOEnabled(imu_accessor *current_imu);
        void MPUsetSlave0FIFOEnabled(imu_accessor *current_imu, bool enabled);

        // I2C_MST_CTRL register
        bool MPUgetMultiMasterEnabled(imu_accessor *current_imu);
        void MPUsetMultiMasterEnabled(imu_accessor *current_imu, bool enabled);
        bool MPUgetWaitForExternalSensorEnabled(imu_accessor *current_imu);
        void MPUsetWaitForExternalSensorEnabled(imu_accessor *current_imu, bool enabled);
        bool MPUgetSlave3FIFOEnabled(imu_accessor *current_imu);
        void MPUsetSlave3FIFOEnabled(imu_accessor *current_imu, bool enabled);
        bool MPUgetSlaveReadWriteTransitionEnabled(imu_accessor *current_imu);
        void MPUsetSlaveReadWriteTransitionEnabled(imu_accessor *current_imu, bool enabled);
        uint8_t MPUgetMasterClockSpeed(imu_accessor *current_imu);
        void MPUsetMasterClockSpeed(imu_accessor *current_imu, uint8_t speed);

        // I2C_SLV* registers (Slave 0-3)
        uint8_t MPUgetSlaveAddress(imu_accessor *current_imu, uint8_t num);
        void MPUsetSlaveAddress(imu_accessor *current_imu, uint8_t num, uint8_t address);
        uint8_t MPUgetSlaveRegister(imu_accessor *current_imu, uint8_t num);
        void MPUsetSlaveRegister(imu_accessor *current_imu, uint8_t num, uint8_t reg);
        bool MPUgetSlaveEnabled(imu_accessor *current_imu, uint8_t num);
        void MPUsetSlaveEnabled(imu_accessor *current_imu, uint8_t num, bool enabled);
        bool MPUgetSlaveWordByteSwap(imu_accessor *current_imu, uint8_t num);
        void MPUsetSlaveWordByteSwap(imu_accessor *current_imu, uint8_t num, bool enabled);
        bool MPUgetSlaveWriteMode(imu_accessor *current_imu, uint8_t num);
        void MPUsetSlaveWriteMode(imu_accessor *current_imu, uint8_t num, bool mode);
        bool MPUgetSlaveWordGroupOffset(imu_accessor *current_imu, uint8_t num);
        void MPUsetSlaveWordGroupOffset(imu_accessor *current_imu, uint8_t num, bool enabled);
        uint8_t MPUgetSlaveDataLength(imu_accessor *current_imu, uint8_t num);
        void MPUsetSlaveDataLength(imu_accessor *current_imu, uint8_t num, uint8_t length);

        // I2C_SLV* registers (Slave 4)
        uint8_t MPUgetSlave4Address(imu_accessor *current_imu);
        void MPUsetSlave4Address(imu_accessor *current_imu, uint8_t address);
        uint8_t MPUgetSlave4Register(imu_accessor *current_imu);
        void MPUsetSlave4Register(imu_accessor *current_imu, uint8_t reg);
        void MPUsetSlave4OutputByte(imu_accessor *current_imu, uint8_t data);
        bool MPUgetSlave4Enabled(imu_accessor *current_imu);
        void MPUsetSlave4Enabled(imu_accessor *current_imu, bool enabled);
        bool MPUgetSlave4InterruptEnabled(imu_accessor *current_imu);
        void MPUsetSlave4InterruptEnabled(imu_accessor *current_imu, bool enabled);
        bool MPUgetSlave4WriteMode(imu_accessor *current_imu);
        void MPUsetSlave4WriteMode(imu_accessor *current_imu, bool mode);
        uint8_t MPUgetSlave4MasterDelay(imu_accessor *current_imu);
        void MPUsetSlave4MasterDelay(imu_accessor *current_imu, uint8_t delay);
        uint8_t MPUgetSlate4InputByte(imu_accessor *current_imu);

        // I2C_MST_STATUS register
        bool MPUgetPassthroughStatus(imu_accessor *current_imu);
        bool MPUgetSlave4IsDone(imu_accessor *current_imu);
        bool MPUgetLostArbitration(imu_accessor *current_imu);
        bool MPUgetSlave4Nack(imu_accessor *current_imu);
        bool MPUgetSlave3Nack(imu_accessor *current_imu);
        bool MPUgetSlave2Nack(imu_accessor *current_imu);
        bool MPUgetSlave1Nack(imu_accessor *current_imu);
        bool MPUgetSlave0Nack(imu_accessor *current_imu);

        // INT_PIN_CFG register
        bool MPUgetInterruptMode(imu_accessor *current_imu);
        void MPUsetInterruptMode(imu_accessor *current_imu, bool mode);
        bool MPUgetInterruptDrive(imu_accessor *current_imu);
        void MPUsetInterruptDrive(imu_accessor *current_imu, bool drive);
        bool MPUgetInterruptLatch(imu_accessor *current_imu);
        void MPUsetInterruptLatch(imu_accessor *current_imu, bool latch);
        bool MPUgetInterruptLatchClear(imu_accessor *current_imu);
        void MPUsetInterruptLatchClear(imu_accessor *current_imu, bool clear);
        bool MPUgetFSyncInterruptLevel(imu_accessor *current_imu);
        void MPUsetFSyncInterruptLevel(imu_accessor *current_imu, bool level);
        bool MPUgetFSyncInterruptEnabled(imu_accessor *current_imu);
        void MPUsetFSyncInterruptEnabled(imu_accessor *current_imu, bool enabled);
        bool MPUgetI2CBypassEnabled(imu_accessor *current_imu);
        void MPUsetI2CBypassEnabled(imu_accessor *current_imu, bool enabled);
        bool MPUgetClockOutputEnabled(imu_accessor *current_imu);
        void MPUsetClockOutputEnabled(imu_accessor *current_imu, bool enabled);

        // INT_ENABLE register
        uint8_t MPUgetIntEnabled(imu_accessor *current_imu);
        void MPUsetIntEnabled(imu_accessor *current_imu, uint8_t enabled);
        bool MPUgetIntFreefallEnabled(imu_accessor *current_imu);
        void MPUsetIntFreefallEnabled(imu_accessor *current_imu, bool enabled);
        bool MPUgetIntMotionEnabled(imu_accessor *current_imu);
        void MPUsetIntMotionEnabled(imu_accessor *current_imu, bool enabled);
        bool MPUgetIntZeroMotionEnabled(imu_accessor *current_imu);
        void MPUsetIntZeroMotionEnabled(imu_accessor *current_imu, bool enabled);
        bool MPUgetIntFIFOBufferOverflowEnabled(imu_accessor *current_imu);
        void MPUsetIntFIFOBufferOverflowEnabled(imu_accessor *current_imu, bool enabled);
        bool MPUgetIntI2CMasterEnabled(imu_accessor *current_imu);
        void MPUsetIntI2CMasterEnabled(imu_accessor *current_imu, bool enabled);
        bool MPUgetIntDataReadyEnabled(imu_accessor *current_imu);
        void MPUsetIntDataReadyEnabled(imu_accessor *current_imu, bool enabled);

        // INT_STATUS register
        uint8_t MPUgetIntStatus(imu_accessor *current_imu);
        bool MPUgetIntFreefallStatus(imu_accessor *current_imu);
        bool MPUgetIntMotionStatus(imu_accessor *current_imu);
        bool MPUgetIntZeroMotionStatus(imu_accessor *current_imu);
        bool MPUgetIntFIFOBufferOverflowStatus(imu_accessor *current_imu);
        bool MPUgetIntI2CMasterStatus(imu_accessor *current_imu);
        bool MPUgetIntDataReadyStatus(imu_accessor *current_imu);

        // ACCEL_*OUT_* registers
        void MPUgetMotion9(imu_accessor *current_imu, int16_t* ax, int16_t* ay, int16_t* az, int16_t* gx, int16_t* gy, int16_t* gz, int16_t* mx, int16_t* my, int16_t* mz);
        void MPUgetMotion6(imu_accessor *current_imu, int16_t* ax, int16_t* ay, int16_t* az, int16_t* gx, int16_t* gy, int16_t* gz);
        void MPUgetAcceleration(imu_accessor *current_imu, int16_t* x, int16_t* y, int16_t* z);
        int16_t MPUgetAccelerationX(imu_accessor *current_imu);
        int16_t MPUgetAccelerationY(imu_accessor *current_imu);
        int16_t MPUgetAccelerationZ(imu_accessor *current_imu);

        // TEMP_OUT_* registers
        int16_t MPUgetTemperature(imu_accessor *current_imu);

        // GYRO_*OUT_* registers
        void MPUgetRotation(imu_accessor *current_imu, int16_t* x, int16_t* y, int16_t* z);
        int16_t MPUgetRotationX(imu_accessor *current_imu);
        int16_t MPUgetRotationY(imu_accessor *current_imu);
        int16_t MPUgetRotationZ(imu_accessor *current_imu);

        // EXT_SENS_DATA_* registers
        uint8_t MPUgetExternalSensorByte(imu_accessor *current_imu, int position);
        uint16_t MPUgetExternalSensorWord(imu_accessor *current_imu, int position);
        uint32_t MPUgetExternalSensorDWord(imu_accessor *current_imu, int position);

        // MOT_DETECT_STATUS register
        bool MPUgetXNegMotionDetected(imu_accessor *current_imu);
        bool MPUgetXPosMotionDetected(imu_accessor *current_imu);
        bool MPUgetYNegMotionDetected(imu_accessor *current_imu);
        bool MPUgetYPosMotionDetected(imu_accessor *current_imu);
        bool MPUgetZNegMotionDetected(imu_accessor *current_imu);
        bool MPUgetZPosMotionDetected(imu_accessor *current_imu);
        bool MPUgetZeroMotionDetected(imu_accessor *current_imu);

        // I2C_SLV*_DO register
        void MPUsetSlaveOutputByte(imu_accessor *current_imu, uint8_t num, uint8_t data);

        // I2C_MST_DELAY_CTRL register
        bool MPUgetExternalShadowDelayEnabled(imu_accessor *current_imu);
        void MPUsetExternalShadowDelayEnabled(imu_accessor *current_imu, bool enabled);
        bool MPUgetSlaveDelayEnabled(imu_accessor *current_imu, uint8_t num);
        void MPUsetSlaveDelayEnabled(imu_accessor *current_imu, uint8_t num, bool enabled);

        // SIGNAL_PATH_RESET register
        void MPUresetGyroscopePath(imu_accessor *current_imu);
        void MPUresetAccelerometerPath(imu_accessor *current_imu);
        void MPUresetTemperaturePath(imu_accessor *current_imu);

        // MOT_DETECT_CTRL register
        uint8_t MPUgetAccelerometerPowerOnDelay(imu_accessor *current_imu);
        void MPUsetAccelerometerPowerOnDelay(imu_accessor *current_imu, uint8_t delay);
        uint8_t MPUgetFreefallDetectionCounterDecrement(imu_accessor *current_imu);
        void MPUsetFreefallDetectionCounterDecrement(imu_accessor *current_imu, uint8_t decrement);
        uint8_t MPUgetMotionDetectionCounterDecrement(imu_accessor *current_imu);
        void MPUsetMotionDetectionCounterDecrement(imu_accessor *current_imu, uint8_t decrement);

        // USER_CTRL register
        bool MPUgetFIFOEnabled(imu_accessor *current_imu);
        void MPUsetFIFOEnabled(imu_accessor *current_imu, bool enabled);
        bool MPUgetI2CMasterModeEnabled(imu_accessor *current_imu);
        void MPUsetI2CMasterModeEnabled(imu_accessor *current_imu, bool enabled);
        void MPUswitchSPIEnabled(imu_accessor *current_imu, bool enabled);
        void MPUresetFIFO(imu_accessor *current_imu);
        void MPUresetI2CMaster(imu_accessor *current_imu);
        void MPUresetSensors(imu_accessor *current_imu);

        // PWR_MGMT_1 register
        void MPUreset(imu_accessor *current_imu);
        bool MPUgetSleepEnabled(imu_accessor *current_imu);
        void MPUsetSleepEnabled(imu_accessor *current_imu, bool enabled);
        bool MPUgetWakeCycleEnabled(imu_accessor *current_imu);
        void MPUsetWakeCycleEnabled(imu_accessor *current_imu, bool enabled);
        bool MPUgetTempSensorEnabled(imu_accessor *current_imu);
        void MPUsetTempSensorEnabled(imu_accessor *current_imu, bool enabled);
        uint8_t MPUgetClockSource(imu_accessor *current_imu);
        void MPUsetClockSource(imu_accessor *current_imu, uint8_t source);

        // PWR_MGMT_2 register
        uint8_t MPUgetWakeFrequency(imu_accessor *current_imu);
        void MPUsetWakeFrequency(imu_accessor *current_imu, uint8_t frequency);
        bool MPUgetStandbyXAccelEnabled(imu_accessor *current_imu);
        void MPUsetStandbyXAccelEnabled(imu_accessor *current_imu, bool enabled);
        bool MPUgetStandbyYAccelEnabled(imu_accessor *current_imu);
        void MPUsetStandbyYAccelEnabled(imu_accessor *current_imu, bool enabled);
        bool MPUgetStandbyZAccelEnabled(imu_accessor *current_imu);
        void MPUsetStandbyZAccelEnabled(imu_accessor *current_imu, bool enabled);
        bool MPUgetStandbyXGyroEnabled(imu_accessor *current_imu);
        void MPUsetStandbyXGyroEnabled(imu_accessor *current_imu, bool enabled);
        bool MPUgetStandbyYGyroEnabled(imu_accessor *current_imu);
        void MPUsetStandbyYGyroEnabled(imu_accessor *current_imu, bool enabled);
        bool MPUgetStandbyZGyroEnabled(imu_accessor *current_imu);
        void MPUsetStandbyZGyroEnabled(imu_accessor *current_imu, bool enabled);

        // FIFO_COUNT_* registers
        uint16_t MPUgetFIFOCount(imu_accessor *current_imu);

        // FIFO_R_W register
        uint8_t MPUgetFIFOByte(imu_accessor *current_imu);
        void MPUsetFIFOByte(imu_accessor *current_imu, uint8_t data);
        void MPUgetFIFOBytes(imu_accessor *current_imu, uint8_t *data, uint8_t length);

        // WHO_AM_I register
        uint8_t MPUgetDeviceID(imu_accessor *current_imu);
        void MPUsetDeviceID(imu_accessor *current_imu, uint8_t id);
        
        // ======== UNDOCUMENTED/DMP REGISTERS/METHODS ========
        
        // XG_OFFS_TC register
        uint8_t MPUgetOTPBankValid(imu_accessor *current_imu);
        void MPUsetOTPBankValid(imu_accessor *current_imu, bool enabled);
        int8_t MPUgetXGyroOffset(imu_accessor *current_imu);
        void MPUsetXGyroOffset(imu_accessor *current_imu, int8_t offset);

        // YG_OFFS_TC register
        int8_t MPUgetYGyroOffset(imu_accessor *current_imu);
        void MPUsetYGyroOffset(imu_accessor *current_imu, int8_t offset);

        // ZG_OFFS_TC register
        int8_t MPUgetZGyroOffset(imu_accessor *current_imu);
        void MPUsetZGyroOffset(imu_accessor *current_imu, int8_t offset);

        // X_FINE_GAIN register
        int8_t MPUgetXFineGain(imu_accessor *current_imu);
        void MPUsetXFineGain(imu_accessor *current_imu, int8_t gain);

        // Y_FINE_GAIN register
        int8_t MPUgetYFineGain(imu_accessor *current_imu);
        void MPUsetYFineGain(imu_accessor *current_imu, int8_t gain);

        // Z_FINE_GAIN register
        int8_t MPUgetZFineGain(imu_accessor *current_imu);
        void MPUsetZFineGain(imu_accessor *current_imu, int8_t gain);

        // XA_OFFS_* registers
        int16_t MPUgetXAccelOffset(imu_accessor *current_imu);
        void MPUsetXAccelOffset(imu_accessor *current_imu, int16_t offset);

        // YA_OFFS_* register
        int16_t MPUgetYAccelOffset(imu_accessor *current_imu);
        void MPUsetYAccelOffset(imu_accessor *current_imu, int16_t offset);

        // ZA_OFFS_* register
        int16_t MPUgetZAccelOffset(imu_accessor *current_imu);
        void MPUsetZAccelOffset(imu_accessor *current_imu, int16_t offset);

        // XG_OFFS_USR* registers
        int16_t MPUgetXGyroOffsetUser(imu_accessor *current_imu);
        void MPUsetXGyroOffsetUser(imu_accessor *current_imu, int16_t offset);

        // YG_OFFS_USR* register
        int16_t MPUgetYGyroOffsetUser(imu_accessor *current_imu);
        void MPUsetYGyroOffsetUser(imu_accessor *current_imu, int16_t offset);

        // ZG_OFFS_USR* register
        int16_t MPUgetZGyroOffsetUser(imu_accessor *current_imu);
        void MPUsetZGyroOffsetUser(imu_accessor *current_imu, int16_t offset);
        
        // INT_ENABLE register (DMP functions)
        bool MPUgetIntPLLReadyEnabled(imu_accessor *current_imu);
        void MPUsetIntPLLReadyEnabled(imu_accessor *current_imu, bool enabled);
        bool MPUgetIntDMPEnabled(imu_accessor *current_imu);
        void MPUsetIntDMPEnabled(imu_accessor *current_imu, bool enabled);
        
        // DMP_INT_STATUS
        bool MPUgetDMPInt5Status(imu_accessor *current_imu);
        bool MPUgetDMPInt4Status(imu_accessor *current_imu);
        bool MPUgetDMPInt3Status(imu_accessor *current_imu);
        bool MPUgetDMPInt2Status(imu_accessor *current_imu);
        bool MPUgetDMPInt1Status(imu_accessor *current_imu);
        bool MPUgetDMPInt0Status(imu_accessor *current_imu);

        // INT_STATUS register (DMP functions)
        bool MPUgetIntPLLReadyStatus(imu_accessor *current_imu);
        bool MPUgetIntDMPStatus(imu_accessor *current_imu);
        
        // USER_CTRL register (DMP functions)
        bool MPUgetDMPEnabled(imu_accessor *current_imu);
        void MPUsetDMPEnabled(imu_accessor *current_imu, bool enabled);
        void MPUresetDMP(imu_accessor *current_imu);
        
        // BANK_SEL register
        void MPUsetMemoryBank(imu_accessor *current_imu, uint8_t bank, bool prefetchEnabled, bool userBank);
        
        // MEM_START_ADDR register
        void MPUsetMemoryStartAddress(imu_accessor *current_imu, uint8_t address);
        
        // MEM_R_W register
        uint8_t MPUreadMemoryByte(imu_accessor *current_imu);
        void MPUwriteMemoryByte(imu_accessor *current_imu, uint8_t data);
        void MPUreadMemoryBlock(imu_accessor *current_imu, uint8_t *data, uint16_t dataSize, uint8_t bank, uint8_t address);
        bool MPUwriteMemoryBlock(imu_accessor *current_imu, const uint8_t *data, uint16_t dataSize, uint8_t bank, uint8_t address, bool verify, bool useProgMem);
        bool MPUwriteProgMemoryBlock(imu_accessor *current_imu, const uint8_t *data, uint16_t dataSize, uint8_t bank, uint8_t address, bool verify);

        bool MPUwriteDMPConfigurationSet(imu_accessor *current_imu, const uint8_t *data, uint16_t dataSize, bool useProgMem);
        bool MPUwriteProgDMPConfigurationSet(imu_accessor *current_imu, const uint8_t *data, uint16_t dataSize);

        // DMP_CFG_1 register
        uint8_t MPUgetDMPConfig1(imu_accessor *current_imu);
        void MPUsetDMPConfig1(imu_accessor *current_imu, uint8_t config);

        // DMP_CFG_2 register
        uint8_t MPUgetDMPConfig2(imu_accessor *current_imu);
        void MPUsetDMPConfig2(imu_accessor *current_imu, uint8_t config);

        extern uint8_t MPUCameraAddr;
        extern uint8_t MPUBoardAddr;
        extern uint8_t MPUbuffer[14];
				
        extern uint16_t MPUfifoCount;     	// count of all bytes currently in FIFO
        extern uint8_t  MPUfifoBuffer[64];	// FIFO storage buffer
        
        static uint8_t MPUverifyBuffer[MPU6050_DMP_MEMORY_CHUNK_SIZE];
        //static uint8_t MPUprogBuffer[MPU6050_DMP_MEMORY_CHUNK_SIZE];

#endif /* _MPU6050_H_ */
