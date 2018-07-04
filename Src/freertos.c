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
  * Copyright (c) 2018 STMicroelectronics International N.V. 
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */     
#include "u8g2.h"  
#include "u8g2_arm.h"
#include <stdio.h>
#include "speed.h"
#include "usart.h"
#include "string.h"
#include "GPS_Parser.h"
#include "Location.h"
#include "Simple_distance.h"

/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
osThreadId defaultTaskHandle;
osThreadId myLCDHandle;
osThreadId myGPS_parserHandle;
osThreadId myButtonsHandle;
osMessageQId myButtons_state_QueueHandle;
osSemaphoreId myBinarySemUART_ISRHandle;
osSemaphoreId myBinarySemDisplay_DataHandle;
osSemaphoreId myBinarySemButtons_ISRHandle;

/* USER CODE BEGIN Variables */
u8g2_t u8g2;
#define StartParcing() HAL_UART_Receive_IT(&huart1,(uint8_t *)&UART_byte,1)
#define OFFSET 1
#define HEIGHT
char UART_byte=0;
char GPS_buffer[BUFFSIZE];
char Screen_buffer[15];
uint8_t GPS_buff_pos = 0;
GPS_data GPS;
Race_data Race;
Display Disp;
__IO ITStatus UartReady = RESET;
Position Previous_Position,Current_position; 
uint8_t buttons_state, buttons_long_press_state;



/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void StartDefaultTask(void const * argument);
void StartLCD(void const * argument);
void StarGPS_parser(void const * argument);
void StartButtons(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
/*	static portBASE_TYPE xHigherPriorityTaskWoken;
	xHigherPriorityTaskWoken = pdFALSE;*/
	BaseType_t xYieldRequired;
		
	if (UartHandle->Instance == USART1)
	{
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
			HAL_UART_Receive_IT(&huart1,(uint8_t *)&UART_byte,1);
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
/* USER CODE END FunctionPrototypes */

/* Hook prototypes */

/* Init FreeRTOS */

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

/* StartDefaultTask function */
void StartDefaultTask(void const * argument)
{

  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
	StartParcing();
  for(;;)
  {
				osDelay(1);
  }

  /* USER CODE END StartDefaultTask */
}

/* StartLCD function */
void StartLCD(void const * argument)
{
  /* USER CODE BEGIN StartLCD */
	//uint8_t buttons_state = 0;
  /* Infinite loop */
  for(;;)
  {
		xSemaphoreTake(myBinarySemDisplay_DataHandle,portMAX_DELAY);
		//xQueueReceive( myButtons_state_QueueHandle, &buttons_state, portMAX_DELAY);
		u8g2_ClearBuffer(&u8g2);
		rallycomp(&GPS, &Race, &Disp, buttons_state);
		u8g2_SendBuffer(&u8g2);
		xSemaphoreGive(myBinarySemDisplay_DataHandle);
    osDelay(100);
  }
  /* USER CODE END StartLCD */
}

/* StarGPS_parser function */
void StarGPS_parser(void const * argument)
{
  /* USER CODE BEGIN StarGPS_parser */
	float Dist;
  /* Infinite loop */
  for(;;)
  {
		//xSemaphoreTake(myBinarySemUART_ISRHandle, portMAX_DELAY);
		xSemaphoreTake(myBinarySemDisplay_DataHandle,portMAX_DELAY);
		Parce_NMEA_string(GPS_buffer, &GPS, &Current_position);
		if (GPS.status != 'V')	
		{
			if (Previous_Position.Lat != 0)
			{
				//Dist = DistanceKm(&Previous_Position,&Current_position);
				Dist = DistanceBetween(&Previous_Position,&Current_position);
			//Dist = 1.0;
				Race.odo1 += Dist;
				Race.odo2 += Dist;
				if (Race.odo1 > 99.99) Race.odo1 = 0;
			}
			Previous_Position.Lat = Current_position.Lat;
			Previous_Position.Lon = Current_position.Lon;
		}
		GPS_buff_pos = 0;
		xSemaphoreGive(myBinarySemDisplay_DataHandle);
		//xSemaphoreGive(myBinarySemUART_ISRHandle);
		HAL_UART_Receive_IT(&huart1,(uint8_t *)&UART_byte,1);
		vTaskSuspend(myGPS_parserHandle);
    osDelay(1);
  }
	
  /* USER CODE END StarGPS_parser */
}

/* StartButtons function */
void StartButtons(void const * argument)
{
  /* USER CODE BEGIN StartButtons */
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
		
			if (buttons_state & 1<<1){
				Disp.pos2++;
				if (Disp.pos2>2) Disp.pos2 = 0; 
			}
			if (buttons_state & 1<<2)
				Race.odo1 += 1.0;
			if (buttons_state & 1<<3)
				Race.odo1 = 0;
		xQueueSendToBack(myButtons_state_QueueHandle, &buttons_state, 0);
		osDelay(10);
		vTaskSuspend(myButtonsHandle);

  }
  /* USER CODE END StartButtons */
}

/* USER CODE BEGIN Application */
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
