#include "eeprom.h"

int eeprom_test; 
	
void eeprom_read(eeprom_struct *eeprom, Display *Disp, Race_data *Race)
{
	HAL_I2C_Mem_Read(&hi2c1, (uint16_t) I2C1_DEVICE_ADDRESS<<1, EEPROM_1_ADDRESS, 1, (uint8_t*)eeprom,8,5);
	Race->odo1 = eeprom->odo1;
	Race->odo2 = eeprom->odo2;
	eeprom_test = sizeof(eeprom);
}

void eeprom_write(eeprom_struct *eeprom)
{
	HAL_I2C_Mem_Write(&hi2c1, (uint16_t) I2C1_DEVICE_ADDRESS<<1, EEPROM_1_ADDRESS, 1, (uint8_t*)eeprom,8,5);
}

//void eeprom_collect_data ();