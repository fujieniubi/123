#include "main.h"
#include "MAX5531.h"
#include "spi.h"
#include "gpio.h"



void MAX5531_reg_write(uint8_t cmd,uint16_t dat)   
{   
	uint8_t command_data[2];
	command_data[0]=(uint8_t)((cmd<<4)|(dat>>8));
	command_data[1]=(uint8_t)(dat&0x00ff);

	MAX5531_CS(0); 
	spi_transmit(command_data,2);
	MAX5531_CS(1); 

}

void MAX5531_Init(void)
{
	
  MAX5531_CS(1); 
	MAX5531_reg_write(0x0D,0x0000);         //进入normal模式，参考电压1.214V
	HAL_Delay(10);
	MAX5531_reg_write(0x0C,0x0000);         //进入standby模式，参考电压1.214V

}
void MAX5531_Enter_Normal(void)
{
	
  MAX5531_CS(1); 
	MAX5531_reg_write(0x0F,0x0000);         //进入normal模式，参考电压1.214V


}

void MAX5531_Enter_Standby(void)
{
	
  MAX5531_CS(1); 

	MAX5531_reg_write(0x0E,0x0000);         //进入standby模式，参考电压1.214V

}

void MAX5531_Enter_Shutdown(void)
{
	
  MAX5531_CS(1); 

	MAX5531_reg_write(0x0C,0x0000);         //进入Shutdown模式，参考电压1.214V

}

void MAX5531_SetVoltage(float volt)//mv
{
	uint16_t DAC_Data;
  DAC_Data = (uint16_t)(volt*3.373f);
	MAX5531_reg_write(0x0F,DAC_Data);	
}




