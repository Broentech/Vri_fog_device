//h+//////////////////////////////////////////////////////////////////////////
/*!
//  \file      I2cHandler.c
//
//  \brief     I2C I/O implementation file
//
//  \author    Luca Petricca
//
//  \date      17.02.2014
//
//  \par       Copyright: BroenTech AS
//
//
//
//  \par       Revision History
//
//
//
//
*/
//h-//////////////////////////////////////////////////////////////////////////

#include "I2cHandler.h"


//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	init_I2C2
/*!
//  Initialize the I2C 2 interface (including the GPIO pins)
//
//  \param  N/A
//
//  \return N/A
//
//  \author Luca Petricca
//
//  \date  18.02.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////

void init_I2C2(void)
{

	//Enable clocks
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);

	//Mux out I2C_2 SCL & SDA
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_I2C2); // PB10 I2C_2 SCL
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_I2C2); // PB11 I2C_2 SDA



	//Setup SCL and SDA pins
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_400KHz;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_OType	= GPIO_OType_OD;
	GPIO_Init(GPIOB, &GPIO_InitStructure);



	// Configure and initialize I2C2
	I2C_InitTypeDef I2C_InitStructure;
    I2C_DeInit(I2C2);
	I2C_InitStructure.I2C_Mode 			= I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle 	= I2C_DutyCycle_2;
	I2C_InitStructure.I2C_Ack 			= I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed 	= 100000;
	I2C_InitStructure.I2C_OwnAddress1 	= 0x00;
	I2C_Init(I2C2, &I2C_InitStructure);
	// Enable I2C2
	I2C_Cmd(I2C2, ENABLE);
}

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	I2C_startslave_write
/*!
//  Initialize communication with a defined slave
//
//  \param  I2C_TypeDef* I2Cx, uint8_t address
//
//  \return N/A
//
//	\This function generate start signal and sent the slave address with the write bit on
//
//  \Note: Parameters are the I2C interface the parameter address is the SLAVE address ex.(I2C1,0x69)
//
//
//  \author Luca Petricca
//
//  \date  18.02.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////

void I2C_start_slave_write(I2C_TypeDef* I2Cx, uint8_t address){
	I2C_AcknowledgeConfig(I2Cx, ENABLE);
	// While the bus is busy.
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
	// Send START condition
	I2C_GenerateSTART(I2Cx, ENABLE);
	// Test on EV5 and clear it
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));
	// Send slave Address for write
	I2C_Send7bitAddress(I2Cx, address, I2C_Direction_Transmitter);
	// Test on EV6 and clear it
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

}

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	I2C_startslave_read
/*!
//  Initialize communication with a defined slave
//
//  \param  I2C_TypeDef* I2Cx, uint8_t address
//
//  \return N/A
//
//	\This function generate start signal and sent the slave address with the read bit on
//
//  \Note: Parameters are the I2C interface the parameter address is the SLAVE address ex.(I2C1,0x69)
//
//
//  \author Luca Petricca
//
//  \date  18.02.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////

void I2C_start_slave_read(I2C_TypeDef* I2Cx, uint8_t address){

	// Send START condition
	I2C_GenerateSTART(I2Cx, ENABLE);
	// Test on EV5 and clear it
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));
	// Send slave Address for write
	I2C_Send7bitAddress(I2Cx, address, I2C_Direction_Receiver);
	// Test on EV6 and clear it
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
}

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	 I2C_read
/*!
//  Read data from I2C
//
//  \param  I2C_TypeDef* I2Cx,
//
//  \return uint8_t address
//
//	\This function read the data on specified I2C bus
//
//
//  \author Luca Petricca
//
//  \date  18.02.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////

uint8_t I2C_read(I2C_TypeDef* I2Cx){
	// wait until one byte has been received
	while( !I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED) );
	// read data from I2C data register and return data byte
	uint8_t data = I2C_ReceiveData(I2Cx);
	return data;
}

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	 I2C_send
/*!
//  Send data on I2C
//
//  \param  I2C_TypeDef* I2Cx, uint8_t data
//
//  \return N/A
//
//	\This function send the data on specified I2C bus
//
//
//  \author Luca Petricca
//
//  \date  18.02.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////

void I2C_send(I2C_TypeDef* I2Cx, uint8_t data){
	I2C_SendData(I2Cx, data);
	/* Test on EV8 and clear it */
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
}

//f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	 I2C_stop
/*!
//  Send data on I2C
//
//  \param  I2C_TypeDef* I2Cx
//
//  \return N/A
//
//	\This function generate stop condition on the specified I2C interface
//
//
//  \author Luca Petricca
//
//  \date  18.02.2014
//
*/
//f-//////////////////////////////////////////////////////////////////////////

void I2C_stop(I2C_TypeDef* I2Cx){

	// Disable the ACK and Generate STOP signal
    I2C_AcknowledgeConfig(I2Cx, DISABLE);
    I2C_GenerateSTOP(I2Cx, ENABLE);
}
