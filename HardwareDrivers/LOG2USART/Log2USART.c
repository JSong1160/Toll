/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    key.c
  * @brief   This file provides code for LOG to use USART.
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "log2usart.h"

/* USER CODE BEGIN 0 */
int fputc(int ch, FILE *f);
/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0)//循环发送,直到发送完毕   
    USART1->DR = (uint8_t) ch;      
	return ch;
}


/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
