//h+//////////////////////////////////////////////////////////////////////////
/*!
//  \file      PackageHandler.c
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
//	\todo: fix the sending datagrams functions for including a custom header
//
*/
//h-//////////////////////////////////////////////////////////////////////////

#include <string.h>
#include "PackageHandler.h"
#include "Datagram_structure.h"
#include "eeprom_handler.h"


extern const uint8_t datagramsize;

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	sendDatagramint
//
//  This function takes a sensor value and a tag, which describes the value, creates a datagram
//  and prints it on the serial port.
//
//  \param  int value - Sensor value
//          char tag  - Sensor value description tag, must be 4 bytes
//
//  \return N/A
//
//  \author Luca Petricca
//
//  \date  09.06.2014
//
//
//f-//////////////////////////////////////////////////////////////////////////



void sendDatagramint(Broentech_Package_Header header, int value_1, int value_2, int value_3)
{

	// Define package structure 32 byte
  Broentech_Package SerialPacked;

  int i;
  memcpy(&SerialPacked.ints.header.datagramID   ,EEPROM_START_ADD, 4);
  memcpy(&SerialPacked.ints.header.sensID  		,&header.sensID,  4);
  memcpy(&SerialPacked.ints.header.dataType    	,&header.dataType,  4);
  memcpy(&SerialPacked.ints.header.dataID     	,&header.dataID,  4);

  memcpy(&SerialPacked.ints.data[0],  &value_1, 4);
  memcpy(&SerialPacked.ints.data[1],  &value_2, 4);
  memcpy(&SerialPacked.ints.data[2],  &value_3, 4);
  //memcpy(&SerialPacked.vriint.data_4,  &value_4, 2);

  memcpy(&SerialPacked.ints.footer    ,"0000", 4);

  for(i=0; i<datagramsize; i++)
  {
	  UsartPut(USART1, SerialPacked.bytes[i]);
  }
}


//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	sendDatagramfloat
//
//  This function takes a sensor value and a tag, which describes the value, creates a datagram
//  and prints it on the serial port.
//
//  \param  int value - Sensor value
//          char tag  - Sensor value description tag, must be 4 bytes
//
//  \return N/A
//
//  \author Luca Petricca
//
//  \date  09.06.2014
//
//
//f-//////////////////////////////////////////////////////////////////////////

void sendDatagramfloat(float value_1, float value_2, float value_3)
{

	// Define package structure 32 byte
	union Broentech_Package SerialPacked;


  int i;
  memcpy(&SerialPacked.floats.header.datagramID  ,EEPROM_START_ADD, 4);
  memcpy(&SerialPacked.floats.header.sensID  	 ,"TEMP", 4);
  memcpy(&SerialPacked.floats.header.dataType    ,"DFLO", 4);
  memcpy(&SerialPacked.floats.header.dataID    	 ,"T---", 4);

  memcpy(&SerialPacked.floats.data[0], 		&value_1,  4);
  memcpy(&SerialPacked.floats.data[1], 		&value_2,  4);
  memcpy(&SerialPacked.floats.data[2], 		&value_3,  4);
  memcpy(&SerialPacked.floats.footer,			"0000", 4);


  for(i=0; i<datagramsize; i++)
  {
	  UsartPut(USART1, SerialPacked.bytes[i]);
  }
}

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	sendDatagramshort
//
//  This function takes a sensor value and a tag, which describes the value, creates a datagram
//  and prints it on the serial port.
//
//  \param  int value - Sensor value
//          char tag  - Sensor value description tag, must be 4 bytes
//
//  \return N/A
//
//  \author Luca Petricca
//
//  \date  09.06.2014
//
//
//f-//////////////////////////////////////////////////////////////////////////

