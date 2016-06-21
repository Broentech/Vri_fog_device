//h+//////////////////////////////////////////////////////////////////////////
/*!
//  \file      main.c
//
//  \brief     Application entry point
//
//			   Please connect the Pin A9(USART Tx) to the RX pin of the FTDI adapter
//			   and the Pin A10(USART Rx) to the TX pin of the FTDI adapter
//
//			   NB. Please comment the fputc funtion inside the printf file
//
//  \author    Luca Petricca
//
//  \date      14.04.2014
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

// local includes
#include "configfile.h"
#include "usartHandler.h"
#include "initGpio.h"
#include "interHandler.h"
#include "I2cHandler.h"
#include "sensHandler.h"
#include "packageHandler.h"
#include "radioCraftDriver.h"

#include "stm32l1xx.h"
#include "stdio.h"
#include "stm32l1xx_syscfg.h"
#include "stm32l1xx_rcc.h"
#include "misc.h"
#include "stm32l1xx_tim.h"
#include "stm32l1xx_exti.h"
#include "stm32l1xx_pwr.h"
#include "stm32l1xx_flash.h"




 extern uint32_t sleeptime;
 Broentech_Package Receivedpackage;
 extern int rectime;


//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	initALL
/*!
//
//  \param  N/A
//
//  \return N/A
//
//  \author Luca Petricca
//
//  \date  14.04.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////



void initALL()
{
	int flag;
				/*initialize the clocks and basic peripherals*/
   RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE);		//set the SYSCLOCK
   RCC_HCLKConfig(RCC_SYSCLK_Div1);				//set the SYSCLOCK
   initUSART(USART1); 							//Initialize USART1
   //initUSART(USART3); 							//Initialize USART3
   ADC_Initialize();							//Initialize ADCs
   I2C_LowLevel_Init(I2C1, 100000, 0);			//Initialize I2C1 bus @ 100Khz speed
   I2C_LowLevel_Init(I2C2, 100000, 0);			//Initialize I2C1 bus @ 100Khz speed
   initLED();	         						//Initialize LEDs D3 D4
   initGPIO();									//initialize PB2 and PB12 used as external GPIO
   //InitTimer();  									//Initialize Timer

   	   	 /* Initialize and configure RF related functions */
   initRFconfpin();	// Init the GPIO PB15 used as CONFIG PIN with the RADIOCRAFT module


   //Configure the RF BOARD to standard value (configfile.c): NETID 2.2.2.2 Channel 2
   if (readintvalue(FLAG_EEPROM)!=0xf0f0f0f0){ //flag eeprom = f0f0f0f0 only when already initialized
   	   flag= ConfigureRF();
	   close_RFconfig();
	   if (flag==ERROR)
	   	   printf("Configuration Failed");
	   else
		   printf("Configuration RF ok");
   }
   else
	   close_RFconfig();

   	  /* Initialize EEPROM VALUES*/
   if (readintvalue(FLAG_EEPROM)!=0xf0f0f0f0){   //flag eeprom = f0f0f0f0 only when already initialized
	   init_eeprom(); //Initialize eeprom
	   Receivedpackage.bytes[0]='$';
	   Receivedpackage.bytes[1]='V';
	   Receivedpackage.bytes[2]='x';
	   Receivedpackage.bytes[3]='x';
   	}

	   	   /*Initialize Sensors*/

   init_acceler();			//initialize accelerometer

 	  	  /* Initialize interrupts sources*/
EnRtcInter();								//Initialize RTC Interrupt Source
EnUsartInter();								//Enable the USART Interrupts
//EnPVDInter();      						//Enable the power PVD
//EnExtInter();								//Initialize External Interrupt Source
//EnTimInterr();								//Initialize Timer Interrupt Source

}



//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	main
/*!
//
//  \param  N/A
//
//  \return N/A
//
//  \author Luca Petricca
//
//  \date  14.04.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////

int main(void)
{
   int rectimetemp, adc2, adc3, bat, i, accx, accy, accz;
   float temp=0;
   accx=accy=accz=adc2=bat=adc3=0;
   uint8_t receivedflag, j=0;
   Broentech_Package_Header header;


   	initALL();   // Initialize all the peripherals
	/* Check I2C device and tell me who is connected and who is not
	 for (j=0; j<255; j+=2){
		for (i=0; i<1000; i++);   //Delay
		 if(I2C_check_dev(I2C2, j)==SUCCESS)
			 printf("device %d ok \n\r", j);
	 }

	 for (i=0; i<100000; i++);   //Delay
	 printf("Initialization Status: Ok, Devices checked! \n\r");	//Send string over USART1
	 for (i=0; i<1000000; i++);   //Delay
	 */


   while(1)
   {
	//wakeup_RF();		// Wake up the RF chip

	/*read ADC values*/
	bat=(3*readADCbat());  //read battery value
	temp=read_temp();
	// adc3=readADC3(); //read ADC3 Sensors
	// adc2=readADC2(); //read ADC2 Sensor
	sendDatagramfloat(temp, 0.0, 0.0);
	//  sendDatagramint(adc2,0,0);
	//  sendDatagramint(adc3,0,0);

	//build header and sent datagram for bat
	memcpy(&header.sensID,		"BATT",4);
	memcpy(&header.dataType,	"AINT",4);
	memcpy(&header.dataID,		"B---",4);
	sendDatagramint(header,bat,0,0);


	temp=0.0;
	bat=adc3=adc2=0;
	//go to sleep
	//sleep_RF();
	PWR_EnterSleepMode(PWR_Regulator_LowPower, PWR_SLEEPEntry_WFI);

   }
}
