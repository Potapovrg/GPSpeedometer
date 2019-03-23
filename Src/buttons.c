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

void buttons_events( uint8_t *buttons_state, uint8_t *buttons_long_press_state, Display *Disp, GPS_data *GPS, Race_data *Race,eeprom_struct *eeprom)
{
  switch (Disp->menu_page){
		case 2:
		if BUTTON_PRESSED(0){
			CHANGE_BACKLIGHT_BRIGHTNESS();
		}
		
		else if BUTTON_LONG_PRESSED(0){
				CHANGE_MENU_PAGE();
			}
		
		if BUTTON_PRESSED(1){
			Race->GMT.h++;
			if (Race->GMT.h>13) Race->GMT.h = -13;
			eeprom_time_collect(eeprom,Race,Disp);
			eeprom_time_write(eeprom);	
		}
		
		else if BUTTON_LONG_PRESSED(1){
			Race->GMT.m +=15;
			if (Race->GMT.m>=60) Race->GMT.m = 0;
			eeprom_time_collect(eeprom,Race,Disp);
			eeprom_time_write(eeprom);
		}
		
		if BUTTON_PRESSED(2){
			Race->Timer_setup.h++;
			if (Race->Timer_setup.h > 24) Race->Timer_setup.h = 0;
			eeprom_time_collect(eeprom,Race,Disp);
			eeprom_time_write(eeprom);
			}
		
		else if BUTTON_LONG_PRESSED(2){
			Race->Timer_setup.m++;
			if (Race->Timer_setup.m >= 60) Race->Timer_setup.h = 0;
			eeprom_time_collect(eeprom,Race,Disp);
			eeprom_time_write(eeprom);
			}
		
			if BUTTON_PRESSED(3){
				if (CHECK_FLAG(Race->flags,TIMER_FLAG))	CLEAR_FLAG(Race->flags,TIMER_FLAG);
					else {
						SET_FLAG(Race->flags,TIMER_FLAG);
						Race->Timer_start.h = GPS->Time.h;
						Race->Timer_start.m = GPS->Time.m;
						Race->Timer_start.s = GPS->Time.s;
					}
				eeprom_time_collect(eeprom,Race,Disp);
				eeprom_time_write(eeprom);
				HAL_Delay(5);
				eeprom_ui_collect(eeprom,Race,Disp);
				eeprom_ui_write(eeprom);	
			}
			
			else if BUTTON_LONG_PRESSED(3){
				CLEAR_FLAG(Race->flags,TIMER_FLAG);
				Race->Timer_setup.h = 0;
				Race->Timer_setup.m = 0;
				eeprom_time_collect(eeprom,Race,Disp);
				eeprom_time_write(eeprom);
				HAL_Delay(5);
				eeprom_ui_collect(eeprom,Race,Disp);
				eeprom_ui_write(eeprom);	
			}
			
			break;
		
		default:
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
				eeprom_ui_collect(eeprom,Race,Disp);
				eeprom_ui_write(eeprom);
			}
			
			else if BUTTON_LONG_PRESSED(0){
				CHANGE_MENU_PAGE();
			}				
			if BUTTON_PRESSED(1){
				Disp->pos2++;
				if (Disp->pos2==Disp->pos1) Disp->pos2++;	
				eeprom_ui_collect(eeprom,Race,Disp);
				eeprom_ui_write(eeprom);
			}
			else if BUTTON_LONG_PRESSED(1){
				Disp->pos1++;
				if (Disp->pos1==Disp->pos2) Disp->pos1++;
				eeprom_ui_collect(eeprom,Race,Disp);
				eeprom_ui_write(eeprom);
			}
			
			
			if BUTTON_PRESSED(2)
			{
				if (CHECK_FLAG(Race->flags,DIRECTION_FLAG)) CLEAR_FLAG(Race->flags,DIRECTION_FLAG);
				else SET_FLAG(Race->flags,DIRECTION_FLAG);
				eeprom_ui_collect(eeprom,Race,Disp);
				eeprom_ui_write(eeprom);			
			}
			else if BUTTON_LONG_PRESSED(2){
				Race->odo2 = 0;
				eeprom_race_collect(eeprom,Race);
				eeprom_race_write(eeprom);			
			}
			
			
			
			if (*buttons_state & 1<<3)
			{
				Race->odo1 = 0;
				eeprom_race_collect(eeprom,Race);
				eeprom_race_write(eeprom);
			}	
			
	}
*buttons_state = 0;	
*buttons_long_press_state = 0;
};	
