#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

#include "GPS_Parser.h"
#include "eeprom.h"
#include "flags.h"
#include "race.h"

#ifndef BUTTONS
#define BUTTONS

//uint8_t buttons_state;
#endif

#define NUMBER_OF_BUTTONS 4

#define BUTTON_PRESSED(BIT) ((*buttons_state & 1<< BIT))
#define BUTTON_LONG_PRESSED(BIT) ((*buttons_long_press_state & 1<< BIT))

#define CHANGE_MENU_PAGE() Disp->menu_page++;\
													 eeprom_ui_collect(eeprom,Race,Disp);\
													 eeprom_ui_write(eeprom);

#define CHANGE_BACKLIGHT_BRIGHTNESS()\
	if (CHECK_FLAG(Race->flags,BACKLIGHT_FLAG))\
				{\
					TIM2->CCR1=65535;\
					CLEAR_FLAG(Race->flags,BACKLIGHT_FLAG);\
				}\
				else\
				{\
					TIM2->CCR1=10000;\
					SET_FLAG(Race->flags,BACKLIGHT_FLAG);\
				}\
				eeprom_ui_collect(eeprom,Race,Disp);\
				eeprom_ui_write(eeprom);\

void read_buttons(uint8_t *buttons_state,uint8_t *buttons_long_press_state);
void buttons_events( uint8_t *buttons_state, uint8_t *buttons_long_press_state, Display *Disp, GPS_data *GPS, Race_data *Race,eeprom_struct *eeprom);