void sendDatagramshort(short value_1, short value_2, short value_3)
{

	// Define package structure 32 byte
	union Broentech_Package SerialPacked;



  int i;
  memcpy(&SerialPacked.shorts.header.datagramID   ,EEPROM_START_ADD, 4);
  memcpy(&SerialPacked.shorts.header.sensID  	 ,"TEMP", 4);
  memcpy(&SerialPacked.shorts.header.dataType     ,"DFLO", 4);
  memcpy(&SerialPacked.shorts.header.dataID    	 ,"T---", 4);


   memcpy(&SerialPacked.shorts.data[0], 		&value_1,  2);
   memcpy(&SerialPacked.shorts.data[1], 		&value_2,  2);
   memcpy(&SerialPacked.shorts.data[2], 		&value_3,  2);
   memcpy(&SerialPacked.shorts.pad[0], 		    "0",  1);
   memcpy(&SerialPacked.shorts.pad[1], 		    "0",  1);
   memcpy(&SerialPacked.shorts.pad[2], 		    "0",  1);
   memcpy(&SerialPacked.shorts.pad[3], 		    "0",  1);
   memcpy(&SerialPacked.shorts.pad[4], 		    "0",  1);
   memcpy(&SerialPacked.shorts.pad[5], 		    "0",  1);
   memcpy(&SerialPacked.shorts.footer,			"0000", 4);


  for(i=0; i<datagramsize; i++)
  {
	  UsartPut(USART1, SerialPacked.bytes[i]);
  }
}

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	sendDatagramchar
//
//  This function takes a sensor value and a tag, which describes the value, creates a datagram
//  and prints it on the serial port.
//
//  \param  int value - Sensor value
//          char tag  - Sensor value description tag, must be 4 bytes
//
//  \return N/A
//
//  \author Luca Petricca
//
//  \date  09.06.2014
//
//
//f-//////////////////////////////////////////////////////////////////////////

void sendDatagramchar(char* data)
{

	// Define package structure 32 byte
	union Broentech_Package SerialPacked;

  int i;
  memcpy(&SerialPacked.chars.header.datagramID  ,EEPROM_START_ADD, 4);
  memcpy(&SerialPacked.chars.header.sensID  	 ,"TEMP", 4);
  memcpy(&SerialPacked.chars.header.dataType    ,"DFLO", 4);
  memcpy(&SerialPacked.chars.header.dataID    	 ,"T---", 4);

  for(i=0; i<12; i++){
  memcpy(&SerialPacked.chars.data[i], 		&data,  1);
  data++;
  }

  memcpy(&SerialPacked.chars.footer,			"0000", 4);


  for(i=0; i<datagramsize; i++)
  {
	  UsartPut(USART1, SerialPacked.bytes[i]);
  }
}

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	receiveDatagramshort
//
//  This function receive a datagram store it in a given location
//
//
//  \param  union Broentech_Package* --> where to store the datagram
//
//
//  \return int: SUCCESS or ERROR
//
//  \author Luca Petricca
//
//  \date  09.06.2014
//
//
//f-//////////////////////////////////////////////////////////////////////////

int receiveDatagram(union Broentech_Package *SerialPacked)
{

	// Define package structure 32 byte
	int i, j;
	char datagram[32];

    for (i=0; i<datagramsize; i++){
     	//GPIO_WriteBit(GPIOA,GPIO_Pin_12,Bit_SET);
    	datagram[i]=UsartGet(USART1);
    	//GPIO_WriteBit(GPIOA,GPIO_Pin_12,Bit_RESET);

    }
  //  printf("This was 32");

  GPIO_WriteBit(GPIOA,GPIO_Pin_12,Bit_SET);

  memcpy(SerialPacked->received.datagramID   	  ,datagram[0], 4);
  memcpy(SerialPacked->received.ctype  	 		  ,datagram[4], 4);
  memcpy(SerialPacked->received.opcode   		  ,datagram[8], 4);
  memcpy(SerialPacked->received.address    	      ,datagram[12], 2);

   memcpy(SerialPacked->received.intdata		  ,datagram[14], 12);
   memcpy(SerialPacked->received.chardata		  ,datagram[26], 4);
   memcpy(SerialPacked->received.footer			  ,datagram[30], 2);


	 for (i=0;i<4;i++)					//update the tag value
		 writecharvalue(VRITAG_add_off,&datagram, 4 );


return SUCCESS;
}


//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	sendAck
//
//  This function sent an acknoledge package.
//
//  \param
//
//  \return N/A
//
//  \author Luca Petricca
//
//  \date  09.06.2014
//
//
//f-//////////////////////////////////////////////////////////////////////////

