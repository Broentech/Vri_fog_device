//h+//////////////////////////////////////////////////////////////////////////
/*!
//  \file      DataStructure.h
//
//  \brief     Definitions for the Broentech datatypes plugin, 32 bit systems. Note, these should work out of the box
//             for STM32 microcontrollers (4 byte integers). For Atmega on Arduino Uno, ints are 2 bytes, therefore on the receiver side
//             the SHORT version must be used, on transmitter side INT must be used
//
//  \author    Luca Petricca, Stian Broen
//
//  \date      19.06.2014
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

#ifndef _BROENTECH_DATA_STRUCTURE_H
#define _BROENTECH_DATA_STRUCTURE_H

#define DATATYPE_INT "INTE"
#define DATATYPE_FLOAT "FLOA"
#define DATATYPE_SHORT "SHOR"
#define DATATYPE_CHAR "CHAR"
#define VRIBOARD_ID "$V"
#define ARDUINO_ID "$A"
#define CUSTOMBOARD_ID "$C"
#define BOARD_UNIQUE_ID_UNKNOWN "XX"
#define sizeOfPackage 32

#include "stdio.h"
#include "misc.h"

// Package header, 16 bytes
typedef struct Broentech_Package_Header
{
   char datagramID[4]; // $VXX = unassigned VRI id, $V01 = assigned VRI id etc | 4 bytes 
   char sensID[4];     // Sensor ID: Temp,  CO_2, Humi                         | 4 bytes 
   char dataType[4];   // Type of the data: INT,DOU,FLO,CHA                    | 4 bytes 
   char dataID[4];     // data labels for the 4 payloads: example: xyz-        | 4 bytes
} Broentech_Package_Header;

// Define 32 byte packages
typedef struct Broentech_Package_INT
{
   Broentech_Package_Header header;
   int data[3]; // | 12 bytes
   char footer[4]; // END\n
} Broentech_Package_INT;

typedef struct Broentech_Package_FLOAT
{
   Broentech_Package_Header header;
   float data[3]; // | 12 bytes
   char footer[4]; // END\n
} Broentech_Package_FLOAT;

typedef struct Broentech_Package_CHAR
{
   Broentech_Package_Header header;
   char data[12]; // | 12 bytes
   char footer[4]; // END\n
} Broentech_Package_CHAR;

typedef struct Broentech_Package_SHORT
{
   Broentech_Package_Header header;
   short data[3]; // | 6 bytes
   char pad[6];  // SPACING | 6 bytes
   char footer[4]; // END\n
} Broentech_Package_SHORT;

typedef struct Broentech_Package_RECEIVED
{
   char datagramID[4];  // $VXX = unassigned VRI id, $V01 = assigned VRI id etc  | 4 bytes
   char ctype[4];       // command type: configure, request data, etc            | 4 bytes
   char opcode[4];      // Command ID: Opcode of the command                     | 4 bytes
   int intdata[3];      // Payload 3 integers 									 | 12 bytes
   char chardata[4];    // payload 4 chars         	                             | 4 bytes
   char address[2];      // address and register to write                        | 2 bytes
   char footer[2];      // END\n												 | 2 bytes
} Broentech_Package_RECEIVED;

typedef union Broentech_Package
{
   Broentech_Package_INT ints;
   Broentech_Package_FLOAT floats;
   Broentech_Package_CHAR chars;
   Broentech_Package_SHORT shorts;
   Broentech_Package_RECEIVED received;
   unsigned char bytes[sizeOfPackage];
} Broentech_Package;

#endif
