#include "u8g2_arm.h"

uint8_t control = 0xFA;

uint8_t *u8g2_m_st7920_16_1(uint8_t *page_cnt)
{
  static uint8_t buf[128];
  *page_cnt = 1;
  return buf;
}

void u8g2_Setup_st7920_s_128x64_1(u8g2_t *u8g2, const u8g2_cb_t *rotation, u8x8_msg_cb byte_cb, u8x8_msg_cb gpio_and_delay_cb)
{
  uint8_t tile_buf_height;
  uint8_t *buf;
  u8g2_SetupDisplay(u8g2, u8x8_d_st7920_128x64, u8x8_cad_st7920_spi, byte_cb, gpio_and_delay_cb);
  buf = u8g2_m_st7920_16_1(&tile_buf_height);
  u8g2_SetupBuffer(u8g2, buf, tile_buf_height, u8g2_ll_hvline_horizontal_right_lsb, rotation);
}

const uint8_t u8g2_font_logisoso30_tn[475] U8G2_FONT_SECTION("u8g2_font_logisoso30_tn") = 
  "\22\0\4\4\4\5\4\6\6\21$\0\376\36\370\36\0\0\0\0\0\1\302 \6\0\20\234\1*\34\335"
  "\266\236k\350\260\60cB\220\230\242I\262bI\36\210\230$\314\230`CG\1+\17\313\330\234\211\34"
  "m\36<pD\216\66\0,\13d\330[C\4\12\61Q\0-\10KX\235\341\3\7.\12D\30\134"
  "C\4\12\21\0/\42\356\27\234\225$Q*\211RI\224J\242$K\22%Y\222(\311\222DI\22"
  "\245\222(\225D)\5\60\32\357\25\234\253`\252\65MH\221 \207\377\377;\22\244\210\264Y\225\260\24"
  "\0\61\20\350\35\234\211\232*\36<\20C\210\376\377\37\62$\357\25\234\253`\252\65MH\221 \207w"
  "$\304\21-J\264dQ\242E)-JiQ\242%\213>\370\1\63!\357\365\233\341OK\26%Z"
  "\224\322\242DM\36Dj\226\60Y\372\305\60\22F\214\60R\206\10\0\64!\357\25\234\213\354X\332\216"
  "\245\355X\332\216\245\204\24\21Rc\10\221!D\206\320\203\337\221\245G\0\65!\357\25\234\341\17\310\322"
  "\27\245\330\64qQ\212\4\71td\351-:t$H\21i\263*a)\0\66$\357\25\234\253`\252"
  "\65MH\221 \207-]\224b\323\304\205\231\22\245\322\341\357H\220\42\322fU\302R\0\67\42\357\25"
  "\234\341\17\210eF\202\30\321J\311\22-J\226\322\242d)-J\226h\245d\211VJ\16\0\70%"
  "\357\25\234\253`\252\65MH\221 \207\237\225(S\244\315\242\65MH\221 \207\337\221 E\244\315\252"
  "\204\245\0\71%\357\25\234\253`\252\65MH\221 \207V\242\214\11'mX\225 K-:\354H"
  "\220\42\322fU\302R\0:\17\24\231\134C\4\12\361\20\212@!\2\0\0\0\0";

