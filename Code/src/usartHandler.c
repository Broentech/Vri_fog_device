//h+//////////////////////////////////////////////////////////////////////////
/*!
//  \file      usartHandler.c
//
//  \brief     USART I/O implementation file
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
////////////////////////////////////////////////////////////////////////////////////////////////
#include "usartHandler.h"


//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	Usart1Put
//
//  Redifine some methods for making for the printf function printing on usart interface
//
//  \param  uint8_t ch -
//
//  \return N/A
//
//  \author Luca Petricca
//
//  \date  01.02.2014
//
//
//f-//////////////////////////////////////////////////////////////////////////
void UsartPut(USART_TypeDef* USARTx, uint8_t ch)
{
   while(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11));
   USART_SendData(USARTx, (uint8_t) ch);
   //Loop until the end of transmission
   while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET)
   {
   }
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	UsartGet
/*!
//  Redifine some methods for making for the printf function printing on usart interface
//
//  \param  USART_TypeDef*USARTx   Can Be USART1 or USART2
//
//  \return N/A
//
//  \author Luca Petricca
//
//  \date  01.02.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////
uint8_t UsartGet(USART_TypeDef* USARTx)
{
          while (USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET);
		  return (uint8_t)USART_ReceiveData(USARTx);
}


//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	UsartGetTimed
/*!
//  Redifine Usart get with timeout
//
//  \param  USART_TypeDef*USARTx   Can Be USART1 or USART2, * Char
//
//  \return Error or success
//
//  \author Luca Petricca
//
//  \date  01.02.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////
int UsartGetTimed(USART_TypeDef* USARTx, uint8_t* c)
{
	extern int TIMEOUT;
	int timeout=TIMEOUT;
          while (USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET)
        	  	  if(timeout--==0)
        	  		  return ERROR;

		  *c= (uint8_t)USART_ReceiveData(USARTx);
          return SUCCESS;
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	fputc
/*!
//
//  \param  int ch  -
//			FILE *f -
//
//  \return int     -
//
//  \author Luca Petricca
//
//  \date  01.02.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////
int fputc(USART_TypeDef* USARTx,int ch, FILE * f)
{
   UsartPut(USARTx, ch);
   return ch;
}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	fgetc
/*!
//
//  \param  FILE *f -
//
//  \return int     -
//
//  \author Luca Petricca
//
//  \date  01.02.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////
int fgetc(FILE *f)
{
	UsartGet(USART1);
}


//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	readString
/*!
//
//  \param  char *pt -pointer where the data are stored
 * 			USART_TypeDef*USARTx   Can Be USART1 , USART2 or USART3
//
//  \return int    return the number of byte read
//
//  \author Luca Petricca
//
//  \date  01.02.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////

int readString(char *pt, USART_TypeDef* USARTx){
	char termination ='\n';   //termination character
	int counter= 0;

	while(1) {
	 if(0 == pt) return 0;
	*(pt+counter)=UsartGet(USARTx);
	if(pt[counter] == termination) return counter;
	counter++;

	}


}
//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	initUSART
/*!
//  Initialize USART
//
//  \param   USART_TypeDef*USARTx   Can Be USART1 or USART2
//
//  \return N/A
//
//  \author Luca Petricca
//
//  \date  14.03.2014
//
//
//  Added automatic interface selection
//
//
*/
//f-//////////////////////////////////////////////////////////////////////////

void initUSART(USART_TypeDef* USARTx)
{
   /*define Structures for GPIO and USART initialization*/
   GPIO_InitTypeDef GPIO_InitStructure;
   USART_InitTypeDef USART_InitStructure;

   if(USARTx==USART1){

	/* Enable PORT A clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);


   /* Enable USART1 clock */
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);


   /* Mux out USART1 Rx & Tx */
   GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1); // PA9 USART2_TX
   GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1); // PA10 USART2_RX



   /* Configure USART Rx & Tx (-+ and A10) as alternate function */
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
   GPIO_Init(GPIOA, &GPIO_InitStructure);



   /*Configure USART paramenters*/
   USART_InitStructure.USART_BaudRate = 19200;
   USART_InitStructure.USART_WordLength = USART_WordLength_8b;
   USART_InitStructure.USART_StopBits = USART_StopBits_1;
   USART_InitStructure.USART_Parity = USART_Parity_No;
   USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
   USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
   USART_Init(USART1, &USART_InitStructure);

   USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

   /* Enable USART */
   USART_Cmd(USART1, ENABLE);
   }
   else if(USARTx==USART2) {

 	   /* Enable PORT A clock */
 	   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
 	   /* Enable USART2 clock */
 	   RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);


 	   /* Mux out USART2 Rx & Tx */
 	   GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2); // PA2 USART2_TX
 	   GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2); // PA3 USART2_RX


 	   /* Configure USART Rx & Tx (A2 and A3) as alternate function */
 	   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
 	   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
 	   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
 	   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
 	   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
 	   GPIO_Init(GPIOA, &GPIO_InitStructure);

 	   /*Configure USART paramenters*/
 	   USART_InitStructure.USART_BaudRate = 19200;
 	   USART_InitStructure.USART_WordLength = USART_WordLength_8b;
 	   USART_InitStructure.USART_StopBits = USART_StopBits_1;
 	   USART_InitStructure.USART_Parity = USART_Parity_No;
 	   USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
 	   USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
 	   USART_Init(USART2, &USART_InitStructure);

 	   /* Enable USART */
 	   USART_Cmd(USART2, ENABLE);
    }
    else {

 	   /* Enable PORT A clock */
 	   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
 	   /* Enable USART2 clock */
 	   RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);


 	   /* Mux out USART2 Rx & Tx */
 	   GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3); // PB10 USART2_TX
 	   GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3); // PB11 USART2_RX


 	   /* Configure USART Rx & Tx (B10 and B11) as alternate function */
 	   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
 	   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
 	   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
 	   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
 	   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
 	   GPIO_Init(GPIOB, &GPIO_InitStructure);

 	   /*Configure USART paramenters*/
 	   USART_InitStructure.USART_BaudRate = 19200;
 	   USART_InitStructure.USART_WordLength = USART_WordLength_8b;
 	   USART_InitStructure.USART_StopBits = USART_StopBits_1;
 	   USART_InitStructure.USART_Parity = USART_Parity_No;
 	   USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
 	   USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
 	   USART_Init(USART3, &USART_InitStructure);

 	  //enable interrupts
 	  	  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);


 	   /* Enable USART */
 	   USART_Cmd(USART3, ENABLE);

    }

 }


