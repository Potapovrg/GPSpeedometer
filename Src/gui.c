
#include "gui.h"
int8_t x=43;
int8_t y=15;

char buf[15];
//uint32_t a=0;

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
	
void rallycomp(GPS_data *GPS, Race_data *Race, Display *Disp){
	if (Disp->pos1>3){
		if (Disp->pos2!=0) Disp->pos1 = 0;
		else Disp->pos1 = 1;
	};
	if (Disp->pos2>3){
		if (Disp->pos1!=0) Disp->pos2 = 0;
		else Disp->pos2 = 1;
	};
	u8g2_DrawBox(&u8g2,0,31,128,2);
  u8g2_DrawBox(&u8g2,18,0,2,64);
	draw_position(Disp->pos1,POS1,GPS,Race);
	draw_position(Disp->pos2,POS2,GPS,Race);	
}

void speedo(GPS_data *GPS, Race_data *Race, Display *Disp) {         
  u8g2_SetFontDirection(&u8g2,0);
	u8g2_SetFont(&u8g2,u8g2_font_logisoso30_tr);
	if (GPS->status=='V')GPS->Speed.kelometers = 0;
	sprintf(buf,"%3d",GPS->Speed.kelometers);
  u8g2_DrawStr(&u8g2,0,30,buf);
  u8g2_SetFont(&u8g2,u8g2_font_9x18B_tr);
  u8g2_DrawStr(&u8g2,60,15,"km");
	u8g2_DrawStr(&u8g2,60,30,"h");
	if (CHECK_FLAG(Race->flags,DIRECTION_FLAG)) u8g2_DrawStr(&u8g2,0,45,"A-");
	else u8g2_DrawStr(&u8g2,0,45,"A+");
	//u8g2_DrawStr(&u8g2,0,45,"A+");
	sprintf(buf,"% 4.1f",Race->odo1);
  u8g2_DrawStr(&u8g2,16+calculate_shift_18(Race->odo1),45,buf);
  u8g2_DrawStr(&u8g2,0,62,"OD");
	sprintf(buf,"%6d",Race->total_distance);
	u8g2_DrawStr(&u8g2,25,62,buf);
  //u8g2_DrawStr(&u8g2,87,14,"Bat.");
	sprintf(buf,"%.1fV",Race->voltage);
  u8g2_DrawStr(&u8g2,83,14,buf);
  //u8g2_DrawStr(&u8g2,87,45,"Time");
	sprintf(buf,"%02d:%02d", GPS->Time.h+3,GPS->Time.m);
  u8g2_DrawStr(&u8g2,82,30,buf);
	sprintf(buf,"%4dm", GPS->height);
	u8g2_DrawStr(&u8g2,82,45,buf);
	sprintf(buf,"Q%1d", GPS->quality);
	u8g2_DrawStr(&u8g2,82,62,buf);
	sprintf(buf,"H%02d", GPS->hdop);
	u8g2_DrawStr(&u8g2,100,62,buf);
  u8g2_DrawBox(&u8g2,0,32,128,1);
  u8g2_DrawBox(&u8g2,80,0,1,64);  
}

uint8_t calculate_shift_18(float odo)
{
	if (odo < 10.0) return 27;
	else if ((odo >= 10)&(odo < 100)) return 18;
	else if ((odo >= 100)&(odo < 1000)) return 9;
	else return 0;
}

uint8_t calculate_shift(float odo)
{
	if (odo < 10.0) return 38;
	else if ((odo >= 10)&(odo < 100)) return 19;
	else return 0;
}

