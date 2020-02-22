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
	funcname�FOS_createResources()
	contents�FOS�����̐������s��
	��    ���F�Ȃ�
	�� �� �l�F�Ȃ�
	��    �l�F
*********************************************************************/
void OS_createResources(void)
{
	unsigned char i;
	
    taskENTER_CRITICAL();           //�����ٽ���
    
	vTaskResume(DAMReceiverTask_Handler);
	
	for (i=STANDBY_TASK_NUM+1; i < TASK_NUM_MAX; i++) 
	{
		//��������
		xTaskCreate((TaskFunction_t )taskCfg[i].func,
					(const char*    )taskCfg[i].name,
					(uint16_t		)taskCfg[i].size,
					(void*			)taskCfg[i].para,
					(UBaseType_t    )taskCfg[i].prio,
					(TaskHandle_t*  )taskCfg[i].handler);
	}
    taskEXIT_CRITICAL();            //�˳��ٽ���

}

/*********************************************************************
	funcname�FOS_killResources()
	contents�FOS�����̒�~���s��
	��    ���F�Ȃ�
	�� �� �l�F�Ȃ�
	��    �l�F
*********************************************************************/
void OS_killResources(void)
{
	unsigned char i;
	
    taskENTER_CRITICAL();           //�����ٽ���
	for (i=STANDBY_TASK_NUM+1; i < TASK_NUM_MAX; i++) 
	{
		vTaskDelete(*taskCfg[i].handler); //ɾ������
	}
    taskEXIT_CRITICAL();            //�˳��ٽ���

}



