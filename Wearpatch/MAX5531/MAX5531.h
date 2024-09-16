#ifndef MAX5531_H
#define MAX5531_H
#include "main.h"
#include "spi.h"



extern SPI_HandleTypeDef hspi1;                     
#define  spi_transmit(pdata,data_size)              HAL_SPI_Transmit(&hspi1,pdata,data_size,10)
#define MAX5531_CS(state) 				                  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, state)
  


 

void MAX5531_reg_write(uint8_t cmd,uint16_t dat);
void MAX5531_Init(void);
void MAX5531_Enter_Normal(void);
void MAX5531_Enter_Shutdown(void);
void MAX5531_Enter_Standby(void);
void MAX5531_SetVoltage(float volt);
#endif
