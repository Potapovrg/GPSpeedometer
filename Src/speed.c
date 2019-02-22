
#include "speed.h"



char buf[15];
//uint32_t a=0;

void speedo(GPS_data *GPS, Race_data *Race, Display *Disp) {         
  u8g2_SetFontDirection(&u8g2,0);
	u8g2_SetFont(&u8g2,u8g2_font_logisoso30_tr);
	sprintf(buf,"%3d",GPS->Speed.kelometers);
  u8g2_DrawStr(&u8g2,-5,30,buf);
	//u8g2_DrawStr(&u8g2,0,30,buf);
  u8g2_SetFont(&u8g2,u8g2_font_9x18B_tr);
  u8g2_DrawStr(&u8g2,53,30,"Km/h");
	u8g2_DrawStr(&u8g2,0,45,"A+");
	//Race->odo1=999;
	sprintf(buf,"% 4.1f",Race->odo1);
  u8g2_DrawStr(&u8g2,30,45,buf);
  u8g2_DrawStr(&u8g2,0,62,"ODO");
	//Race->total_distance=999999;
	sprintf(buf,"%6d",Race->total_distance);
	u8g2_DrawStr(&u8g2,30,62,buf);
  u8g2_DrawStr(&u8g2,92,14,"Bat.");
	sprintf(buf,"%.1f",Race->voltage);
  u8g2_DrawStr(&u8g2,92,30,buf);
  u8g2_DrawStr(&u8g2,92,45,"Time");
	sprintf(buf,"%02d%02d", GPS->Time.h+3,GPS->Time.m);
  u8g2_DrawStr(&u8g2,92,62,buf);
  u8g2_DrawBox(&u8g2,0,32,128,1);
  u8g2_DrawBox(&u8g2,90,0,1,64);  
}


uint8_t calculate_shift(float odo)
{
	if (odo < 10.0) return 38;
	else if ((odo >= 10)&(odo < 100)) return 19;
	else return 0;
}

void rallycomp(GPS_data *GPS, Race_data *Race, Display *Disp){
	uint8_t shift;
	
  u8g2_SetFontDirection(&u8g2,0);
  u8g2_SetFont(&u8g2,u8g2_font_logisoso30_tr);

	sprintf(buf,"%.2f",Race->odo1);
	//if (Race->odo1 < 10.0) shift = 19;
	//else shift = 0;
	shift = calculate_shift(Race->odo1);
	u8g2_DrawStr(&u8g2,24+shift,64,buf);
	if (Disp->pos2>6) Disp->pos2 = 0; 
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
			if (CHECK_FLAG(Race->flags,DIRECTION_FLAG)) u8g2_DrawStr(&u8g2,14,22,"B-");
			else u8g2_DrawStr(&u8g2,14,22,"B+");
			u8g2_SetFontDirection(&u8g2,0);
			u8g2_SetFont(&u8g2,u8g2_font_logisoso30_tr);
			sprintf(buf,"%.2f",Race->odo2);
			shift = calculate_shift(Race->odo2);
			u8g2_DrawStr(&u8g2,24+shift,30,buf);
			break;
		case 3:
			u8g2_SetFont(&u8g2,u8g2_font_9x18B_tr);
			u8g2_SetFontDirection(&u8g2,3);
			u8g2_DrawStr(&u8g2,14,28,"LOC");
			u8g2_SetFontDirection(&u8g2,0);
			switch (GPS->status) {
				case 'V':
				u8g2_SetFont(&u8g2,u8g2_font_logisoso30_tr);
				u8g2_DrawStr(&u8g2,24,30,"NO FIX");
				break;
				case 'A':
				u8g2_SetFont(&u8g2,u8g2_font_9x18B_tr);
				sprintf(buf,"%c%03d %02d.%04d",GPS->Latitude.sign, GPS->Latitude.degrees, GPS->Latitude.minutes, GPS->Latitude.tenth_minutes);
				u8g2_DrawStr(&u8g2,20,14,buf);
				sprintf(buf,"%c%03d %02d.%04d",GPS->Longitude.sign, GPS->Longitude.degrees, GPS->Longitude.minutes, GPS->Longitude.tenth_minutes);
				u8g2_DrawStr(&u8g2,20,28,buf);
				break;
			}
		break;
		case 4:
			u8g2_SetFont(&u8g2,u8g2_font_9x18B_tr);
			u8g2_SetFontDirection(&u8g2,3);
			u8g2_DrawStr(&u8g2,14,28,"VLT");
			u8g2_SetFontDirection(&u8g2,0);
			u8g2_SetFont(&u8g2,u8g2_font_logisoso30_tr);
			sprintf(buf,"%.1f",Race->voltage);
			u8g2_DrawStr(&u8g2,62,30,buf);
		break;
		case 5:
			u8g2_SetFont(&u8g2,u8g2_font_9x18B_tr);
			u8g2_SetFontDirection(&u8g2,3);
			u8g2_DrawStr(&u8g2,14,28,"COR");
			u8g2_SetFontDirection(&u8g2,0);
			u8g2_SetFont(&u8g2,u8g2_font_logisoso30_tr);
			switch (GPS->status) {
				case 'A':
					u8g2_DrawStr(&u8g2,24,30,"NO FIX");
				break;
				case 'V':
					u8g2_DrawDisc(&u8g2,118,6,6,U8G2_DRAW_ALL);
					u8g2_SetDrawColor(&u8g2,0);
					u8g2_DrawDisc(&u8g2,118,6,3,U8G2_DRAW_ALL);
					u8g2_SetDrawColor(&u8g2,1);
					sprintf(buf,"%03d",GPS->Coarse);
					u8g2_DrawStr(&u8g2,54,30,buf);
				break;
			}
		break;
		case 6:
			u8g2_SetFont(&u8g2,u8g2_font_9x18B_tr);
			u8g2_SetFontDirection(&u8g2,3);
			u8g2_DrawStr(&u8g2,14,28,"TOT");
			u8g2_SetFontDirection(&u8g2,0);
			u8g2_SetFont(&u8g2,u8g2_font_logisoso22_tr);
			sprintf(buf,"%6d",Race->total_distance);
			u8g2_DrawStr(&u8g2,38,26,buf);
			
		break;
	}
	
  u8g2_DrawBox(&u8g2,0,31,128,2);
  u8g2_DrawBox(&u8g2,18,0,2,64);
	u8g2_SetFont(&u8g2,u8g2_font_9x18B_tr);
	u8g2_SetFontDirection(&u8g2,3);
  if (CHECK_FLAG(Race->flags,DIRECTION_FLAG)) u8g2_DrawStr(&u8g2,14,54,"A-");
	else u8g2_DrawStr(&u8g2,14,54,"A+");
	}

	void gui(GPS_data *GPS, Race_data *Race, Display *Disp)
	{
		u8g2_ClearBuffer(&u8g2);
		switch (Disp->menu_page){
			case 0:
				rallycomp(GPS,Race,Disp);
			break;
			case 1:
				speedo(GPS,Race,Disp);
			break;
		}
		u8g2_SendBuffer(&u8g2);
	};
	