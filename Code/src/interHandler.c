//h+//////////////////////////////////////////////////////////////////////////
/*!
//  \file      interHandler.c
//
//  \brief     interr handler:  implementation file: initialize and set all the interrupt sources
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

#include "interHandler.h"



  int j=0, i=0, k=0, l=0;
  extern uint32_t sleeptime;
  extern int rectime;

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	InitTimer
/*!
//  Initialize Timer2
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


void InitTimer(void){

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_TimeBaseInitTypeDef timerInitStructure;
	timerInitStructure.TIM_Prescaler = 6550;
	timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	timerInitStructure.TIM_Period = 500;
	timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV4;
	TIM_TimeBaseInit(TIM2, &timerInitStructure);
	TIM_Cmd(TIM2, ENABLE);

	// ENABLE Interrupt generation from the timer
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

 }

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	EnTimInterr
/*!
//  Enable Timer interrupts in the NVIC structure
//
//  \param  N/A
//
//  \return N/A
//
//  \author Luca Petricca
//
//  \date  02.04.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////

void EnTimInterr() {
    NVIC_InitTypeDef nvicStructure;
    nvicStructure.NVIC_IRQChannel = TIM2_IRQn;
    nvicStructure.NVIC_IRQChannelPreemptionPriority = 0;
    nvicStructure.NVIC_IRQChannelSubPriority = 1;
    nvicStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvicStructure);
}




//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	EnExtInterr
/*!
//  Enable and configure External interrupts from the pin A0
//
//  \param  N/A
//
//  \return N/A
//
//  \author Luca Petricca
//
//  \date  02.04.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////


void EnExtInter() {
	//EXTI_X must be equal to pin_Yx.. you can choose Y as ABCD but NOT the X number pin0(abcd)->Exti0->irq0

	//GPIO_EXTILineConfig(GPIO_PortSourceGPIOA , GPIO_PinSource0);

     EXTI_InitTypeDef EXTI_InitStructure;

     /* Configure EXTI Line0 */
     EXTI_InitStructure.EXTI_Line = EXTI_Line0;
     EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
     EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
     EXTI_InitStructure.EXTI_LineCmd = ENABLE;
     EXTI_Init(&EXTI_InitStructure);

     /* Enable and set EXTI Line0 Interrupt to the lowest priority */
     NVIC_InitTypeDef NVIC_InitStructure;
     NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
     NVIC_Init(&NVIC_InitStructure);


}



//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	EnRtcInter
/*!
//  Enable and configure External interrupts from RTC
//
//  \param  N/A
//
//  \return N/A
//
//  \author Luca Petricca
//
//  \date  02.04.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////


void EnRtcInter(void){

	  NVIC_InitTypeDef NVIC_InitStructure;
	  EXTI_InitTypeDef EXTI_InitStructure;
	  RTC_InitTypeDef RTC_InitStructure;

	  /* Enable the PWR clock */
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

	  /* Allow access to RTC */
	  PWR_RTCAccessCmd(ENABLE);

	/* LSI used as RTC source clock */
	/* The RTC Clock may varies due to LSI frequency dispersion. */
	  /* Enable the LSI OSC */
	  RCC_LSICmd(ENABLE);

	  /* Wait till LSI is ready */
	  while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET);

	  /* Select the RTC Clock Source */
	  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);

	  /* Enable the RTC Clock */
	  RCC_RTCCLKCmd(ENABLE);

	  /* Wait for RTC APB registers synchronisation */
	  RTC_WaitForSynchro();

	  /* Calendar Configuration */
	  RTC_InitStructure.RTC_AsynchPrediv = 0x7F;
	  RTC_InitStructure.RTC_SynchPrediv =  0x120; /* (37KHz / 128) - 1 = 0x120*/
	  RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;
	  RTC_Init(&RTC_InitStructure);

	  /*
	  To enable the RTC Wakeup interrupt, the following sequence is required:
	  1. Configure and enable the EXTI Line 20 in interrupt mode and select the rising edge
	  sensitivity.
	  2. Configure and enable the RTC_WKUP IRQ channel in the NVIC.
	  3. Configure the RTC to generate the RTC wakeup timer event.

	  System reset, as well as low power modes (Sleep, Stop and Standby) have no influence on
	  the wakeup timer.
	  */
	  /* EXTI configuration *******************************************************/
	  EXTI_ClearITPendingBit(EXTI_Line20);
	  EXTI_InitStructure.EXTI_Line = EXTI_Line20;
	  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	  EXTI_Init(&EXTI_InitStructure);

	  /* Enable the RTC Wakeup Interrupt */
	  NVIC_InitStructure.NVIC_IRQChannel = RTC_WKUP_IRQn;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_Init(&NVIC_InitStructure);

	  RTC_WakeUpCmd(DISABLE);
	  PWR_RTCAccessCmd(ENABLE);

	  RTC_WakeUpClockConfig(RTC_WakeUpClock_CK_SPRE_16bits);
	  RTC_SetWakeUpCounter(readintvalue(SLEEPTIME_add)); //0x01f4
	  //The WUTF flag must then be cleared by software.
	  RTC_ClearITPendingBit(RTC_IT_WUT); //ClearITPendingBit clears also the flag
	  //RTC_ClearFlag(RTC_FLAG_WUTF); //MANDATORY!
	  RTC_ITConfig(RTC_IT_WUT, ENABLE); //enable interrupt
	  RTC_WakeUpCmd(ENABLE);
	  PWR_RTCAccessCmd(DISABLE); //just in case
 }


