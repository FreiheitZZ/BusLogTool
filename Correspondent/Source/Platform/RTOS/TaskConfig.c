#include "./TaskConfig.h"

////////////////////////////////////////////////
extern EventGroupHandle_t EventGroupHandler;

void TSK_Initial(void *pvParameters);
TaskHandle_t InitialTask_Handler;


void TSK_StandBy(void *pvParameters);
TaskHandle_t StandbyTask_Handler;

void TSK_USBReceive(void *pvParameters);
TaskHandle_t USBReceiveTask_Handler;

void TSK_USBSend(void *pvParameters);
TaskHandle_t USBSendTask_Handler;

void TSK_DAMReceiver(void *pvParameters);
TaskHandle_t DAMReceiverTask_Handler;

void TSK_DAMTransmitter(void *pvParameters);
TaskHandle_t DAMTransmitterTask_Handler;

/*********************************************************************
	funcname丗OS_createResources()
	contents丗OS帒尮偺惗惉傪峴偆
	堷    悢丗側偟
	栠 傝 抣丗側偟
	旛    峫丗
*********************************************************************/
void OS_createResources(void)
{
	unsigned char i;
	
    taskENTER_CRITICAL();           //进入临界区
    
	vTaskResume(DAMReceiverTask_Handler);
	
	for (i=STANDBY_TASK_NUM+1; i < TASK_NUM_MAX; i++) 
	{
		//创建任务
		xTaskCreate((TaskFunction_t )taskCfg[i].func,
					(const char*    )taskCfg[i].name,
					(uint16_t		)taskCfg[i].size,
					(void*			)taskCfg[i].para,
					(UBaseType_t    )taskCfg[i].prio,
					(TaskHandle_t*  )taskCfg[i].handler);
	}
    taskEXIT_CRITICAL();            //退出临界区

}

/*********************************************************************
	funcname丗OS_killResources()
	contents丗OS帒尮偺掆巭傪峴偆
	堷    悢丗側偟
	栠 傝 抣丗側偟
	旛    峫丗
*********************************************************************/
void OS_killResources(void)
{
	unsigned char i;
	
    taskENTER_CRITICAL();           //进入临界区
	for (i=STANDBY_TASK_NUM+1; i < TASK_NUM_MAX; i++) 
	{
		vTaskDelete(*taskCfg[i].handler); //删除任务
	}
    taskEXIT_CRITICAL();            //退出临界区

}



