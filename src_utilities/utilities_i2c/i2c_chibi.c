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

#include "ch.h"
#include "hal.h"
#include "i2c_chibi.h"
#include <string.h>

/** Read a single bit from an 8-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr Register regAddr to read from
 * @param bitNum Bit position to read (0-7)
 * @param data Container for single bit value
 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
 * @return Status of read operation (true = success)
 */
int8_t I2CdevreadBit(I2CDriver *i2c_driver, uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t *data, uint16_t timeout) {
    uint8_t b = 0;
    uint8_t count = I2CdevreadByte(i2c_driver, devAddr, regAddr, &b, timeout);
    *data = b & (1 << bitNum);
    return count;
}

/** Read a single bit from a 16-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr Register regAddr to read from
 * @param bitNum Bit position to read (0-15)
 * @param data Container for single bit value
 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
 * @return Status of read operation (true = success)
 */
int8_t I2CdevreadBitW(I2CDriver *i2c_driver, uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint16_t *data, uint16_t timeout) {
	  uint16_t b = 0;
    uint8_t count = I2CdevreadWord(i2c_driver, devAddr, regAddr, &b, timeout);
    *data = b & (1 << bitNum);
    return count;
}

/** Read multiple bits from an 8-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr Register regAddr to read from
 * @param bitStart First bit position to read (0-7)
 * @param length Number of bits to read (not more than 8)
 * @param data Container for right-aligned value (i.e. '101' read from any bitStart position will equal 0x05)
 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
 * @return Status of read operation (true = success)
 */
int8_t I2CdevreadBits(I2CDriver *i2c_driver, uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t *data, uint16_t timeout) {
	// 01101001 read byte
    // 76543210 bit numbers
    //    xxx   args: bitStart=4, length=3
    //    010   masked
    //   -> 010 shifted
    uint8_t count, b=0;
    if ((count = I2CdevreadByte(i2c_driver, devAddr, regAddr, &b, timeout)) != 0) {
        uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
        b &= mask;
        b >>= (bitStart - length + 1);
        *data = b;
    }
    return count;
}

/** Read multiple bits from a 16-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr Register regAddr to read from
 * @param bitStart First bit position to read (0-15)
 * @param length Number of bits to read (not more than 16)
 * @param data Container for right-aligned value (i.e. '101' read from any bitStart position will equal 0x05)
 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
 * @return Status of read operation (1 = success, 0 = failure, -1 = timeout)
 */
int8_t I2CdevreadBitsW(I2CDriver *i2c_driver, uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint16_t *data, uint16_t timeout) {
	// 1101011001101001 read byte
    // fedcba9876543210 bit numbers
    //    xxx           args: bitStart=12, length=3
    //    101           masked
    //           -> 101 shifted
    uint8_t count;
    uint16_t w = 0;
    if ((count = I2CdevreadWord(i2c_driver, devAddr, regAddr, &w, timeout)) != 0) {
        uint16_t mask = ((1 << length) - 1) << (bitStart - length + 1);
        w &= mask;
        w >>= (bitStart - length + 1);
        *data = w;
    }
    return count;
}

/** Read single byte from an 8-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr Register regAddr to read from
 * @param data Container for byte value read from device
 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
 * @return Status of read operation (true = success)
 */
int8_t I2CdevreadByte(I2CDriver *i2c_driver, uint8_t devAddr, uint8_t regAddr, uint8_t *data, uint16_t timeout) {
	return I2CdevreadBytes(i2c_driver, devAddr, regAddr, 1, data, timeout);
}

/** Read single word from a 16-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr Register regAddr to read from
 * @param data Container for word value read from device
 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
 * @return Status of read operation (true = success)
 */
int8_t I2CdevreadWord(I2CDriver *i2c_driver, uint8_t devAddr, uint8_t regAddr, uint16_t *data, uint16_t timeout) {
	return I2CdevreadWords(i2c_driver, devAddr, regAddr, 1, data, timeout);
}

/** Read multiple bytes from an 8-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr First register regAddr to read from
 * @param length Number of bytes to read
 * @param data Buffer to store read data in
 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
 * @return Number of bytes read (-1 indicates failure)
 */
