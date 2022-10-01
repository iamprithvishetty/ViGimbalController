/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef _BOARD_H_
#define _BOARD_H_

/*
 * Setup for the Vi Gimbal Controller
 */

/*
 * Board identifier.
 */
#define BOARD_VI_GIMBAL_CONTROLLER
#define BOARD_NAME              "Vi Gimbal Controller"

/*
 * Board frequencies.
 */
#define STM32_LSECLK            32768
#define STM32_HSECLK            8000000

/*
 * MCU type, supported types are defined in ./os/hal/platforms/hal_lld.h.
 */
#define STM32F103xE

/* on-board */

#define GPIOB_USB_DISC          9

#define LED_1                   PAL_LINE(GPIOB,12)
#define LED_2                   PAL_LINE(GPIOB,13)

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 *
 * The digits have the following meaning:
 *   0 - Analog input.
 *   1 - Push Pull output 10MHz.
 *   2 - Push Pull output 2MHz.
 *   3 - Push Pull output 50MHz.
 *   4 - Digital input.
 *   5 - Open Drain output 10MHz.
 *   6 - Open Drain output 2MHz.
 *   7 - Open Drain output 50MHz.
 *   8 - Digital input with PullUp or PullDown resistor depending on ODR.
 *   9 - Alternate Push Pull output 10MHz.
 *   A - Alternate Push Pull output 2MHz.
 *   B - Alternate Push Pull output 50MHz.
 *   C - Reserved.
 *   D - Alternate Open Drain output 10MHz.
 *   E - Alternate Open Drain output 2MHz.
 *   F - Alternate Open Drain output 50MHz.
 * Please refer to the STM32 Reference Manual for details.
 */

/*
 * Port A setup.
 * Everything input with pull-up except:
 * PA1  - Alternate Push Pull output 50MHz (PWM TIM2 CH2)
 * PA2  - Alternate Push Pull output 50MHz (PWM TIM2 CH3)
 * PA3  - Alternate Push Pull output 50MHz (PWM TIM2 CH4)
 * PA6  - Alternate Push Pull output 50MHz (PWM TIM3 CH1)
 * PA7  - Alternate Push Pull output 50MHz (PWM TIM3 CH2)
 * PA8  - Digital input (ICU TIM1 CH1)
 */
#define VAL_GPIOACRL            0xBB88BBB8      /*  PA7...PA0 */
#define VAL_GPIOACRH            0x88888884      /* PA15...PA8 */
#define VAL_GPIOAODR            0xFFFFFFFF

/*
 * Port B setup.
 * Everything input with pull-up except:
 * PB0  - Alternate Push Pull output 50MHz (PWM TIM3 CH3)
 * PB1  - Alternate Push Pull output 50MHz (PWM TIM3 CH4)
 * PB6  - Alternate Open Drain output 2MHz (I2C1_SCL).
 * PB7  - Alternate Open Drain output 2MHz (I2C1_SDA).
 * PB8  - Alternate Push Pull output 50MHz (PWM TIM4 CH3)
 * PB9  - Alternate Push Pull output 50MHz (PWM TIM4 CH4)
 * PB10 - Alternate Open Drain output 2MHz (I2C2_SCL).
 * PB11 - Alternate Open Drain output 2MHz (I2C2_SDA).
 * PB12 - Push Pull output 50MHz (LED_1).
 * PB13 - Push Pull output 50MHz (LED_2).
 */
#define VAL_GPIOBCRL            0xEE8888BB      /*  PB7...PB0 */
#define VAL_GPIOBCRH            0x8833EEBB      /* PB15...PB8 */
#define VAL_GPIOBODR            0xFFFFFFFF

/*
 * Port C setup.
 * Everything input with pull-up except:
 * PC6  - Digital input (ICU TIM8 CH1)
 */
#define VAL_GPIOCCRL            0x84888888      /*  PC7...PC0 */
#define VAL_GPIOCCRH            0x88888888      /* PC15...PC8 */
#define VAL_GPIOCODR            0xFFFFFFFF

/*
 * Port D setup.
 * Everything input with pull-up except:
 * PD0  - Normal input (XTAL).
 * PD1  - Normal input (XTAL).
 */
#define VAL_GPIODCRL            0x88888844      /*  PD7...PD0 */
#define VAL_GPIODCRH            0x88888888      /* PD15...PD8 */
#define VAL_GPIODODR            0xFFFFFFFF

/*
 * Port E setup.
 * Everything input with pull-up except:
 */
#define VAL_GPIOECRL            0x88888888      /*  PE7...PE0 */
#define VAL_GPIOECRH            0x88888888      /* PE15...PE8 */
#define VAL_GPIOEODR            0xFFFFFFFF

/*
 * USB bus activation macro, required by the USB driver.
 */
#define usb_lld_connect_bus(usbp) palClearPad(GPIOB, GPIOB_USB_DISC)

/*
 * USB bus de-activation macro, required by the USB driver.
 */
#define usb_lld_disconnect_bus(usbp) palSetPad(GPIOB, GPIOB_USB_DISC)

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* _BOARD_H_ */
