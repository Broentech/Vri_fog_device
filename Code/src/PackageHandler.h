//h+//////////////////////////////////////////////////////////////////////////
/*!
//  \file      PackageHandler.h
//
//  \brief     Build and define sizes, type and structure of the communication packages
//
//  \author    Luca Petricca
//
//  \date      09.06.2014
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

#ifndef PACKAGE_HANDLER_H_
#define PACKAGE_HANDLER_H_


#include "misc.h"
#include "stdio.h"
#include "Datagram_structure.h"
#include "stm32l1xx_gpio.h"
#include "stm32l1xx_rcc.h"
#include "Configfile.h"

void sendDatagramint(Broentech_Package_Header header ,int value_1, int value_2, int value_3);
void sendDatagramfloat(float value_1, float value_2, float value_3);
void sendDatagramshort(short value_1, short value_2, short value_3);
void sendDatagramchar(char* data);
int receiveDatagram(union Broentech_Package* SerialPacked);
void sendAck(void);
void sendNack();
int checkDatagram(Broentech_Package *pack);
int parseDatagram(Broentech_Package *pack );

#endif
