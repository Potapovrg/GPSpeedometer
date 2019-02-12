
#include "speed.h"


struct float_distance
{
	uint16_t kilometers;
	uint8_t ten_meteres;
};

char buf[15];
//uint32_t a=0;

void speedo(void) {         
  u8g2_SetFont(&u8g2,u8g2_font_logisoso30_tr);  
  //u8g2_DrawStr(&u8g2,-5,30,"  0");
	u8g2_DrawStr(&u8g2,0,30,buf);
  u8g2_SetFont(&u8g2,u8g2_font_9x18B_tr);
  u8g2_DrawStr(&u8g2,53,30,"Km/h");
  u8g2_DrawStr(&u8g2,0,45,"A+:40576.2");
  u8g2_DrawStr(&u8g2,0,62,"ODO:157308");
  u8g2_DrawStr(&u8g2,92,14,"Bat.");
  u8g2_DrawStr(&u8g2,92,30,"13.4");
  u8g2_DrawStr(&u8g2,92,45,"Rpm");
  u8g2_DrawStr(&u8g2,92,62,"0000");
  u8g2_DrawBox(&u8g2,0,32,128,1);
  u8g2_DrawBox(&u8g2,90,0,1,64);  
}

void distance_output(struct float_distance distance, int horisontal_position, int vertical_position)
{ 
	struct position 
	{
		uint8_t horisontal_position;
		uint8_t vertical_position;
	};
	
 if (distance.kilometers < 10) horisontal_position = horisontal_position + 2 * 19;
 else if (distance.kilometers < 100) horisontal_position = horisontal_position + 19;
 sprintf(buf, "%i\n", distance.ten_meteres);
 u8g2_DrawStr(&u8g2,horisontal_position,vertical_position,buf);
 
}


