#include <string.h>				/* memcpy(),memset()etc */
#include "FreeRTOS.h"
#include "task.h"
#include "..\..\Device\led\led.h"

extern TaskHandle_t StandbyTask_Handler;

void TSK_StandBy(void *pvParameters)
{
	OS_createResources();
#if 0
	while(1)
	{
		LED0 = 0;
		delay_ms(200);
		UART_transmitData(1, "uart1");
		LED1 = 0;
		delay_ms(200);
		UART_transmitData(2, "uart2");
		LED2 = 0;
		delay_ms(200);
		LED3 = 0;
		delay_ms(200);
		LED4 = 0;
		delay_ms(200);
		LED0 = 1;
		LED1 = 1;
		LED2 = 1;
		LED3 = 1;
		LED4 = 1;
		delay_ms(500);
		usb_printf("USB connected."); 
	}
#endif
	vTaskDelete(StandbyTask_Handler); //删除开始任务
}


