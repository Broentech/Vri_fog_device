//h+//////////////////////////////////////////////////////////////////////////
/*!
//  \file      initGpio.c
//
//  \brief		initialize Buttons, Led, Gpio etc.
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
*/
//h-//////////////////////////////////////////////////////////////////////////

// local includes
#include "initGpio.h"
#include "stm32l1xx.h"

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	initLED
/*!
//  Initialize PB6 LED
//
//  \param  N/A
//
//  \return N/A
//
//  \author Luca Petricca
//
//  \date  01.02.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////
void initLED()
{
	/* Initialize LED D3 connected to PA7 */
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
   GPIO_InitTypeDef GPIO_InitStructureled1;
   GPIO_InitStructureled1.GPIO_Pin = GPIO_Pin_7;
   GPIO_InitStructureled1.GPIO_Mode = GPIO_Mode_OUT;
   GPIO_InitStructureled1.GPIO_Speed = GPIO_Speed_2MHz;
   GPIO_InitStructureled1.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructureled1.GPIO_PuPd = GPIO_PuPd_NOPULL;
   GPIO_Init(GPIOA, &GPIO_InitStructureled1);

   /* Initialize LED D4 connected to PB5 */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
  GPIO_InitStructureled1.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructureled1.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructureled1.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructureled1.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructureled1.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructureled1);

}

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	initButton
/*!
//  Initialize PA0 user button
//
//  \param  N/A
//
//  \return N/A
//
//  \author Luca Petricca
//
//  \date  01.04.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////

void initButton() {

		/* Enable PORT A clock */
	   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	   GPIO_InitTypeDef GPIO_InitStructure_button;
	   GPIO_InitStructure_button.GPIO_Mode = GPIO_Mode_IN;
	   GPIO_InitStructure_button.GPIO_Pin = GPIO_Pin_1;
	   GPIO_Init(GPIOA, &GPIO_InitStructure_button);
}



//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	initRFconfpin
/*!
//  Initialize PB 15 used to assert the CONFIG PIN of the RADIOCRAFT Module
//
//  \param  N/A
//
//  \return N/A
//
//  \author Luca Petricca
//
//  \date  12.06.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////

void initRFconfpin() {

	//Pin B15 as RFconfig pin
	/* Enable PORT B clock */
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
   GPIO_InitTypeDef GPIO_InitStructure;
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_400KHz;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
   GPIO_Init(GPIOB, &GPIO_InitStructure);

   //Pin A 11 and A12 as RTS and CTS pins
	/* Enable PORT A clock */
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
   GPIO_InitTypeDef GPIO_InitStructure1;
   GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_11;
   GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_IN;
   GPIO_InitStructure1.GPIO_Speed = GPIO_Speed_400KHz;
   GPIO_Init(GPIOA, &GPIO_InitStructure1);

		/* Enable PORT B clock */
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
   GPIO_InitTypeDef GPIO_InitStructure2;
   GPIO_InitStructure2.GPIO_Pin =GPIO_Pin_12;
   GPIO_InitStructure2.GPIO_Mode = GPIO_Mode_OUT;
   GPIO_InitStructure2.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure2.GPIO_Speed = GPIO_Speed_400KHz;
   GPIO_Init(GPIOA, &GPIO_InitStructure2);

   GPIO_WriteBit(GPIOB,GPIO_Pin_15,Bit_SET);

   GPIO_WriteBit(GPIOA,GPIO_Pin_12,Bit_RESET);



}


//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	initGPIO
/*!
//  Initialize PB 2 and PB 12 used As external configurable GPIO
//
//  \param  N/A
//
//  \return N/A
//
//  \author Luca Petricca
//
//  \date  12.06.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////

void initGPIO() {

		/* Enable PORT B clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_400KHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	   //initialize them to 0 //
	GPIO_WriteBit(GPIOB,GPIO_Pin_2,Bit_RESET);
	GPIO_WriteBit(GPIOB,GPIO_Pin_12,Bit_RESET);

	}

