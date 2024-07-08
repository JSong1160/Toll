#ifndef __LCD_INIT_H
#define __LCD_INIT_H

#include "gpio.h"

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t

#define USE_HORIZONTAL 2  //设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏


#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 172
#define LCD_H 320

#else
#define LCD_W 320
#define LCD_H 172
#define LCD_W_CharNum 40
#endif


#define soft_spi 1
//PA4 -> NSS(CS) PA5 -> SCK(SCL) PA6 -> DC PA7 -> MOSI(SDA)
//-----------------LCD端口定义----------------
//SCL=SCLK
#define LCD_SCLK_Clr() GPIOA->BSRR |= (1 << (5 + 16))
#define LCD_SCLK_Set() GPIOA->BSRR |= (1 << 5)
//SDA=MOSI   √
#define LCD_MOSI_Clr() GPIOA->BSRR |= (1 << (7 + 16))
#define LCD_MOSI_Set() GPIOA->BSRR |= (1 << 7)
//DC
#define LCD_DC_Clr()   GPIOA->BSRR |= (1 << (6 + 16))
#define LCD_DC_Set()   GPIOA->BSRR |= (1 << 6)
//CS  -> NSS
#define LCD_CS_Clr()   GPIOA->BSRR |= (1 << (4 + 16))
#define LCD_CS_Set()   GPIOA->BSRR |= (1 << 4)




void LCD_GPIO_Init(void);//初始化GPIO
void LCD_Writ_Bus(u8 dat);//模拟SPI时序
void LCD_WR_DATA8(u8 dat);//写入一个字节
void LCD_WR_DATA(u16 dat);//写入两个字节
void LCD_WR_REG(u8 dat);//写入一个指令
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2);//设置坐标函数
void LCD_Init(void);//LCD初始化
#endif





