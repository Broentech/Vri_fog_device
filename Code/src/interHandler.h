//h+//////////////////////////////////////////////////////////////////////////
/*!
//  \file      interHandler.h
//
//  \brief     interrupt handler declaration file : set and initialize all the interrupts sources
//
//  \author    Luca Petricca
//
//  \date      01.04.2014
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

#ifndef _VRI_TIMER_HANDLER_H_
#define _VRI_TIMER_HANDLER_H_

#include "stm32l1xx_gpio.h"
#include "stm32l1xx_exti.h"
#include "stm32l1xx_tim.h"
#include "stm32l1xx_rcc.h"
#include "stm32l1xx_rtc.h"
#include "stm32l1xx_pwr.h"
#include "stm32l1xx_usart.h"
#include "misc.h"
#include "stdio.h"
#include "configfile.h"
#include "Datagram_structure.h"


extern Broentech_Package Receivedpackage;


void InitTimer(void);
void EnTimInterr(void);
void EnExtInter(void);
void SysTick_Handler(void);
void TIM2_IRQHandler(void);
void EXTI0_IRQHandler(void);
void EnRtcInter(void);
void RTC_WKUP_IRQHandler(void);
void EnPVDInter(void);
void EXTI16_IRQHandler(void);
void EnUsartInter(void);
void USART1_IRQHandler(void);


#endif
