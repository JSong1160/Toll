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
#include "usart.h"
/* USER CODE BEGIN 0 */
void KEY_Scan(void);
uint8_t Button_GetState(uint16_t pin);
uint8_t Button_Debounce(uint16_t pin);
uint8_t KEY_Value[3] = {0};

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* function of KEY_SCAN                                                       */
/*----------------------------------------------------------------------------*/
void KEY_Scan(void)
{
	uint8_t button1State = Button_Debounce(KEY_A__Pin);
	uint8_t button2State = Button_Debounce(KEY_B__Pin);
	uint8_t button3State = Button_Debounce(KEY_CO_Pin);
  KEY_Value[0] = button1State;
	KEY_Value[1] = button2State;
	KEY_Value[2] = button3State;
	//以下内容替换成消息队列进行数据传递(LCD_Display Done 之后)
	if (button1State) // 按键1被按下时执行的代码
	{
			HAL_UART_Transmit(&huart1, KEY_Value, 1, 2000);//KEY_Value = 1;
	} 

	if (button2State) // 按键2被按下时执行的代码
	{
			HAL_UART_Transmit(&huart1, KEY_Value, 1, 2000);//KEY_Value = 1;
	} 

	if (button3State) // 按键3被按下时执行的代码
	{
			HAL_UART_Transmit(&huart1, KEY_Value, 1, 2000);//KEY_Value = 1;
	} 
	HAL_Delay(300);
}


// 获取按键状态，返回1表示按键按下，返回0表示按键松开
uint8_t Button_GetState(uint16_t pin) {
    return HAL_GPIO_ReadPin(BUTTON_PORT, pin) == GPIO_PIN_RESET ? 0 : 1; 
}


// 按键消抖函数
uint8_t Button_Debounce(uint16_t pin) {
    static uint8_t buttonState[3] = {0};  // 按键当前状态
    static uint8_t lastButtonState[3] = {0};  // 按键上一次的状态
    static uint32_t lastDebounceTime[3] = {0};  // 上一次消抖的时间

    uint8_t index = 0;
    if (pin == KEY_A__Pin) index = 0;
    else if (pin == KEY_B__Pin) index = 1;
    else if (pin == KEY_CO_Pin) index = 2;

    uint8_t currentState = Button_GetState(pin);
    uint32_t currentTime = HAL_GetTick();  // 获取当前时间（毫秒）

    // 如果按键状态发生了变化，更新消抖计时
    if (currentState != lastButtonState[index]) 
		{
        lastDebounceTime[index] = currentTime;
    }

    // 只有当按键状态稳定超过消抖延迟时间时，才更新按键状态
    if ((currentTime - lastDebounceTime[index]) > DEBOUNCE_DELAY)			
		{
        if (currentState != buttonState[index]) 
				{
            buttonState[index] = currentState;
        }
    }

    lastButtonState[index] = currentState;

    return buttonState[index];
}
/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
