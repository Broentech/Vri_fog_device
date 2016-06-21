
//h+//////////////////////////////////////////////////////////////////////////
/*!
//  \file      eeprom_handler.c
//
//  \brief     Initialize and implement function for the eeprom values
//
//  \author    Luca Petricca
//
//  \date      28.10.2014
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

#include "eeprom_handler.h"
#include "Configfile.h"


//initialize some eeprom areas with standard values
int init_eeprom(){

	uint8_t c[4]={"$Vxx"};

	writecharvalue(VRITAG_add_off,&c,4); 		//inizialize Vxx memory location
	writeintvalue(FLAG_EEPROM, 0xf0f0f0f0); 	//write FLAGVALUE to special character
	writeintvalue(SLEEPTIME_add, sleeptime); 	// write SLEEPTIME to 3 seconds

}


// write an int32 value in the offset memory location of the eeprom
int writeintvalue(uint32_t offset, uint32_t value){
	__disable_irq();
		DATA_EEPROM_Unlock();
		DATA_EEPROM_ProgramWord(EEPROM_START_ADD +offset, value);
		DATA_EEPROM_Lock();
	__enable_irq();

	return SUCCESS;

}

// write an char value in the offset memory location of the eeprom
int writecharvalue(uint32_t offset, uint8_t* value, int length){
			__disable_irq();
			DATA_EEPROM_Unlock();
			uint8_t *wAddr=(EEPROM_START_ADD +offset);
			while(length--){
				*wAddr++=*value++;
				while(FLASH->SR&FLASH_SR_BSY); //wait for the flag
			}
			DATA_EEPROM_Lock();
			__enable_irq();


			return SUCCESS;
}


// read an int32 value in the offset memory location of the eeprom
uint32_t readintvalue(uint32_t offset){

	uint32_t tmp=0;
	tmp=*(__IO uint32_t*)(EEPROM_START_ADD+offset);
	return tmp;
 }

// read $length char values in the offset memory location of the eeprom
int readcharvalue(uint32_t offset, uint8_t* value, int length){
		__disable_irq();
		uint8_t *wAddr;
		wAddr=(uint8_t *)(EEPROM_START_ADD +offset);
		while(length--){
		 *value++=*wAddr++;
		}
		__enable_irq();
	return SUCCESS;

}