void sendAck()
{

	// Define package structure 32 byte
	Broentech_Package SerialPacked;


  int i;
  memcpy(&SerialPacked.chars.header.datagramID   ,EEPROM_START_ADD, 4);
  memcpy(&SerialPacked.chars.header.sensID  	 ,"ACKa", 4);
  memcpy(&SerialPacked.chars.header.dataType     ,"ACKa", 4);
  memcpy(&SerialPacked.chars.header.dataID    	 ,"ACKa", 4);

  for(i=0; i<12; i=i+1){
  memcpy(&SerialPacked.chars.data[i], 		'1',  1);
  }

  memcpy(&SerialPacked.chars.footer,			"0000", 4);


  for(i=0; i<datagramsize; i++)
  {
	  UsartPut(USART1, SerialPacked.bytes[i]);
  }
}



//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	sendNack
//
//  This function sent an NOT acknoledge package.
//
//  \param
//
//  \return N/A
//
//  \author Luca Petricca
//
//  \date  10.11.2014
//
//
//f-//////////////////////////////////////////////////////////////////////////

void sendNack()
{

	// Define package structure 32 byte
	Broentech_Package SerialPacked;


  int i;
  memcpy(&SerialPacked.chars.header.datagramID   ,EEPROM_START_ADD, 4);
  memcpy(&SerialPacked.chars.header.sensID  	 ,"NACK", 4);
  memcpy(&SerialPacked.chars.header.dataType     ,"NACK", 4);
  memcpy(&SerialPacked.chars.header.dataID    	 ,"NACK", 4);

  for(i=0; i<12; i=i+1){
  memcpy(&SerialPacked.chars.data[i], 		'0',  1);
  }

  memcpy(&SerialPacked.chars.footer,			"0000", 4);


  for(i=0; i<datagramsize; i++)
  {
	  UsartPut(USART1, SerialPacked.bytes[i]);
  }
}


//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	checkdatagram
//
//  This function Check for valid package package by looking the first two CHARS "$V" and the last two CHARS "00".
//
//  \param: pointer to the package to be check
//
//  \return SUCCESS or ERROR
//
//  \author Luca Petricca
//
//  \date  10.11.2014
//
//
//f-//////////////////////////////////////////////////////////////////////////

int checkDatagram(Broentech_Package *pack )
{
	Broentech_Package package= *pack;
	return((package.bytes[0]=='$')&&(package.bytes[1]=='V')&&(package.bytes[30]=='0')&&(package.bytes[31]=='0'));

}


//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	parseDatagram
//
//  This function parse and execute the actions on the input datagram. It support
//				1-CONF: Contain Configuration Commands (channel, netId, sleeptime etc)
//				2-INFO: To Be defined
//				3-OTHE: To be defined
//				4-RSET: Force the board to be reseted to default value
//
//  \param: the input datagram
//
//  \return: SUCCESS or ERROR
//
//  \author Luca Petricca
//
//  \date  10.11.2014
//
//
//f-//////////////////////////////////////////////////////////////////////////

int parseDatagram(Broentech_Package *pack )
{
		Broentech_Package package= *pack;

			if(strncmp(&package.received.ctype,"CONF",4)==0)   	//Parse and execute the CONF command
				return ctypeConf(&package);
			else if(strncmp(&package.received.ctype,"INFO",4)==0)
				return ctypeInfo(&package);						//Parse and execute the INFO command
			else if(strncmp(&package.received.ctype,"OTHE",4)==0)
				return ctypeOthe(&package);						//Parse and execute the OTHE command

		return ERROR;				 //if no one of the previous is called...there is an error in the datagram

}


//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	ctypeConf()
//
//  This function is called when a received datagram contain the opcode CONF
//
//  \param: the datagram to process
//
//  \return: SUCCESS or ERROR
//
//  \other: The opcode supported for CONF mode are:
//			 1- "sIDx"  = Set the Board ID as the ID of the Datagram
//			 2- "CHAN"  = Set the Trasmission Channel to x. x must be placed in pack.received.INT[0]
//			 3- "NEID"  = Set the Netword ID of the system.. The ID must be contained in pack.received.chardata[0-4]
//			 4- "SLEP"	= Set the Sleeping Time that regulate the core frequency
//			 5- "RSET"	= Reset all the configuration to the initial state ($Vxx) and reset the board
//
//  \author Luca Petricca
//
//  \date  10.11.2014
//
//
//f-//////////////////////////////////////////////////////////////////////////

