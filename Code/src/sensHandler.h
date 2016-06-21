//h+//////////////////////////////////////////////////////////////////////////
/*!
//  \file      sensHandler.h
//
//  \brief     sensor handler declaration file : set and initialize all the sensor
//
//  \author    Luca Petricca
//
//  \date      15.04.2014
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


#ifndef _VRI_SENSOR_HANDLER_H_
#define _VRI_SENSOR_HANDLER_H_

#include "I2cHandler.h"
#include "stm32l1xx.h"
#include "stdio.h"
#include "stm32l1xx_syscfg.h"

//#define address 	0xd2 //address gyro
#define add_temp	0x92
#define	add_hum		0x80
#define add_acc		0x3A
#define add_mpu		0xD0
#define who_am_i 	0x00
#define who_am		0x75

void init_acceler(void);
int read_accx(void);
int read_accy(void);
int read_accz(void);
int conv_acc(int aa);
int read_acctem(void);
float read_temp(void);
float conv_temp(int tt);
int read_hum(void);
int conv_hum(int hh);

#endif


