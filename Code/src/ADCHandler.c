
//h+//////////////////////////////////////////////////////////////////////////
/*!
//  \file      ADCHandler.c
//
//  \brief     ADC implementation file
//
//  \author    Luca Petricca
//
//  \date      18.03.2014
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

#include "ADCHandler.h"


//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	ADC_Initialize
/*!
//  Initialize the ADC on PIN A0-A4
//
//  \param   -
//
//  \return N/A
//
//  \author Luca Petricca
//
//  \date  18.03.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////

void ADC_Initialize(void)
{
  RCC_HSICmd(ENABLE);
  while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);
  ADC_InitTypeDef  ADC_InitStructure={};
  GPIO_InitTypeDef GPIO_InitStructure={};

  		/* Enable GPIOA clock */
  	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

		/* Configure PA_0,1,2,3, (ADC Channel 0,1,2,3) in analog mode= used for sensors */
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);


  		/* Configure PA_4 (ADC Channel 4) in analog mode= battery voltage sensing */
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure the PIN A5 as enabler for the BATTERY SENSING */
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
   GPIO_InitTypeDef GPIO_InitStructure1;
   GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_5;
   GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_OUT;
   GPIO_InitStructure1.GPIO_Speed = GPIO_Speed_2MHz;
   GPIO_InitStructure1.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure1.GPIO_PuPd = GPIO_PuPd_NOPULL;
   GPIO_Init(GPIOA, &GPIO_InitStructure1);


		/* Enable ADC1 clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

		/* ADC1 configuration */
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_Resolution= ADC_Resolution_12b;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 1;
	ADC_Init(ADC1, &ADC_InitStructure);

		/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);

    	/* Wait until the ADC1 is ready */
  	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_ADONS) == RESET);
  	RCC_HSICmd(DISABLE);

  	 GPIO_WriteBit(GPIOA,GPIO_Pin_5, Bit_RESET);// DISABLE sensing pin

}

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	readADC0
/*!
//  Read the sampled value from channel_0 (PIN A0)
//
//  \param   void
//
//  \return u_int   Sampled value
//
//  \author Luca Petricca
//
//  \date  18.03.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////

u_int readADC0(void)
{
  u_int ret=0;
  RCC_HSICmd(ENABLE);			//Enable HSI
  while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);
  ADC_Cmd(ADC1, ENABLE);   		//Enable ADC1
  ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1,ADC_SampleTime_16Cycles);
  // Start the conversion
  ADC_SoftwareStartConv(ADC1);
  // Wait until conversion completion
  while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
  // Get the conversion value
  ret= ADC_GetConversionValue(ADC1);

  ADC_Cmd(ADC1, DISABLE); 			//Disable the ADC untill next cycle (power save)
  RCC_HSICmd(DISABLE);				//Disable HSI (save power)
  return ret;

}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	readADC1
/*!
//  Read the sampled value from channel_1 (PIN A1)
//
//  \param   void
//
//  \return u_int   Sampled value
//
//  \author Luca Petricca
//
//  \date  18.03.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////

u_int readADC1(void)
{
  u_int ret=0;
  RCC_HSICmd(ENABLE);			//Enable HSI
  while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);
  ADC_Cmd(ADC1, ENABLE);   		//Enable ADC1
  ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1,ADC_SampleTime_16Cycles);
  // Start the conversion
  ADC_SoftwareStartConv(ADC1);
  // Wait until conversion completion
  while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
  // Get the conversion value
  ret= ADC_GetConversionValue(ADC1);

  ADC_Cmd(ADC1, DISABLE); 			//Disable the ADC untill next cycle (power save)
  RCC_HSICmd(DISABLE);				//Disable HSI (save power)
  return ret;

}


//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	readADC2
/*!
//  Read the sampled value from channel_2 (PIN A2)
//
//  \param   void
//
//  \return u_int   Sampled value
//
//  \author Luca Petricca
//
//  \date  18.03.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////

u_int readADC2(void)
{
  u_int ret=0;
  RCC_HSICmd(ENABLE);			//Enable HSI
  while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);
  ADC_Cmd(ADC1, ENABLE);   		//Enable ADC1
  ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1,ADC_SampleTime_16Cycles);
  // Start the conversion
  ADC_SoftwareStartConv(ADC1);
  // Wait until conversion completion
  while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
  // Get the conversion value
  ret= ADC_GetConversionValue(ADC1);

  ADC_Cmd(ADC1, DISABLE); 			//Disable the ADC untill next cycle (power save)
  RCC_HSICmd(DISABLE);				//Disable HSI (save power)
  return ret;

}


//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	readADC3
/*!
//  Read the sampled value from channel_2 (PIN A2)
//
//  \param   void
//
//  \return u_int   Sampled value
//
//  \author Luca Petricca
//
//  \date  18.03.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////

u_int readADC3(void)
{
  u_int ret=0;
  RCC_HSICmd(ENABLE);			//Enable HSI
  while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);
  ADC_Cmd(ADC1, ENABLE);   		//Enable ADC1
  ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 1,ADC_SampleTime_16Cycles);
  // Start the conversion
  ADC_SoftwareStartConv(ADC1);
  // Wait until conversion completion
  while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
  // Get the conversion value
  ret= ADC_GetConversionValue(ADC1);

  ADC_Cmd(ADC1, DISABLE); 			//Disable the ADC untill next cycle (power save)
  RCC_HSICmd(DISABLE);				//Disable HSI (save power)
  return ret;

}


//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	readADCbat
/*!
//  Read the sampled value from channel_4 (Pin A4): battery voltage
//
//  \param   void
//
//  \return u_int   Sampled value
//
//  \author Luca Petricca
//
//  \date  18.03.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////

u_int readADCbat(void)
{
	int i;
  GPIO_WriteBit(GPIOA,GPIO_Pin_5, Bit_SET);// ENABLE sensing pin
  for (i=0; i<1000; i++);	 //this delay is needed for giving time to the capacitor to charge
  u_int ret=0;
  RCC_HSICmd(ENABLE);			//Enable HSI
  while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);

  ADC_Cmd(ADC1, ENABLE);   		//Enable ADC1
  ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1,ADC_SampleTime_16Cycles);
  // Start the conversion
  ADC_SoftwareStartConv(ADC1);
  // Wait until conversion completion
  while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
  // Get the conversion value
  ret= ADC_GetConversionValue(ADC1);

  ADC_Cmd(ADC1, DISABLE); 			//Disable the ADC untill next cycle (power save)
  RCC_HSICmd(DISABLE);				//Disable HSI (save power)
  GPIO_WriteBit(GPIOA,GPIO_Pin_5, Bit_RESET); //disable the sensing pin


  return ret;
}