int8_t I2CdevreadBytes(I2CDriver *i2c_driver, uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data, uint16_t timeout) {
	//uint8_t mpu_txbuf[1], mpu_rxbuf[I2CDEV_BUFFER_LENGTH], i;
	msg_t rdymsg;
	if(length > I2CDEV_BUFFER_LENGTH) {
		return FALSE;
	}
	if(length == 1){
		uint8_t data_temp[2];
		i2cAcquireBus(i2c_driver);
		rdymsg = i2cMasterTransmitTimeout(i2c_driver, devAddr, &regAddr, 1, data_temp, 2, TIME_MS2I(timeout));
		i2cReleaseBus(i2c_driver);
		*data = data_temp[0];
	}
	else{
		i2cAcquireBus(i2c_driver);
		rdymsg = i2cMasterTransmitTimeout(i2c_driver, devAddr, &regAddr, 1, data, length, TIME_MS2I(timeout));
		i2cReleaseBus(i2c_driver);		
	}

	if(rdymsg == MSG_TIMEOUT || rdymsg == MSG_RESET) {
		return FALSE;
	}
	return TRUE;
}

/** Read multiple words from a 16-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr First register regAddr to read from
 * @param length Number of words to read
 * @param data Buffer to store read data in
 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
 * @return Number of words read (0 indicates failure)
 */
int8_t I2CdevreadWords(I2CDriver *i2c_driver, uint8_t devAddr, uint8_t regAddr, uint8_t length, uint16_t *data, uint16_t timeout) {
	uint8_t mpu_txbuf[1], mpu_rxbuf[I2CDEV_BUFFER_LENGTH], i;
	msg_t rdymsg;
	if((length * 2) > I2CDEV_BUFFER_LENGTH) {
		return FALSE;
	}
	mpu_txbuf[0] = regAddr;
	for(i=0;i<(length * 2);i++) {
		mpu_rxbuf[i] = 0x00;
	}
	i2cAcquireBus(i2c_driver);
	rdymsg = i2cMasterTransmitTimeout(i2c_driver, devAddr, mpu_txbuf, 1, mpu_rxbuf, length * 2, TIME_MS2I(timeout));
	i2cReleaseBus(i2c_driver);
	if(rdymsg == MSG_TIMEOUT || rdymsg == MSG_RESET) {
		return FALSE;
	}
	for(i=0;i<length * 2;i += 2) {
		data[i] = (mpu_rxbuf[i] << 8) + mpu_rxbuf[i+1];
	}
	return TRUE;
}

/** write a single bit in an 8-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr Register regAddr to write to
 * @param bitNum Bit position to write (0-7)
 * @param value New bit value to write
 * @return Status of operation (true = success)
 */
bool I2CdevwriteBit(I2CDriver *i2c_driver, uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t data) {
	  uint8_t b = 0;
    I2CdevreadByte(i2c_driver, devAddr, regAddr, &b, I2CDEV_DEFAULT_READ_TIMEOUT);
    b = (data != 0) ? (b | (1 << bitNum)) : (b & ~(1 << bitNum));
    return I2CdevwriteByte(i2c_driver, devAddr, regAddr, b);
}

/** write a single bit in a 16-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr Register regAddr to write to
 * @param bitNum Bit position to write (0-15)
 * @param value New bit value to write
 * @return Status of operation (true = success)
 */
bool I2CdevwriteBitW(I2CDriver *i2c_driver, uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint16_t data) {
	  uint16_t w = 0;
    I2CdevreadWord(i2c_driver, devAddr, regAddr, &w, I2CDEV_DEFAULT_READ_TIMEOUT);
    w = (data != 0) ? (w | (1 << bitNum)) : (w & ~(1 << bitNum));
    return I2CdevwriteWord(i2c_driver, devAddr, regAddr, w);
}

/** Write multiple bits in an 8-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr Register regAddr to write to
 * @param bitStart First bit position to write (0-7)
 * @param length Number of bits to write (not more than 8)
 * @param data Right-aligned value to write
 * @return Status of operation (true = success)
 */
bool I2CdevwriteBits(I2CDriver *i2c_driver, uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data) {
	//      010 value to write
    // 76543210 bit numbers
    //    xxx   args: bitStart=4, length=3
    // 00011100 mask byte
    // 10101111 original value (sample)
    // 10100011 original & ~mask
    // 10101011 masked | value
    uint8_t b = 0;
    if (I2CdevreadByte(i2c_driver, devAddr, regAddr, &b, I2CDEV_DEFAULT_READ_TIMEOUT) != 0) {
        uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
        data <<= (bitStart - length + 1); // shift data into correct position
        data &= mask; // zero all non-important bits in data
        b &= ~(mask); // zero all important bits in existing byte
        b |= data; // combine data with existing byte
        return I2CdevwriteByte(i2c_driver, devAddr, regAddr, b);
    } else {
        return FALSE;
    }
}

