//h+//////////////////////////////////////////////////////////////////////////
/*!
//  \file      I2cHandler.h
//
//  \brief     I2C I/O declaration file
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
*/
//h-//////////////////////////////////////////////////////////////////////////

#ifndef _VRI_I2C_HANDLER_H_
#define _VRI_I2C_HANDLER_H_


#include "stm32l1xx_gpio.h"
#include "stm32l1xx_i2c.h"
#include "stm32l1xx_rcc.h"


void init_I2C2(void);
void I2C_start_slave_write(I2C_TypeDef* I2Cx, uint8_t address);
void I2C_start_slave_read(I2C_TypeDef* I2Cx, uint8_t address);
uint8_t I2C_read(I2C_TypeDef* I2Cx);
void I2C_send(I2C_TypeDef* I2Cx, uint8_t data);
void I2C_stop(I2C_TypeDef* I2Cx);


#endif
