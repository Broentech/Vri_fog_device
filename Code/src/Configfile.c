//h+//////////////////////////////////////////////////////////////////////////
/*!
//  \file      Configfile.c
//
//  \brief     Contain all the global variables that can be changed by external commands
//
//  \author    Luca Petricca
//
//  \date      18.09.2014
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
//
//h-//////////////////////////////////////////////////////////////////////////*/



#include "configfile.h"


				/*Configuration of MCU Related parameters*/

  uint32_t sleeptime=0x04;							//Default Sleep Time: 4 seconds
  int rectime=50000;								//waiting time for gateway response: 50000


  	  	  	 	/*Configuration of RF Related parameters*/

  uint8_t systemid[4]={2,2,2,2};					//Default System ID: 2.2.2.2
  uint8_t protocol=0; 								//Protocol Used by RF:  0=packets;  1=transparent;
  uint8_t channel=2;								//Set Channel=2


  	  	  	  	 /*Configuration of other parameters*/

  USART_TypeDef* USARTy=USART1;						//Set the Target for Printf() function
  const uint8_t datagramsize=32;					//Set the length of the datagram size in the send/receive loop
  int TIMEOUT=4000; 								// general purpose timeout used for communications


