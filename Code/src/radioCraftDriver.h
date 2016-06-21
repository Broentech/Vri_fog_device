//h+//////////////////////////////////////////////////////////////////////////
/*!
//  \file      radioCraftDriver.h
//
//  \brief     RadioCraft module drivers
//
//  \author    Luca Petricca
//
//  \date      12.06.2014
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

#ifndef _VRI_RADICRAFTO_DRIVER_
#define _VRI_RADICRAFTO_DRIVER_

#include "usartHandler.h"
#include "initGPIO.h"
#include "Configfile.h"

int open_RFconfig(void);
void close_RFconfig(void);
int set_RFchannel(uint8_t ch);
int set_RFuniid(uint8_t* id);
int set_RFsysid(uint8_t* id);
int sleep_RF(void);
void wakeup_RF(void);
int set_RFpower(uint8_t pw);
int set_RFdatarate(uint8_t dr);
int set_RFprotocol(uint8_t prot);
int set_RFdevtype(uint8_t dev);
int set_RFaeskey(char* key);
int set_GWMode();
int set_RouterMode();
set_CTSRTSack();
int ConfigureRF(void);


#endif
