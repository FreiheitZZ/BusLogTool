#include ".\exti.h"
#include "..\..\Common\delay.h" 
#include "FreeRTOS.h"
#include "task.h"

//�ⲿ�жϳ�ʼ������
//��ʼ��PE4Ϊ�ж�����.
void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);//PE4 ���ӵ��ж���4
	
	/* ����EXTI_Line4 */
	EXTI_InitStructure.EXTI_Line =  EXTI_Line4;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		//�ж��¼�
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;				//�ж���ʹ��
	EXTI_Init(&EXTI_InitStructure);							//����
 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;		//�ⲿ�ж�4
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x06;//��ռ���ȼ�6
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;	//�����ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);							//����	   
}

//�ⲿ�ж�4�������
void EXTI4_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line4);//���LINE4�ϵ��жϱ�־λ  
}
