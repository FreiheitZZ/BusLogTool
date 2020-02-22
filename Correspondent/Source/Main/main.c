#include "..\Common\sys.h"
#include "..\Common\delay.h"
#include "..\Common\malloc.h"
#include "FreeRTOS.h"
#include "task.h"

////////////////////////////////////////////////////////
extern	void	initialTask_Create(void);

int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//设置系统中断优先级分组4
	delay_init(84);					//初始化延时函数
	my_mem_init(SRAMIN);            //初始化内部内存池
	
	initialTask_Create();
    vTaskStartScheduler();          //开启任务调度
}

