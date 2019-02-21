 #ifndef _U8G2_ARM_H  
 #define _U8G2_ARM_H  
 #include "u8g2.h"  
 #include "stm32f1xx_hal.h"  
 #define SPI_HANDLER hspi2 // use your SPI hadler  
 extern SPI_HandleTypeDef SPI_HANDLER;  
#define CS GPIO_PIN_12
#define CS_Port GPIOB
#define DC GPIO_PIN_14
#define DC_Port GPIOB
#define SPI_Port GPIOB
#define SCK GPIO_PIN_13
#define MOSI GPIO_PIN_15
uint8_t u8x8_gpio_and_delay_arm(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
uint8_t u8x8_byte_arm_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
void u8g2_Setup_st7920_s_128x64_f(u8g2_t *u8g2, const u8g2_cb_t *rotation, u8x8_msg_cb byte_cb, u8x8_msg_cb gpio_and_delay_cb);
void SPI_Out (uint8_t Data);
 #endif  


