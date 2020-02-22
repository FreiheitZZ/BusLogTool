#include "../../../Common/Common.h"		/* Common Information	*/
#include "../../../Platform/Platform.h"		/* Platform Information	*/

#include "./IICSTM32F407.h"
#include "stm32f4xx_i2c.c"
private void	IICP_nopLoop(unsigned short);		/* 短いウェイト用	*/

/*********************************************************************
	funcname:	IICP_execResume
	contents:	Resume処理
	引    数:	なし
	返    値:	なし
	備    考:	なし
*********************************************************************/
package void
IICP_execResume(unsigned char ch)
{
	I2C_InitTypeDef		I2C_InitStructure;
	GPIO_InitTypeDef	GPIO_InitStructure;

	switch (ch){
		case F407_IIC_CH1:
			if(F407_IIC_CH1_PORT == F407_IIC_CH1_PORT_PB_6_7)
			{
				RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);
				RCC_APB2PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
				
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
				GPIO_Init(GPIOB, &GPIO_InitStructure);

				I2C_InitStructure.I2C_Mode=I2C_Mode_I2C;
				I2C_InitStructure.I2C_DutyCycle=I2C_DutyCycle_2;
				I2C_InitStructure.I2C_Ack=I2C_Ack_Enable;
				I2C_InitStructure.I2C_AcknowledgedAddress=I2C_AcknowledgedAddress_7bit;
				I2C_InitStructure.I2C_ClockSpeed=100000;
				I2C_Init(I2C1,&I2C_InitStructure);
				I2C_Cmd(I2C1,ENABLE);
			}
			else if(F407_IIC_CH1_PORT == F407_IIC_CH1_PORT_PB_8_9)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
				GPIO_Init(GPIOB, &GPIO_InitStructure);
				GPIO_SetBits(GPIOB,GPIO_Pin_8 | GPIO_Pin_9);
			}
			else{;}
			break;
		case F407_IIC_CH2:
			if(F407_IIC_CH2_PORT == F407_IIC_CH2_PORT_PB_10_11)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
		
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
				GPIO_Init(GPIOB, &GPIO_InitStructure);
				GPIO_SetBits(GPIOB,GPIO_Pin_10 | GPIO_Pin_11);
			}
			else if(F407_IIC_CH2_PORT == F407_IIC_CH2_PORT_PF_0_1)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
		
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
				GPIO_Init(GPIOF, &GPIO_InitStructure);
				GPIO_SetBits(GPIOF,GPIO_Pin_0 | GPIO_Pin_1);
			}
			else if(F407_IIC_CH2_PORT == F407_IIC_CH2_PORT_PH_4_5)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
		
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
				GPIO_Init(GPIOH, &GPIO_InitStructure);
				GPIO_SetBits(GPIOH,GPIO_Pin_4 | GPIO_Pin_5);
			}
			else{;}
			break;
		case F407_IIC_CH3:
			if(F407_IIC_CH3_PORT == F407_IIC_CH3_PORT_PA_8_PC_9)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
				GPIO_Init(GPIOA, &GPIO_InitStructure);
				GPIO_SetBits(GPIOA,GPIO_Pin_8);
				
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
		
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
				GPIO_Init(GPIOC, &GPIO_InitStructure);
				GPIO_SetBits(GPIOC,GPIO_Pin_9);
			}
			else if(F407_IIC_CH3_PORT == F407_IIC_CH3_PORT_PH_7_8)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
		
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
				GPIO_Init(GPIOH, &GPIO_InitStructure);
				GPIO_SetBits(GPIOH,GPIO_Pin_7 | GPIO_Pin_8);
			}
			else{;}
			break;
	}
}

