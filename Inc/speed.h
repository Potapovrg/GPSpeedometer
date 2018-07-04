#include "u8g2.h"  
#include "u8g2_arm.h"
#include <stdio.h>
#include "GPS_parser.h"

typedef struct {
	uint8_t pos1;
	uint8_t pos2;
}Display;


void speedo(void);
//void rallycomp(GPS_data *GPS, Race_data *Race, Display *Disp, uint8_t buttons_state);
void rallycomp(Position *Pos,GPS_data *GPS, Race_data *Race, Display *Disp, uint8_t buttons_state);
extern u8g2_t u8g2;

