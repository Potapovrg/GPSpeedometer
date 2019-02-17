#include "eeprom.h"


//eeprom_struct eeprom;

const uint8_t eeprom_size = sizeof(eeprom);

void eeprom_read(eeprom_struct *eeprom, Display *Disp, Race_data *Race)
{
	HAL_I2C_Mem_Read(&hi2c1, (uint16_t) I2C1_DEVICE_ADDRESS<<1, EEPROM_1_ADDRESS, 1, (uint8_t*)eeprom,eeprom_size,5);
	Race->odo1 = eeprom->odo1;
	Race->odo2 = eeprom->odo2;
	Race->total_distance = eeprom->total_distance;
	Disp->pos2 = eeprom->disp_pos2;
	

}

void eeprom_write(eeprom_struct *eeprom, uint8_t *flag)
{
	if (flag != 0)
	{
		HAL_I2C_Mem_Write(&hi2c1, (uint16_t) I2C1_DEVICE_ADDRESS<<1, EEPROM_1_ADDRESS, 1, (uint8_t*)eeprom,eeprom_size,10);
		flag = 0;
	}
}

//void eeprom_collect_data ();