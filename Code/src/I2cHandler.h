//h+//////////////////////////////////////////////////////////////////////////
/*!
//  \file      i2cHandler.h
//
//  \brief		Handles i2c functions
//
//  \author    Luca Petricca
//
//  \date      01.02.2014
//
//  \Copyright(c) 2016 BroenTech Solutions AS
//   Permission is hereby granted, free of charge, to any person obtaining a copy of this
//   software and associated documentation files (the "Software"), to deal in the Software
//   without restriction, including without limitation the rights to use, copy, modify, merge,
//   publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons
//   to whom the Software is furnished to do so, subject to the following conditions:
//
//   The above copyright notice and this permission notice shall be included in all copies or substantial
//   portions of the Software.
//
//   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
//   INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
//   AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
//   DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//  \par       Revision History
//             Released under MIT license
//
//    N.B. This I2C Functions are partly re-implemented starting from the template from:
// 	       https://github.com/jmunsch/STM32F4/tree/master/examples/Library
//
*/
//h-//////////////////////////////////////////////////////////////////////////


#ifndef I2C_H
#define I2C_H

#include "stm32l1xx_i2c.h"


/*f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	I2C_Read
//
//  read n byte from I2C interface
//
//  \param   I2C_TypeDef* I2Cx,   I2C interface used
// 			 uint8_t* buf, 		  pointer: where to save data
// 			 uint32_t nbuf, 	  nbuf: number of bytes to be read
// 			 uint8_t SlaveAddress Address of the slave device
//
//  \return ErrorStatus:	Success or Error
//
//  \author Luca Petricca
//
//  \date  23.09.2014
//
//
//
//
//
//
//f-//////////////////////////////////////////////////////////////////////////*/

ErrorStatus I2C_Read(I2C_TypeDef* I2Cx, uint8_t* buf, uint32_t nbuf, uint8_t SlaveAddress);

/*f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	I2C_Write
//
//  write n byte to I2C interface
//
//  \param   I2C_TypeDef* I2Cx,   I2C interface used
// 			 uint8_t* buf, 		  pointer to the stored data
// 			 uint32_t nbuf, 	  nbuf: number of bytes to be send
// 			 uint8_t SlaveAddress Address of the slave device
//
//  \return ErrorStatus:	Success or Error
//
//  \author Luca Petricca
//
//  \date  23.09.2014
//
//
//
//
//
//
//f-//////////////////////////////////////////////////////////////////////////*/
ErrorStatus I2C_Write(I2C_TypeDef* I2Cx, const uint8_t* buf, uint32_t nbuf,  uint8_t SlaveAddress);


/*f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	I2C_LowLevel_Init
//
//  initialize I2C physical interface
//
//  \param   I2C_TypeDef* I2Cx,   I2C interface to initialize
// 			 int ClockSpeed, 	  I2C speed selection
// 			 int OwnAddress, 	  Address of the Master
//
//
//  \return void
//
//  \author Luca Petricca
//
//  \date  23.09.2014
//
//
//
//
//
//
//f-//////////////////////////////////////////////////////////////////////////*/
void I2C_LowLevel_Init(I2C_TypeDef* I2Cx, int ClockSpeed, int OwnAddress);

/*f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	checkdev
//
//  Check if the specified slave device is alive
//
//  \param   I2C_TypeDef* I2Cx,   I2C interface use
// 			 uint8_t SlaveAddress slave address to check
//
//
//
//  \return ErrorStatus:	Success=connected or Error=not_connected or I2c_error
//
//  \author Luca Petricca
//
//  \date  29.09.2014
//
//
//
//
//
//
//f-//////////////////////////////////////////////////////////////////////////*/
ErrorStatus I2C_check_dev(I2C_TypeDef* I2Cx, uint8_t SlaveAddress);

#endif
