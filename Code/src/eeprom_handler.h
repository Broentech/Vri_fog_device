//h+//////////////////////////////////////////////////////////////////////////
/*!
//  \file      eeprom_handler.h
//
//  \brief     Initialize and implement function for the eeprom values
//
//  \author    Luca Petricca
//
//  \date      28.10.2014
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
*/
//h-//////////////////////////////////////////////////////////////////////////


#ifndef _EEPROM_HANDLER_H_
#define _EEPROM_HANDLER_H_

#include "stm32l1xx.h"
#include "stdio.h"
#include "stm32l1xx_syscfg.h"
#include "misc.h"
#include "core_cmFunc.h"
#include "stm32l1xx_flash.h"
#include "Configfile.h"

 //---------------FIXED DEFINITIONS---------------//

#define EEPROM_START_ADD  ((uint32_t) 0x08080000)	//start address of the EEPROM


int init_eeprom(void);												//Initialize eeprom
int writeintvalue(uint32_t offset, uint32_t value);					//write one int32 value in the eeprom
int writecharvalue(uint32_t offset, uint8_t* value, int length);	//write one char array in the eeprom
uint32_t readintvalue(uint32_t offset);								//read one int32 value
int readcharvalue(uint32_t offset, uint8_t* value, int length);	    //read one char array



#endif
