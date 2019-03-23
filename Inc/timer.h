#include "race.h"
#include "GPS_parser.h"
#include "flags.h"

#ifndef TIMER_DATA_STRUCT
#define TIMER_DATA_STRUCT
typedef struct {
int8_t current_day;
int8_t current_h;
int8_t current_m;
}CurrentDateTime;
#endif

void calculate_timer(GPS_data *GPS,Race_data *Race);
void calculate_date_n_time(GPS_data *GPS,Race_data *Race,CurrentDateTime *Time);