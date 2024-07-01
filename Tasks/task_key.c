/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    key.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "task_key.h"
/* USER CODE BEGIN 0 */
void KEY_Scan(void);

	uint8_t key_a,key_b,key_c;
/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* function of KEY_SCAN                                                           */
/*----------------------------------------------------------------------------*/
void KEY_Scan(void)
{

	
	key_a = HAL_GPIO_ReadPin(GPIOB,KEY_A__Pin);
	key_b = HAL_GPIO_ReadPin(GPIOB,KEY_B__Pin);
	key_c = HAL_GPIO_ReadPin(GPIOB,KEY_CO_Pin);

	

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