int ctypeConf(Broentech_Package *pack )
{
	Broentech_Package package= *pack;


	if(strncmp(&package.received.opcode,"sIDx",4)==0)   		//set ID of the device (VRI_TAG)
		return writecharvalue(VRITAG_add_off, &package.bytes, 4);

	else if(strncmp(&package.received.opcode,"CHAN",4)==0) {	// check channel and set transmission Channel
		uint8_t channel=(uint8_t) package.received.intdata[0];
			if(channel<0 || channel>15)
				return ERROR;
			return set_RFchannel(channel);				//DoCHAN(&package);
		}

	else if(strncmp(&package.received.opcode,"NEID",4)==0)	//set Network Id
		return set_RFsysid(&package.received.chardata);

	else if(strncmp(&package.received.opcode,"SLEP",4)==0){	//set Sleeping Time
		int status;
		if(package.received.intdata[0]<0 || package.received.intdata[0]>0xFFFF)	//sleeptime must be within 0x0000 and 0xFFFF
			return ERROR;

		status= writeintvalue(SLEEPTIME_add, package.received.intdata[0]); 	//update the VALUE inside the EEPROM
		RTC_WakeUpCmd(DISABLE);								//turn down the RTC
		RTC_SetWakeUpCounter(readintvalue(SLEEPTIME_add));	//update the Value
		RTC_WakeUpCmd(ENABLE);								//turn up the RTC
		return status;										//return the status
		}

	else if(strncmp(&package.received.opcode,"RSET",4)==0){	//This command DESTROY all the CONF and reset the board
		writeintvalue(FLAG_EEPROM, 0x00000000);			//reset the flag eeprom memory location.
		NVIC_SystemReset();								//reset the system
		return ERROR;									//this point should never be reached
		}

	else
		return ERROR;      //if no one of the previous is called...there is an error in the datagram
}

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	ctypeINFO()
//
//  This function is called when a received datagram contain the opcode INFO
//
//  \param: the datagram to process
//
//  \return: SUCCESS or ERROR
//
//  \other: The Behaviour of INFO Must Be Defined
//
//
//  \author Luca Petricca
//
//  \date  10.11.2014
//
//
//f-//////////////////////////////////////////////////////////////////////////

int ctypeInfo(Broentech_Package *pack )
{
	Broentech_Package package= *pack;

		if(strncmp(&package.received.opcode,"INFO",4)==0)   		//The INFO Must Be Defined
			return SUCCESS;
		else
			return ERROR; 					//If the OPCODE is not INFO than is an ERROR
}


//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	ctypeOTHE()
//
//  This function is called when a received datagram contain the opcode OTHE
//
//  \param: the datagram to process
//
//  \return: SUCCESS or ERROR
//
//  \other:  The OPCODE can be:
//				GPO1 : Control GPIO1 output: (SET or RESET is encoded in )
//				GPO2:  Control GPIO2 output
//
//
//  \author Luca Petricca
//
//  \date  18.11.2014
//
//
//f-//////////////////////////////////////////////////////////////////////////

int ctypeOthe(Broentech_Package *pack ){

	Broentech_Package package= *pack;

		if(strncmp(&package.received.opcode,"GPO1",4)==0) {  		//If we select GPIO1

			if (package.received.chardata[0]!=48 && package.received.chardata[0]!=49) return ERROR; 		//if the char is not 0 or 1 than is an error

			GPIO_WriteBit(GPIOB, GPIO_Pin_12, package.received.chardata[0]==48 ? Bit_RESET:Bit_SET); //if chardata=0 reset the bit otherwise Set the value
			return SUCCESS;
		}
		else if((strncmp(&package.received.opcode,"GPO2",4)==0)){	//if we select GPIO2
			if (package.received.chardata[0]!=48 && package.received.chardata[0]!=49) return ERROR; 		//if the char is not 0 or 1 than is an error

			GPIO_WriteBit(GPIOB, GPIO_Pin_2, package.received.chardata[0]==48 ? Bit_RESET:Bit_SET); //if chardata=0 reset the bit otherwise Set the value
			return SUCCESS;
		}

		else return ERROR;						//If the OPCODE is not in the list than is an ERROR
	}