/*********************************************************************
	funcname:	IICP_execSuspend
	contents:	Suspend処理
	引    数:	なし
	返    値:	なし
	備    考:	なし
*********************************************************************/
package void
IICP_execSuspend(unsigned char ch)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	switch (ch){
		case F407_IIC_CH1:
			if(F407_IIC_CH1_PORT == F407_IIC_CH1_PORT_PB_6_7)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
				GPIO_Init(GPIOB, &GPIO_InitStructure);
				GPIO_ResetBits(GPIOB,GPIO_Pin_6 | GPIO_Pin_8);
			}
			else if(F407_IIC_CH1_PORT == F407_IIC_CH1_PORT_PB_8_9)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
				GPIO_Init(GPIOB, &GPIO_InitStructure);
				GPIO_ResetBits(GPIOB,GPIO_Pin_8 | GPIO_Pin_9);
			}
			else{;}
			break;
		case F407_IIC_CH2:
			if(F407_IIC_CH2_PORT == F407_IIC_CH2_PORT_PB_10_11)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
		
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
				GPIO_Init(GPIOB, &GPIO_InitStructure);
				GPIO_ResetBits(GPIOB,GPIO_Pin_10 | GPIO_Pin_11);
			}
			else if(F407_IIC_CH2_PORT == F407_IIC_CH2_PORT_PF_0_1)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
		
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
				GPIO_Init(GPIOF, &GPIO_InitStructure);
				GPIO_ResetBits(GPIOF,GPIO_Pin_0 | GPIO_Pin_1);
			}
			else if(F407_IIC_CH2_PORT == F407_IIC_CH2_PORT_PH_4_5)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
		
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
				GPIO_Init(GPIOH, &GPIO_InitStructure);
				GPIO_ResetBits(GPIOH,GPIO_Pin_4 | GPIO_Pin_5);
			}
			else{;}
			break;
		case F407_IIC_CH3:
			if(F407_IIC_CH3_PORT == F407_IIC_CH3_PORT_PA_8_PC_9)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
				GPIO_Init(GPIOA, &GPIO_InitStructure);
				GPIO_ResetBits(GPIOA,GPIO_Pin_8);
				
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
		
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
				GPIO_Init(GPIOC, &GPIO_InitStructure);
				GPIO_ResetBits(GPIOC,GPIO_Pin_9);
			}
			else if(F407_IIC_CH3_PORT == F407_IIC_CH3_PORT_PH_7_8)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
		
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
				GPIO_Init(GPIOH, &GPIO_InitStructure);
				GPIO_ResetBits(GPIOH,GPIO_Pin_7 | GPIO_Pin_8);
			}
			else{;}
			break;
	}
}

/*********************************************************************
	funcname:	IICP_enable
	contents:	IICコントローラ動作を許可する
	引    数:	なし
	返    値:	なし
	備    考:	なし
*********************************************************************/
package void
IICP_enable(unsigned char ch, unsigned char mode)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	switch (ch){
		case F407_IIC_CH1:
			if(F407_IIC_CH1_PORT == F407_IIC_CH1_PORT_PB_6_7)
			{
				if(mode == SDA_IN)
				{
					GPIOB->MODER &= ~(3<<(7*2));
					GPIOB->MODER |=  (0<<(7*2));
				}
				else if(mode == SDA_OUT)
				{
					GPIOB->MODER &= ~(3<<(7*2));
					GPIOB->MODER |=  (1<<(7*2));
					PBout(7) = 1;		//IIC1_SDA
					PBout(6) = 1;		//IIC1_SCL
					delay_us(4);
					PBout(7) = 0;		//IIC1_SDA
					delay_us(4);
					PBout(6) = 0;		//IIC1_SCL
				}
				else{;}
			}
			else if(F407_IIC_CH1_PORT == F407_IIC_CH1_PORT_PB_8_9)
			{
				if(mode == SDA_IN)
				{
					GPIOB->MODER &= ~(3<<(9*2));
					GPIOB->MODER |=  (0<<(9*2));
				}
				else if(mode == SDA_OUT)
				{
					GPIOB->MODER &= ~(3<<(9*2));
					GPIOB->MODER |=  (1<<(9*2));
				}
				else{;}
			}
			else{;}
			break;
		case F407_IIC_CH2:
			if(F407_IIC_CH2_PORT == F407_IIC_CH2_PORT_PB_10_11)
			{
				if(mode == SDA_IN)
				{
					GPIOB->MODER &= ~(3<<(11*2));
					GPIOB->MODER |=  (0<<(11*2));
				}
				else if(mode == SDA_OUT)
				{
					GPIOB->MODER &= ~(3<<(11*2));
					GPIOB->MODER |=  (1<<(11*2));
				}
				else{;}
			}
			else if(F407_IIC_CH2_PORT == F407_IIC_CH2_PORT_PF_0_1)
			{
				if(mode == SDA_IN)
				{
					GPIOF->MODER &= ~(3<<(0*2));
					GPIOF->MODER |=  (0<<(0*2));
				}
				else if(mode == SDA_OUT)
				{
					GPIOF->MODER &= ~(3<<(0*2));
					GPIOF->MODER |=  (1<<(0*2));
				}
				else{;}
			}
			else if(F407_IIC_CH2_PORT == F407_IIC_CH2_PORT_PH_4_5)
			{
				if(mode == SDA_IN)
				{
					GPIOH->MODER &= ~(3<<(5*2));
					GPIOH->MODER |=  (0<<(5*2));
				}
				else if(mode == SDA_OUT)
				{
					GPIOH->MODER &= ~(3<<(5*2));
					GPIOH->MODER |=  (1<<(5*2));
				}
				else{;}
			}
			else{;}
			break;
		case F407_IIC_CH3:
			if(F407_IIC_CH3_PORT == F407_IIC_CH3_PORT_PA_8_PC_9)
			{
				if(mode == SDA_IN)
				{
					GPIOC->MODER &= ~(3<<(9*2));
					GPIOC->MODER |=  (0<<(9*2));
				}
				else if(mode == SDA_OUT)
				{
					GPIOC->MODER &= ~(3<<(9*2));
					GPIOC->MODER |=  (1<<(9*2));
				}
				else{;}
			}
			else if(F407_IIC_CH3_PORT == F407_IIC_CH3_PORT_PH_7_8)
			{
				if(mode == SDA_IN)
				{
					GPIOH->MODER &= ~(3<<(8*2));
					GPIOH->MODER |=  (0<<(8*2));
				}
				else if(mode == SDA_OUT)
				{
					GPIOH->MODER &= ~(3<<(8*2));
					GPIOH->MODER |=  (1<<(8*2));
				}
				else{;}
			}
			else{;}
			break;
	}
}

