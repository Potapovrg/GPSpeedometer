#include "timer.h"
void calculate_timer(GPS_data *GPS,Race_data *Race)
{
	Race->Timer.h = 0;
	Race->Timer.m = 0;
	Race->Timer.s = 0;
	
	Race->Timer.s = Race->Timer_start.s - GPS->Time.s;
	if (Race->Timer.s<0){
			Race->Timer.s = 60 + Race->Timer.s;
			Race->Timer.m = -1;
		}
	else if (Race->Timer.s >= 60){
			Race->Timer.s = Race->Timer.s - 60;
			Race->Timer.m = 1;
		}
	Race->Timer.m += Race->Timer_start.m + Race->Timer_setup.m - GPS->Time.m;
	if (Race->Timer.m<0){
			Race->Timer.m = 60 + Race->Timer.m;
			Race->Timer.h = -1;
		}
	else if (Race->Timer.m >= 60){
			Race->Timer.m = Race->Timer.m - 60;
			Race->Timer.h = 1;
		}
	
	Race->Timer.h += Race->Timer_start.h + Race->Timer_setup.h - GPS->Time.h;
	if (Race->Timer.h < 0){
		Race->Timer.h = 0;
		CLEAR_FLAG(Race->flags,TIMER_FLAG);
	}
}

void calculate_date_n_time(GPS_data *GPS,Race_data *Race,CurrentDateTime *Time)
{
	Time->current_h = 0;
	Time->current_m = 0;
	Time->current_day = 0;
	
	Time->current_m = GPS->Time.m + Race->GMT.m;
	if (Time->current_m < 0){
		Time->current_m = 60 + Time->current_m;
		Time->current_h = -1;
	}
	else if (Time->current_m >= 60){
		Time->current_m = Time->current_m - 60;
		Time->current_h = 1;
	}
	
	Time->current_h += GPS->Time.h + Race->GMT.h;
	if (Time->current_h < 0){
		Time->current_h = 24 + Time->current_h;
		Time->current_day = -1;
	}
	else if (Time->current_h >= 24){
		Time->current_h = Time->current_h - 24;
		Time->current_day = 1;
	}
	Time->current_day += GPS->Date.day;
}