
#include "speed.h"


struct float_distance
{
	uint16_t kilometers;
	uint8_t ten_meteres;
};

char buf[15];
uint32_t a=0;

void speedo(void) {         
  u8g2_SetFont(&u8g2,u8g2_font_logisoso30_tr);  
  //u8g2_DrawStr(&u8g2,-5,30,"  0");
	sprintf(buf, "%i\n", a);
	u8g2_DrawStr(&u8g2,0,30,buf);
	a++;
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


void rallycomp(float distance, GPS_data *GPS){
  u8g2_SetFontDirection(&u8g2,0);
  u8g2_SetFont(&u8g2,u8g2_font_logisoso30_tr);
	switch (GPS->status) {
		case 'V':
			u8g2_DrawStr(&u8g2,24,30,"NO FIX");
		break;
		case 'A':
			sprintf(buf,"%03d",GPS->Speed.kelometers);
			u8g2_DrawStr(&u8g2,71,30,buf);
		break;
	}
	sprintf(buf,"%02.2f",distance);
	u8g2_DrawStr(&u8g2,60,64,buf);
  u8g2_DrawBox(&u8g2,0,31,128,2);
  u8g2_DrawBox(&u8g2,23,0,2,64);
  u8g2_SetFontDirection(&u8g2,3);
  u8g2_SetFont(&u8g2,u8g2_font_9x18B_tr);
  u8g2_DrawStr(&u8g2,18,28,"SPD");
  u8g2_DrawStr(&u8g2,18,60,"INT");
	}
	
