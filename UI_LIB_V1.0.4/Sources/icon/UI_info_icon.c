#include "UI_info_icon.h"



const unsigned char BMP_info_1[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xFF,0x01,0x00,0x00,0x00,0x00,0xF0,0xFF,0xFF,0xFF,0xFF,0x1F,0x00,0x00,0xC0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x01,0xE0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x03,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x07,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x07,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x07,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x07,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x07,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x07,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x07,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x07,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x07,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x07,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x07,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x07,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x07,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x07,0xE0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x03,0xC0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0xF0,0xFF,0xFF,0xFF,0xFF,0x0F,0x00,0x00,0x00,0x00,0x00,0x80,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};/*"F:\BandAll\HB030\HB030_设备信息修改_9.22\图标\info_1.bmp",0*/ 
const unsigned char BMP_info_2[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0xC0,0xFF,0xFF,0xFF,0x01,0x00,0x00,0x00,0x00,0xC0,0x00,0x00,0x80,0x01,0x00,0x00,0x00,0x00,0xC0,0x00,0x00,0x80,0x01,0x00,0x00,0x00,0x00,0xC0,0x00,0x00,0x80,0x01,0x00,0x00,0x00,0x00,0xC0,0x00,0x00,0x80,0x01,0x00,0x00,0x00,0x00,0xC0,0x00,0x00,0x80,0x01,0x00,0x00,0x00,0x00,0xC0,0x00,0x00,0x80,0x01,0x00,0x00,0x00,0x00,0xC0,0x00,0x00,0x80,0x01,0x00,0x00,0x00,0x00,0xC0,0x00,0x00,0x80,0x01,0x00,0x00,0x00,0x00,0xC0,0x00,0x00,0x80,0x01,0x00,0x00,0x00,0x00,0xC0,0x00,0x00,0x80,0x01,0x00,0x00,0x00,0x00,0xC0,0x00,0x00,0x80,0x01,0x00,0x00,0x00,0x00,0xC0,0x00,0x00,0x80,0x01,0x00,0x00,0x00,0x00,0xC0,0x00,0x00,0x80,0x01,0x00,0x00,0x00,0x00,0xC0,0x00,0x00,0x80,0x01,0x00,0x00,0x00,0x00,0xC0,0x00,0x00,0x80,0x01,0x00,0x00,0x00,0x00,0xC0,0x00,0x00,0x80,0x01,0x00,0x00,0x00,0x00,0xC0,0x00,0x00,0x80,0x01,0x00,0x00,0x00,0x00,0xC0,0x00,0x00,0x80,0x01,0x00,0x00,0x00,0x00,0xC0,0x00,0x00,0x80,0x01,0x00,0x00,0x00,0x00,0xC0,0x00,0x00,0x80,0x01,0x00,0x00,0x00,0x00,0xC0,0xFF,0xFF,0xFF,0x01,0x00,0x00,0x00,0x00,0x80,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};/*"F:\BandAll\HB030\HB030_设备信息修改_9.22\图标\info_2.bmp",0*/
const unsigned char BMP_info_3[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x7F,0x00,0x00,0x00,0x00,0x00,0x80,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x80,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x80,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x80,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x80,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x80,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x80,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x80,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x80,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x80,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x80,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x80,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x80,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x80,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x80,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x80,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x80,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x80,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x80,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x80,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};/*"F:\BandAll\HB030\HB030_设备信息修改_9.22\图标\info_3.bmp",0*/ 

const unsigned char bmp_str_info[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFC,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0xFC,0x1F,0x18,0x00,0xF0,0x00,0x80,0x07,0x00,0x0C,0xFC,0x1F,0x00,0x00,0x00,0x00,0xFC,0x1F,0x84,0x00,0x84,0x00,0x84,0x00,0x84,0x00,0x00,0x00,0x00,0x00,0xF8,0x0F,0x04,0x10,0x04,0x10,0x04,0x10,0x04,0x10,0x04,0x10,0xF8,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};/*"F:\BandAll\HB030\单词\INFO.bmp",0*/ 




