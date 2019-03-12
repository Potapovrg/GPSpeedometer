#include "u8g2_arm.h"
#include "u8g2.h"

void u8g2_Setup_st7920_s_128x64_f(u8g2_t *u8g2, const u8g2_cb_t *rotation, u8x8_msg_cb byte_cb, u8x8_msg_cb gpio_and_delay_cb)
{
  uint8_t tile_buf_height;
  uint8_t *buf;
  u8g2_SetupDisplay(u8g2, u8x8_d_st7920_128x64, u8x8_cad_st7920_spi, byte_cb, gpio_and_delay_cb);
  buf = u8g2_m_st7920_16_f(&tile_buf_height);
  u8g2_SetupBuffer(u8g2, buf, tile_buf_height, u8g2_ll_hvline_horizontal_right_lsb, rotation);
}

uint8_t *u8g2_m_st7920_16_f(uint8_t *page_cnt)
{
  static uint8_t buf[1024];
  *page_cnt = 8;
  return buf;
}

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
	
const uint8_t u8g2_font_fub20_tr[2516] U8G2_FONT_SECTION("u8g2_font_fub20_tr") = 
  "_\0\4\4\5\5\4\6\6\33\35\0\371\24\373\24\374\3s\6\374\11\273 \6\0 \210\2!\11\204"
  "\62\270\302\17\26\63\42\17\12)\353\2\21<\71dh\204 \21\0#/\221&\70\337\230\201\202\4\216"
  "\31\70f\340\230QN^\215\31(H\340\230\201c\6\216\21\346\344\325\230\201\202\4\216\31\70f\340\230"
  "\201b\306\1$-\16g\7_\330r\211\226\224\10AdL\20\64A\320\4\63\21\356`\262\204\7C"
  "\224\13\202&\10\232 I\202\220`\243\12i\350\310\0%F\231&\270OI\201\347\306\221 &n\320"
  "\250q\243\306\14\34\65F\344\250!#G\15\21;f\310\330$bJ\231\31rx\310\230\261#F\11"
  "\35\62j\244\230Q\3\307\214\32\67h\20\271Q$\310\215;\70\260\14\0&-\223&X\223\341\224D"
  "\10\22\42G\210\34\241\221DH\246=l\370\20\31\22d\210\24\241\21\211\61\244\316\20\63C\216T\231"
  "S\317\316\24'\12\4\61\273\302\211\371\2\0(\25\6+\247\316\220\61C(\31\63\204\376\233i\210\220"
  "\231h\0)\31\6/\267\302\30\62\323\20\241f\32\42\364d\314\20\232\214\31Bd\14\0*\37km"
  "\32OT#\6\215\30%B\314\210\21\17\202\14\21#B\324\210A#F\205\11\3\0+\20\20\66\250"
  "\237p\371\356\301\3q\302\345;\0,\16\346$\207\12\221\61C\306L\62\6\0-\10\207d\231\302\203"
  "\6.\10\204,\230\302\203\0/\25\250\352\307\326\254DM%j*Q\263\22\65\225\250Y\11\3\60$"
  "\216&\10SATD\310\20\32\63l\4\261\21\304F\20\303\317F\20\33\62l\10!\62DH\241+"
  "\5\0\61\17\210.\370\22\21\23\17F\30!D\377\37\62\35\216&\10W\271DK\312\20!E\202\24"
  "Q\222DI\222,Xw\5K>x\300\0\63\36\215&\370R\261\64+\312\220 E\222BR\307\12"
  "\36\245\22\25\252\64D\326\244\62\4\0\64!\216&\10_A\353\216!\33A\212\4\251!\204\210\20\32"
  "C\233ADF\21y\360\200!Q\232\0\65\33\215&\370\2\13.H\322E\231%&J\220\42IK"
  "T\210\210\254Ie\10\0\66\42\215&\370\222\61DJ\10\221 Db$\25eF\34\61Q\21*\134"
  "\221\30E\202\14\31\65\311\12\1\67\32\215&\370\302\7))$I\220$\205$\11\222$X\220`A"
  "\222\4\213\1\70%\216&\10\317\61\65k\310\224 E\202\24\11RD\310\20JvL\15!\22\304F"
  "\20\303,\21\21\66\252\16\1\71\42\215&\370R\61Dj\250 \65\202\24\256H\220)\201b\210\221\221"
  "T\216 D\204\14\21E\350\12\1:\13\304\61\230\302\203\360 \37\4;\21&f\207\12\335CHd"
  "\10\221\61C\306\214\1<\31\320u\250\273\330\222\224\222$;z<\0\362\0\210\223\7@\234<\200\0"
  "=\15\360t\251\303\7\342a\363\340\201\0>\31\320u\250\203\360\342\344\1\20'\17\200\370\350\241$\211"
  "\222$J\70<\0?\33\215&\370\216\261\64DJ\220\32\23\214$\311\221\4i\70t\366\220\221\244\12"
  "\0@I:\347\306\353y\20m\37\10<u\254l\241\322\204\250 B\315\22JJ\230AC\210\14\232"
  "Qd\220\220\42\203\204\24\31$\244\310 !E\6\315(\62C\306\220)B\315\203\60EN \242]"
  "yp\6\3;g\17B\35\0A(\223\42\70_\361\342\206/\36A\224\4Q\42#\311\20$C\220"
  "\14\71R\304H\21s\364\321H\42$\211\220$A\226\0B$\217*(\303\42\66MH\225 F\202"
  "\30\11bCH\21a\243\252\11\61\22\344F\220\303\31\11\27M\26\1C\37\221&\70\327IU\215H"
  "\25!Gd \11\322\364\303\22\3\211\20+C\250P+\225\306\0D\35\220*\70C:FmH\25"
  "!V\202\34\11\202\370w$\210\225 U\244\15\243t\0E\22\215*\30\303\7-\351\362\301\203\226\364"
  "\362\301\203\4F\20\215*\10\303\7-\351\222\5\27$\351/\1G!\222&H\237\311e\215J\25)"
  "\70\204$\211\341\64\343)R\22$I\24$b\214\314#wh\0H\17\220*H\3A\374\341\203\17"
  "\26\342\37\22I\10\204*\210\302?(J\22\216&\30+\375?E\206lD!\42k\224\35\2K,"
  "\217*(\3\61\22\244J\20*B\246\14ED\12\221(\225\14\35\272d$J\221(E\244\20\231\62"
  "\204\310\20*B\252\4\261d\5L\15\215*\10\3I\372\377\313\7\17\22M\66\225*\230\203\311v\336"
  "\275z\20\212\305\250\21(\6\221@A\206\4\12\62$\220\214\31\202\204\4\21$$\210\240\31\61\6\315"
  "\31\64g\20\25BT\10Q!D\205\10N$\221*X\203\71u\313\226\261b\205\202\20\12BH\310"
  " !\203\206\10\32\42\210H \42\201\212\263\355\324\31O\37\222&H\233Qu\254\12\225!H\204 "
  "\11\242\370S\22\4\211\20$S\250\24;\245\306\0P\25\216*\30\203\42&-H%\303\253\7#\230"
  "(\42J?\5Q.\224&h\233a\205\355\12\225\42H\210 \31\242D\210\22!J\204(\21\242D"
  "\210\22!J\204(\31\202\204\10\222*T\356\201\240\7\301\34R\36\217*(\303\242&.\210\245\303\335"
  "\10R%\330\260qA\214\4\61\22\344F\220\303\303\1S!\220&(\227AU\214\250!F\204\30\21"
  "\302\205\217&Tz\230\64B\204CH\25i\264\320\24\0T\15\220&(\303\17\206\21\246\377?\3U"
  "\26\221*X\3I\374\71\202 \21rDJ\21j\245\322\30\0V,\223\42HCQ\22DI\220"
  ",B\220\14A\62\305\12\21#E\214T\241b\204\310\21\42W\204$\21\222DH\246\305\330\264\351r"
  "\0WK\233\42\270C\261*\210\25#B\254\30\21R\247\210\220:E\206\320\210A\24\215\30D\15\11"
  "\62\204\310\220 Cj\314\314\210\214\31B\214\4\31\22\304H\220!An\304\250\21\3G\214\32\61\360"
  "\324\301S'\313\25-W\264\134)\0X+\221&\70C\271\22\344\210\224\42T\210\24\31b%\10\222"
  " y\324pY\263'\21\22!G\244\24!R\324\20+A\220\4I\2Y\33\220&\30\3\71eD"
  "\210\21)D\67\304\210\20#A\20\341Q\263\204\351\317\0Z\23\217&\30\207OKVZ\262J\223\265"
  "\64Y\323\7\37[\15&\353\246\302\203 \364\377\302\0\134\33\251\346\307\302\70q\303\306\211\33\66\235"
  "\270a\343\304\15\33'\335\260q\342\206\15]\15'\353\266\202\33\372\377\277y\60\0^&->\270["
  "\330\241!\202\206\10)B`\230pb\204\211\21\26*\224D\242\4\205\13#NH\310\20\42I\216\15"
  "_\10N \347\302\203\6`\13\245 |\302\230!c\306\10a\32\314%\370\216\251$DJ\14\42H"
  "D\305\203\60\210\60Ja\342\304\220\42\3b\35\216*\30\3Q\372\242\20\23\23E\12\221 E\202\30"
  "\236\215(D\302\10\21&\24\1c\26\314%\350\216\251$\224\14\32A\10!\35!\32B\15*\63\0"
  "d\33\216&\10+}c\202\10\213\42&\10%\303g$\10\225(q\344\4!\42\4e\34\315%\370"
  "R\261\64D\212\14\42A\210\4\213\7\42)\42\62\210\10\221\62\251\14\1f\23\212&\270\222\231#E"
  "\202\20\243(E\32b\364?\2g!n\346\6\217\11\42,\212\230 \224\14\237\221\30U\242\210\221\23"
  "\204\210\20%AjH\65\312\14\1h\22\215*\10\3I\372\242\14\13\23\25\241\302E\0i\13\204"
  "&h\302\203\200\17>Xj\16%\357\226\6\335\222\240\377/\36\214\0k\34\214*\370\2A\372\10\15"
  "\11\42T\220I\203\10#\22dH\24\241\15\11\62\211\10l\10\204*x\302?(m)\326)\230\3"
  "\221\62eX\240\60\201\242\4)B$H\221BE\12\25)T\244P\221BE\12\25)T\244P\221"
  "BE\1n\20\315)\10\3\211\62,L\224 \205\377\25\1o\27\316%\10\223\261DE\310\20\42A"
  "\14\237\221 D\244\32e\206\0p\36n\352\26\3\21BLL\24)D\202\330\10bxE\202\24\11"
  "+\230\220(D\224N\1q\32n\346\6\23\21\42,J\234 \224\14\237\221 T\242\210\21\66&\210"
  "\322\3r\15\311)\270\2\211\7mH\321\277\2s\31\314%\350\216\241\64$J\220!A\322X*\204"
  "\211\20%!\222\312\14\0t\22J&\310Z\270a\324<(C\214\376\254\230\251\2u\17\315)\10\3"
  ")\374\217\224\230`R\204\0v\35\316!\370\2\61\22\244H\220\42\62\210\14mF\15!E\202\24\211"
  "q\327\231\254\10\0w\62\327!x\3\251R$F\225\32B\250\20\21\62g\310L\61\206\222\21c\6"
  "\221\240\21\11\42#H\215\30\63b\330\231cg\316\225*X\252`\251B\0x\34\315%\370\2)\22"
  "d\210\24\31D\202\324\61\203\345\314\235J\64\204\14\25\204R\21y!n\342\366B)\22\244H\220\42"
  "B\206nF\221 E\202\330\210q\27\226,J\222(\225D\211\1z\22\313%\330\302\203s\304J\25"
  "\243\263R\305\310=\70{\34jk\326\32!\63\206\210\321\263q\303\10\225\32W\254\30\271q\304\350\231"
  ")S\5|\10\242s\246\302\17\32}\31jk\346\2\61S\345\210\321\357\310\25#U\210\24\61\372Q"
  "!C\304\0~\14n`\351\312\221\21,\6\25\1\0\0\0";

