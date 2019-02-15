/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2019 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     
#include "u8g2.h"  
#include "u8g2_arm.h"
#include <stdio.h>
#include "speed.h"
#include "usart.h"
#include "i2c.h"
#include "adc.h"
#include "string.h"
#include "GPS_Parser.h"
#include "Location.h"
#include "Simple_distance.h"
#include "eeprom.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define    DWT_CYCCNT    *(volatile unsigned long *)0xE0001004
#define    DWT_CONTROL   *(volatile unsigned long *)0xE0001000
#define    SCB_DEMCR     *(volatile unsigned long *)0xE000EDFC
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
u8g2_t u8g2;
#define StartParcing() HAL_UART_Receive_IT(&huart1,(uint8_t *)&UART_byte,1)
uint32_t count_tic = 0;
char UART_byte=0;
char GPS_buffer[BUFFSIZE];
char GPS_buffer_rx[BUFFSIZE];
char Screen_buffer[15];
uint8_t GPS_buff_pos = 0;
GPS_data GPS;
Race_data Race;
eeprom_struct eeprom;
Display Disp;
__IO ITStatus UartReady = RESET;
Position Previous_Position,Current_position; 
uint8_t buttons_state, buttons_long_press_state;
int i=65535;
uint32_t adc=0;
int a = 0;
enum mode {normal, power_off, debug};
enum mode work_mode = normal;
//enum mode work_mode = debug;



const char change_baudrate[28] ={0xb5,0x62,0x06,0x00,0x14,0x00,0x01,0x00,0x00,0x00,0xd0,0x08,0x00,0x00,0x00,0xc2,0x01,0x00,0x07,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0xc0,0x7e};
const char change_baudrate_uart_only[28] ={0xb5,0x62,0x06,0x00,0x14,0x00,0x01,0x00,0x00,0x00,0xd0,0x08,0x00,0x00,0x00,0xc2,0x01,0x00,0x07,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0xbf,0x78};
const char uart_only[26] ={0xb5,0x62,0x06,0x00,0x14,0x00,0x01,0x00,0x00,0x00,0xd0,0x08,0x00,0x00,0x80,0x25,0x00,0x00,0x07,0x00,0x02,0x00,0x00,0x00,0x00,0x00};
const char rate_10hz[14] = {0xb5,0x62,0x06,0x08,0x06,0x00,0x64,0x00,0x01,0x00,0x01,0x00,0x7a,0x12};
const char rate_5hz[14] = {0xb5,0x62,0x06,0x08,0x06,0x00,0xc8,0x00,0x01,0x00,0x01,0x00,0xde,0x6a};
const char rate_2hz[13] = {0xb5,0x62,0x06,0x08,0x06,0x00,0xf4,0x01,0x01,0x00,0x01,0x00,0x0b};
const char gl_gps_only[28] = {0xb5,0x62,0x06,0x3e,0x14,0x00,0x00,0x00,0x20,0x02,0x00,0x08,0x10,0x00,0x01,0x00,0x01,0x01,0x06,0x08,0x0e,0x00,0x01,0x00,0x01,0x01,0xb4,0x76};
const char turn_off_gga[11] = {0xb5,0x62,0x06,0x01,0x03,0x00,0xf0,0x00,0x00,0xfa,0x0f};
const char turn_off_gns[11] = {0xb5,0x62,0x06,0x01,0x03,0x00,0xf0,0x01,0x00,0xfb,0x11};
const char turn_off_gsa[11] = {0xb5,0x62,0x06,0x01,0x03,0x00,0xf0,0x02,0x00,0xfc,0x13};
const char turn_off_gsv[11] = {0xb5,0x62,0x06,0x01,0x03,0x00,0xf0,0x03,0x00,0xfd,0x15};

