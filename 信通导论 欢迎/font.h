#include <U8glib.h>//使用OLED需要包含这个头文件
#define INTERVAL_LCD 20
#define setFont_V u8g.setFont(u8g_font_7x13)
unsigned long lcd_time = millis();
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE); //设置OLED型号
static unsigned char u1[] U8G_PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00,
  0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x0E, 0x00,
  0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x1F, 0xC7, 0x03, 0xF8, 0x1F, 0xFB, 0x0F,
  0x00, 0x9C, 0x8F, 0x07, 0x00, 0x8C, 0xC1, 0x01, 0x30, 0xCE, 0xC0, 0x00, 0x60, 0x0E, 0x0F, 0x00,
  0xC0, 0x0F, 0x0E, 0x00, 0x80, 0x07, 0x0E, 0x00, 0x80, 0x07, 0x0E, 0x00, 0x00, 0x0F, 0x0E, 0x00,
  0x80, 0x1F, 0x1F, 0x00, 0x80, 0x1D, 0x1F, 0x00, 0xC0, 0x1D, 0x33, 0x00, 0xE0, 0x98, 0x73, 0x00,
  0x70, 0x80, 0xE1, 0x00, 0x38, 0xC0, 0xE1, 0x01, 0x0C, 0xE0, 0xC0, 0x07, 0x00, 0x30, 0xC0, 0x1F,
  0x00, 0x1C, 0x80, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*"欢",0*/
};
static unsigned char u2[] U8G_PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x1E, 0x00, 0xC0, 0x03, 0x0F, 0x00, 0x80, 0x87, 0x03, 0x00,
  0x00, 0xC7, 0x81, 0x0F, 0x00, 0xF8, 0xF8, 0x0E, 0x00, 0x70, 0x38, 0x0E, 0x00, 0xE0, 0x38, 0x0E,
  0x00, 0xE0, 0x30, 0x06, 0x80, 0xE3, 0x30, 0x06, 0xE0, 0xE7, 0x36, 0x06, 0xF0, 0xE3, 0xF3, 0x07,
  0x80, 0xE1, 0xB3, 0x07, 0x80, 0xE1, 0x39, 0x03, 0x80, 0xF1, 0x38, 0x00, 0x80, 0xF3, 0x38, 0x00,
  0x00, 0x63, 0x38, 0x00, 0x00, 0x03, 0x38, 0x00, 0xF0, 0x03, 0x38, 0x00, 0x7C, 0x1F, 0x38, 0x00,
  0x00, 0xF8, 0x00, 0x00, 0x00, 0xE0, 0x07, 0x00, 0x00, 0x00, 0xFF, 0x7F, 0x00, 0x00, 0xFC, 0x3F,
  0x00, 0x00, 0xF0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*"迎",0*/
};
static unsigned char u3[] U8G_PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00,
  0x00, 0xC0, 0x03, 0x00, 0x00, 0x80, 0x03, 0x00, 0x00, 0x80, 0xE3, 0x00, 0x00, 0x80, 0xE3, 0x01,
  0x00, 0x80, 0xF3, 0x01, 0x00, 0x8E, 0x73, 0x00, 0x00, 0x9E, 0x3B, 0x00, 0x00, 0x9C, 0x0F, 0x00,
  0x00, 0x98, 0x07, 0x00, 0x00, 0x80, 0xC3, 0x01, 0x00, 0x80, 0xFF, 0x03, 0x00, 0xFC, 0x1F, 0x00,
  0xE0, 0x3F, 0x07, 0x00, 0x00, 0x70, 0x0E, 0x00, 0x00, 0x70, 0x06, 0x00, 0x00, 0x78, 0x06, 0x00,
  0x00, 0x38, 0x06, 0x00, 0x00, 0x1C, 0x06, 0x00, 0x00, 0x1E, 0x06, 0x00, 0x00, 0x0E, 0x06, 0x30,
  0x00, 0x07, 0x06, 0x30, 0x80, 0x03, 0x06, 0x70, 0xC0, 0x01, 0x0E, 0x78, 0x60, 0x00, 0x3E, 0x7E,
  0x38, 0x00, 0xFC, 0x3F, 0x00, 0x00, 0xF0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*"光",0*/
};
static unsigned char u4[] U8G_PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x0E, 0x00, 0x00, 0x0F, 0x1E, 0x00, 0x00, 0x1E, 0x1E, 0x00, 0x00, 0x0E, 0x0E, 0x00,
  0x00, 0x0E, 0x06, 0x00, 0x00, 0x0E, 0xC7, 0x0F, 0xF0, 0x0E, 0xFF, 0x07, 0xF0, 0x8E, 0x03, 0x00,
  0x60, 0x8E, 0x01, 0x00, 0x60, 0xCE, 0x1C, 0x00, 0x60, 0xEE, 0x78, 0x00, 0x60, 0x3E, 0xF0, 0x00,
  0x60, 0x0E, 0xE0, 0x00, 0x60, 0x0E, 0x00, 0x07, 0x70, 0x0E, 0xF0, 0x0F, 0x70, 0xEE, 0x3F, 0x1E,
  0x70, 0xCE, 0x39, 0x0E, 0x60, 0xCE, 0x31, 0x0E, 0x00, 0xCE, 0x31, 0x06, 0x00, 0xCE, 0x31, 0x07,
  0x00, 0xCE, 0x31, 0x07, 0x00, 0x8E, 0xF1, 0x07, 0x00, 0x8E, 0xFF, 0x01, 0x00, 0x8E, 0x01, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*"临",0*/
};//显示“欢迎光临”字样