//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	SysTick_Handler
//
// SysTick interrupt handler  (Systick generate an interrup every n clock ticks)
//
//  \param  N/A
//
//  \return N/A
//
//  \author Luca Petricca
//
//  \date  31.03.2014

//f-//////////////////////////////////////////////////////////////////////////


void SysTick_Handler(void) {

		j++;
	  printf("SysTick Interrupt executed: %d \n\r", j);

}

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	TIM2_IRQHandler
//
//	Brief: 	Timer 2 interrupt handler
//          (Timer 2 generate an interrupt every time it reach the end of its period)
//  \param  N/A
//
//  \return N/A
//
//  \author Luca Petricca
//
//  \date  31.03.2014

//f-//////////////////////////////////////////////////////////////////////////


void TIM2_IRQHandler(void) {

	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET){
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		printf("Timer Interrupt executed: %d \n\r", i);
		i++;
	}
}


//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	EXTI_IRQHandler
//
//	Brief: 	Timer 2 interrupt handler
//          (Timer 2 generate an interrupt every time it reach the end of its period)
//  \param  N/A
//
//  \return N/A
//
//  \author Luca Petricca
//
//  \date  31.03.2014

//f-//////////////////////////////////////////////////////////////////////////


void EXTI0_IRQHandler(void){
	 EXTI_ClearITPendingBit(EXTI_Line0);
	 k++;
	 printf("External Interrupt executed: %d \n\r", k);

	}


//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	RTC_WKUP_IRQHandler
//
//	Brief: 	RTC wakeup interrup handler
//
//  \param  N/A
//
//  \return N/A
//
//  \author Luca Petricca
//
//  \date  31.03.2014

//f-//////////////////////////////////////////////////////////////////////////

void RTC_WKUP_IRQHandler(void)
{
  if(RTC_GetITStatus(RTC_IT_WUT) != RESET) {
    EXTI_ClearITPendingBit(EXTI_Line20); //OK
    PWR_RTCAccessCmd(ENABLE);
    RTC_ClearITPendingBit(RTC_IT_WUT);
    RTC_ClearFlag(RTC_FLAG_WUTF);
    PWR_RTCAccessCmd(DISABLE);
    l++;
    printf("RTC Interrupt executed: %d \n\r", l);

  }
}

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	EnPVDInter
//
//	Brief: 	Enable the PVD detector to 2.9 volts
//
//  \param  N/A
//
//  \return N/A
//
//  \author Luca Petricca
//
//  \date  12.06.2014

