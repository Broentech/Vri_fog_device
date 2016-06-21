//h+//////////////////////////////////////////////////////////////////////////
/*!
//  \file      Configfile.h
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
*/
//h-//////////////////////////////////////////////////////////////////////////


#ifndef _VRI_CONFFILE_H_
#define _VRI_CONFFILE_H_


#include "stm32l1xx.h"
#include "stdio.h"
#include "stm32l1xx_syscfg.h"
#include "misc.h"

#define VRITAG_add			  	    ((uint32_t) 0x08080000) //address
#define VRITAG_add_off			  	((uint32_t) 0x00) 		//offset
#define SLEEPTIME_add 		  		((uint32_t) 0x04) 		//offset
#define FLAG_EEPROM				 	((uint32_t) 0x08)		//offset

 extern uint32_t sleeptime; 		//Set the sleeping time
 extern uint8_t systemid[4];		//Set the System ID
 extern int rectime;				//Set the waiting time for a gateway packed
 extern uint8_t protocol;			//Standard protocol:transparent vs packets
 extern uint8_t channel;			//Standard Channel
 extern USART_TypeDef* USARTy;   	//Set the Target for Printf() function
 extern const uint8_t datagramsize;	//set the lengt of datagrams in the send receive loop
 extern int TIMEOUT;




#endif