/*????????? GGA: 0xb5,0x62,0x06,0x01,0x03,0x00,0xf0,0x00,0x00,0xfa,0x0f
????????? GNS: 0xb5,0x62,0x06,0x01,0x03,0x00,0xf0,0x01,0x00,0xfb,0x11
????????? GSA: 0xb5,0x62,0x06,0x01,0x03,0x00,0xf0,0x02,0x00,0xfc,0x13
????????? GSV: 0xb5,0x62,0x06,0x01,0x03,0x00,0xf0,0x03,0x00,0xfd,0x15 */
/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId myLCDHandle;
osThreadId myGPS_parserHandle;
osThreadId myButtonsHandle;
osThreadId myEEPROMHandle;
osMessageQId myButtons_state_QueueHandle;
osSemaphoreId myBinarySemUART_ISRHandle;
osSemaphoreId myBinarySemDisplay_DataHandle;
osSemaphoreId myBinarySemButtons_ISRHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
/*	static portBASE_TYPE xHigherPriorityTaskWoken;
	xHigherPriorityTaskWoken = pdFALSE;*/
	BaseType_t xYieldRequired;
	if (UartHandle->Instance == USART1)
	{
		HAL_UART_Receive_IT(&huart1,(uint8_t *)&UART_byte,1);
		HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);	
		if (UART_byte == 0x0A)
		{
//			xSemaphoreGiveFromISR(myBinarySemUART_ISRHandle,&xHigherPriorityTaskWoken);
			xYieldRequired = xTaskResumeFromISR(myGPS_parserHandle);

     if( xYieldRequired == pdTRUE )
     {
         taskYIELD();
     }
			//if( xHigherPriorityTaskWoken == pdTRUE ) taskYIELD();	
		}
		else 
		{
			GPS_buffer[GPS_buff_pos]=UART_byte;
			GPS_buff_pos++;
			if (GPS_buff_pos > BUFFSIZE - 1) GPS_buff_pos = 0; 
			//HAL_UART_Receive_IT(&huart1,(uint8_t *)&UART_byte,1);
			//HAL_UART_Receive_IT(&huart1,(uint8_t *)&UART_byte,1);
		}
	}
	
}

 void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
		BaseType_t xYieldRequired;
		xYieldRequired = xTaskResumeFromISR(myButtonsHandle);
     if( xYieldRequired == pdTRUE )
     {
         taskYIELD();
     }
} 

void HAL_ADC_LevelOutOfWindowCallback(ADC_HandleTypeDef* hadc2)
{
	switch (work_mode){
		case power_off:
			  //HAL_I2C_Mem_Write(&hi2c1, (uint16_t) I2C1_DEVICE_ADDRESS<<1, ODO1_ADDRESS, 1, (uint8_t*)&Race.odo1, 8, 5);
				eeprom_write(&eeprom);
				work_mode = normal;
			  ADC2 ->HTR = 4095;
				ADC2 ->LTR = 1350;
			break;
		case normal:
				work_mode = power_off;
				ADC2 ->HTR = 1200;
				ADC2 ->LTR = 0;
			break;
		case debug:
			__HAL_ADC_DISABLE_IT(hadc2, ADC_IT_AWD);
			break;
	}
}

