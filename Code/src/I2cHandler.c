//h+//////////////////////////////////////////////////////////////////////////
/*!
//  \file      i2cHandler.c
//
//  \brief		Handles i2c functions
//
//  \author    Luca Petricca
//
//  \date      01.02.2014
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
//
//    N.B. This I2C Functions are partly re-implemented starting from the template from:
// 	       https://github.com/jmunsch/STM32F4/tree/master/examples/Library
*/
//h-//////////////////////////////////////////////////////////////////////////


#include <stm32l1xx.h>
#include <stm32l1xx_i2c.h>
#include <stm32l1xx_rcc.h>
#include <stm32l1xx_gpio.h>

#include "I2cHandler.h"

#define Timed(x) Timeout = 0xFFFF; while (x) { if (Timeout-- == 0) goto errReturn;}  //define timeout: if timeout happen than it generate error

/*f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	I2C_Read
//
//  read n byte from I2C interface
//
//  \param   I2C_TypeDef* I2Cx,   I2C interface used
// 			 uint8_t* buf, 		  pointer: where to save data
// 			 uint32_t nbuf, 	  nbuf: number of bytes to be read
// 			 uint8_t SlaveAddress Address of the slave device
//
//  \return ErrorStatus:	Success or Error
//
//  \author Luca Petricca
//
//  \date  23.09.2014
//
//
//
//
//
//
//f-//////////////////////////////////////////////////////////////////////////*/

ErrorStatus I2C_Read(I2C_TypeDef* I2Cx, uint8_t *buf,uint32_t nbyte, uint8_t SlaveAddress)
{
  __IO uint32_t Timeout = 0;

  //    I2Cx->CR2 |= I2C_IT_ERR;  interrupts for errors

  if (!nbyte)
    return SUCCESS;

  // Wait for idle I2C interface
  Timed(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));

  // Enable Acknowledgement, clear POS flag
  I2C_AcknowledgeConfig(I2Cx, ENABLE);
  I2C_NACKPositionConfig(I2Cx, I2C_NACKPosition_Current);

  // Intiate Start Sequence (wait for EV5
  I2C_GenerateSTART(I2Cx, ENABLE);
  Timed(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));

  // Send Address
  I2C_Send7bitAddress(I2Cx, SlaveAddress, I2C_Direction_Receiver);

  // wait for flag
  Timed(!I2C_GetFlagStatus(I2Cx, I2C_FLAG_ADDR));

  if (nbyte == 1)
    {

      // Clear Ack bit
      I2C_AcknowledgeConfig(I2Cx, DISABLE);

      // EV6_1 -- must be atomic -- Clear ADDR, generate STOP
      __disable_irq();
      (void) I2Cx->SR2;
      I2C_GenerateSTOP(I2Cx,ENABLE);
      __enable_irq();

      // Receive data   EV7
      Timed(!I2C_GetFlagStatus(I2Cx, I2C_FLAG_RXNE));
      *buf++ = I2C_ReceiveData(I2Cx);

    }
  else if (nbyte == 2)
    {
      // Set POS flag
      I2C_NACKPositionConfig(I2Cx, I2C_NACKPosition_Next);

      // EV6_1 -- must be atomic and in this order
      __disable_irq();
      (void) I2Cx->SR2;                           // Clear ADDR flag
      I2C_AcknowledgeConfig(I2Cx, DISABLE);       // Clear Ack bit
      __enable_irq();

      // EV7_3  -- Wait for BTF, program stop, read data twice
      Timed(!I2C_GetFlagStatus(I2Cx, I2C_FLAG_BTF));

      __disable_irq();
      I2C_GenerateSTOP(I2Cx,ENABLE);
      *buf++ = I2Cx->DR;
      __enable_irq();

      *buf++ = I2Cx->DR;

    }
  else
    {
      (void) I2Cx->SR2;                           // Clear ADDR flag
      while (nbyte-- != 3){
    	  // EV7 -- cannot guarantee 1 transfer completion time, wait for BTF
          //        instead of RXNE
    	  Timed(!I2C_GetFlagStatus(I2Cx, I2C_FLAG_BTF));
    	  *buf++ = I2C_ReceiveData(I2Cx);
      }

      Timed(!I2C_GetFlagStatus(I2Cx, I2C_FLAG_BTF));

      // EV7_2 -- Figure 1 has an error, doesn't read N-2 !
      I2C_AcknowledgeConfig(I2Cx, DISABLE);           // clear ack bit

      __disable_irq();
      *buf++ = I2C_ReceiveData(I2Cx);             // receive byte N-2
      I2C_GenerateSTOP(I2Cx,ENABLE);                  // program stop
      __enable_irq();

      *buf++ = I2C_ReceiveData(I2Cx);             // receive byte N-1

      // wait for byte N
      Timed(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED));
      *buf++ = I2C_ReceiveData(I2Cx);
      nbyte = 0;
    }

  // Wait for stop
  Timed(I2C_GetFlagStatus(I2Cx, I2C_FLAG_STOPF));
  return SUCCESS;

 errReturn:
  // Any cleanup here
  return ERROR;

}

