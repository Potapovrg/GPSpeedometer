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

#define EEPROM_RACE_SIZE 16
#define EEPROM_UI_SIZE 8

typedef struct {
  float odo1;
	float odo2;
	int32_t total_distance;
	int8_t disp_pos1;
	int8_t disp_pos2;
	int8_t race_flags;
	int8_t menu_page;
}eeprom_struct;

typedef struct {
  float odo1;
	float odo2;
	uint32_t total_distance;
	uint32_t crc;
	}eeprom_race_struct;

	typedef struct {
  int8_t disp_pos1;
	int8_t disp_pos2;
	int8_t race_flags;
	int8_t menu_page;
	uint32_t crc;
	}eeprom_ui_struct;

	
extern eeprom_struct eeprom;
#endif



void eeprom_read(eeprom_struct *eeprom, Display *Disp, Race_data *Race);
void eeprom_write(eeprom_struct *eeprom, uint8_t *flag);
void eeprom_collect(eeprom_struct *eeprom, Display *Disp, Race_data *Race, uint8_t *flag);
	
void eeprom_read_2(eeprom_race_struct *eeprom_race, eeprom_ui_struct *eeprom_ui,Race_data *Race,Display *Disp);
void eeprom_race_collect(eeprom_race_struct *eeprom_race,Race_data *Race, uint8_t *flag);
void eeprom_ui_collect(eeprom_ui_struct *eeprom_ui,Race_data *Race,Display *Disp);
void eeprom_race_write(eeprom_race_struct *eeprom_race, uint8_t *flag);
void eeprom_ui_write(eeprom_ui_struct *eeprom_ui);
