#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "string.h"
#include "race.h"


#define BUFFSIZE 300
#define TIME_FORMAT "%2d%2d%2d.%2d"
#define TIME_POSITION 1
#define STATUS_FORMAT "%c"
#define STATUS_POSITION 2
#define LATITUDE_FORMAT "%2d%2d.%5d"
#define POSITION_LATITUDE_FORMAT "%9d"
#define LATITUDE_POSITION 3
#define LATITUDE_SIGN_FORMAT "%c"
#define LATITUDE_SIGN_POSITION 4
#define LONGITUDE_FORMAT "%3d%2d.%5d"
#define POSITION_LONGITUDE_FORMAT "%9d"
#define LONGITUDE_POSITION 5
#define LONGITUDE_SIGN_FORMAT "%c"
#define LONGITUDE_SIGN_POSITION 6
#define DATE_FORMAT "%2d%2d%2d"
#define DATE_POSITION 9
#define COARSE_FORMAT "%3d"
#define COARSE_POSITION 1
#define SPEED_FORMAT "%3d.%2d"
#define SPEED_POSITION 7
#define QUALITY_POSITION 6
#define QUALITY_FORMAT "%1d"
#define HDOP_FORMAT "%2d"
#define HDOP_POSITION 8
#define HEIGHT_FORMAT "%4d"
#define HEIGHT_POSITION 9
#define HEIGHT_CORRECTION_FORMAT "%4d" //geoid separaration
#define HEIGHT_CORRECTION_POSITION 11
#define GMT_HOURS_FORMAT "%2d"
#define GMT_HOURS_POSITION 5
#define GMT_MINUTES_FORMAT "%2d"
#define GMT_MINUTES_POSITION 6

#ifndef GPS_DATA_STRUCT
#define GPS_DATA_STRUCT
typedef struct {
	char status;
	char RMC_status;
	char VTG_status;
	int Coarse;
	int height;
	int height_correction;
	int hdop;
	int quality;
	struct {
		int h;
		int m;
		int s;
		int ms;
	} Time;
	struct {
		int degrees;
		int minutes;
		int tenth_minutes;
		char sign;
	} Latitude;
	struct {
		int degrees;
		int minutes;
		int tenth_minutes;
		char sign;
	} Longitude;
	struct {
		int kelometers;
		int tenth_kelometers;
	} Speed;
	struct {
		int degrees;
		int tenth_degrees;
	} Course;
	struct {
		int day;
		int month;
		int year;
	}Date;
	struct {
	int32_t lat;
	int32_t lon;
	}Position;
	struct {
	int hours;
	int minutes;
	}GMT;
}GPS_data;

typedef struct {
	int32_t Lat;
	int32_t Lon;
}Position;
/*
typedef struct {
	int8_t start;
	int8_t end;
}NMEA_string;*/
#endif

void Parse_RMC(char *GPS_buffer, GPS_data *GPS, Position *Position);
void Parse_VTG(char *GPS_buffer, GPS_data *GPS);
void Parse_GGA(char *GPS_buffer, GPS_data *GPS);
void Parse_ZDA(char *GPS_buffer, GPS_data *GPS);
void Get_GPS_data(char *GPS_buffer, GPS_data *GPS, Position *Position);
