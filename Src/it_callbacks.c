#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "eeprom.h"
#include "stm32f1xx_it.h"
#include "usart.h"

uint8_t current_sentence;


void HAL_UART_RxIdleCallback(UART_HandleTypeDef *UartHandle)
{
//__HAL_UART_CLEAR_FLAG(&huart1, UART_FLAG_IDLE);
current_sentence=DMA1_Channel5->CNDTR;

};

