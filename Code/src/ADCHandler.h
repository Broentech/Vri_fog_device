//h+//////////////////////////////////////////////////////////////////////////
/*!
//  \file      ADCtHandler.h
//
//  \brief     ADC declaration file
//
//  \author    Luca Petricca
//
//  \date      19.03.2014
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

#ifndef _VRI_ADC_HANDLER_H_
#define _VRI_ADC_HANDLER_H_

#include "stm32l1xx_gpio.h"
#include "stm32l1xx_adc.h"
#include "stdio.h"
#include "stm32l1xx_rcc.h"

void ADC_Initialize(void);
u_int readADC0(void);
u_int readADC1(void);
u_int readADC2(void);
u_int readADC3(void);
u_int readADCbat(void);

#endif
