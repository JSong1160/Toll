/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    log2usart.c
  * @brief   This file provides code for LOG to use USART1.
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "log2usart.h"

/* USER CODE BEGIN 0 */
int fputc(int ch, FILE *f);
/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure fpuc                                                              */
/*----------------------------------------------------------------------------*/
#include "stdio.h"
#ifdef __GNUC__
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(&huart1,(uint8_t *)&ch,1,0xFFFF);//阻塞方式打印,串口1
  return ch;
}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
