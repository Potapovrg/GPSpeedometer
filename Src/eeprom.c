#include "eeprom.h"
uint32_t eeprom_crc[1];

//eeprom_struct eeprom;

const uint8_t eeprom_size = sizeof(eeprom);
uint32_t crc_buf[4];
uint32_t test;
void eeprom_read(eeprom_struct *eeprom,Race_data *Race,Display *Disp)
{
	//uint32_t crc_buf[4];

	HAL_I2C_Mem_Read(&hi2c1, (uint16_t) I2C1_DEVICE_ADDRESS<<1, EEPROM_RACE_ADDRESS, 1, (uint8_t*)&eeprom->race,EEPROM_RACE_SIZE,10);
	memcpy(crc_buf,&eeprom->race,EEPROM_RACE_SIZE-4);
	if (eeprom->race.crc == HAL_CRC_Calculate(&hcrc,crc_buf,(EEPROM_RACE_SIZE-4)/4))
	{
		Race->odo1 = eeprom->race.odo1;
		Race->odo2 = eeprom->race.odo2;
		Race->total_distance = eeprom->race.total_distance;
	}
	
	HAL_I2C_Mem_Read(&hi2c1, (uint16_t) I2C1_DEVICE_ADDRESS<<1, EEPROM_UI_ADDRESS, 1, (uint8_t*)&eeprom->ui,EEPROM_UI_SIZE,10);
	memcpy(crc_buf,&eeprom->ui,EEPROM_UI_SIZE-4);
	if (eeprom->ui.crc == HAL_CRC_Calculate(&hcrc,crc_buf,(EEPROM_UI_SIZE-4)/4))
	{
		Disp->pos1 = eeprom->ui.disp_pos1;
		Disp->pos2 = eeprom->ui.disp_pos2;
		Race->flags = eeprom->ui.race_flags;
		Disp->menu_page = eeprom->ui.menu_page;
	}
	
	HAL_I2C_Mem_Read(&hi2c1, (uint16_t) I2C1_DEVICE_ADDRESS<<1, EEPROM_TIME_ADDRESS, 1, (uint8_t*)&eeprom->time,EEPROM_TIME_SIZE,10);
	memcpy(crc_buf,&eeprom->time,EEPROM_TIME_SIZE-4);
	if (eeprom->time.crc == HAL_CRC_Calculate(&hcrc,crc_buf,(EEPROM_TIME_SIZE-4)/4))
	{
		Race->GMT.h = eeprom->time.GMT_h;
		Race->GMT.m = eeprom->time.GMT_m;
	}
}

void eeprom_race_collect(eeprom_struct *eeprom,Race_data *Race)
{
	//uint32_t crc_buf[4];
	
	eeprom->race.odo1 = Race->odo1;
	eeprom->race.odo2 = Race->odo2;
	eeprom->race.total_distance = Race->total_distance;
	
	memcpy(crc_buf,&eeprom->race,EEPROM_RACE_SIZE-4);
	eeprom->race.crc = HAL_CRC_Calculate(&hcrc,crc_buf,(EEPROM_RACE_SIZE-4)/4);
	
	eeprom->flag = 1;
};

void eeprom_ui_collect(eeprom_struct *eeprom,Race_data *Race,Display *Disp)
{
	//uint32_t crc_buf[4];
	eeprom->ui.disp_pos1 = Disp->pos1;
	eeprom->ui.disp_pos2 = Disp->pos2;
	eeprom->ui.race_flags = Race->flags;
	eeprom->ui.menu_page = Disp->menu_page;
	
	memcpy(crc_buf,&eeprom->ui,EEPROM_UI_SIZE-4);
	eeprom->ui.crc = HAL_CRC_Calculate(&hcrc,crc_buf,(EEPROM_UI_SIZE-4)/4);
};

void eeprom_time_collect(eeprom_struct *eeprom,Race_data *Race,Display *Disp)
{
	eeprom->time.GMT_h = Race->GMT.h;
	eeprom->time.GMT_m = Race->GMT.m;
	
	memcpy(crc_buf,&eeprom->time,EEPROM_TIME_SIZE-4);
	eeprom->time.crc = HAL_CRC_Calculate(&hcrc,crc_buf,(EEPROM_TIME_SIZE-4)/4);
};

void eeprom_race_write(eeprom_struct *eeprom)
{
		if (eeprom->flag != 0)
	{
		HAL_I2C_Mem_Write(&hi2c1, (uint16_t) I2C1_DEVICE_ADDRESS<<1, EEPROM_RACE_ADDRESS, 1, (uint8_t*)&eeprom->race,EEPROM_RACE_SIZE,10);
			eeprom->flag = 0;
	}
}

void eeprom_ui_write(eeprom_struct *eeprom)
{
	HAL_I2C_Mem_Write(&hi2c1, (uint16_t) I2C1_DEVICE_ADDRESS<<1, EEPROM_UI_ADDRESS, 1, (uint8_t*)&eeprom->ui,EEPROM_UI_SIZE,10);	
}

void eeprom_time_write(eeprom_struct *eeprom)
{
	HAL_I2C_Mem_Write(&hi2c1, (uint16_t) I2C1_DEVICE_ADDRESS<<1, EEPROM_TIME_ADDRESS, 1, (uint8_t*)&eeprom->time,EEPROM_TIME_SIZE,10);	
}
