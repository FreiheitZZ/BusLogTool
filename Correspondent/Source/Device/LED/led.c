#include ".\led.h" 

//��ʼ��PF9��PF10Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{    	 
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure_1;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOFʱ��
	//GPIOF9,F10��ʼ������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;//LED0��LED1��ӦIO��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
	GPIO_SetBits(GPIOA,GPIO_Pin_8);//GPIOF9,F10���øߣ�����

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//ʹ��GPIOFʱ��
	//GPIOF9,F10��ʼ������
	GPIO_InitStructure_1.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_8 | GPIO_Pin_9;//LED0��LED1��ӦIO��
	GPIO_InitStructure_1.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
	GPIO_InitStructure_1.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure_1.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure_1.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOB, &GPIO_InitStructure_1);//��ʼ��GPIO
	GPIO_SetBits(GPIOB,GPIO_Pin_5 | GPIO_Pin_8 | GPIO_Pin_9);//GPIOF9,F10���øߣ�����

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//ʹ��GPIOFʱ��
	//GPIOF9,F10��ʼ������
	GPIO_InitStructure_1.GPIO_Pin = GPIO_Pin_13;//LED0��LED1��ӦIO��
	GPIO_InitStructure_1.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
	GPIO_InitStructure_1.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure_1.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure_1.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOC, &GPIO_InitStructure_1);//��ʼ��GPIO
	GPIO_SetBits(GPIOC,GPIO_Pin_13);//GPIOF9,F10���øߣ�����

}






