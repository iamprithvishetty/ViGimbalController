/* ============================================
ChibiOS I2Cdev Main I2C device class code is placed under the MIT license
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

#ifndef I2C_CHIBI_H_
#define I2C_CHIBI_H_

#include "hal.h"

#define I2CDEV_DEFAULT_READ_TIMEOUT     1000
#define I2CDEV_BUFFER_LENGTH			64

int8_t I2CdevreadBit(I2CDriver *i2c_driver, uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t *data, uint16_t timeout);
int8_t I2CdevreadBitW(I2CDriver *i2c_driver, uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint16_t *data, uint16_t timeout);
int8_t I2CdevreadBits(I2CDriver *i2c_driver, uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t *data, uint16_t timeout);
int8_t I2CdevreadBitsW(I2CDriver *i2c_driver, uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint16_t *data, uint16_t timeout);
int8_t I2CdevreadByte(I2CDriver *i2c_driver, uint8_t devAddr, uint8_t regAddr, uint8_t *data, uint16_t timeout);
int8_t I2CdevreadWord(I2CDriver *i2c_driver, uint8_t devAddr, uint8_t regAddr, uint16_t *data, uint16_t timeout);
int8_t I2CdevreadBytes(I2CDriver *i2c_driver, uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data, uint16_t timeout);
int8_t I2CdevreadWords(I2CDriver *i2c_driver, uint8_t devAddr, uint8_t regAddr, uint8_t length, uint16_t *data, uint16_t timeout);

bool I2CdevwriteBit(I2CDriver *i2c_driver, uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t data);
bool I2CdevwriteBitW(I2CDriver *i2c_driver, uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint16_t data);
bool I2CdevwriteBits(I2CDriver *i2c_driver, uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data);
bool I2CdevwriteBitsW(I2CDriver *i2c_driver, uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint16_t data);
bool I2CdevwriteByte(I2CDriver *i2c_driver, uint8_t devAddr, uint8_t regAddr, uint8_t data);
bool I2CdevwriteWord(I2CDriver *i2c_driver, uint8_t devAddr, uint8_t regAddr, uint16_t data);
bool I2CdevwriteBytes(I2CDriver *i2c_driver, uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data);
bool I2CdevwriteWords(I2CDriver *i2c_driver, uint8_t devAddr, uint8_t regAddr, uint8_t length, uint16_t *data);

#endif