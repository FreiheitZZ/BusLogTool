#include "FreeRTOS.h"
#include "task.h"
#include "./Initial.h"


#include "..\..\Common\sys.h"
#include "..\..\Common\delay.h"
#include "..\..\Common\usart.h"
#include "..\..\Device\led\led.h"
#include "..\..\Device\timer\timer.h"
#include "..\..\Device\exti\exti.h"
#include "string.h"
#include "..\..\Common\malloc.h"

#include "limits.h"
#include "..\..\Common\ringbuffer.h"
#include "..\..\Driver\uart\uart.h"
#include "usb_defines.h"
#include "usb_core.h"
#include "usbd_desc.h"
#include "usbd_cdc_core.h"
#include "usbd_usr.h"

#include "usb_conf.h" 
#include "usbd_cdc_vcp.h" 

extern vu8 bDeviceState;		//USBá??ó ?é??
USB_OTG_CORE_HANDLE USB_OTG_dev;

extern struct taskDefine
{
	TaskFunction_t	func;		//任务函数
	const char*		name;		//任务名称
	uint16_t		size;		//任务堆栈大小
	void*			para;		//传递给任务函数的参数
	UBaseType_t		prio;		//任务优先级
	TaskHandle_t*	handler;	//任务句柄
};

extern enum TaskNum
{
	INITIAL_TASK_NUM,
	STANDBY_TASK_NUM,
	USBRECEIVE_TASK_NUM,
	USBSEND_TASK_NUM,
	TASK_NUM_MAX,
};

extern const struct taskDefine taskCfg[TASK_NUM_MAX];


void SYS_initReset(void);
void SYS_execResume(void);
void SYS_execSuspend(void);

static void (*const initResetCallFunc[])(void) = {
	{	SYS_initReset	},	/* System		*/
};

static void (*const execResumeCallFunc[])(void) = {
	{	SYS_execResume		},	/* System		*/
};

static void (*const execSuspendCallFunc[])(void) = {
	{	SYS_execSuspend		},	/* System		*/
};

static	unsigned char		s_aRxData_usart1[400];	/* 庴怣僶僢僼傽(儕儞僌僶僢僼傽)	*/
static	unsigned char		s_aRxData_usart2[400];	/* 庴怣僶僢僼傽(儕儞僌僶僢僼傽)	*/

extern unsigned char		s_EntryNo_usart1;
extern unsigned char		s_EntryNo_usart2;
extern TaskHandle_t InitialTask_Handler;


void initialTask_Create(void)
{
	//创建开始任务
	xTaskCreate((TaskFunction_t )taskCfg[INITIAL_TASK_NUM].func,
				(const char*	)taskCfg[INITIAL_TASK_NUM].name,
				(uint16_t		)taskCfg[INITIAL_TASK_NUM].size,
				(void*			)taskCfg[INITIAL_TASK_NUM].para,
				(UBaseType_t	)taskCfg[INITIAL_TASK_NUM].prio,
				(TaskHandle_t*	)taskCfg[INITIAL_TASK_NUM].handler);
}

//开始任务任务函数
void TSK_Initial(void *pvParameters)
{
    taskENTER_CRITICAL();           //进入临界区
	
	LED_Init();		        			//初始化LED端口
	EXTIX_Init();						//初始化外部中断
	uart_init(1, 115200);		//初始化串口波特率为115200
	uart_init(2, 115200);		//初始化串口波特率为115200
	USBD_Init(&USB_OTG_dev,USB_OTG_FS_CORE_ID,&USR_desc,&USBD_CDC_cb,&USR_cb);

	s_EntryNo_usart1 = RB_reqEntry(&s_aRxData_usart1[0], sizeof(s_aRxData_usart1));
	s_EntryNo_usart2 = RB_reqEntry(&s_aRxData_usart2[0], sizeof(s_aRxData_usart2));
	
	//创建设置事件位的任务
    xTaskCreate((TaskFunction_t )taskCfg[STANDBY_TASK_NUM].func,
                (const char*    )taskCfg[STANDBY_TASK_NUM].name,
                (uint16_t       )taskCfg[STANDBY_TASK_NUM].size,
                (void*          )taskCfg[STANDBY_TASK_NUM].para,
                (UBaseType_t    )taskCfg[STANDBY_TASK_NUM].prio,
                (TaskHandle_t*  )taskCfg[STANDBY_TASK_NUM].handler);	

    vTaskDelete(InitialTask_Handler); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
}


void INI_initReset(void)
{
	/*************************************************************
		帺摦曄悢掕媊
	*************************************************************/
	unsigned char	cnt;

	/*************************************************************
		帪寁愝掕
	*************************************************************/
	//PLT_setClockTimerMode();	/* 帪寁愝掕乮巄掕乯		*/

	/*************************************************************
		弶婜壔
	*************************************************************/
	for (cnt = 0 ; cnt < sizeof(initResetCallFunc) / sizeof(void *) ; cnt++){
		initResetCallFunc[cnt]();
	}
	
}

void INI_initResume(void)
{
	/*************************************************************
		帺摦曄悢掕媊
	*************************************************************/
	unsigned char	cnt;
	/*************************************************************
		弶婜壔
	*************************************************************/
	for (cnt = 0 ; cnt < sizeof(execResumeCallFunc) / sizeof(void *) ; cnt++){
		execResumeCallFunc[cnt]();
	}
}

void INI_initSuspend(void)
{
	/*************************************************************
		帺摦曄悢掕媊
	*************************************************************/
	unsigned char	cnt;
	/*************************************************************
		弶婜壔
	*************************************************************/
	for (cnt = 0 ; cnt < sizeof(execSuspendCallFunc) / sizeof(void *) ; cnt++){
		execSuspendCallFunc[cnt]();
	}
}

void SYS_initReset(void)
{}

void SYS_execResume(void)
{}

void SYS_execSuspend(void)
{}