/*void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc1)

{
		adc = (uint32_t) HAL_ADC_GetValue(&hadc2);
}*/
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void StartLCD(void const * argument);
void StarGPS_parser(void const * argument);
void StartButtons(void const * argument);
void StartTask05(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of myBinarySemUART_ISR */
  osSemaphoreDef(myBinarySemUART_ISR);
  myBinarySemUART_ISRHandle = osSemaphoreCreate(osSemaphore(myBinarySemUART_ISR), 1);

  /* definition and creation of myBinarySemDisplay_Data */
  osSemaphoreDef(myBinarySemDisplay_Data);
  myBinarySemDisplay_DataHandle = osSemaphoreCreate(osSemaphore(myBinarySemDisplay_Data), 1);

  /* definition and creation of myBinarySemButtons_ISR */
  osSemaphoreDef(myBinarySemButtons_ISR);
  myBinarySemButtons_ISRHandle = osSemaphoreCreate(osSemaphore(myBinarySemButtons_ISR), 1);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityIdle, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of myLCD */
  osThreadDef(myLCD, StartLCD, osPriorityBelowNormal, 0, 128);
  myLCDHandle = osThreadCreate(osThread(myLCD), NULL);

  /* definition and creation of myGPS_parser */
  osThreadDef(myGPS_parser, StarGPS_parser, osPriorityNormal, 0, 128);
  myGPS_parserHandle = osThreadCreate(osThread(myGPS_parser), NULL);

  /* definition and creation of myButtons */
  osThreadDef(myButtons, StartButtons, osPriorityIdle, 0, 128);
  myButtonsHandle = osThreadCreate(osThread(myButtons), NULL);

  /* definition and creation of myEEPROM */
  osThreadDef(myEEPROM, StartTask05, osPriorityIdle, 0, 128);
  myEEPROMHandle = osThreadCreate(osThread(myEEPROM), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
	vTaskSuspend(myGPS_parserHandle);
	vTaskSuspend(myButtonsHandle);
  /* USER CODE END RTOS_THREADS */

  /* Create the queue(s) */
  /* definition and creation of myButtons_state_Queue */
  osMessageQDef(myButtons_state_Queue, 8, uint8_t);
  myButtons_state_QueueHandle = osMessageCreate(osMessageQ(myButtons_state_Queue), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{

  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
	osDelay(500);
	HAL_UART_Transmit(&huart1,(uint8_t*)&turn_off_gga,11,0xFFFF);
	HAL_UART_Transmit(&huart1,(uint8_t*)&turn_off_gns,11,0xFFFF);
	HAL_UART_Transmit(&huart1,(uint8_t*)&turn_off_gsa,11,0xFFFF);
	HAL_UART_Transmit(&huart1,(uint8_t*)&turn_off_gsv,11,0xFFFF);
	HAL_UART_Transmit(&huart1,(uint8_t*)&rate_5hz,14,0xFFFF);
	/*HAL_UART_Transmit(&huart1,(uint8_t*)&rate_2hz,13,0xFFFF);
	//HAL_UART_Transmit(&huart1,(uint8_t*)&gl_gps_only,28,0xFFFF);
	//HAL_UART_Transmit(&huart1,(uint8_t*)&change_baudrate_uart_only,28,0xFFFF);*/
	//HAL_UART_Transmit(&huart1,(uint8_t*)&uart_only,26,0xFFFF);
/*
	__HAL_UART_DISABLE(&huart1);
	USART1->BRR = 640;
	__HAL_UART_ENABLE(&huart1);*/

	StartParcing();
  for(;;)
  {

				osDelay(1);
  }

  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartLCD */
/**
* @brief Function implementing the myLCD thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLCD */
void StartLCD(void const * argument)
{
  /* USER CODE BEGIN StartLCD */
	SCB_DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	Disp.pos2 = 0;
	eeprom_read(&eeprom,&Disp,&Race);
	//HAL_I2C_Mem_Read(&hi2c1, (uint16_t) I2C1_DEVICE_ADDRESS<<1, ODO1_ADDRESS, 1, (uint8_t*)&Race.odo1, 8, 5); /*As odo1 & odo2 goes one after another in Race sruct 
	//and their size is 4 bytes each we can read/write them both in one time by sending 8 bytes via HAL_I2C_Mem_Read/Write functions*/
  /* Infinite loop */
  for(;;)
  {
		vTaskDelayUntil( &xLastWakeTime, ( 100 / portTICK_RATE_MS ) );
		xSemaphoreTake(myBinarySemDisplay_DataHandle,portMAX_DELAY);
		//xQueueReceive( myButtons_state_QueueHandle, &buttons_state, portMAX_DELAY);
		/*DWT_CYCCNT = 0;
		DWT_CONTROL|= DWT_CTRL_CYCCNTENA_Msk; */
		u8g2_ClearBuffer(&u8g2);
		rallycomp(&Current_position,&GPS, &Race, &Disp, buttons_state);
		u8g2_SendBuffer(&u8g2);
		//count_tic = DWT_CYCCNT;
		xSemaphoreGive(myBinarySemDisplay_DataHandle);
    //osDelay(100);
  }
  /* USER CODE END StartLCD */
}

/* USER CODE BEGIN Header_StarGPS_parser */
/**
* @brief Function implementing the myGPS_parser thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StarGPS_parser */
void StarGPS_parser(void const * argument)
{
  /* USER CODE BEGIN StarGPS_parser */
	float Dist;
	Previous_Position.Lat = 0;
	Current_position.Lat = 0;
	Previous_Position.Lon = 0;
	Current_position.Lon = 0;
  /* Infinite loop */
  for(;;)
  {
		//HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
		//xSemaphoreTake(myBinarySemUART_ISRHandle, portMAX_DELAY);
		DWT_CYCCNT = 0;
		DWT_CONTROL|= DWT_CTRL_CYCCNTENA_Msk; 
		memcpy(GPS_buffer_rx,GPS_buffer,BUFFSIZE);
		count_tic = DWT_CYCCNT;
		GPS_buff_pos = 0;
		//HAL_UART_Receive_IT(&huart1,(uint8_t *)&UART_byte,1);
		xSemaphoreTake(myBinarySemDisplay_DataHandle,portMAX_DELAY);
		Parce_NMEA_string(GPS_buffer_rx, &GPS, &Current_position);
		//if ((GPS.status != 'V')&&(GPS.Speed.kelometers>2))	
		if (GPS.status != 'V')
		{
			if (Previous_Position.Lat != 0)
			{
				Dist = DistanceKm(&Previous_Position,&Current_position);
				//Dist = DistanceBetween(&Previous_Position,&Current_position);
				if (Dist < 0.2)
				{					
				Race.odo1 += Dist;
				Race.odo2 += Dist;
				eeprom.odo1 = Race.odo1;
				eeprom.odo2 = Race.odo2;
				//HAL_I2C_Mem_Write(&hi2c1, (uint16_t) I2C1_DEVICE_ADDRESS<<1, ODO1_ADDRESS, 1, (uint8_t*)&Race.odo1, 8, 5);
				
				}
			}
				//if (Race.odo1 > 99.99) Race.odo1 = 0;
			Previous_Position.Lat = Current_position.Lat;
			Previous_Position.Lon = Current_position.Lon;
		}
		//GPS_buff_pos = 0;
		xSemaphoreGive(myBinarySemDisplay_DataHandle);
		//xSemaphoreGive(myBinarySemUART_ISRHandle);
		//HAL_UART_Receive_IT(&huart1,(uint8_t *)&UART_byte,1);
		vTaskSuspend(myGPS_parserHandle);
    //osDelay(1);
  }
	
  /* USER CODE END StarGPS_parser */
}

/* USER CODE BEGIN Header_StartButtons */
/**
* @brief Function implementing the myButtons thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartButtons */
void StartButtons(void const * argument)
{
  /* USER CODE BEGIN StartButtons */
	//int i=65535;
  /* Infinite loop */
  for(;;)
  {
		osDelay(10);
		if (!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2))
			buttons_state |= (1 << 0);
    else
      buttons_state &= ~(1 << 0);
		if (!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1))
			buttons_state |= (1 << 1);
    else
      buttons_state &= ~(1 << 1);
		if (!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4))
			buttons_state |= (1 << 2);
    else
			buttons_state &= ~(1 << 2);
			if (!HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3))
			buttons_state |= (1 << 3);
    else
			buttons_state &= ~(1 << 3);
		  
			if (buttons_state & 1<<0){
				Race.odo1 += 0.1;
				Race.odo2 += 0.1;
				//HAL_UART_Transmit(&huart1,(uint8_t*)&rate_5hz,14,0xFFFF);
				//HAL_UART_Transmit(&huart1,(uint8_t*)&rate_2hz,13,0xFFFF);
				eeprom.odo1 = Race.odo1;
				eeprom.odo2 = Race.odo2;
				//eeprom_write(&eeprom);
				//HAL_I2C_Mem_Write(&hi2c1, (uint16_t) I2C1_DEVICE_ADDRESS<<1, ODO1_ADDRESS, 1, (uint8_t*)&Race.odo1, 8, 5);
				//HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_15);	
				i -= 10000;
				if (i < 10000) i = 65535;
				TIM2->CCR1=i;
			}
			if (buttons_state & 1<<1){
				Disp.pos2++;
			}
			if (buttons_state & 1<<2)
			{
				//HAL_UART_Transmit(&huart1,(uint8_t*)&rate_5hz,14,0xFFFF); 
				Race.odo2 = 0;
				HAL_I2C_Mem_Write(&hi2c1, (uint16_t) I2C1_DEVICE_ADDRESS<<1, ODO2_ADDRESS, 1, (uint8_t*)&Race.odo2, 4, 5);
			}
			if (buttons_state & 1<<3)
			{
				Race.odo1 = 0;
				HAL_I2C_Mem_Write(&hi2c1, (uint16_t) I2C1_DEVICE_ADDRESS<<1, ODO1_ADDRESS, 1, (uint8_t*)&Race.odo1, 4, 5);	//write to memory address 08
			}
		xQueueSendToBack(myButtons_state_QueueHandle, &buttons_state, 0);
		osDelay(10);
		vTaskSuspend(myButtonsHandle);

  }
  /* USER CODE END StartButtons */
}

/* USER CODE BEGIN Header_StartTask05 */
/**
* @brief Function implementing the myEEPROM thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask05 */
void StartTask05(void const * argument)
{
  /* USER CODE BEGIN StartTask05 */
	/*xBuffer[0]='A';
	
	//xBuffer[0] = 'M'; //0x4D
  HAL_I2C_Mem_Write(&hi2c1, (uint16_t) I2C1_DEVICE_ADDRESS<<1, MEMORY_ADDRESS, 1, (uint8_t*)&af, 4, 5);	//write to memory address 08 
	osDelay(10);
	HAL_I2C_Mem_Read(&hi2c1, (uint16_t) I2C1_DEVICE_ADDRESS<<1, MEMORY_ADDRESS, 1, (uint8_t*)&bf, 4, 5); //read memory address 08
*/
  /* Infinite loop */
  for(;;)
  {
    Race.voltage = (33*((float) HAL_ADC_GetValue(&hadc2)))/4096 + 0.38;
		//a = sizeof (eeprom);
		osDelay(1000);
  }
  /* USER CODE END StartTask05 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
