#include "u8g2.h"  
#include "u8g2_arm.h"
#include <stdio.h>
#include "GPS_parser.h"

#ifndef DISPLAY_STRUCT
#define DISPLAY_STRUCT
typedef struct {
	int8_t pos1;
	int8_t pos2;
}Display;
#endif

void speedo(void);
//void rallycomp(GPS_data *GPS, Race_data *Race, Display *Disp, uint8_t buttons_state);
void rallycomp(Position *Pos,GPS_data *GPS, Race_data *Race, Display *Disp, uint8_t buttons_state);
extern u8g2_t u8g2;

