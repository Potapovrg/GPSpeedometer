#include "buttons.h"
#include "main.h"

void read_buttons(uint8_t *buttons_state,uint8_t *buttons_long_press_state)
{
	int8_t button_counter[NUMBER_OF_BUTTONS];
	#ifdef ST7920
	uint16_t Gpio_pin[NUMBER_OF_BUTTONS] = {GPIO_PIN_2,GPIO_PIN_1,GPIO_PIN_4,GPIO_PIN_3};
	#endif
	
	#ifdef SSD1309
	uint16_t Gpio_pin[NUMBER_OF_BUTTONS] = {GPIO_PIN_3,GPIO_PIN_4,GPIO_PIN_1,GPIO_PIN_2};
	#endif
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

void buttons_events( uint8_t *buttons_state, uint8_t *buttons_long_press_state, Display *Disp, Race_data *Race,eeprom_ui_struct *eeprom_ui, uint8_t *eeprom_flag)
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
			}
			
			else if BUTTON_LONG_PRESSED(0){
				Disp->menu_page++;
				if (Disp->menu_page>1) Disp->menu_page = 0;
			}				
			if BUTTON_PRESSED(1){
				Disp->pos2++;
				if (Disp->pos2==Disp->pos1) Disp->pos2++;		
			}
			else if BUTTON_LONG_PRESSED(1){
				Disp->pos1++;
				if (Disp->pos1==Disp->pos2) Disp->pos1++;			
			}
			
			
			if BUTTON_PRESSED(2)
			{
				if (CHECK_FLAG(Race->flags,DIRECTION_FLAG)) CLEAR_FLAG(Race->flags,DIRECTION_FLAG);
				else SET_FLAG(Race->flags,DIRECTION_FLAG);
				
				//eeprom_collect(eeprom,Disp,Race,eeprom_flag);
				//eeprom_write(eeprom,eeprom_flag);				
			}
			else if BUTTON_LONG_PRESSED(2){
				Race->odo2 = 0;		
			}
			
			
			
			if (*buttons_state & 1<<3)
			{
				Race->odo1 = 0;
}	
//eeprom_collect(eeprom,Disp,Race,eeprom_flag);
eeprom_ui_collect(eeprom_ui,Race,Disp);
eeprom_ui_write(eeprom_ui);
*buttons_state = 0;	
*buttons_long_press_state = 0;
};	