void rallycomp(Position *Pos, GPS_data *GPS, Race_data *Race, Display *Disp, uint8_t buttons_state){
	uint8_t shift;
	
  u8g2_SetFontDirection(&u8g2,0);
  u8g2_SetFont(&u8g2,u8g2_font_logisoso30_tr);

	sprintf(buf,"%.2f",Race->odo1);
	if (Race->odo1 < 10.0) shift = 19;
	else shift = 0;
	u8g2_DrawStr(&u8g2,43+shift,64,buf);
	if (Disp->pos2>4) Disp->pos2 = 0; 
	switch (Disp->pos2){
		case 0:
			u8g2_SetFont(&u8g2,u8g2_font_9x18B_tr);
			u8g2_SetFontDirection(&u8g2,3);
			u8g2_DrawStr(&u8g2,14,28,"SPD");
		
			u8g2_SetFontDirection(&u8g2,0);
			u8g2_SetFont(&u8g2,u8g2_font_logisoso30_tr);
		switch (GPS->status) {
		case 'V':
			u8g2_DrawStr(&u8g2,24,30,"NO FIX");
		break;
		case 'A':
			sprintf(buf,"%3d",GPS->Speed.kelometers);
			u8g2_DrawStr(&u8g2,71,30,buf);
		break;
		}
		break;
		case 1:
			u8g2_SetFont(&u8g2,u8g2_font_9x18B_tr);
			u8g2_SetFontDirection(&u8g2,3);
			u8g2_DrawStr(&u8g2,14,24,"TM");
		
			u8g2_SetFontDirection(&u8g2,0);
			u8g2_SetFont(&u8g2,u8g2_font_logisoso22_tr);
			sprintf(buf,"%02d:%02d:%02d", GPS->Time.h+3,GPS->Time.m,GPS->Time.s);
			u8g2_DrawStr(&u8g2,20,27,buf);
		break;
		case 2:
			u8g2_SetFont(&u8g2,u8g2_font_9x18B_tr);
			u8g2_SetFontDirection(&u8g2,3);
			u8g2_DrawStr(&u8g2,14,28,"OD2");
			u8g2_SetFontDirection(&u8g2,0);
			u8g2_SetFont(&u8g2,u8g2_font_logisoso30_tr);
			sprintf(buf,"%.2f",Race->odo2);
			if (Race->odo2 < 10.0) shift = 19;
			else shift = 0;
			u8g2_DrawStr(&u8g2,43+shift,30,buf);
			break;
		case 3:
			u8g2_SetFont(&u8g2,u8g2_font_9x18B_tr);
			u8g2_SetFontDirection(&u8g2,3);
			u8g2_DrawStr(&u8g2,14,28,"LOC");
			u8g2_SetFontDirection(&u8g2,0);
			u8g2_SetFont(&u8g2,u8g2_font_9x18B_tr);
			//sprintf(buf,"%010d",Pos->Lat);
			sprintf(buf,"%c%03d %02d.%04d",GPS->Latitude.sign, GPS->Latitude.degrees, GPS->Latitude.minutes, GPS->Latitude.tenth_minutes);
			u8g2_DrawStr(&u8g2,20,14,buf);
			//sprintf(buf,"%010d",Pos->Lon);
			sprintf(buf,"%c%03d %02d.%04d",GPS->Longitude.sign, GPS->Longitude.degrees, GPS->Longitude.minutes, GPS->Longitude.tenth_minutes);
			u8g2_DrawStr(&u8g2,20,28,buf);
		break;
		case 4:
			u8g2_SetFont(&u8g2,u8g2_font_9x18B_tr);
			u8g2_SetFontDirection(&u8g2,3);
			u8g2_DrawStr(&u8g2,14,28,"VLT");
			u8g2_SetFontDirection(&u8g2,0);
			u8g2_SetFont(&u8g2,u8g2_font_logisoso30_tr);
			sprintf(buf,"%4d",Race->voltage);
			u8g2_DrawStr(&u8g2,43,30,buf);
		break;
	}
	
  u8g2_DrawBox(&u8g2,0,31,128,2);
  u8g2_DrawBox(&u8g2,18,0,2,64);
	/*u8g2_DrawStr(&u8g2,30,46,"Float");
	sprintf(buf,"%02.2f",odo1);
	u8g2_DrawStr(&u8g2,38,60,buf);
	u8g2_DrawStr(&u8g2,90,46,"Long");
	sprintf(buf,"%05d",odo2);
	u8g2_DrawStr(&u8g2,80,60,buf);*/
	
	u8g2_SetFont(&u8g2,u8g2_font_9x18B_tr);
	u8g2_SetFontDirection(&u8g2,3);
  //u8g2_DrawStr(&u8g2,18,28,"SPD");
	//u8g2_DrawStr(&u8g2,14,24,"TM");
  u8g2_DrawStr(&u8g2,14,60,"OD1");
	}
	
		//speedo();
		/*u8g2_ClearBuffer(&u8g2);
		u8g2_SetFont(&u8g2,u8g2_font_9x18B_tr);
		sprintf(Screen_buffer, "Time:%02d:%02d:%02d", GPS.Time.h+3,GPS.Time.m,GPS.Time.s);
		u8g2_DrawStr(&u8g2,0,10,Screen_buffer);
		sprintf(Screen_buffer, "%02d.%02d.%4d", GPS.Date.day,GPS.Date.month,GPS.Date.year+2000);
		u8g2_DrawStr(&u8g2,0,20+OFFSET,Screen_buffer);
		sprintf(Screen_buffer, "%02d %02d.%03d %c", GPS.Latitude.degrees,GPS.Latitude.minutes,GPS.Latitude.tenth_minutes,GPS.Latitude.sign);
		u8g2_DrawStr(&u8g2,0,30+2*OFFSET,Screen_buffer);
		sprintf(Screen_buffer, "%2d %02d.%03d %c", GPS.Longitude.degrees,GPS.Longitude.minutes,GPS.Longitude.tenth_minutes,GPS.Longitude.sign);
		u8g2_DrawStr(&u8g2,0,40+3*OFFSET,Screen_buffer);
		sprintf(Screen_buffer, "Status:%c", GPS.status);
		u8g2_DrawStr(&u8g2,0,50+4*OFFSET,Screen_buffer);
		//sprintf(Screen_buffer, "Speed:%3d.%2d",GPS.Speed.kelometers,GPS.Speed.tenth_kelometers);
		sprintf(Screen_buffer, "DST:%1.3f",distance);
		u8g2_DrawStr(&u8g2,0,60+5*OFFSET,Screen_buffer);*/