const uint8_t u8g2_font_9x18B_tr[1207] U8G2_FONT_SECTION("u8g2_font_9x18B_tr") = 
  "_\0\3\3\4\4\3\5\5\11\21\0\375\12\375\13\377\1\223\3)\4\236 \5\0\364\31!\7\262\207"
  "\31\217\4\42\10E\276\31\22.\2#\23\247\205\71J\22\221DrQ\222H.J\22\221D\2$\21"
  "\270|yB\213\12EHe\224PT\214\62\0%\23\250\204\71#\12EB\222H\305R\211\210\42a"
  "\232\0&\23\250\204\71C\211L\42\223\10\247#\12E\244B\32\11'\7B\277\31\207\0(\15\304~"
  "Y\22\221D\244\67\221L\0)\15\304~\31\62\221L\244\27\221D\4*\15x\214y**\66\232E"
  "\233\14\0+\13x\214yb\265CL\254\6,\10Cw\31\26\12\0-\6\27\245\31\7.\6#\207"
  "\31\6/\15\250\204\331R\261TY\252,\25\3\60\15\247\205Y\63\211\32\337$j#\0\61\15\250\204"
  "y\322!M\42\326\333!\0\62\14\247\205Y\63\211\232TQ\307\3\63\15\247\205\31W\241\342X\225$"
  "\42\1\64\20\247\205\231\302\31I\242$\21I\216R\25\0\65\15\247\205\31\7\251jY\225$\42\1\66"
  "\20\247\205Y$\241TZR\221\321$j#\0\67\15\247\205\31W\241T(\25J\265\1\70\21\247\205"
  "Y\63\211\232Dm&Q\243I\324F\0\71\20\247\205Y\63\211\32M\42\31U\25E$\0:\10s"
  "\207\31v\220\1;\11\223w\31v\220\205\2<\10\226\205\231\62]u=\10G\225\31w\204\3>\11"
  "\226\205\31R\335t\4?\16\247\205Y\63\211\232T\250U\16\225\1@\25\251\204Y\65\25\221\204\222B"
  "I\241\244PRH$\71\244\4A\16\247\205y\321\341\232DT\222\250\261\11B\16\247\205\31\26\31\333"
  "!\42\343v\210\0C\15\247\205Y$\21U\317\42\21\5\0D\14\247\205\31%\25\31?IJ\0E"
  "\14\247\205\31\7\251jI\252\365\0F\14\247\205\31\7\251jI\252+\0G\17\247\205Y\63\211\32U"
  "\251F\223\250\215\0H\13\247\205\31\62n\7\32o\2I\11\246\205\31&\241~\62J\15\247\205yD"
  "\251^D\22\221\210\4K\21\247\205\31\62\222D\211\66\244ID*\62\232\0L\11\247\205\31R\375\365"
  "\0M\15\247\205\31\262\312\241\22\241\361M\0N\15\247\205\31\62Z\311B\61\325\270\11O\13\247\205\71"
  "\25\31\223T\0P\15\247\205\31%\25\31\223\244$\325\12Q\27\270}YC\211H&\221Id\22"
  "\231D&\221\220$\302:@\0R\16\247\205\31\26\31\267CDIEF\23S\17\247\205\71\25\31U"
  "\134\226Ji\222\12\0T\11\246\205\31&\241\376\4U\13\247\205\31\62\376&Q\33\1V\20\247\205\31"
  "\62\66\211\222D$\221\15Wc\0W\21\247\205\31\62^\42\224\10%r\250Lb\21\0X\20\247\205"
  "\31\62\232Dm\32\216\316$j\64\1Y\15\250\204\31B\242D$\243\212\365\6Z\12\247\205\31WE"
  "\275J\17[\11\305~\31\67\375[\1\134\23\250\204\31r\200X\16\220\3\304r\200\34 \226\3\4]"
  "\11\304~\31$\375\223\1^\12H\264yR\232H\42\24_\7\30|\31\207\0`\7\64\326\31\62\5"
  "a\14w\205\71e\251\344\20\243I\14b\15\247\205\31RU\213\214\267C\4\0c\13w\205\71\25\31"
  "U\233\244\2d\13\247\205\271Z\16\61\336$\6e\15w\205\71\25\31\355@\225I*\0f\15\246\205"
  "Y#\211\216\62\232P\33\0g\22\247m\71\207\220D$\21\211H\342\212\214&\251\0h\13\247\205\31"
  "RU\213\214o\2i\13\246\205YB\71\204\250'\3j\16\325ny\352\200\231\336(\24\311\4\0k"
  "\17\247\205\31RM\22%\32M\42R\221\11l\11\246\205\31D\375\311\0m\20x\204\31\27\25\212\204"
  "\42\241H(\22\242\0n\12w\205\31\222%\32o\2o\14w\205Y\63\211\32\233Dm\4p\15\247"
  "m\31%\25\31'II\252\12q\15\247mY\25\21\215M\42\22U\65r\13w\205\31\222\321DU"
  "G\0s\14w\205\71\25\31\271L\223T\0t\14\227\205YR\231M\252\213l\2u\11w\205\31\62"
  "\276I\14v\16w\205\31\62\232DI\42\33Nc\0w\20x\204\31B\26\11EB\221\34&\42\11"
  "\0x\15w\205\31\62\211\332\64:\223\250\11y\22\247m\31\62\232DI\42\222\310\206CYD(\4"
  "z\11v\205\31F\231\216\6{\14\266\205Y\24\241\66\251P+\1|\7\302\31\37\6}\15\266\205"
  "\31S\241\326\221P\323\14\0~\12\70\274\71#\212\204\64\1\0\0\0";

