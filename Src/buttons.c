#include "buttons.h"

void read_buttons(uint8_t *buttons_state,uint8_t *buttons_long_press_state)
{
	int8_t button_counter[NUMBER_OF_BUTTONS];
	uint16_t Gpio_pin[NUMBER_OF_BUTTONS] = {GPIO_PIN_2,GPIO_PIN_1,GPIO_PIN_4,GPIO_PIN_3};
	for (int8_t counter=0;counter<=20;counter++)
	{
		osDelay(10);
		for (int8_t i=0; i<=NUMBER_OF_BUTTONS-1;i++)
		{
		if (!HAL_GPIO_ReadPin(GPIOA,*(Gpio_pin+i))) (*(button_counter+i))++;	
		}			
	}
	for (int8_t i=0; i<=NUMBER_OF_BUTTONS-1;i++)
	{
		if ((*(button_counter+i)>1)&&(*(button_counter+i)<=15)) *buttons_state |= (1 << i);
		else if (*(button_counter+i)>15) *buttons_long_press_state |= (1 << i);
		*(button_counter+i)=0;
	}
}

void buttons_events( uint8_t *buttons_state, uint8_t *buttons_long_press_state, Display *Disp, Race_data *Race, eeprom_struct *eeprom, uint8_t *eeprom_flag)
{
  
			if (*buttons_state & 1<<0){
				//Race.odo1 += 0.1;
				//Race.odo2 += 0.1;
				Race->backlight++;
				if (Race->backlight>1) Race->backlight=0;
				switch (Race->backlight)
				{
					case 0:
					TIM2->CCR1=65535;
					break;
					case 1:
					TIM2->CCR1=10000;
					break;
				}
				eeprom->backlight = Race->backlight;
				*eeprom_flag = 1;
			}
			if (*buttons_long_press_state & 1<<1){
				Disp->pos2=3;
				*buttons_long_press_state =0;
				//eeprom_write(&eeprom,&eeprom_flag);				
			}
			
			if (*buttons_state & 1<<1){
				Disp->pos2++;
				eeprom->disp_pos2 = Disp->pos2;
				*buttons_state =0;
				*eeprom_flag = 1;
				//eeprom_write(&eeprom,&eeprom_flag);				
			}
			
			if (*buttons_state & 1<<2)
			{
				Race->odo2 = 0;
				eeprom->odo2 = Race->odo2;
				*eeprom_flag = 1;
				
			}
			if (*buttons_state & 1<<3)
			{
				Race->odo1 = 0;
				eeprom->odo1 = Race->odo1;
				*eeprom_flag = 1;
				
}	
};	