//#include <stdio.h>
#include "cmsis_os.h"

#define BACKLIGHT_FLAG 0
#define DIRECTION_FLAG 1
#define TIMER_FLAG 2

#ifndef RACE_STRUCT
#define RACE_STRUCT
typedef struct {
	float odo1;
	float odo2;
	float voltage;
	double total_distance_buf;
	int32_t total_distance;
	int8_t flags;
	
	struct {
	int8_t h;
	int8_t m;
	}GMT;
	
	struct {
	int8_t h;
	int8_t m;
	int8_t s;
	}Timer_start;
	
	struct {
	int8_t h;
	int8_t m;
	}Timer_setup;
	
	struct {
	int8_t h;
	int8_t m;
	int8_t s;
	}Timer;
}Race_data;
#endif