void draw_position(int8_t pos, int8_t y_shift, GPS_data *GPS, Race_data *Race)
{
	switch (pos){
		default:
			draw_odo(1,pos,y_shift,Race);
		break;
		case 1:
			draw_odo(2,pos,y_shift,Race);
		break;
		case 2:
			u8g2_SetFont(&u8g2,u8g2_font_9x18B_tr);
			u8g2_SetFontDirection(&u8g2,3);
			u8g2_DrawStr(&u8g2,ANOT_POS_X,ANOT_3_POS_Y+ANOT_SHIFT*y_shift,"COR");
			u8g2_SetFontDirection(&u8g2,0);
			u8g2_SetFont(&u8g2,u8g2_font_logisoso30_tr);
			switch (GPS->status) {
				case 'V':
					u8g2_DrawStr(&u8g2,24,VAL_POS_Y+VAL_SHIFT*y_shift,"NO FIX");
				break;
				case 'A':
					u8g2_DrawDisc(&u8g2,120,6+VAL_SHIFT*y_shift,6,U8G2_DRAW_ALL);
					u8g2_SetDrawColor(&u8g2,0);
					u8g2_DrawDisc(&u8g2,120,6+VAL_SHIFT*y_shift,3,U8G2_DRAW_ALL);
					u8g2_SetDrawColor(&u8g2,1);
					sprintf(buf,"%03d",GPS->Coarse);
					u8g2_DrawStr(&u8g2,54,VAL_POS_Y+VAL_SHIFT*y_shift,buf);
				break;
			}
		break;
		case 3:
				u8g2_SetFont(&u8g2,u8g2_font_9x18B_tr);
				u8g2_SetFontDirection(&u8g2,3);
				u8g2_DrawStr(&u8g2,ANOT_POS_X,ANOT_3_POS_Y+ANOT_SHIFT*y_shift,"SPD");
				u8g2_SetFontDirection(&u8g2,0);
				u8g2_SetFont(&u8g2,u8g2_font_logisoso30_tr);
				switch (GPS->status) {
					case 'V':
						u8g2_DrawStr(&u8g2,24,VAL_POS_Y+VAL_SHIFT*y_shift,"NO FIX");
					break;
					case 'A':
						sprintf(buf,"%3d",GPS->Speed.kelometers);
						u8g2_DrawStr(&u8g2,54,VAL_POS_Y+VAL_SHIFT*y_shift,buf);
						u8g2_SetFont(&u8g2,u8g2_font_9x18B_tr);
						u8g2_DrawStr(&u8g2,110,15+VAL_SHIFT*y_shift,"km");
						u8g2_DrawStr(&u8g2,110,30+VAL_SHIFT*y_shift,"h");
					break;
				}
			break;		
	}
}

void draw_odo(int8_t odo,int8_t pos,int8_t y_shift,Race_data *Race)
{
	char *a  = "A";
	char *b = "B";
	char *forward = "+";
	char *reverse = "-";
	
	char *odo_symbol;
	char *odo_dir;
	float *odo_val;
	
	if (odo == 1)
	{
		odo_val=&Race->odo1;
		odo_symbol=a;			
	}
	else if (odo == 2)
	{
		odo_val=&Race->odo2;
		odo_symbol=b;
	}
	
	u8g2_SetFontDirection(&u8g2,0);
	u8g2_SetFont(&u8g2,u8g2_font_logisoso30_tr);
	if (*odo_val<1000) sprintf(buf,"%.2f",*odo_val);
	else sprintf(buf,"%.1f",*odo_val);
	u8g2_DrawStr(&u8g2,24+calculate_shift(*odo_val),VAL_POS_Y+VAL_SHIFT*y_shift,buf);
	
	if (CHECK_FLAG(Race->flags,DIRECTION_FLAG)) odo_dir = reverse;
	else odo_dir = forward;
	sprintf(buf,"%s%s",odo_dir,odo_symbol);
	u8g2_SetFont(&u8g2,u8g2_font_9x18B_tr);
	u8g2_SetFontDirection(&u8g2,3);
	u8g2_DrawStr(&u8g2,ANOT_POS_X,ANOT_2_POS_Y+ANOT_SHIFT*y_shift,buf);
}

void start_sreen(void){
	u8g2_InitDisplay(&u8g2);
	u8g2_SetPowerSave(&u8g2, 0);
	u8g2_ClearBuffer(&u8g2);
	u8g2_SetFontDirection(&u8g2,0);
	u8g2_SetFont(&u8g2,u8g2_font_logisoso30_tr);
	u8g2_DrawStr(&u8g2,-1,40,"GPS");
	u8g2_DrawStr(&u8g2,53,54,"peed");
	u8g2_SendBuffer(&u8g2);
	}
/*
void rallycomp(GPS_data *GPS, Race_data *Race, Display *Disp){
	//uint8_t shift;
	
  u8g2_SetFontDirection(&u8g2,0);
  u8g2_SetFont(&u8g2,u8g2_font_logisoso30_tr);
	if (Race->odo1<1000) sprintf(buf,"%.2f",Race->odo1);
	else sprintf(buf,"%.1f",Race->odo1);
	//if (Race->odo1 < 10.0) shift = 19;
	//else shift = 0;
	//shift = calculate_shift(Race->odo1);
	u8g2_DrawStr(&u8g2,24+calculate_shift(Race->odo1),64,buf);
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
			if (Race->odo2<1000) sprintf(buf,"%.2f",Race->odo2);
			else sprintf(buf,"%.1f",Race->odo2);
			//shift = calculate_shift(Race->odo2);
			u8g2_DrawStr(&u8g2,24+calculate_shift(Race->odo2),30,buf);
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
				case 'V':
					u8g2_DrawStr(&u8g2,24,30,"NO FIX");
				break;
				case 'A':
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
	}*/

