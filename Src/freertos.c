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
/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
osThreadId defaultTaskHandle;
osThreadId myLCDHandle;
osThreadId myGPS_parserHandle;
osSemaphoreId myBinarySemUART_ISRHandle;

/* USER CODE BEGIN Variables */
u8g2_t u8g2;
#define BUFFSIZE 75
#define StartParcing() HAL_UART_Receive_IT(&huart1,(uint8_t *)&UART_byte,1)
char UART_byte=0;
char GPS_buffer[BUFFSIZE];
uint8_t GPS_buff_pos = 0;
__IO ITStatus UartReady = RESET;

/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void StartDefaultTask(void const * argument);
void StartLCD(void const * argument);
void StarGPS_parser(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
	static portBASE_TYPE xHigherPriorityTaskWoken;
	xHigherPriorityTaskWoken = pdFALSE;
	
	if (UartHandle->Instance == USART1)
	{
		if (UART_byte == 0x0D)
		{
			HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);	
			xSemaphoreGiveFromISR(myBinarySemUART_ISRHandle,&xHigherPriorityTaskWoken);
			if( xHigherPriorityTaskWoken == pdTRUE ) taskYIELD();	
		}
		else 
		{
			GPS_buffer[GPS_buff_pos]=UART_byte;
			GPS_buff_pos++;
			HAL_UART_Receive_IT(&huart1,(uint8_t *)&UART_byte,1);
		}
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

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of myLCD */
  osThreadDef(myLCD, StartLCD, osPriorityNormal, 0, 128);
  myLCDHandle = osThreadCreate(osThread(myLCD), NULL);

  /* definition and creation of myGPS_parser */
  osThreadDef(myGPS_parser, StarGPS_parser, osPriorityIdle, 0, 128);
  myGPS_parserHandle = osThreadCreate(osThread(myGPS_parser), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* StartDefaultTask function */
void StartDefaultTask(void const * argument)
{

  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
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
  /* Infinite loop */
  for(;;)
  {
		u8g2_ClearBuffer(&u8g2);
		//rallycomp();
		speedo();
		//u8g2_SetFont(&u8g2,u8g2_font_9x18B_tr);
		//u8g2_DrawStr(&u8g2,30,30,GPS_buffer);
		u8g2_SendBuffer(&u8g2);	
    osDelay(1000);
  }
  /* USER CODE END StartLCD */
}

/* StarGPS_parser function */
void StarGPS_parser(void const * argument)
{
  /* USER CODE BEGIN StarGPS_parser */
	enum GPS_parser_state {String_start, String_type, String_parsing};
	enum GPS_parser_state State = String_start;
	StartParcing();
  /* Infinite loop */
  for(;;)
  {
		xSemaphoreTake(myBinarySemUART_ISRHandle, portMAX_DELAY);
		//HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);					
		HAL_UART_Transmit(&huart1,(uint8_t *)&GPS_buffer,GPS_buff_pos,100);
		GPS_buff_pos=0;
		HAL_UART_Receive_IT(&huart1,(uint8_t *)&UART_byte,1);
    //osDelay(1);
  }
  /* USER CODE END StarGPS_parser */
}

/* USER CODE BEGIN Application */
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
