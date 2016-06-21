//h+//////////////////////////////////////////////////////////////////////////
/*!
//  \file      radioCraftDriver.c
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

#include "usartHandler.h"


//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	wait_ack
/*!
//   wait for the acknoledgment flag from the RF module by reading ">" value
//
//  \param  N/A
//
//  \return int  //1 if success, 0 in case of error
//
//  \author Luca Petricca
//
//  \date  1.07.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////


int wait_ack(void){
	int timeout;
	timeout=5000;

	while(UsartGet(USART1)!='>')
	  {
	    if((timeout--)==0)
	    {
	      GPIO_WriteBit(GPIOB, GPIO_Pin_15, Bit_SET);
	      UsartPut(USART1, 'X');   // try to close the communication with the RF chip
	      return ERROR;
	    }
	   }
	}

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	open_command
/*!
//   Enter into the configuratio menu with the Radicraft module
//
//  \param  N/A
//
//  \return int  //1 if success, 0 in case of error
//
//  \author Luca Petricca
//
//  \date  10.07.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////


int open_RFconfig(){

	GPIO_WriteBit(GPIOB, GPIO_Pin_15, Bit_RESET);

	if(wait_ack()==ERROR){   // if you not success return error
		return ERROR;
	}

	  GPIO_WriteBit(GPIOB, GPIO_Pin_15, Bit_SET);
	 	    return SUCCESS;
	}


//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	close_RFconfig
/*!
//   Exit from the configuration menu with the Radicraft module
//
//  \param  N/A
//
//  \return N/A
//
//  \author Luca Petricca
//
//  \date  10.07.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////


void close_RFconfig(){

	GPIO_WriteBit(GPIOB, GPIO_Pin_15, Bit_SET);
	UsartPut(USART1, 'X');

}

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	set_RFchannel
/*!
//   Set the RF channel
//
//  \param  uint8_t ch channel number (1-15 depending from the datasheet)
//
//  \return int ;  //1 if success, 0 in case of error
//
//  \author Luca Petricca
//
//  \date  09.07.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////


int set_RFchannel(uint8_t ch){

	// check the parameters
			if (ch<1 || ch>15){
				return ERROR;
				}


	// enter in Config mode
		if (open_RFconfig()==ERROR){
			return ERROR;
			}

	// Enter in memory mode
		 UsartPut(USART1, 'M');   // Send 0x4D to RF and wait for ack

		 if(wait_ack()==ERROR){   // if you not success return error
		 		return ERROR;
		 	}

		    // Enter in memory mode

		     UsartPut(USART1, 0x00);   // select address to write
		     UsartPut(USART1, ch);    // Send the new channel
		     UsartPut(USART1, 255);   // close the memory configuration and wait for ack
		     if(wait_ack()==ERROR){   // if you not success return error
		    		 		return ERROR;
		    		 	}

		     close_RFconfig();
		 	 return SUCCESS;
}

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	set_RFsysid
/*!
//   Set the system id of the network
//
//  \param  uint8_t id[4] set the new system id
//
//  \return int ;  //1 if success, 0 in case of error
//
//  \author Luca Petricca
//
//  \date  09.07.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////


int set_RFsysid(uint8_t* id){

	// enter in Config mode
	if (open_RFconfig()==ERROR){
		return ERROR;
	}
	// Enter in memory mode
	UsartPut(USART1, 'M');   // Send 0x4D to RF and wait for ack

	if(wait_ack()==ERROR){   // if you not success return error
		return ERROR;
	}
	// Enter in memory mode
	UsartPut(USART1, 49);   // select address to write
	UsartPut(USART1, id[0]);    // Send the new id[0]
	UsartPut(USART1, 50);   // select address to write
	UsartPut(USART1, (id[1]));    // Send the id[1]
	UsartPut(USART1, 51);   // select address to write
	UsartPut(USART1, (id[2]));    // Send the id[2]
	UsartPut(USART1, 52);   // select address to write
	UsartPut(USART1, (id[3]));    // Send the id[3]

	UsartPut(USART1, 255);   // close the memory configuration and wait for ack
	if(wait_ack()==ERROR){   // if you not success return error
			return ERROR;
		}
	close_RFconfig();
	return SUCCESS;
}

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	set_RFuniid
/*!
//   Set the RF unique id of the chip (DO NOT CHANGE.. is already unique from the factory)
//
//  \param  uint8_t id[4]	contain 4 bytes of the unique ID
//
//  \return int ;  //1 if success, 0 in case of error
//
//  \author Luca Petricca
//
//  \date  09.07.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////


int set_RFuniid(uint8_t* id){

	// enter in Config mode
	if (open_RFconfig()==ERROR){
		return ERROR;
	}

	// Enter in memory mode
	UsartPut(USART1, 'M');   // Send 0x4D to RF and wait for ack

	if(wait_ack()==ERROR){   // if you not success return error
		return ERROR;
	}
	// Enter in memory mode
	UsartPut(USART1, 45);   // select address to write
	UsartPut(USART1, id[0]);    // Send the new id[0]
	UsartPut(USART1, 46);   // select address to write
	UsartPut(USART1, (id[1]));    // Send the id[1]
	UsartPut(USART1, 47);   // select address to write
	UsartPut(USART1, (id[2]));    // Send the id[2]
	UsartPut(USART1, 48);   // select address to write
	UsartPut(USART1, (id[3]));    // Send the id[3]


	UsartPut(USART1, 255);   // close the memory configuration and wait for ack
	if(wait_ack()==ERROR){   // if you not success return error
		return ERROR;
	}

	close_RFconfig();
	return SUCCESS;
	}

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	sleep_RF
/*!
//   put Radicraft module into sleep mode
//
//  \param  N/A
//
//  \return int  //1 if success, 0 in case of error
//
//  \author Luca Petricca
//
//  \date  10.07.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////


int sleep_RF(){

	GPIO_WriteBit(GPIOB, GPIO_Pin_15, Bit_RESET); //assert low the CONFIG PIN and wait for ack

	if(wait_ack()==ERROR){   // if you not success return error
		return ERROR;
	}
	UsartPut(USART1, 'Z');

	return SUCCESS;
}

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	wakeup_RF
/*!
//   wakeup Radicraft module
//
//  \param  N/A
//
//  \return N/A
//
//  \author Luca Petricca
//
//  \date  11.07.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////


void wakeup_RF(){

	GPIO_WriteBit(GPIOB, GPIO_Pin_15, Bit_SET); //assert high the CONFIG PIN

	}

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	set_RFpower
/*!
//   Set the RF output power
//
//  \param  uint8_t pw power number 1-5
//
//  \return int ;  //1 if success, 0 in case of error
//
//  \author Luca Petricca
//
//  \date  11.07.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////


int set_RFpower(uint8_t pw){

	// check the parameters
			if (pw<1 || pw>5){
				return ERROR;
				}
	// enter in Config mode
		if (open_RFconfig()==ERROR){
			return ERROR;
			}

	// Enter in memory mode
		 UsartPut(USART1, 'M');   // Send 0x4D to RF and wait for ack

		 if(wait_ack()==ERROR){   // if you not success return error
		 		return ERROR;
		 	}

		    // Enter in memory mode

		     UsartPut(USART1, 0x01);   // select address to write
		     UsartPut(USART1, pw);    // Send the new channel
		     UsartPut(USART1, 255);   // close the memory configuration and wait for ack
		     if(wait_ack()==ERROR){   // if you not success return error
		    		 		return ERROR;
		    		 	}

		     close_RFconfig(); //close RF config menu
		 	 return SUCCESS;
}

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	set_RFdatarate
/*!
//   Set the RF datarate
//
//  \param  uint8_t dr data rate 1-6
//
//  \return int ;  //1 if success, 0 in case of error
//
//  \author Luca Petricca
//
//  \date  11.07.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////


int set_RFdatarate(uint8_t dr){

	// check the parameters
			if (dr<1 || dr>6){
				return ERROR;
				}
	// enter in Config mode
		if (open_RFconfig()==ERROR){
			return ERROR;
			}

	// Enter in memory mode
		 UsartPut(USART1, 'M');   // Send 0x4D to RF and wait for ack

		 if(wait_ack()==ERROR){   // if you not success return error
		 		return ERROR;
		 	}

		    // Enter in memory mode

		     UsartPut(USART1, 0x02);   // select address to write
		     UsartPut(USART1, dr);    // Send the new channel
		     UsartPut(USART1, 255);   // close the memory configuration and wait for ack
		     if(wait_ack()==ERROR){   // if you not success return error
		    		 		return ERROR;
		    		 	}

		     close_RFconfig(); //close RF config menu
		 	 return SUCCESS;
}

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	set_CTSRTSack()
/*!
//   Set device the UART flow control CTS and RTS
//
//  \param  uint8_t prot
//
//  \return int ;  //1 if success, 0 in case of error
//
//  \author Luca Petricca
//
//  \date  16.10.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////


int set_CTSRTSack(){

	// enter in Config mode
	if (open_RFconfig()==ERROR){
		return ERROR;
		}

	// Enter in memory mode
	 UsartPut(USART1, 'M');   // Send 0x4D to RF and wait for ack

	 if(wait_ack()==ERROR){   // if you not success return error
			return ERROR;
		}

	 UsartPut(USART1, 0x3A);   // select address to write 58
	 UsartPut(USART1, 0x03);    // Enable RTSCTS control
	 UsartPut(USART1, 255);   // close the memory configuration and wait for ack
	 if(wait_ack()==ERROR){   // if you not success return error
		return ERROR;
	 }

	 close_RFconfig(); //close RF config menu
	 return SUCCESS;
}




//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	set_RFprotocol
/*!
//   Set device type:  0=packet, 1=transparent
//
//  \param  uint8_t prot
//
//  \return int ;  //1 if success, 0 in case of error
//
//  \author Luca Petricca
//
//  \date  11.07.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////


int set_RFprotocol(uint8_t prot){

	// check the parameters
			if (prot<0 || prot>1){
				return ERROR;
				}

	// enter in Config mode
		if (open_RFconfig()==ERROR){
			return ERROR;
			}

	// Enter in memory mode
		 UsartPut(USART1, 'M');   // Send 0x4D to RF and wait for ack

		 if(wait_ack()==ERROR){   // if you not success return error
		 		return ERROR;
		 	}

		    // Enter in memory mode

		     UsartPut(USART1, 0x03);   // select address to write 14
		     UsartPut(USART1, prot);    // Send the new channel
		     UsartPut(USART1, 255);   // close the memory configuration and wait for ack
		     if(wait_ack()==ERROR){   // if you not success return error
		    		 		return ERROR;
		    		 	}

		     close_RFconfig(); //close RF config menu
		 	 return SUCCESS;
}

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	set_RFdevtype
/*!
//   Set device type from the memory:  1=gateway, 2=router
//
//  \param  uint8_t dev
//
//  \return int ;  //1 if success, 0 in case of error
//
//  \author Luca Petricca
//
//  \date  11.07.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////


int set_RFdevtype(uint8_t dev){

	// check the parameters
		if (dev<0 || dev>1){
			return ERROR;
			}

	// enter in Config mode
		if (open_RFconfig()==ERROR){
			return ERROR;
			}

	// Enter in memory mode
		 UsartPut(USART1, 'M');   // Send 0x4D to RF and wait for ack

		 if(wait_ack()==ERROR){   // if you not success return error
		 		return ERROR;
		 	}

		    // Enter in memory mode

		     UsartPut(USART1, 0x0E);   // select address to write 14
		     UsartPut(USART1, dev);    // Send the new channel
		     UsartPut(USART1, 255);   // close the memory configuration and wait for ack
		     if(wait_ack()==ERROR){   // if you not success return error
		    		 		return ERROR;
		    		 	}

		     close_RFconfig(); //close RF config menu
		 	 return SUCCESS;
}

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	set_RFaeskey
/*!
//   Set the RF aes key encryption
//
//  \param   char[16]	contain 16 bytes aes key
//
//  \return int ;  //1 if success, 0 in case of error
//
//  \author Luca Petricca
//
//  \date  09.07.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////


int set_RFaeskey(char* key){
	int i;
	// enter in Config mode
	if (open_RFconfig()==ERROR){
		return ERROR;
	}

	 UsartPut(USART1, 0x4B);   // select address to write
	 UsartPut(USART1, 0x37);    // select address to write

	 if(wait_ack()==ERROR){  // wait for ack
		return ERROR;
	  }

	 for(i=0; i<16; i++){
	 UsartPut(USART1, (key[i]));    // Send the id[1]
	 }

	 if(wait_ack()==ERROR){   // if you not success return error
		return ERROR;
	 }

	 close_RFconfig();
	 return SUCCESS;
}

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	set_GWMode
/*!
//   Set the device as Gateway with preloaded configuration
//
//  \param   -
//
//  \return int ;  //1 if success, 0 in case of error
//
//  \author Luca Petricca
//
//  \date  09.09.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////


int set_GWMode(){
	int i;

	// enter in Config mode
	if (open_RFconfig()==ERROR){
		return ERROR;
	}

	 UsartPut(USART1, 0x47);   // select address to write
	 if(wait_ack()==ERROR){  // wait for ack
		return ERROR;
	  }

	 close_RFconfig();
	 return SUCCESS;
}

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	set_RouterMode
/*!
//   Set the device as Router with preloaded configuration
//
//  \param   -
//
//  \return int ;  //1 if success, 0 in case of error
//
//  \author Luca Petricca
//
//  \date  09.09.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////



int set_RouterMode(){
	int i;

	// enter in Config mode
	if (open_RFconfig()==ERROR){
		return ERROR;
	}
	for (i=0; i<10000; i++); //Delay

	 UsartPut(USART1, 0x52);   // select address to write

	 if(wait_ack()==ERROR){  // wait for ack
		return ERROR;
							}
	 close_RFconfig();
	 return SUCCESS;
}


//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	ConfigureRF
/*!
//   Configure RF device
//
//  \param   -
//
//  \return int ;  //1 if success, 0 in case of error
//
//  \author Luca Petricca
//
//  \date  09.09.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////



int ConfigureRF(void){
	int i, delay;
	delay =100000;
	extern uint8_t protocol;
	extern uint8_t channel;
	extern uint8_t systemid[4];

	//close_RFconfig(); 							//exit from initialization spikes on RF pin

	//set up the Radiocraft module... and get stuck if you fail.
		 for (i=0; i<delay; i++); //Delay
		if(set_RouterMode()==ERROR)
			return ERROR;
		 for (i=0; i<delay; i++); //Delay
		if(set_CTSRTSack()==ERROR)
			return ERROR;
		for (i=0; i<delay; i++); //Delay
	   if(set_RFprotocol(protocol)==ERROR) 				//set0packet 1transparent
			return ERROR;
	   for (i=0; i<delay; i++); //Delay
	   if(set_RFsysid(&systemid)==ERROR) 				//Default System ID: 1111
			return ERROR;
	   for (i=0; i<delay; i++); //Delay
	   if(set_RFchannel(channel)==ERROR)
			return ERROR;
	   for (i=0; i<2*delay; i++); //Delay

	 return SUCCESS;
}
