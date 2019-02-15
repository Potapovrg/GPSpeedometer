#include "GPS_parser.h"

int coma;
int eol;
int position;
int hour;

int token[50];
int *token_length = token;


//$GNRMC,073810.00,A,5140.89642,N,03910.49043,E,0.260,,270218,,,A*69 NMEA string example
//$GNVTG,,,,,,,,,N*2E

void Parce_NMEA_string(char *GPS_buffer, GPS_data *GPS, Position *Position)
{
	int32_t degrees, minutes, part_minutes; 
	//int32_t first_part, second_part;
	char *token1 = GPS_buffer;
	while (*GPS_buffer != '\0')
	{
		position++;
		switch (*GPS_buffer){
			case ',':
				*(token_length+coma)=position;
				coma++;
			break;
			case '*':
				eol++;
			break;
			default:
				break;
		}
		GPS_buffer++;
	}
	GPS_buffer = token1;
	coma = 0;
	eol = 0;
	position = 0;
	
	/*sscanf(GPS_buffer, "$GNRMC,%2d%2d%2d.%2d,%c,%2d%2d.%5d,%c,%3d%2d.%5d,%c,%3d.%3d,%3d.%3d,%2d%2d%2d",&GPS.Time.h,&GPS.Time.m,&GPS.Time.s,&GPS.Time.ms,&GPS.status,
			&GPS->Latitude.degrees,&GPS->Latitude.minutes,&GPS->Latitude.tenth_minutes,&GPS->Latitude.sign,&GPS->Longitude.degrees,&GPS->Longitude.minutes,&GPS->Longitude.tenth_minutes,
			&GPS->Longitude.sign,&GPS->Speed.knots,&GPS->Speed.tenth_knots,&GPS->Course.degrees,&GPS->Course.tenth_degrees,&GPS->Date.day,&GPS->Date.month,&GPS->Date.year);*/
	

	//if (strncmp(GPS_buffer, "$GNRMC", 6)==0)
	if (strncmp(GPS_buffer+3, "RMC", 3)==0)
	{
		sscanf(GPS_buffer+*(token_length+TIME_POSITION),TIME_FORMAT,&GPS->Time.h,&GPS->Time.m,&GPS->Time.s,&GPS->Time.ms);
		sscanf(GPS_buffer+*(token_length+STATUS_POSITION),STATUS_FORMAT,&GPS->status);
		sscanf(GPS_buffer+*(token_length+LATITUDE_POSITION),LATITUDE_FORMAT,&GPS->Latitude.degrees,&GPS->Latitude.minutes,&GPS->Latitude.tenth_minutes);
		
		sscanf(GPS_buffer+*(token_length+LATITUDE_SIGN_POSITION),LATITUDE_SIGN_FORMAT,&GPS->Latitude.sign);
		sscanf(GPS_buffer+*(token_length+LONGITUDE_POSITION),LONGITUDE_FORMAT,&GPS->Longitude.degrees,&GPS->Longitude.minutes,&GPS->Longitude.tenth_minutes);
		
		sscanf(GPS_buffer+*(token_length+LONGITUDE_SIGN_POSITION),LONGITUDE_SIGN_FORMAT,&GPS->Longitude.sign);
		sscanf(GPS_buffer+*(token_length+DATE_POSITION),DATE_FORMAT,&GPS->Date.day,&GPS->Date.month,&GPS->Date.year);
		
		if (GPS->status != 'V')
			{/*
				sscanf(GPS_buffer+*(token_length+LATITUDE_POSITION),"%5d.%5d",&first_part,&second_part);
				Position->Lat = first_part*100000+second_part;
				sscanf(GPS_buffer+*(token_length+LONGITUDE_POSITION),"%5d.%5d",&first_part,&second_part);
				Position->Lon = first_part*100000+second_part;	*/

				sscanf(GPS_buffer+*(token_length+LATITUDE_POSITION),"%2d%2d.%5d",&degrees,&minutes,&part_minutes);
				Position->Lat = degrees*10000000+(minutes*1000000)/6+(part_minutes*10)/6;
				sscanf(GPS_buffer+*(token_length+LONGITUDE_POSITION),"%3d%2d.%5d",&degrees,&minutes,&part_minutes);
				Position->Lon = degrees*10000000+(minutes*1000000)/6+(part_minutes*10)/6;	
			}
		
	}
		else if (strncmp(GPS_buffer+3, "VTG", 3)==0)
			{
				sscanf(GPS_buffer+*(token_length+COARSE_POSITION),COARSE_FORMAT,&GPS->Coarse);	
				sscanf(GPS_buffer+*(token_length+SPEED_POSITION),SPEED_FORMAT,&GPS->Speed.kelometers,&GPS->Speed.tenth_kelometers);	
			}
}