uint8_t u8x8_gpio_and_delay_arm(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
  switch(msg)
  {
    case U8X8_MSG_GPIO_AND_DELAY_INIT:	// called once during init phase of u8g2/u8x8
			//HAL_Delay(100);
			//__NOP();
			HAL_Delay(1);		
      break;							// can be used to setup pins
    case U8X8_MSG_DELAY_NANO:
			__NOP();			// delay arg_int * 1 nano second
      break;    
    case U8X8_MSG_DELAY_100NANO:		// delay arg_int * 100 nano seconds
			__NOP();
      break;
    case U8X8_MSG_DELAY_10MICRO:		// delay arg_int * 10 micro seconds
			/*for (uint16_t n = 0; n < 320; n++)
			{
				__NOP();
			}*/
      break;
    case U8X8_MSG_DELAY_MILLI:			// delay arg_int * 1 milli second
			//HAL_Delay(arg_int);
      break;
    case U8X8_MSG_DELAY_I2C:				// arg_int is the I2C speed in 100KHz, e.g. 4 = 400 KHz
      break;							// arg_int=1: delay by 5us, arg_int = 4: delay by 1.25us
    //case U8X8_MSG_GPIO_D0:				// D0 or SPI clock pin: Output level in arg_int
    case U8X8_MSG_GPIO_SPI_CLOCK:
			if (arg_int) HAL_GPIO_WritePin(SPI_Port, SCK, GPIO_PIN_SET);
			else HAL_GPIO_WritePin(SPI_Port, SCK, GPIO_PIN_RESET);

      break;
    //case U8X8_MSG_GPIO_D1:				// D1 or SPI data pin: Output level in arg_int
    case U8X8_MSG_GPIO_SPI_DATA:
			if (arg_int) HAL_GPIO_WritePin(SPI_Port, MOSI, GPIO_PIN_SET);
			else HAL_GPIO_WritePin(SPI_Port, MOSI, GPIO_PIN_RESET);
      break;
    case U8X8_MSG_GPIO_D2:				// D2 pin: Output level in arg_int
      break;
    case U8X8_MSG_GPIO_D3:				// D3 pin: Output level in arg_int
      break;
    case U8X8_MSG_GPIO_D4:				// D4 pin: Output level in arg_int
      break;
    case U8X8_MSG_GPIO_D5:				// D5 pin: Output level in arg_int
      break;
    case U8X8_MSG_GPIO_D6:				// D6 pin: Output level in arg_int
      break;
    case U8X8_MSG_GPIO_D7:				// D7 pin: Output level in arg_int
      break;
    case U8X8_MSG_GPIO_E:				// E/WR pin: Output level in arg_int
      break;
    case U8X8_MSG_GPIO_CS:				// CS (chip select) pin: Output level in arg_int
			if (arg_int) HAL_GPIO_WritePin(CS_Port, CS, GPIO_PIN_SET);
			else HAL_GPIO_WritePin(CS_Port, CS, GPIO_PIN_RESET);
      break;
    case U8X8_MSG_GPIO_DC:				// DC (data/cmd, A0, register select) pin: Output level in arg_int
			if (arg_int) HAL_GPIO_WritePin(DC_Port, DC, GPIO_PIN_SET);
			else HAL_GPIO_WritePin(DC_Port, DC, GPIO_PIN_RESET);
      break;
    case U8X8_MSG_GPIO_RESET:			// Reset pin: Output level in arg_int
      break;
    case U8X8_MSG_GPIO_CS1:				// CS1 (chip select) pin: Output level in arg_int
      break;
    case U8X8_MSG_GPIO_CS2:				// CS2 (chip select) pin: Output level in arg_int
      break;
    case U8X8_MSG_GPIO_I2C_CLOCK:		// arg_int=0: Output low at I2C clock pin
      break;							// arg_int=1: Input dir with pullup high for I2C clock pin
    case U8X8_MSG_GPIO_I2C_DATA:			// arg_int=0: Output low at I2C data pin
      break;							// arg_int=1: Input dir with pullup high for I2C data pin
    case U8X8_MSG_GPIO_MENU_SELECT:
      u8x8_SetGPIOResult(u8x8, /* get menu select pin state */ 0);
      break;
    case U8X8_MSG_GPIO_MENU_NEXT:
      u8x8_SetGPIOResult(u8x8, /* get menu next pin state */ 0);
      break;
    case U8X8_MSG_GPIO_MENU_PREV:
      u8x8_SetGPIOResult(u8x8, /* get menu prev pin state */ 0);
      break;
    case U8X8_MSG_GPIO_MENU_HOME:
      u8x8_SetGPIOResult(u8x8, /* get menu home pin state */ 0);
      break;
    default:
      u8x8_SetGPIOResult(u8x8, 1);			// default return value
      break;
  }
  return 1;
}

