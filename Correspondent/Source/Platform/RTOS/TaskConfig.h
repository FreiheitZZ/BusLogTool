#ifndef TASK_CONFIG_H
#define TASK_CONFIG_H

#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"

////////////////////////////////////////////////
extern void TSK_Initial(void *pvParameters);
extern TaskHandle_t InitialTask_Handler;


extern void TSK_StandBy(void *pvParameters);
extern TaskHandle_t StandbyTask_Handler;

extern void TSK_USBReceive(void *pvParameters);
extern TaskHandle_t USBReceiveTask_Handler;

extern void TSK_USBSend(void *pvParameters);
extern TaskHandle_t USBSendTask_Handler;

extern void TSK_DAMReceiver(void *pvParameters);
extern TaskHandle_t DAMReceiverTask_Handler;

extern void TSK_DAMTransmitter(void *pvParameters);
extern TaskHandle_t DAMTransmitterTask_Handler;

void	OS_startTickTimer	(void);
void	OS_stopTickTimer	(void);


////////////////////////////////////////////////

struct taskDefine
{
	TaskFunction_t	func;		//������
	const char*		name;		//��������
	uint16_t		size;		//�����ջ��С
	void*			para;		//���ݸ��������Ĳ���
	UBaseType_t		prio;		//�������ȼ�
	TaskHandle_t*	handler;	//������
};

enum TaskNum
{
	INITIAL_TASK_NUM = 0,
	STANDBY_TASK_NUM,
	USBRECEIVE_TASK_NUM,
	USBSEND_TASK_NUM,
	DAMRECEIVER_TASK_NUM,
	DAMTRANSMITTER_TASK_NUM,
	TASK_NUM_MAX,
};

const struct taskDefine taskCfg[TASK_NUM_MAX] = 
{
	{TSK_Initial,		"Initial_task",		256,	NULL,	1,	&InitialTask_Handler	},
	{TSK_StandBy,		"Standby_task",		256,	NULL,	1,	&StandbyTask_Handler	},
	{TSK_USBReceive,	"USBReceive_task", 	256,	NULL,	2,	&USBReceiveTask_Handler	},
	{TSK_USBSend,		"USBSend_task",		256,	NULL,	3,	&USBSendTask_Handler	},
	{TSK_DAMReceiver,	"DAMReceiver_task",	512,	NULL,	2,	&DAMReceiverTask_Handler},
	{TSK_DAMTransmitter,"DAMTransmitter_task",512,	NULL,	3,	&DAMTransmitterTask_Handler	},
};

////////////////////////////////////////////////


#endif

