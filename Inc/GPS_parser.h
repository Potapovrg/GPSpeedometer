#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define BUFFSIZE 200
#define TIME_FORMAT "%2d%2d%2d.%2d"
#define TIME_POSITION 0
#define STATUS_FORMAT "%c"
#define STATUS_POSITION 1
#define LATITUDE_FORMAT "%2d%2d.%5d"
#define POSITION_LATITUDE_FORMAT "%9d"
#define LATITUDE_POSITION 2
#define LATITUDE_SIGN_FORMAT "%c"
#define LATITUDE_SIGN_POSITION 3
#define LONGITUDE_FORMAT "%3d%2d.%5d"
#define POSITION_LONGITUDE_FORMAT "%9d"
#define LONGITUDE_POSITION 4
#define LONGITUDE_SIGN_FORMAT "%c"
#define LONGITUDE_SIGN_POSITION 5
#define DATE_FORMAT "%2d%2d%2d"
#define DATE_POSITION 8
#define SPEED_FORMAT "%3d.%2d"
#define SPEED_POSITION 6
/*#define _FORMAT
#define _POSITION
#define _FORMAT
#define _POSITION*/

			
#ifndef GPS_DATA_STRUCT
#define GPS_DATA_STRUCT
typedef struct {
	char status;
	char RMC_status;
	char VTG_status;
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
	
}GPS_data;

typedef struct {
	int32_t Lat;
	int32_t Lon;
}Position;

typedef struct {
	float odo1;
	float odo2;
	uint32_t voltage;
}Race_data;

#endif

//typedef enum {GNRMC,GNVTG} string_type;

void Parce_NMEA_string(char *GPS_buffer, GPS_data *GPS, Position *Position);
