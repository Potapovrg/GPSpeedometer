#include <stdio.h>

#define BACKLIGHT_FLAG 0
#define DIRECTION_FLAG 1

#ifndef RACE_STRUCT
#define RACE_STRUCT
typedef struct {
	float odo1;
	float odo2;
	float voltage;
	double total_distance_buf;
	int32_t total_distance;
	int8_t flags;
}Race_data;
#endif