/*********************************************************************
	funcname:	IICP_disable
	contents:	IICコントローラ動作を停止する
	引    数:	なし
	返    値:	なし
	備    考:	停止前にバスを開放する
*********************************************************************/
package void
IICP_disable(void)
{
	PidaIE = 1;					/* SDAポートを入力に変更		*/
	PidaOE = 0;
	PiclIE = 1;					/* SCLポートを入力に変更		*/
	PiclOE = 0;
	PiMcl = 0;					/* 汎用入出力モードに設定		*/
	PiMda = 0;					/* 汎用入出力モードに設定		*/
	DISABLE_IIC;				/* 動作停止			*/
}

package void
IICP_enIICReceive(void)
{
	EN_IIC_RCV;
}

package void
IICP_enIICTransmit(void)
{
	EN_IIC_TRS;
}


/*********************************************************************
	funcname:	IICP_transmitByte
	contents:	データ送信を行う
	引    数:	data : 送信するバイトデータ
	返    値:	なし
	備    考:	なし
*********************************************************************/
package void
IICP_transmitByte(unsigned char data)
{
	unsigned short int cnt = 0;
	CLR_INTIIC;
	IICnTB = (data);			/* １バイト送信する		*/
	while(( GmICR & 0x0010 ) == 0 ){
		cnt++;
		if( cnt >= IIC_WAIT_CNT_MAX ){
			break;
		}
	}
	CLR_INTIIC;
	IICP_nopLoop(12);			/* ウェイトを入れる		*/
}

/*********************************************************************
	funcname:	IICP_reveiveByte
	contents:	receive IIC data
	引    数:	data : 
	返    値:	なし
	備    考:	なし
*********************************************************************/
package unsigned char
IICP_receiveByte(unsigned char acklevel)
{
	unsigned short int cnt = 0;
	unsigned char retVal = 0;
	DISABLE_START;
	CLR_INTIIC;	
	IICnMD3 = acklevel;
	IICnTB = 0xFF;
	while(( GmICR & 0x0010 ) == 0 ){
		cnt++;
		if( cnt >= IIC_WAIT_CNT_MAX ){
			break;
		}
	}
	if( cnt >= IIC_WAIT_CNT_MAX )
	{
		IICP_set_receive_err();
	}
	retVal = IICnRB;	
	CLR_INTIIC;
	EN_RESTART;	
	IICnMD3 = 0x02;
	IICP_nopLoop(12);			/* ウェイトを入れる		*/
	return retVal;
}

private void
IICP_nopLoop(unsigned short n)
{
	while (n > 0) {
		n--;
	}
}

