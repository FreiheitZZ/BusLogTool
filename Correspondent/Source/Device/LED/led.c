#include ".\led.h" 

//初始化PF9和PF10为输出口.并使能这两个口的时钟		    
//LED IO初始化
void LED_Init(void)
{    	 
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure_1;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOF时钟
	//GPIOF9,F10初始化设置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;//LED0和LED1对应IO口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
	GPIO_SetBits(GPIOA,GPIO_Pin_8);//GPIOF9,F10设置高，灯灭

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能GPIOF时钟
	//GPIOF9,F10初始化设置
	GPIO_InitStructure_1.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_8 | GPIO_Pin_9;//LED0和LED1对应IO口
	GPIO_InitStructure_1.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
	GPIO_InitStructure_1.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure_1.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure_1.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOB, &GPIO_InitStructure_1);//初始化GPIO
	GPIO_SetBits(GPIOB,GPIO_Pin_5 | GPIO_Pin_8 | GPIO_Pin_9);//GPIOF9,F10设置高，灯灭

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//使能GPIOF时钟
	//GPIOF9,F10初始化设置
	GPIO_InitStructure_1.GPIO_Pin = GPIO_Pin_13;//LED0和LED1对应IO口
	GPIO_InitStructure_1.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
	GPIO_InitStructure_1.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure_1.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure_1.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOC, &GPIO_InitStructure_1);//初始化GPIO
	GPIO_SetBits(GPIOC,GPIO_Pin_13);//GPIOF9,F10设置高，灯灭

}