const uint8_t u8g2_font_logisoso22_tr[2249] U8G2_FONT_SECTION("u8g2_font_logisoso22_tr") = 
  "`\0\4\4\5\5\4\6\6\26!\0\372\26\372\26\0\2\374\5\324\10\260 \6\0 \350\2!\14\303"
  ".\230\302\17\22\205(\1\0\42\17\206\260\374\302\210\22\42\202\210\10\22\2\0#\62\313*\370\316\220\61"
  "C\306\14\31\63d\314\210A#\6\215\30\361\340\301\220\21\203F\14y\360`\304\220\61C\306\214\30\64"
  "b\320\210\61C\306\14\31\3\0$\35\213k\367\322\300\351J\235IA\346\224\205\364\345\204\246L\235!"
  "\221\346T\271\201\23\1%&\313*\370\306 $#$\31Qd\206\343\6N\67p\240\300\351\6\16\24"
  "Bd\204\211\21B\212\10)\202\210\4\0&%\353*\370\22\251CH\306\220\30\64b\340\310\201\343\310"
  "\225\62\65b\320\210\21&F\30\311\6M\32\22i\322 '\12\203\254\214\202\211 !\0(\30\306\62"
  "\350\216\30\42c\206\214\31#f\376\321\230\61d\306\220\11\2\0)\31\306\66\370\206\230Ac\6\215\231"
  "H\320\230\371d\314$c\206\214\12\3\0*\24J)\354\222@Q\42\244Pb\310\210\12Y\11\24\4"
  "\0+\16)-\371\316\260i\36\260\31\66\15\0,\12\203\354\227F\10\23!\0-\10i\354\371\302\3"
  "\6.\11c,\230F\210\22\0/\32\312*\350\336\314\306M\66n\262q\303\210\215\33\66n\262q\223"
  "\215\33\7\0\60\25\313*\370N\251\63)\310\234\262\377WgH\244\71U\6\0\61\15\306\66\370\316$"
  "$\36\210\231\377?\62\33\313*\370N\251\63)\310\234\262\21\271\11\307M\70n\34\271\351\310=x\60"
  "\0\63\32\313\352\367\302\7\343\310MGnBr\5I\16\234\27\242\216\20Ic\6\0\64\36\313*\370"
  "\316\300\31\12\234P\244\300\11\205\14\22\62f\310\230!c\36<\30\65p\66\0\65\34\313*\370\302\7"
  "\6g\210&\211\12\62\247L\15\234\320\224\251\63$\322\234*\3\0\66\34\313*\370N\251\63)\310\234"
  "\62\70!\232$*\310\234\262WgH\244\71U\6\0\67\32\313*\370\302\7\246\14\35\32\70\35\271\201"
  "\323\15\234\335\300\351\310\15\34\5\0\70\36\313*\370N\251\63)\310\234\262\325\31\22i\316\244 \63b"
  "\224]\235!\221\346T\31\0\71\36\313*\370N\251\63)\310\234\262WgH(ICb\340@S\246"
  "\316\220Hs\252\14\0:\14\243\355\230F\210\362\0C\224\0;\16\303\255\230F\210\362\0C\230\10\1"
  "\0<\21\247\61\351\226\240\61\223\220\31$jV\204\206\5=\12\12\351\350\302\367\240\36<>\23\247\61"
  "\351B\60Q\204\250\32%h\10%\203D\5\3?\33\353*\370N\251\63)\310\234\62\65p\272q\304"
  "\250\33\70\337\203\12\71P\24\0@It\253v_i\205\315\212\221\42Hf,\221AFF\14:c"
  "\6\215\231!c\314\14\31cf\310\30\63C\306\230\31\62\306\314\220\61f\206\214\61\63d\214\231!c"
  "\314\264\30\304d\20\211\62\343\301\214\7R\36\204C\246j\0A&\313*\350\322\300q\264+V\312\252"
  "\21\242F\14\22\62f\310\230!c\306\210I\222B\305\240\21\243D\214\62\65\0B\42\313*\370\302\241"
  "$*\6\215\30%b\224E#T$I\62\206\304\240\21\243\354\350\14\11\25I\16\1C\27\313*\370"
  "N\251\63)\310\234\262p\376+SgH\244\71U\6\0D\23\313*\370\2\232$*\6\235\262\377\217"
  "\134$A\3\0E\22\313*\370\302\7\6\347a\222L\6\316\207\17\36\14F\20\313*\370\302\7\6\347"
  "a\222L\6\316?\4G\27\313*\370N\251\63)\310\234\62\70opeWgH(I\203\0H\17"
  "\313*\370\302(\373\253\7\17R\331\277\32I\10\303.\230\302\37\30J\22\313*\370\342\374\377\320\224\251"
  "\63$\322\234*\3\0K)\313*\370\302(C#\306\220\30\63d\232\21dF\14:d\252X\315L"
  "\35\32\61h\4\231!c&\31Cb\320\210Q\3L\15\313*\370\302\300\371\377\17\37<\30M\36\313"
  "*\370\302(Sg\260I\241\305\203\7+F\230\30ab\204\221 F\202\230\262W\3N\33\313*\370"
  "\302(S\207\16\241\301&I&&F\230\30a$\67\30\335\312\324\0O\25\313*\370N\251\63)\310"
  "\234\262\377WgH\244\71U\6\0P\27\313*\370\302\241$*\6\215\30e\217F\250Hrh\340\374"
  "!\0Q\24\313*\370N\251\63)\310\234\262\377WgH\244I\203\0R&\313*\370\302\241$*\6"
  "\215\30e\217F\250H\202f\310\230I\306\14\31\63d\320\210A#\6\215\30%b\324\0S\30\313*"
  "\370N\251\63)\310\234\262\220\376\320\224\251\63$\322\234*\3\0T\16\313*\370\302\7\203\6\316\377"
  "\4\0U\21\313*\370\302(\373\377WgH\244\71U\6\0V'\313*\350\302(\253D\14\32\61h"
  "\310\230!c\206\214\21\63d\220\220A#\6\215\30\64b\320\10auFpF\0W\27\312*\350\302"
  " \373\213 &D\230\20aB\304\203?\20\202\11\1X+\313*\350\302(C#\6\15\31\63d\232"
  "!\203F\14\32\61\310\224\261\252\254\32\61h\304\230!c\306\210\231b\320\210A#F\15Y\42\313*"
  "\350\302(C#\6\15\21Cd\232!cF\214\262\252X\71r\3\307\15\234n\340t\3\7\2Z\35"
  "\313*\370\302\7\3\307\15\34\67p\334\300q\3\307\15\34\67p\334\300q\3\37<\30[\15\307\62\370"
  "\302\203D\363\377\243\7\6\134\31\313*\350\302\300\221\3G\16\234r\340\224\3\247\34\70\345\300\201\4\247"
  "\34]\15\306\66\370\302\203\61\363\377\233\7\6^\13\210\354\355\12\31##\214\14_\10N\240\347\302\203"
  "\6`\12\205t\355\302\30Ab\6a!-&\370\22\71T\210\246\31\64f\320\320Q\210\322(!\64"
  "d\324\220QCF\215a\301\246\310\0b\26\353*\370\302\300y\210&\211\12\62\247\354\257\316\270H\202"
  "\6\0c\26+*\370N\251\63)\310\234\262p^\231:C\42\315\251\62\0d\24\353*\370\342|\203"
  "$\205\233S\366WgH(I\203\0e\31+*\370N\251\63)\310\234\262\352\301\203\204S\5!C"
  "\42\315\251\62\0f\25\353*\370\26\61Ch\206\214\31\70W*\64\32\70\377\25\0g\37\353\252\366\16"
  "\222\24nN\331j\304\230!i\16\225\32\70\322P\12\25\243\254r\221\346\10\0h\22\353*\370\302\300"
  "y\210&\211\12\62\247\354\377j\0i\21\345*\230\202\230\61\341\301\14\231\377'%\210\14j\24\251\257"
  "\366\232\270q\341!\32\66\377\377\314\314\222\63d\0k&\353*\370\302\300\371\312\320\210A#\306\14\31"
  "Bd\232\21dF\14\62u\10\15\32\22D\210L\64b\320\210Q\3l\16\346*\230\302\230\371\377\337"
  "\230(B\0m,\63&h\3\232\62)\216<\30A\246\314\251Q\246F\231\32ej\224\251Q\246F"
  "\231\32ej\224\251Q\246F\231\32ej\224\251\11n\17+*\370\2\232$*\310\234\262\377\253\1o"
  "\24+*\370N\251\63)\310\234\262\277:C\42\315\251\62\0p\26\353\252\366\2\232$*\310\234\262\277"
  ":\343\42\11\232\201\363\20\0q\24\353\252\366\16\222\24nN\331_\235!\241$\15\302\371\0r\15)"
  "&\270\302\7A\214\315\377\31\0s\30**\330\16\241\63(\306\34\62t\316\224u\207\254!\201\344\24"
  "\31\0t\21\347&\230\306\240y\363\300\304\240\371\257\212\224!u\17+*\370\302(\373\277:CBI"
  "\32\4v$+*\350\202\60S\246D\14\32\61h\210\240!c\206\214\21\63d\314\220AB\6\215\30"
  "\64B\224e\325\0w\67\63*x\203\260Q\246F\31\42e\210\224\241BB\4\225\31\62\246\314\220!"
  "f\206L!f\310\24C\4\11\31\61\321\210\31\31\31\61\310\214!\63\305\312\24+S\6\0x!+"
  "*\350\302(CC\306\14\231h\304 c\305\10\216#W\312\324\210\61C\306L\61h\304\250\1y)"
  "\353\252\346\306\240\21\203F\214\31\62f\214\230I\306\14\31\63b\320\210Q\42FYU\254\34\355\6\216"
  "\12\62\350\220\61b\0z\30+*\370\302\7\343\210\221\33G\214\334\70b\344\306\21#\367\340\301\0{"
  "\27Gs\347\226\30J\310\14\232O\310\14\32Dj\320|D\15)\1|\10\203{\367\302?H}\26"
  "Gs\347\202\250A\24\315\257&\32\63\321|C\204\314 Q\0~\13\214\244\351J\310%KL\14"
  "\6\0 \350\2\0\0\0";

