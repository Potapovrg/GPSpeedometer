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
		if ((*(button_counter+i)>1)&&(*(button_counter+i)<=15)) SET_FLAG(*buttons_state,i);
		else if (*(button_counter+i)>15) SET_FLAG(*buttons_long_press_state,i);
		*(button_counter+i)=0;
	}
}

void buttons_events( uint8_t *buttons_state, uint8_t *buttons_long_press_state, Display *Disp, Race_data *Race, eeprom_struct *eeprom, uint8_t *eeprom_flag)
{
  
			if BUTTON_PRESSED(0){
				if (CHECK_FLAG(Race->flags,BACKLIGHT_FLAG))
				{
					TIM2->CCR1=65535;
					CLEAR_FLAG(Race->flags,BACKLIGHT_FLAG);
				}
				else 
				{
					TIM2->CCR1=10000;
					SET_FLAG(Race->flags,BACKLIGHT_FLAG);
				}
				eeprom->race_flags = Race->flags;
				*eeprom_flag = 1;
				//eeprom_write(eeprom,eeprom_flag);	
			}
			
			else if BUTTON_LONG_PRESSED(0){
				Disp->menu_page++;
				if (Disp->menu_page>1) Disp->menu_page = 0;
				eeprom->menu_page = Disp->menu_page;
			}				
			if BUTTON_PRESSED(1){
				Disp->pos2++;
				if (Disp->pos2==Disp->pos1) Disp->pos2++;
				eeprom->disp_pos2 = Disp->pos2;
				*eeprom_flag = 1;
				//eeprom_write(&eeprom,&eeprom_flag);				
			}
			else if BUTTON_LONG_PRESSED(1){
				Disp->pos1++;
				if (Disp->pos1==Disp->pos2) Disp->pos1++;
				eeprom->disp_pos1 = Disp->pos1;
				*eeprom_flag = 1;
				//eeprom_write(&eeprom,&eeprom_flag);				
			}
			
			
			if BUTTON_PRESSED(2)
			{
				if (CHECK_FLAG(Race->flags,DIRECTION_FLAG)) CLEAR_FLAG(Race->flags,DIRECTION_FLAG);
				else SET_FLAG(Race->flags,DIRECTION_FLAG);
				
			}
			else if BUTTON_LONG_PRESSED(2){
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
*buttons_state = 0;	
*buttons_long_press_state = 0;
};	