/** Write multiple bits in a 16-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr Register regAddr to write to
 * @param bitStart First bit position to write (0-15)
 * @param length Number of bits to write (not more than 16)
 * @param data Right-aligned value to write
 * @return Status of operation (true = success)
 */
bool I2CdevwriteBitsW(I2CDriver *i2c_driver, uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint16_t data) {
	//              010 value to write
    // fedcba9876543210 bit numbers
    //    xxx           args: bitStart=12, length=3
    // 0001110000000000 mask byte
    // 1010111110010110 original value (sample)
    // 1010001110010110 original & ~mask
    // 1010101110010110 masked | value
    uint16_t w = 0;
    if (I2CdevreadWord(i2c_driver, devAddr, regAddr, &w, I2CDEV_DEFAULT_READ_TIMEOUT) != 0) {
        uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
        data <<= (bitStart - length + 1); // shift data into correct position
        data &= mask; // zero all non-important bits in data
        w &= ~(mask); // zero all important bits in existing word
        w |= data; // combine data with existing word
        return I2CdevwriteWord(i2c_driver, devAddr, regAddr, w);
    } else {
        return FALSE;
    }
}

/** Write single byte to an 8-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr Register address to write to
 * @param data New byte value to write
 * @return Status of operation (true = success)
 */
bool I2CdevwriteByte(I2CDriver *i2c_driver, uint8_t devAddr, uint8_t regAddr, uint8_t data) {
	return I2CdevwriteBytes(i2c_driver,devAddr, regAddr, 1, &data);
}

/** Write single word to a 16-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr Register address to write to
 * @param data New word value to write
 * @return Status of operation (true = success)
 */
bool I2CdevwriteWord(I2CDriver *i2c_driver, uint8_t devAddr, uint8_t regAddr, uint16_t data) {
	return I2CdevwriteWords(i2c_driver, devAddr, regAddr, 1, &data);
}

/** Write multiple bytes to an 8-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr First register address to write to
 * @param length Number of bytes to write
 * @param data Buffer to copy new data from
 * @return Status of operation (true = success)
 */
bool I2CdevwriteBytes(I2CDriver *i2c_driver, uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data) {
	uint8_t mpu_txbuf[I2CDEV_BUFFER_LENGTH], mpu_rxbuf[1];
	msg_t rdymsg;
	if((length + 1)> I2CDEV_BUFFER_LENGTH) {
		return FALSE;
	}
	mpu_txbuf[0] = regAddr;
	memcpy(mpu_txbuf + sizeof(uint8_t), data, sizeof(uint8_t) * length);
	
	i2cAcquireBus(i2c_driver);
	rdymsg = i2cMasterTransmit(i2c_driver, devAddr, mpu_txbuf, length + 1, mpu_rxbuf, 0);
	i2cReleaseBus(i2c_driver);
	if(rdymsg == MSG_TIMEOUT || rdymsg == MSG_RESET) {
		return FALSE;
	}
	return TRUE;
}

/** Write multiple words to a 16-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr First register address to write to
 * @param length Number of words to write
 * @param data Buffer to copy new data from
 * @return Status of operation (true = success)
 */
bool I2CdevwriteWords(I2CDriver *i2c_driver, uint8_t devAddr, uint8_t regAddr, uint8_t length, uint16_t *data) {
	uint8_t mpu_txbuf[I2CDEV_BUFFER_LENGTH], mpu_rxbuf[1], i;
	msg_t rdymsg;
	if(((length * 2) + 1)> I2CDEV_BUFFER_LENGTH) {
		return FALSE;
	}
	mpu_txbuf[0] = regAddr;
	for(i=1;i<((length * 2) + 1);i += 2) {
		mpu_txbuf[i] = (data[i] >> 8) & 0xff;
		mpu_txbuf[i+1] = data[i] & 0xff;
	}
	i2cAcquireBus(i2c_driver);
	rdymsg = i2cMasterTransmit(i2c_driver, devAddr, mpu_txbuf, (length * 2) + 1, mpu_rxbuf, 0);
	i2cReleaseBus(i2c_driver);
	if(rdymsg == MSG_TIMEOUT || rdymsg == MSG_RESET) {
		return FALSE;
	}
	return TRUE;
}