#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

#include "GPS_Parser.h"
#include "eeprom.h"

#ifndef BUTTONS
#define BUTTONS

//uint8_t buttons_state;
#endif

#define NUMBER_OF_BUTTONS 4

void read_buttons(uint8_t *buttons_state,uint8_t *buttons_long_press_state);
void buttons_events( uint8_t *buttons_state, uint8_t *buttons_long_press_state, Display *Disp, Race_data *Race, eeprom_struct *eeprom, uint8_t *flag);
void read_buttons_2(uint8_t *buttons_state,uint8_t *buttons_long_press_state);
void read_buttons_3(uint8_t *buttons_state,uint8_t *buttons_long_press_state);