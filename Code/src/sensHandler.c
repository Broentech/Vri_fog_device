//h+//////////////////////////////////////////////////////////////////////////
/*!
//  \file      sensHandler.c
//
//  \brief     sensor handler:  implementation file: initialize and set the sensors
//
//  \author    Luca Petricca
//
//  \date      15.04.2014
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

#include "sensHandler.h"


//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	init_acceler
/*!
//  initialize and setup sensors registers
//
//  \param  N/A
//
//  \return void
//
//  \author Luca Petricca
//
//  \date  15.04.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////

void init_acceler(void){

	//ACCELEROMETER SETUP Wake it up by writting 1 into the address 0x2A
	uint32_t reg=42;     //register to be written 0x2a
	uint32_t a[2]={reg, 3};	 // a is vector of the data to be sent (register address+value)
	uint32_t *buffer=&a;  //what to write into the register
	uint32_t len=2;		//len is the number of bytes to be write (register address+ real value)

	I2C_Write(I2C2, buffer, len, add_acc); //send

}

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	read_hum
/*!
//  Read
//
//  \param  N/A
//
//  \return int Return humidity as int
//
//  \author Luca Petricca
//
//  \date  15.04.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////

int read_hum(void){

	int lsb, msb, ret=0;  	//lsb and msb is the two byte read form the sensors. ret is the combined and shifted value
	uint8_t valh[2]={0,0};	  		//val[2] is the initialization for the buffer memory (where to store the data)
	uint8_t* value=&valh[0];	//pointer to val
	uint32_t reg=0xe5;		// reg is the register to be read (first)
	uint32_t len=2;			//len is the number of bytes to be read

	I2C_Read(I2C1, value, len, add_hum);   //read values
	lsb=(int) (*value);
	msb=(int) *(value+1);
	ret=(lsb<<6)|msb>>2;

	return ret;

}

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	read_accx
/*!
//  Read
//
//  \param  N/A
//
//  \return int Return x value acceleration as int
//
//  \author Luca Petricca
//
//  \date  15.04.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////

int read_accx(void){


	int lsb, msb, ret=0;  	//lsb and msb is the two byte read form the sensors. ret is the combined and shifted value
	uint8_t val[2];	  	//val[2] is the initialization for the buffer memory (where to store the data)
	uint8_t* value=&val[0];	//pointer to val
	uint32_t reg=0x01;		// reg is the register to be read (first)
	uint32_t len=2;			//len is the number of bytes to be read
	I2C_Read(I2C2, value, len, add_acc);   //read values
	lsb=(int) (*value);
	msb=(int) *(value+1);
	ret=(lsb<<4)|msb>>4;

 return ret;
}

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	read_accy
/*!
//  Read
//
//  \param  N/A
//
//  \return int Return y value acceleration as int
//
//  \author Luca Petricca
//
//  \date  15.04.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////


int read_accy(void){

	int lsb, msb, ret=0;  	//lsb and msb is the two byte read form the sensors. ret is the combined and shifted value
	uint8_t val[2];	  	//val[2] is the initialization for the buffer memory (where to store the data)
	uint8_t* value=&val[0];	//pointer to val
	uint32_t reg=0x03;		// reg is the register to be read (first)
	uint32_t len=2;			//len is the number of bytes to be read
	I2C_Read(I2C2, value, len, add_acc);   //read values
	lsb=(int) (*value);
	msb=(int) *(value+1);
	ret=(lsb<<4)|msb>>4;

 return ret;

}

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	read_accz
/*!
//  Read
//
//  \param  N/A
//
//  \return int Return z value acceleration as int
//
//  \author Luca Petricca
//
//  \date  15.04.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////


int read_accz(void){

		int lsb, msb, ret=0;  	//lsb and msb is the two byte read form the sensors. ret is the combined and shifted value
		uint8_t val[2];	  		//val[2] is the initialization for the buffer memory (where to store the data)
		uint8_t* value=&val[0];	//pointer to val
		uint8_t regleng=1;		//regleng is the length of the register to be read
		uint32_t reg=0x05;		// reg is the register to be read (first)
		uint32_t len=2;			//len is the number of bytes to be read
		I2C_Read(I2C2, value, len, add_acc);  //read values
		lsb=(int) (*value);
		msb=(int) *(value+1);
		ret=(lsb<<4)|msb>>4;

	 return ret;

}

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	read_temp
/*!
//  Read
//
//  \param  N/A
//
//  \return int Return temperature as float
//
//  \author Luca Petricca
//
//  \date  15.04.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////

float read_temp(void){


	int lsb, msb, ret=0;  	//lsb and msb is the two byte read form the sensors. ret is the combined and shifted value
	uint8_t val[2];	  		//val[2] is the initialization for the buffer memory (where to store the data)
	uint8_t* value=&val[0];	//pointer to val
	uint8_t regleng=1;		//regleng is the length of the register to be read
	uint32_t reg=0x00;		// reg is the register to be read (first)
	uint32_t len=2;			//len is the number of bytes to be read

	I2C_Read(I2C1, value, len, add_temp);  //read values
	lsb=(int) (*value);
	msb=(int) *(value+1);
	ret=(lsb<<4)|msb>>4;

	return conv_temp(ret);

}

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	conv_temp
/*!
//  Convert temperature from register value to celsius degree x100
//
//  \param  int Value to convert
//
//  \return int Return temperature value as int
//
//  \author Luca Petricca
//
//  \date  15.04.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////

float conv_temp(int tt){

return ( (float) ((float)tt * 0.0625));

}



//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	conv_acc
/*!
//  Convert temperature from register value to g x100
//
//  \param  int Value to convert
//
//  \return int Return acceleration value as int
//
//  \author Luca Petricca
//
//  \date  15.04.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////

int conv_acc(int aa){

	return aa;
}



//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	conv_hum
/*!
//  Convert humidity from register value to human readable
//
//  \param  int Value to convert
//
//  \return int Return humidity value as int
//
//  \author Luca Petricca
//
//  \date  15.04.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////

int conv_hum(int hh){

	return hh;
}


//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	read_accx
/*!
//  Read
//
//  \param  N/A
//
//  \return int Return x value acceleration as int
//
//  \author Luca Petricca
//
//  \date  15.04.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////

int read_acctem(void){


	int lsb, msb, ret=0;  	//lsb and msb is the two byte read form the sensors. ret is the combined and shifted value
	uint8_t val[1];	  	//val[2] is the initialization for the buffer memory (where to store the data)
	uint8_t* value=&val[0];	//pointer to val
	uint32_t reg=who_am;		// reg is the register to be read (first)
	uint32_t len=1;			//len is the number of bytes to be read

	I2C_Read(I2C1, value, len, add_mpu);  //read values
	lsb=(int) (*value);
	//msb=(int) *(value+1);
	//ret=lsb|msb>>8;

 return lsb;
}
