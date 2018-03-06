#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define BUFFSIZE 200
#define TIME_FORMAT "%2d%2d%2d.%2d"
#define TIME_POSITION 0
#define STATUS_FORMAT "%c"
#define STATUS_POSITION 1
#define LATITUDE_FORMAT "%2d%2d.%5d"
#define LATITUDE_POSITION 2
#define LATITUDE_SIGN_FORMAT "%c"
#define LATITUDE_SIGN_POSITION 3
#define LONGITUDE_FORMAT "%3d%2d.%5d"
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

	/*sscanf(GPS_buffer, "$GNRMC,%2d%2d%2d.%2d,%c,%2d%2d.%5d,%c,%3d%2d.%5d,%c,%3d.%3d,%3d.%3d,%2d%2d%2d",&GPS.Time.h,&GPS.Time.m,&GPS.Time.s,&GPS.Time.ms,&GPS.status,
			&GPS.Latitude.degrees,&GPS.Latitude.minutes,&GPS.Latitude.tenth_minutes,&GPS.Latitude.sign,&GPS.Longitude.degrees,&GPS.Longitude.minutes,&GPS.Longitude.tenth_minutes,
			&GPS.Longitude.sign,&GPS.Speed.knots,&GPS.Speed.tenth_knots,&GPS.Course.degrees,&GPS.Course.tenth_degrees,&GPS.Date.day,&GPS.Date.month,&GPS.Date.year);*/

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
	
}GPS_data;


//typedef enum {GNRMC,GNVTG} string_type;

void Parce_NMEA_string(char *GPS_buffer, GPS_data *GPS);
