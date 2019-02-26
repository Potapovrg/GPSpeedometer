#include "u8g2.h"  
#include "u8g2_arm.h"
#include <stdio.h>
#include "GPS_parser.h"
#include "race.h"
#include "flags.h"

#ifndef DISPLAY_STRUCT
#define DISPLAY_STRUCT
typedef struct {
	int8_t pos1;
	int8_t pos2;
	int8_t menu_page;
}Display;
#endif

void speedo(GPS_data *GPS, Race_data *Race, Display *Disp);
//void rallycomp(GPS_data *GPS, Race_data *Race, Display *Disp, uint8_t buttons_state);
void rallycomp(GPS_data *GPS, Race_data *Race, Display *Disp);
void gui(GPS_data *GPS, Race_data *Race, Display *Disp);
void start_sreen(void);
uint8_t calculate_shift(float odo);
uint8_t calculate_shift_18(float odo);
extern u8g2_t u8g2;

