#include "..\Common\sys.h"
#include "..\Common\delay.h"
#include "..\Common\malloc.h"
#include "FreeRTOS.h"
#include "task.h"

////////////////////////////////////////////////////////
extern	void	initialTask_Create(void);

int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//����ϵͳ�ж����ȼ�����4
	delay_init(84);					//��ʼ����ʱ����
	my_mem_init(SRAMIN);            //��ʼ���ڲ��ڴ��
	
	initialTask_Create();
    vTaskStartScheduler();          //�����������
}