/*f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	I2C_Write
//
//  write n byte to I2C interface
//
//  \param   I2C_TypeDef* I2Cx,   I2C interface used
// 			 uint8_t* buf, 		  pointer to the stored data
// 			 uint32_t nbuf, 	  nbuf: number of bytes to be send
// 			 uint8_t SlaveAddress Address of the slave device
//
//  \return ErrorStatus:	Success or Error
//
//  \author Luca Petricca
//
//  \date  23.09.2014
//
//
//
//
//
//
//f-//////////////////////////////////////////////////////////////////////////*/
ErrorStatus I2C_Write(I2C_TypeDef* I2Cx, const uint8_t* buf,  uint32_t nbyte, uint8_t SlaveAddress)
{
    __IO uint32_t Timeout = 0;

    /* Enable Error IT (used in all modes: DMA, Polling and Interrupts */
    //    I2Cx->CR2 |= I2C_IT_ERR;

    if (nbyte)
      {
	Timed(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));

	// Initiate Start Sequence

	I2C_GenerateSTART(I2Cx, ENABLE);
	Timed(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));

	// Send Address  EV5

	I2C_Send7bitAddress(I2Cx, SlaveAddress, I2C_Direction_Transmitter);
	Timed(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	// Write first byte EV8_1

	I2C_SendData(I2Cx, *buf++);

	while (--nbyte) {

	  // wait on BTF

	  Timed(!I2C_GetFlagStatus(I2Cx, I2C_FLAG_BTF));
	  I2C_SendData(I2Cx, *buf++);
	}

	Timed(!I2C_GetFlagStatus(I2Cx, I2C_FLAG_BTF));
	I2C_GenerateSTOP(I2Cx, ENABLE);
	Timed(I2C_GetFlagStatus(I2Cx, I2C_FLAG_STOPF));
      }
    return SUCCESS;
 errReturn:
    return ERROR;
}

/*f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	checkdev
//
//  Check if the specified slave device is alive
//
//  \param   I2C_TypeDef* I2Cx,   I2C interface use
// 			 uint8_t SlaveAddress slave address to check
//
//
//
//  \return ErrorStatus:	Success=connected or Error=not_connected or I2c_error
//
//  \author Luca Petricca
//
//  \date  29.09.2014
//
//
//
//
//
//
//f-//////////////////////////////////////////////////////////////////////////*/

ErrorStatus I2C_check_dev(I2C_TypeDef* I2Cx, uint8_t addr)
	{
	  int timeout, I2C_TIMEOUT=5000 ;
	  timeout = I2C_TIMEOUT;
	  while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY))
	  {
	    if((timeout--)==0)   // wait until I2C-Bus is not busy anymore
	    {
	      return ERROR;
	    }
	  }
	  I2C_GenerateSTART(I2Cx, ENABLE);
	  timeout = I2C_TIMEOUT;
	  while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
	  {
	    if((timeout--)==0)  // wait while sending I2C-Bus START condition
	    {
	      I2C_GenerateSTOP(I2Cx, ENABLE);
	      return ERROR;
	    }
	  }
	  I2C_Send7bitAddress(I2Cx, addr, I2C_Direction_Transmitter);
	  timeout = I2C_TIMEOUT;
	  while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
	  {
	    if((timeout--)==0)   // wait while sending slave address for write
	    {
	      I2C_GenerateSTOP(I2Cx, ENABLE);
	      return ERROR;
	    }
	  }
	  I2C_GenerateSTOP(I2Cx, ENABLE);
	  return SUCCESS;
	}

/*f+//////////////////////////////////////////////////////////////////////////
//
//  Name:	I2C_LowLevel_Init
//
//  initialize I2C physical interface
//
//  \param   I2C_TypeDef* I2Cx,   I2C interface to initialize
// 			 int ClockSpeed, 	  I2C speed selection
// 			 int OwnAddress, 	  Address of the Master
//
//
//  \return void
//
//  \author Luca Petricca
//
//  \date  23.09.2014
//
//f-//////////////////////////////////////////////////////////////////////////*/

void I2C_LowLevel_Init(I2C_TypeDef* I2Cx, int ClockSpeed, int OwnAddress)
{

    GPIO_InitTypeDef  GPIO_InitStructure;
    I2C_InitTypeDef  I2C_InitStructure;

    // Enable GPIOB clocks
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

    // Configure I2C clock and GPIO
    GPIO_StructInit(&GPIO_InitStructure);


    if (I2Cx == I2C1){

        /* I2C1 clock enable */
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

        //GPIO Alternate functions configuration
        GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_I2C1);
        GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_I2C1);

        /* I2C1 SDA and SCL configuration */
        GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_400KHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
        GPIO_Init(GPIOB, &GPIO_InitStructure);

        /* I2C1 Reset */
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, DISABLE);

      }
      else {

        /* I2C2 clock enable */
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);

        //GPIO Alternate functions configuration
        GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_I2C2);
        GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_I2C2);

        /* I2C2 SDA and SCL configuration */
        GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_400KHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
        GPIO_Init(GPIOB, &GPIO_InitStructure);

        /* I2C2  Reset */
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2, DISABLE);

      }

    /* Configure I2Cx                */
    I2C_StructInit(&I2C_InitStructure);
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_OwnAddress1 = OwnAddress;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_ClockSpeed = ClockSpeed;

    I2C_Init(I2Cx, &I2C_InitStructure);
    I2C_Cmd(I2Cx, ENABLE);
}
