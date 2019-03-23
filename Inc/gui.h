#include "u8g2.h"  
#include "u8g2_arm.h"
#include <stdio.h>
#include "GPS_parser.h"
#include "race.h"
#include "flags.h"
#include "timer.h"

#ifndef DISPLAY_STRUCT
#define DISPLAY_STRUCT
typedef struct {
	int8_t pos1;
	int8_t pos2;
	int8_t menu_page;
}Display;
#endif

#define POS1 0
#define POS2 1
#define VAL_POS_Y 30
#define VAL_SHIFT 34
#define ANOT_POS_X 14
#define ANOT_2_POS_Y 22
#define ANOT_3_POS_Y 28
#define ANOT_SHIFT 33

void speedo(GPS_data *GPS, Race_data *Race, Display *Disp);
//void rallycomp(GPS_data *GPS, Race_data *Race, Display *Disp, uint8_t buttons_state);
void rallycomp(GPS_data *GPS, Race_data *Race, Display *Disp);
void time(GPS_data *GPS, Race_data *Race, Display *Disp);
void draw_position(int8_t pos, int8_t y_shift, GPS_data *GPS, Race_data *Race);
void draw_odo(int8_t odo,int8_t pos, int8_t y_shift,Race_data *Race);
void gui(GPS_data *GPS, Race_data *Race, Display *Disp);
void start_sreen(void);
uint8_t calculate_shift(float odo);
uint8_t calculate_shift_18(float odo);
extern u8g2_t u8g2;

