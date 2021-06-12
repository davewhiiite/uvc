/* Library modified July 2020 by Dave White to include an average of N 
   ADC samples before returning the result.
 

* ***** NOTE ***** **************************************************** *
* THIS LIBRARY IS FOR AN MCP3221A5T-I/OT - WHICH HAS AN ADDRESS OF  101 *
* ***** **** ***** **************************************************** *

 * Copyright (c) 2012 dstyles, MIT License
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
 * and associated documentation files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, publish, distribute, 
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is 
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or 
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
 
/* Datasheet Information:
*
* The address byte is the first byte received following the
* START condition from the master device. The first part
* of the control byte consists of a 4-bit device code,
* which is set to 1001 for the MCP3221. The device code
* is followed by three address bits: A2, A1 and A0. The
* default address bits are 101. Contact the Microchip
* factory for additional address bit options. The address
* bits allow up to eight MCP3221 devices on the same
* bus and are used to determine which device is
* accessed.
*
* The eighth bit of the slave address determines if the
* master device wants to read conversion data or write to
* the MCP3221. When set to a ‘1’, a read operation is
* selected. When set to a ‘0’, a write operation is
* selected. There are no writable registers on the
* MCP3221. Therefore, this bit must be set to a ’1’ in
* order to initiate a conversion.
*
* ***** NOTE ***** *****************************************************************************************
* THIS LIBRARY IS FOR AN MCP3221A5T-I/OT - WHICH HAS AN ADDRESS OF  101  - The A5 bit denotes the address
* ***** **** ***** *****************************************************************************************
*/


#ifndef MCP3221_N_H

#define MCP3221_N_H

#include "mbed.h"

#define    MCP3221_CONVERSE 0x9B //10011011 NOTE IT ENDS IN 1, this is the READ ADDRESS. This is all this device does.
                                 //It opens a conversation via this specific READ address

//Library for the MCP3221 12 BIT ADC.

class MCP3221_N
{
public:

  /*
  Creates instance
  Connect module using I2C port pins sda and scl. The output is referenced to the supply voltage which can be
  2.7v to 5.0v. The read will return the correct voltage, if you supply the correct supplyVoltage when instantiating.
  */
  MCP3221_N(PinName sda, PinName scl, float supplyVoltage, uint8_t N);
  
  /*
  Destroys instance.
  */ 
  ~MCP3221_N();
  
  /*
  Reads the analog register of the MCP3221 and converts it to a useable value. (a voltage) 
  */
  float read();
  
private:
  
  I2C i2c;
  float _supplyVoltage;
  char _data[2];
  uint8_t _numSamples;

};

#endif

