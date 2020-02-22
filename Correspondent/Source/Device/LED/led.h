#ifndef __LED_H
#define __LED_H
#include "..\..\Common\sys.h"

//LED端口定义
#define LED0 PCout(13)	// DS0
#define LED1 PAout(8)	// DS1	 
#define LED2 PBout(8)	// DS2
#define LED3 PBout(9)	// DS3	 
#define LED4 PBout(5)	// DS4

void LED_Init(void);//初始化		 				    
#endif
