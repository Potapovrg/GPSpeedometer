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
  * Copyright (c) 2017 STMicroelectronics International N.V. 
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
osThreadId mySpeedHandle;
osThreadId myBlinkHandle;
osSemaphoreId myBinarySemUART_ISRHandle;

/* USER CODE BEGIN Variables */
u8g2_t u8g2;
//uint8_t b1[];
#define BUFFSIZE 3
char b1[BUFFSIZE];
__IO ITStatus UartReady = RESET;

/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void StartDefaultTask(void const * argument);
void StartSpeed(void const * argument);
void StartBlink(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
	if (UartHandle->Instance == USART1)
	{
		//HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
		HAL_UART_Transmit(&huart1,(uint8_t *)&b1,BUFFSIZE,100);
		if (strncmp (b1, "abc", 3) == 0) 
		{
			HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
		}
		  HAL_UART_Receive_IT(&huart1,(uint8_t *)&b1,BUFFSIZE);
		//if (strcmp (b1, "123\r")==0) HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
		//uint8_t c3po[]="\r\n";
		//HAL_UART_Transmit(&huart1,(uint8_t *)&c3po,1,100);
		//UartReady = SET;
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

  /* definition and creation of mySpeed */
  osThreadDef(mySpeed, StartSpeed, osPriorityNormal, 1, 128);
  mySpeedHandle = osThreadCreate(osThread(mySpeed), NULL);

  /* definition and creation of myBlink */
  osThreadDef(myBlink, StartBlink, osPriorityIdle, 0, 128);
  myBlinkHandle = osThreadCreate(osThread(myBlink), NULL);

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

/* StartSpeed function */
void StartSpeed(void const * argument)
{
  /* USER CODE BEGIN StartSpeed */
  /* Infinite loop */
  for(;;)
  {
	u8g2_ClearBuffer(&u8g2);
	//rallycomp();
	speedo();
	u8g2_SendBuffer(&u8g2);	
	//uint8_t c3po[]="Sir, the possibility of successfully navigating an asteroid field is approximately 3,720 to 1 \r\n";
	//HAL_UART_Transmit(&huart1,(uint8_t *)&b1,97,100);
   osDelay(1000);
  }
  /* USER CODE END StartSpeed */
}

/* StartBlink function */
void StartBlink(void const * argument)
{
  /* USER CODE BEGIN StartBlink */
			if(HAL_UART_Receive_IT(&huart1, (uint8_t *)&b1,BUFFSIZE)== !HAL_OK)
		{
			//HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
		}
  /* Infinite loop */
  for(;;)
  {
		//HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);

    osDelay(10);
  }
  /* USER CODE END StartBlink */
}

/* USER CODE BEGIN Application */
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
