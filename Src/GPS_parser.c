#include "GPS_parser.h"

int coma;
int eol;
int string;
int position;
int hour;

int token[50];
int nmea_string_start[10];
int nmea_string_end[10];
int *token_length = token;
int *str_start = nmea_string_start;
int *str_end = nmea_string_end;
NMEA_string RMC_string;

//$GNRMC,073810.00,A,5140.89642,N,03910.49043,E,0.260,,270218,,,A*69 NMEA string example
//$GNVTG,,,,,,,,,N*2E

void Get_GPS_data(char *GPS_buffer, GPS_data *GPS, Position *Position)
{
Parse_RMC(GPS_buffer,GPS,Position);
Parse_VTG(GPS_buffer,GPS);
Parse_GGA(GPS_buffer,GPS);
}

void Tokenize(char *GPS_buffer)
{
	char *token1 = GPS_buffer;
 
	while (*GPS_buffer!='*')
	{
		switch (*GPS_buffer){
			case ',':
				coma++;
				*(token_length+coma)= position+1;
			break;
			case '$':
				*(str_start+string)= position;
				string++;
			break;
			case '*':
				*(str_end+eol)= position;
				eol++;
			break;
			default:
				break;
		}
		position++;
		GPS_buffer++;
	}
	GPS_buffer = token1;
	coma = 0;
	eol = 0;
	position = 0;
};

void Parse_RMC(char *GPS_buffer, GPS_data *GPS, Position *Position)
{
	char *istr;
	int32_t degrees, minutes, part_minutes;
	
	istr = strstr (GPS_buffer,"RMC");
	if ((istr!=NULL)&(strstr(istr,"*")!=NULL))
	{
		Tokenize(istr);
		sscanf(istr+*(token_length+TIME_POSITION),TIME_FORMAT,&GPS->Time.h,&GPS->Time.m,&GPS->Time.s,&GPS->Time.ms);
		sscanf(istr+*(token_length+STATUS_POSITION),STATUS_FORMAT,&GPS->status);
		sscanf(istr+*(token_length+LATITUDE_POSITION),LATITUDE_FORMAT,&GPS->Latitude.degrees,&GPS->Latitude.minutes,&GPS->Latitude.tenth_minutes);
		sscanf(istr+*(token_length+LATITUDE_SIGN_POSITION),LATITUDE_SIGN_FORMAT,&GPS->Latitude.sign);
		sscanf(istr+*(token_length+LONGITUDE_POSITION),LONGITUDE_FORMAT,&GPS->Longitude.degrees,&GPS->Longitude.minutes,&GPS->Longitude.tenth_minutes);
		sscanf(istr+*(token_length+LONGITUDE_SIGN_POSITION),LONGITUDE_SIGN_FORMAT,&GPS->Longitude.sign);
		sscanf(istr+*(token_length+DATE_POSITION),DATE_FORMAT,&GPS->Date.day,&GPS->Date.month,&GPS->Date.year);
			
			if (GPS->status != 'V')
				{
					sscanf(istr+*(token_length+LATITUDE_POSITION),"%2d%2d.%5d",&degrees,&minutes,&part_minutes);
					Position->Lat = degrees*10000000+(minutes*1000000)/6+(part_minutes*10)/6;
					sscanf(istr+*(token_length+LONGITUDE_POSITION),"%3d%2d.%5d",&degrees,&minutes,&part_minutes);
					Position->Lon = degrees*10000000+(minutes*1000000)/6+(part_minutes*10)/6;	
				}
		
	};
}

void Parse_VTG(char *GPS_buffer, GPS_data *GPS)
{
	char *istr;
	istr = strstr (GPS_buffer,"VTG");
	if (istr!=NULL)
	{
		Tokenize(istr);
		sscanf(istr+*(token_length+COARSE_POSITION),COARSE_FORMAT,&GPS->Coarse);	
		sscanf(istr+*(token_length+SPEED_POSITION),SPEED_FORMAT,&GPS->Speed.kelometers,&GPS->Speed.tenth_kelometers);			
	};
}

void Parse_GGA(char *GPS_buffer, GPS_data *GPS)
{
	char *istr;
	istr = strstr (GPS_buffer,"GGA");
	if (istr!=NULL)
	{
		Tokenize(istr);
		sscanf(istr+*(token_length+QUALITY_POSITION),QUALITY_FORMAT,&GPS->quality);	
		sscanf(istr+*(token_length+HDOP_POSITION),HDOP_FORMAT,&GPS->hdop);
		sscanf(istr+*(token_length+HEIGHT_POSITION),HEIGHT_FORMAT,&GPS->height);
	}
	
}
