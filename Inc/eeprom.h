#include <stdint.h>
#include "gui.h"
#include "GPS_parser.h"
#include "i2c.h"
#include "crc.h"

#ifndef EEPROM_STRUCT
#define EEPROM_STRUCT

#define I2C1_DEVICE_ADDRESS      0x50   /* A0 = A1 = A2 = 0 */ 
#define EEPROM_1_ADDRESS 0x00
#define EEPROM_CRC_ADDRESS 0x10

#define EEPROM_RACE_ADDRESS 0x00
#define EEPROM_UI_ADDRESS 0x10
#define EEPROM_TIME_ADDRESS 0x20

#define EEPROM_RACE_SIZE 16
#define EEPROM_UI_SIZE 8
#define EEPROM_TIME_SIZE 12

typedef struct {
	struct {
  float odo1;
	float odo2;
	uint32_t total_distance;
	uint32_t crc;
	}Race;
	
	struct {
  int8_t disp_pos1;
	int8_t disp_pos2;
	int8_t race_flags;
	int8_t menu_page;
	uint32_t crc;
	}UI;
	
	struct {
  int8_t timer_start_h;
	int8_t timer_start_m;
	int8_t timer_start_s;
	int8_t timer_h;
	int8_t timer_m;
	int8_t GMT_h;
	int8_t GMT_m;
	int8_t dummy; //have to add this, because struct be alicout to 4
	uint32_t crc;
	}Time;
	
	uint8_t flag;
}eeprom_struct;
	
extern eeprom_struct eeprom;
#endif



void eeprom_read(eeprom_struct *eeprom,Race_data *Race,Display *Disp);
void eeprom_race_collect(eeprom_struct *eeprom,Race_data *Race);
void eeprom_ui_collect(eeprom_struct *eeprom,Race_data *Race,Display *Disp);
void eeprom_time_collect(eeprom_struct *eeprom,Race_data *Race,Display *Disp);
void eeprom_race_write(eeprom_struct *eeprom);
void eeprom_ui_write(eeprom_struct *eeprom);
void eeprom_time_write(eeprom_struct *eeprom);