//f-//////////////////////////////////////////////////////////////////////////


void EnPVDInter(void)
{
	/* Enable PWR clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);


	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;

	// Enable the EXTI16 (PVD) Power Supervisor Interrupt
	// EXTI16 rising edge for falling voltage, falling edge for rising voltage on PVD
	NVIC_InitStructure.NVIC_IRQChannel = PVD_IRQn;  // PVD programmable voltage detect
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	PWR_PVDCmd(DISABLE);    // disable PVD before change
	PWR_PVDLevelConfig(PWR_PVDLevel_6); // level falling to trigger powerfail
	PWR_PVDCmd(ENABLE); // enable PVD

	EXTI_ClearITPendingBit(EXTI_Line16);        // clear pending IRQs
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Line = EXTI_Line16;     // set up irq trigger
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  // trigger power rising edge (voltage drop)
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;       // alert if power status changes
	EXTI_Init(&EXTI_InitStructure);

}

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	EXTI16_IRQHandler
//
//	Brief: 	Handle the EXTI16 interrupt triggered by PVD (LOW BATTERY)
//
//  \param  N/A
//
//  \return N/A
//
//  \author Luca Petricca
//
//  \date  12.06.2014

//f-//////////////////////////////////////////////////////////////////////////

void EXTI16_IRQHandler(void){
	int batt;
	EXTI_ClearITPendingBit(EXTI_Line16);
	wakeup_RF();
	batt=readADCbat();
	batt=readADCbat();
	printf("battery low.. %d \n\r", batt);
	sleep_RF();
	}


//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	void USART_NVIC_Config(void)
//
//	Brief: 	initialize the usart interrupts on NVIC
//
//  \param  N/A
//
//  \return N/A
//
//  \author Luca Petricca
//
//  \date  12.10.2014

//f-//////////////////////////////////////////////////////////////////////////


void EnUsartInter(void)
{
	  NVIC_InitTypeDef NVIC_InitStructure;

	  /* Enable the USART2 Interrupt */
	  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_Init(&NVIC_InitStructure);

}



//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	void USART1_IRQHandler(void)
//
//	Brief: 	Interrupt handler of usart interrupts
//
//  \param  N/A
//
//  \return N/A
//
//  \author Luca Petricca
//
//  \date  15.10.2014

//f-//////////////////////////////////////////////////////////////////////////


void USART1_IRQHandler(void)
{
	int i=0;
	int status=SUCCESS;

   if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)				//interrupt called in when you receive a char on usart1
  {
       GPIO_WriteBit(GPIOA,GPIO_Pin_12,Bit_SET); //pause the RF trasmission
	   USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);//disable the RXNE interrupts


	   for (i=0;i<32;i++){
	       GPIO_WriteBit(GPIOA,GPIO_Pin_12,Bit_SET);				//pause the RF trasmission
   		   status=UsartGetTimed(USART1, &Receivedpackage.bytes[i]);	//Receive the char in the buffer
   		   GPIO_WriteBit(GPIOA,GPIO_Pin_12,Bit_RESET);				//Restart the RF trasmission
   		   if (status==ERROR) break;								//if the tramission Timed out than break
   		   }

	   	if (status==SUCCESS){										//if you received 32 chars
	   		 if(checkDatagram(&Receivedpackage))					//and the datagram is correct parse it
	   			status=parseDatagram(&Receivedpackage);
	   		 else status=ERROR;
	   	   }

	     USART_ClearFlag(USART1, USART_IT_RXNE);
	     USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	     USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	     GPIO_WriteBit(GPIOA,GPIO_Pin_12,Bit_RESET); //Restart the RF trasmission

	     if (status==SUCCESS)										//if everything is correct than send ACK
	    	 sendAck();
	     else														//If not send NACK
	    	 sendNack();

  	 }

  /*if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
  {
    /* Write one byte to the transmit data register //
    USART_SendData(USART1, TxBuffer[TxCount++]);

    if(TxCount == NbrOfDataToTransfer)
    {
      // Disable the USART1 Transmit interrupt
      USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
    } */
}