void SPI_Out (uint8_t Data) 
{
	while(HAL_SPI_GetState(&SPI_HANDLER) == HAL_SPI_STATE_BUSY){};
	HAL_SPI_Transmit(&SPI_HANDLER, &Data, 1, 10000);
}

uint8_t u8x8_byte_arm_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr) {
	register uint8_t *ptr = arg_ptr;	
  switch(msg) {
    case U8X8_MSG_BYTE_SEND: //Send one or more bytes, located at arg_ptr, arg_int contains the number of bytes.
			if (arg_int == 0) control = 0xF8;
			else control = 0xFA;
			SPI_Out (control); 
				while( arg_int > 0 ) {
				//SPI_Out (*ptr);
				SPI_Out (*ptr & 0xF0);
				SPI_Out (*ptr << 4);
					*ptr++;
					arg_int--;
															}
      break;
    case U8X8_MSG_BYTE_INIT: //Send once during the init phase of the display.
			SPI_Out (0xF8);
			SPI_Out (arg_int & 0xF0);
			SPI_Out (arg_int << 4);
      break;
    case U8X8_MSG_BYTE_SET_DC: //Set the level of the data/command pin. arg_int contains the expected output level. Use u8x8_gpio_SetDC(u8x8, arg_int) to send a message to the GPIO procedure.
			u8x8_gpio_SetDC(u8x8, arg_int);	
      break;
    case U8X8_MSG_BYTE_START_TRANSFER: //Set the chip select line here. u8x8->display_info->chip_enable_level contains the expected level. Use u8x8_gpio_SetCS(u8x8, u8x8->display_info->chip_enable_level) to call the GPIO procedure.
			//HAL_SPI_MspInit(&SPI_HANDLER);	
			u8x8_gpio_SetCS(u8x8, u8x8->display_info->chip_enable_level);  
			u8x8->gpio_and_delay_cb(u8x8, U8X8_MSG_DELAY_NANO, u8x8->display_info->post_chip_enable_wait_ns, NULL);
      break;
    case U8X8_MSG_BYTE_END_TRANSFER: //Unselect the device. Use the CS level from here: u8x8->display_info->chip_disable_level. 
			//HAL_SPI_MspDeInit(&SPI_HANDLER);
			u8x8->gpio_and_delay_cb(u8x8, U8X8_MSG_DELAY_NANO, u8x8->display_info->pre_chip_disable_wait_ns, NULL);
      u8x8_gpio_SetCS(u8x8, u8x8->display_info->chip_disable_level);
      break;
    default:
      return 0;
  }  
  return 1;
}
