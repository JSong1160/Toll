#include "../inc/lcd_init.h"


void LCD_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
//    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_SET);

    /*Configure GPIO pins : PA4 PA5 PA6 PA7 */
    GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}


/******************************************************************************
      ����˵����LCD��������д�뺯��
      ������ݣ�dat  Ҫд��Ĵ�������
      ����ֵ��  ��
******************************************************************************/
void LCD_Writ_Bus(u8 dat)
{
    u8 i;
    LCD_CS_Clr();
    for(i=0;i<8;i++)
    {
        LCD_SCLK_Clr();
        if(dat&0x80)
        {
            LCD_MOSI_Set();
        }
        else
        {
            LCD_MOSI_Clr();
        }
        LCD_SCLK_Set();
        dat<<=1;
    }
    LCD_CS_Set();
}


/******************************************************************************
      ����˵����LCDд������
      ������ݣ�dat д�������
      ����ֵ��  ��
******************************************************************************/
void LCD_WR_DATA8(u8 dat)
{
    LCD_Writ_Bus(dat);
}


/******************************************************************************
      ����˵����LCDд������
      ������ݣ�dat д�������
      ����ֵ��  ��
******************************************************************************/
void LCD_WR_DATA(u16 dat)
{
    LCD_Writ_Bus(dat>>8);
    LCD_Writ_Bus(dat);
}


/******************************************************************************
      ����˵����LCDд������
      ������ݣ�dat д�������
      ����ֵ��  ��
******************************************************************************/
void LCD_WR_REG(u8 dat)
{
    LCD_DC_Clr();//д����
    LCD_Writ_Bus(dat);
    LCD_DC_Set();//д����
}


/******************************************************************************
      ����˵����������ʼ�ͽ�����ַ
      ������ݣ�x1,x2 �����е���ʼ�ͽ�����ַ
                y1,y2 �����е���ʼ�ͽ�����ַ
      ����ֵ��  ��
******************************************************************************/
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2)
{
    if(USE_HORIZONTAL==0)
    {
        LCD_WR_REG(0x2a);//�е�ַ����
        LCD_WR_DATA(x1+34);
        LCD_WR_DATA(x2+34);
        LCD_WR_REG(0x2b);//�е�ַ����
        LCD_WR_DATA(y1);
        LCD_WR_DATA(y2);
        LCD_WR_REG(0x2c);//������д
    }
    else if(USE_HORIZONTAL==1)
    {
        LCD_WR_REG(0x2a);//�е�ַ����
        LCD_WR_DATA(x1+34);
        LCD_WR_DATA(x2+34);
        LCD_WR_REG(0x2b);//�е�ַ����
        LCD_WR_DATA(y1);
        LCD_WR_DATA(y2);
        LCD_WR_REG(0x2c);//������д
    }
    else if(USE_HORIZONTAL==2)
    {
        LCD_WR_REG(0x2a);//�е�ַ����
        LCD_WR_DATA(x1);
        LCD_WR_DATA(x2);
        LCD_WR_REG(0x2b);//�е�ַ����
        LCD_WR_DATA(y1+34);
        LCD_WR_DATA(y2+34);
        LCD_WR_REG(0x2c);//������д
    }
    else
    {
        LCD_WR_REG(0x2a);//�е�ַ����
        LCD_WR_DATA(x1);
        LCD_WR_DATA(x2);
        LCD_WR_REG(0x2b);//�е�ַ����
        LCD_WR_DATA(y1+34);
        LCD_WR_DATA(y2+34);
        LCD_WR_REG(0x2c);//������д
    }
}
void LCD_Init(void)
{
    //��ʼ��GPIO
    LCD_GPIO_Init();

    LCD_WR_REG(0x11);
    LCD_WR_REG(0x36);
    if(USE_HORIZONTAL==0)LCD_WR_DATA8(0x00);
    else if(USE_HORIZONTAL==1)LCD_WR_DATA8(0xC0);
    else if(USE_HORIZONTAL==2)LCD_WR_DATA8(0x70);
    else LCD_WR_DATA8(0xA0);

    LCD_WR_REG(0x3A);
    LCD_WR_DATA8(0x05);

    LCD_WR_REG(0xB2);
    LCD_WR_DATA8(0x0C);
    LCD_WR_DATA8(0x0C);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x33);
    LCD_WR_DATA8(0x33);

    LCD_WR_REG(0xB7);
    LCD_WR_DATA8(0x35);

    LCD_WR_REG(0xBB);
    LCD_WR_DATA8(0x35);

    LCD_WR_REG(0xC0);
    LCD_WR_DATA8(0x2C);

    LCD_WR_REG(0xC2);
    LCD_WR_DATA8(0x01);

    LCD_WR_REG(0xC3);
    LCD_WR_DATA8(0x13);

    LCD_WR_REG(0xC4);
    LCD_WR_DATA8(0x20);

    LCD_WR_REG(0xC6);
    LCD_WR_DATA8(0x0F);

    LCD_WR_REG(0xD0);
    LCD_WR_DATA8(0xA4);
    LCD_WR_DATA8(0xA1);

    LCD_WR_REG(0xD6);
    LCD_WR_DATA8(0xA1);

    LCD_WR_REG(0xE0);
    LCD_WR_DATA8(0xF0);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x04);
    LCD_WR_DATA8(0x04);
    LCD_WR_DATA8(0x04);
    LCD_WR_DATA8(0x05);
    LCD_WR_DATA8(0x29);
    LCD_WR_DATA8(0x33);
    LCD_WR_DATA8(0x3E);
    LCD_WR_DATA8(0x38);
    LCD_WR_DATA8(0x12);
    LCD_WR_DATA8(0x12);
    LCD_WR_DATA8(0x28);
    LCD_WR_DATA8(0x30);

    LCD_WR_REG(0xE1);
    LCD_WR_DATA8(0xF0);
    LCD_WR_DATA8(0x07);
    LCD_WR_DATA8(0x0A);
    LCD_WR_DATA8(0x0D);
    LCD_WR_DATA8(0x0B);
    LCD_WR_DATA8(0x07);
    LCD_WR_DATA8(0x28);
    LCD_WR_DATA8(0x33);
    LCD_WR_DATA8(0x3E);
    LCD_WR_DATA8(0x36);
    LCD_WR_DATA8(0x14);
    LCD_WR_DATA8(0x14);
    LCD_WR_DATA8(0x29);
    LCD_WR_DATA8(0x32);

 	LCD_WR_REG(0x2A);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x22);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0xCD);
	LCD_WR_DATA8(0x2B);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x01);
	LCD_WR_DATA8(0x3F);
	LCD_WR_REG(0x2C);
    LCD_WR_REG(0x21);

    LCD_WR_REG(0x11);
    LCD_WR_REG(0x29);
}









