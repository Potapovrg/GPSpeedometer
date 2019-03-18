#include "eeprom.h"
uint32_t eeprom_crc[1];

//eeprom_struct eeprom;

const uint8_t eeprom_size = sizeof(eeprom);
uint32_t crc_buf[4];
uint32_t test;
void eeprom_read_2(eeprom_race_struct *eeprom_race, eeprom_ui_struct *eeprom_ui,Race_data *Race,Display *Disp)
{
	//uint32_t crc_buf[4];

	HAL_I2C_Mem_Read(&hi2c1, (uint16_t) I2C1_DEVICE_ADDRESS<<1, EEPROM_RACE_ADDRESS, 1, (uint8_t*)eeprom_race,EEPROM_RACE_SIZE,10);
	memcpy(crc_buf,eeprom_race,EEPROM_RACE_SIZE-4);
	if (eeprom_race->crc == HAL_CRC_Calculate(&hcrc,crc_buf,(EEPROM_RACE_SIZE-4)/4))
	{
		Race->odo1 = eeprom_race->odo1;
		Race->odo2 = eeprom_race->odo2;
		Race->total_distance = eeprom_race->total_distance;
	}
	HAL_I2C_Mem_Read(&hi2c1, (uint16_t) I2C1_DEVICE_ADDRESS<<1, EEPROM_UI_ADDRESS, 1, (uint8_t*)eeprom_ui,EEPROM_UI_SIZE,10);
	memcpy(crc_buf,eeprom_ui,EEPROM_UI_SIZE-4);
	if (eeprom_ui->crc == HAL_CRC_Calculate(&hcrc,crc_buf,(EEPROM_UI_SIZE-4)/4))
	{
		Disp->pos1 = eeprom_ui->disp_pos1;
		Disp->pos2 = eeprom_ui->disp_pos2;
		Race->flags = eeprom_ui->race_flags;
		Disp->menu_page = eeprom_ui->menu_page;
	}
}

void eeprom_race_collect(eeprom_race_struct *eeprom_race,Race_data *Race, uint8_t *flag)
{
	//uint32_t crc_buf[4];
	
	eeprom_race->odo1 = Race->odo1;
	eeprom_race->odo2 = Race->odo2;
	eeprom_race->total_distance = Race->total_distance;
	
	memcpy(crc_buf,eeprom_race,EEPROM_RACE_SIZE-4);
	eeprom_race->crc = HAL_CRC_Calculate(&hcrc,crc_buf,(EEPROM_RACE_SIZE-4)/4);
	
	*flag = 1;
};

void eeprom_ui_collect(eeprom_ui_struct *eeprom_ui,Race_data *Race,Display *Disp)
{
	//uint32_t crc_buf[4];
	eeprom_ui->disp_pos1 = Disp->pos1;
	eeprom_ui->disp_pos2 = Disp->pos2;
	eeprom_ui->race_flags = Race->flags;
	eeprom_ui->menu_page = Disp->menu_page;
	
	memcpy(crc_buf,eeprom_ui,EEPROM_UI_SIZE-4);
	eeprom_ui->crc = HAL_CRC_Calculate(&hcrc,crc_buf,(EEPROM_UI_SIZE-4)/4);
};

void eeprom_race_write(eeprom_race_struct *eeprom_race, uint8_t *flag)
{
		if (*flag != 0)
	{
		HAL_I2C_Mem_Write(&hi2c1, (uint16_t) I2C1_DEVICE_ADDRESS<<1, EEPROM_RACE_ADDRESS, 1, (uint8_t*)eeprom_race,EEPROM_RACE_SIZE,10);
			*flag = 0;
	}
}

void eeprom_ui_write(eeprom_ui_struct *eeprom_ui)
{
	HAL_I2C_Mem_Write(&hi2c1, (uint16_t) I2C1_DEVICE_ADDRESS<<1, EEPROM_UI_ADDRESS, 1, (uint8_t*)eeprom_ui,EEPROM_UI_SIZE,10);	
}
	
void eeprom_read(eeprom_struct *eeprom, Display *Disp, Race_data *Race)
{
	uint32_t crc_buf[4];
	
	HAL_I2C_Mem_Read(&hi2c1, (uint16_t) I2C1_DEVICE_ADDRESS<<1, EEPROM_1_ADDRESS, 1, (uint8_t*)eeprom,eeprom_size,10);
	HAL_I2C_Mem_Read(&hi2c1, (uint16_t) I2C1_DEVICE_ADDRESS<<1, EEPROM_CRC_ADDRESS, 1, (uint8_t*)eeprom_crc,4,10);
	memcpy(crc_buf,eeprom,eeprom_size);
	if (eeprom_crc[0] == HAL_CRC_Calculate(&hcrc,crc_buf,4))
	{
		Race->odo1 = eeprom->odo1;
		Race->odo2 = eeprom->odo2;
		Race->total_distance = eeprom->total_distance;
		Disp->pos1 = eeprom->disp_pos1;
		Disp->pos2 = eeprom->disp_pos2;
		Race->flags = eeprom->race_flags;
		Disp->menu_page = eeprom->menu_page;
	}
}

void eeprom_collect(eeprom_struct *eeprom, Display *Disp, Race_data *Race, uint8_t *flag)
{
	uint32_t crc_buf[4]; // sizeof(eeprom) = 16 4 * 4 byte
	eeprom->odo1 = Race->odo1;
	eeprom->odo2 = Race->odo2;
	eeprom->total_distance = Race->total_distance;
	eeprom->disp_pos1 = Disp->pos1;
	eeprom->disp_pos2 = Disp->pos2;
	eeprom->race_flags = Race->flags;
	eeprom->menu_page = Disp->menu_page;
	memcpy(crc_buf,eeprom,eeprom_size);
	eeprom_crc[0] = HAL_CRC_Calculate(&hcrc,crc_buf,4);
	*flag = 1;
};


void eeprom_write(eeprom_struct *eeprom, uint8_t *flag)
{
	if (*flag != 0)
	{
		HAL_I2C_Mem_Write(&hi2c1, (uint16_t) I2C1_DEVICE_ADDRESS<<1, EEPROM_1_ADDRESS, 1, (uint8_t*)eeprom,eeprom_size,10);
		//HAL_Delay(1);
		for (int i=0;i<30000;i++)
		{
			__NOP();
		}
		HAL_I2C_Mem_Write(&hi2c1, (uint16_t) I2C1_DEVICE_ADDRESS<<1, EEPROM_CRC_ADDRESS, 1, (uint8_t*)eeprom_crc,4,10);
		*flag = 0;
	}
}

//void eeprom_collect_data ();