const uint8_t u8g2_font_logisoso30_tr[2883] U8G2_FONT_SECTION("u8g2_font_logisoso30_tr") = 
  "`\0\4\4\5\6\5\6\6\35,\0\370\36\370\36\0\3\322\7{\13* \6\0\200\340\14!\15\304"
  "\243 \13\377\201I\21(D\0\42\17\250\260\71\15C\234\214\20\42$\214\10\0#=\317\223\340\134D"
  "H\21!E\204\20\31BDH\21!E\204\24\21RD\10\25!\361\340\67DH\21!D\206\310\203"
  "\237PT\204\20\221BDH\21!E\204\24\21RD\10\221!\4\0$*\317\224\334ldij."
  "\325\232&eJ\224J\207-a\262\325\32\265m\265\204\311\242C\227\252D\231\42mV\245$KW\0"
  "%\71\317\223\340,\244H\30\32\201f\304\220!$\220\214\61B\210\14\331\261\224\222%;\226\332\261\224"
  "\222%;\226\232Ad\312\20\71Bd\304\10\62#F\220\71A\250\4\261!\0&\62\357\223\340\134\5"
  "S-ZS\11)\42\244\210\220%[\226l\321\222&\317\241#A\214\4\61\22D\220\220@B\2\15"
  "G\33\235 T\244\15\243e%\10'\14\244\240\371\12#\216\10\11\2\0(\33\310\263 M\302\6\225"
  "\241\210\320 \212\6\321\377\212\20U\204\10\25\242J\10\0)\37\310\263\340,\241\10\25\242\212\20)B"
  "TME\210>\32D\33Bd\312\220)\64L\20\0*\35\255\231\365\134C\207\205\31\23\202\304\24M"
  "\222\25K\362@\304$a\306\4\33:\12\0+\17\213\241\346L\344h\363\340\201#r\264\1,\14\304"
  "\240\336\32\42P\210\211\2\0-\10\213\240\352\14\37\70.\12\204\240\340\32\42P\210\0/#\316\233\340"
  "\254$\211RI\224J\242T\22%Y\222(\311\222DI\226$J\222(\225D\251$J)\0\60\32"
  "\317\223\340\134\5S\255iB\212\4\71\374\377\337\221 E\244\315\252\204\245\0\61\21\310\263\340L\324T"
  "\361\340\201\30B\364\377\377\0\62$\317\223\340\134\5S\255iB\212\4\71\274#!\216hQ\242%\213"
  "\22-JiQJ\213\22-Y\364\301\17\63!\317\223\337\14Z\262(\321\242\224\26%j\362 R"
  "\263\204\311\322/\206\221\60b\204\221\62D\0\64!\317\223\340\134d\307\322v,m\307\322v,%\244"
  "\210\220\32C\210\14!\62\204\36\374\216,=\2\65!\317\223\340\14@\226\276(\305\246\211\213R$"
  "\310\241#Ko\321\241#A\212H\233U\11K\1\66$\317\223\340\134\5S\255iB\212\4\71l\351"
  "\242\24\233&.\314\224(\225\16G\202\24\221\66\253\22\226\2\67\42\317\223\340\14@,\63\22\304"
  "\210VJ\226hQ\262\224\26%KiQ\262D+%K\264Rr\0\70&\317\223\340\134\5S\255i"
  "B\212\4\71\374\254D\231\42m\26\255iB\212\4\71\374\216\4)\42mV%,\5\0\71%\317\223"
  "\340\134\5S\255iB\212\4\71\374\263\22eL\70i\303\252\4Yj\321aG\202\24\221\66\253\22\226"
  "\2:\17$\242\344\32\42P\210\207P\4\12\21\0;\20d\242\342\32\42P\210\207P\4\12\61Q\0"
  "<\27I\252\345\214\301F\21*C\246\42R\342\206\225\252\31\261q\2\3=\15n\231%\15?X\17"
  "\361\203\17\26>\30I\252\345\14\1\207\221*F\254T)bS\221\251\15\251a\342\2\2?!\357\223"
  "\340\134\5S\255iB\212\4\71\354\310RZ\262J\203&+%K\277\207X\60Y\302\342\0@l\233"
  "\224\330\257\347\201\64~\20\364\301\300s\306\314\226*]\246\24\222\42\204\324\220(\263\206\4\241Eh\212"
  "\24BC\210\20\32B\204\320\20\42\204\206\20!\64\204\10\241!D\10\15!Bh\10\21BC\210\20"
  "\32B\204\320\20\42\204\246\14!D\17F\20z\60\204\320\203\60\304\312\220*\17\260<\300\362\340\316\3"
  "{@\364\201\330\7\301\33\1A\61\317\223\340ld\211\326\324\244\301\33\242\33A\214\4\61\22\304\210\14"
  "#\62l\14!\62\204\310\20\42\64h\21\33&MH\21!\66\204\30\211q\330\21B\61\317\223\340\14"
  "\311\26\261iB\252\4\61\22\304H\220\33An\4\61\22\304H\20\62\321\204\15\233&\244J\20#A"
  "\16?#A\252D\23\66\213\222\1C\34\317\223\340\134\5S\255iB\212\4\71\334\322\377w\330\221 "
  "E\244\315\252\204\245\0D\30\317\223\340\14\252\330\64qA\214\4\71\374\377?#\341\242\11\33U\0E"
  "\23\317\223\340\14@\226\376\226\15o\310\322\337>\370\1F\22\317\223\340\14@\226\376\226\15o\310"
  "\322\377-\0G\35\317\223\340\134\5S\255iB\212\4\71\334\322G{\207\337\221 U\302I\33V%"
  "\10H\21\317\223\340\14\344\360\377\356\301\17\320\341\377\35\1I\10\304\243 \13\377\7J\25\317\223\340\274"
  "\364\377\377\26\35v$H\21i\263*a)\0K<\317\223\340\14\304\222\221 U\202P\21Bd\310"
  "\224\241\210H!\22\245H\20K\206\356\340A\223&\17\36D\227\214\4\61\22\245\210\220\42C\210L\31"
  "Bd\10\25!U\202\30\11b\5L\16\317\223\340\14d\351\377\377\337>\370\1M(\317\223\340\14\344"
  "\320\245\322j\15\67-\134<\370\301\212\22(J\240(\201d\10\222!H\206\240\11\203&\14:\374\35"
  "\1N%\317\223\340\14\344\320%\313L\225\252E\33\261a\323\4\5\21\24D\220\220@B\2I\33\216"
  "v\245Y\356\320\21O\32\317\223\340\134\5S\255iB\212\4\71\374\377\337\221 E\244\315\252\204\245\0"
  "P\36\317\223\340\14\311\26\261iB\310\4\61\22\344\360\63\22\244J\64a\263(\31Y\372\337\2Q\32"
  "\317\223\340\134\5S\255iB\212\4\71\374\377\337\221 E\244\15#V%\10R\64\317\223\340\14\311\26"
  "\261iB\310\4\61\22\344\360\63\22\244J\64a\263h\21\31B\204\6QC\210\14\251\61\244\210\220\42"
  "B\212\10\61\22\304H\20#A\216\0S$\317\223\340\134\5S\255iB\212\4\71\334\22&[\255Q"
  "\333VK\230,:\354H\220\42\322fU\302R\0T\16\317\223\340\14F\226\376\377\377\25\0U\24"
  "\317\223\340\14\344\360\377\377\357H\220\42\322fU\302R\0V\65\317\223\340\14\344\320\221\30G\202\30\11"
  "bCH\21!Ef\24\31Bd\10\221!\64\210\14\251\61\244\210\220\42B\212\310\60\22\344F\220\303"
  "\335I{J\226*\0W\36\315\233\340\14\244\360?\11\202$\10\222 (F\240\30\201b\4\212\7\377"
  "\5O\324\250)X\71\317\223\340\14\344H\20#A\212\10)\62\243\310\20\42C\21\31RDH\221 "
  "F\202\34\272\203\367\20\31\11b$\210\21!D\206\20\31B\224\220\42B\212\10\261!\304\320\21Y\60"
  "\317\223\340\14\344H\214#A\212\10)\42\204\312PD\206\20\21RD\210\221 \206\16\341A\223\226\222"
  "%J\226R\262\224\222%Z\224,Q\262\0Z#\317\223\340\14Z\224,Q\262D\311\22%K\224"
  ",Q\262D\311\22%K\224,Q\262D\213>\370\1[\17\311\253\340\14\37\250\242\377\377W\17\36\30"
  "\134 \316\233\340\14D\211\26\245\264(\265D\251%J-Qj\211\22-JiQJ\213RK\224\0"
  "]\17\310\263\340\14\37\10\242\377\377G\17\36\30^\16\253\240\377<\245\316\220 B\4\15\1_\10s"
  "\200\336\14?``\15\307\260\375\14\204\10\215\32Dh\0a*\361\222`]&\225\261bT\15\61\62"
  "\304\310\20#M\331\242\66\236\24#B\216\10\71\42\344\210\224*\363 \304\203 \217\16\11b\34\357\223"
  "\340\14d\351/J\261i\342\242\24\11r\370\227\212\204\213&lH\224\2c\33\357\222\340\134\5S"
  "\255iB\212\4\71\334\322\357\260#A\212H\233U\11K\1d\33\357\223\340\274\364W%\310\60i\341"
  "\202T:\374\277#A\252\204\223\66\254J\20e\36\357\222\340\134\5S\255iR\210D\251t\270{\360"
  "\3\264\264\23C\212H\233U\11K\1f\31\357\223\340|%\317\245ZD\206\20\31Bd\351]\223\236"
  "\221\245\377\357\0g)\357\223\330\134j\230\264pQ\246D\251t\270KU\242L\221\66\253R\241#K"
  "m\262\65MZ\220\303\335\3\22mV\245\1h\25\357\223\340\14d\351/J\261i\342\242\24\11r\370"
  "\377\357\10i\24\346\233\340\32b\210\220\21\17\230\10\375\377'&\212\220\31j\30\353\244\330\214\2\311\21"
  "\24\17;\372\377\377;\64h^\244\71U\6\0k\63\357\223\340\14d\351\357\220\221 U\202\24\21B"
  "E\10\221\241\210\14!\42\244H\224\42A,\63U\252L\20\62A\250\14\231JH\21!U\202\30\11"
  "r\4l\20\350\223 \13\204\350\377\377?Bq\304L\1m;\372\222\240\17$\212\225b\222\346A\222"
  "\7*J\35JW\14\35\71t\344\320\221CG\16\35\71t\344\320\221CG\16\35\71t\344\320\221C"
  "G\16\35\71t\344\320\221CG\16\35\5n\23\357\222\340\14$J\261i\342\242\24\11r\370\377\357\10"
  "o\31\357\222\340\134\5S\255iB\212\4\71\374\277#A\212H\233U\11K\1p\35\357\223\330\14$"
  "J\261i\342\242\24\11r\370\227\212\204\213&lH\224\42K\277\5q\33\357\223\330\134%\310\60i"
  "\341\202T:\374\277#A\252\204\223\66\254J\220\245?r\21\354\222 \14$\36|@$\15B\372\377"
  "C\0s\37\355\222`L\305\20\251YQ&\25.K\42K\225\12eIT\250\322\224X\262&Y!"
  "\0t\25\352\213 +\304\350G\17\36(!F\377\237\241\71d\252\0u\23\357\222\340\14\344\360\377\337"
  "\221 U\302I\33V%\10v\63\357\222\340\14\344\320\221\30G\202\30\11bCH\21!Ef\24\31"
  "Bd\10\15\42C\210\14\251\61\244\210\220\42\62\214\4\61\22\344F\220Cw\360JC\0wP\373\222"
  "\340\17\344\10\242\243\202\134\61\42\343\212\21!V\214\10)cDH\31\33C\352\20\241Q\207(:D"
  "\15\42jH\14\32E\206\4\21bcH\20!Fd\10e$\210PF\202\314\220q$\310 \34A"
  "\6\341!\204\207\20\236\62y\312\24\0x,\357\222\340\14\344H\20#A\212\14!\62T\21!E\202"
  "\34\272\223&\313\22-j\360 \62\22\304\210\20\42C\210\22RD\210\241#y\65\357\223\330,\303\210"
  "\220\42B\212\10)\42\204\10\15\242\206\20\31Bd\10\221\31\66\204\30\11b$\210\221 Fb\340\35"
  "\32\255S\262\344\302\20K\225\356dA\0z\30\357\222\340\14Z\262\322\222\225\226\254\224h\311\242D"
  "K\26}\360\3{\37j\254\334|\303H\25\62S\212\30\375\25\251B\245\4\26+F\216\30\375Y\61"
  "S\305\310\15|\11\304\304\34\15\377\37\10}\36j\254\34\15\2\211\225\62F\254\30\375Y\15E\25\252"
  "\212\30\375\252\24!C\245\210\11\4~\16\260\220\352\14d\314\70\371\206\324\10\0\6\0\200\340\14\0"
  "\0\0";

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

uint8_t u8x8_gpio_and_delay_arm(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
	switch(msg)
	{
	  case U8X8_MSG_GPIO_AND_DELAY_INIT:
    HAL_Delay(100);
    break;
		case U8X8_MSG_DELAY_MILLI:
		HAL_Delay(arg_int);
		break;
	case U8X8_MSG_DELAY_NANO:
		__NOP();
	break;
	}
	
	
  return 1;
}

uint8_t u8x8_byte_arm_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
  switch(msg)
  {
    case U8X8_MSG_BYTE_SEND:

		HAL_SPI_Transmit(&hspi2, (uint8_t *) arg_ptr, arg_int, 10000);
      break;
    case U8X8_MSG_BYTE_START_TRANSFER:
      HAL_GPIO_WritePin(CS_Port, CS, GPIO_PIN_SET);
      __nop(); // 21 ns
      break;
    case U8X8_MSG_BYTE_END_TRANSFER:
      __nop(); // 21 ns
      HAL_GPIO_WritePin(CS_Port, CS, GPIO_PIN_RESET);
      break;
    default:
      return 0;
  }
  return 1;
}

