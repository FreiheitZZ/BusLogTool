/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	ヘッダーファイル取り込み
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
/*┌─────────┐
　│System Information│
　└─────────┘*/
/* nothing */
/*┌────────────┐
　│Environment Information │
　└────────────┘*/
#include "../../../Common/Common.h"		/* Common Information	*/
#include "../../../Platform/Platform.h"		/* Platform Information	*/
/*┌────────┐
　│User Information│
　└────────┘*/
#include "./SPIMN103LF15.h"

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	外部変数定義と外部変数へのリンク　[External Linkage]
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
/* nothing */

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	内部変数定義　[Internal Linkage]
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
private void	SPIP_nopLoop(unsigned short);		/* 短いウェイト用	*/

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	内部関数プロトタイプ宣言　[Internal Linkage]
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
/* nothing */

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	外部関数定義(public)　[External Linkage]
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
/* nothing */

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	外部関数定義(package)　[External Linkage]
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
/*********************************************************************
	funcname:	SPIP_execResume
	contents:	Resume処理
	引    数:	なし
	返    値:	なし
	備    考:	なし
*********************************************************************/
package void
SPIP_execResume(unsigned char ch)
{
	switch(ch)
	{
		case SPIP_CH0:
		case SPIP_CH2:
		case SPIP_CH3:
		case SPIP_CH4:
		case SPIP_CH5:
		case SPIP_CH6:
		case SPIP_CH7:
		case SPIP_CH8:
		case SPIP_CH9:
		break;
		case SPIP_CH1:
		SPI1_PORT_ENTRY_INIT();
		SPI1_BAUTRATE_SET();
		break;
		default:
		break;
	}
}

/*********************************************************************
	funcname:	SPIP_execSuspend
	contents:	Suspend処理
	引    数:	なし
	返    値:	なし
	備    考:	なし
*********************************************************************/
package void
SPIP_execSuspend(unsigned char ch)
{
	switch(ch)
	{
		case SPIP_CH0:
		case SPIP_CH2:
		case SPIP_CH3:
		case SPIP_CH4:
		case SPIP_CH5:
		case SPIP_CH6:
		case SPIP_CH7:
		case SPIP_CH8:
		case SPIP_CH9:			
		break;
		case SPIP_CH1:
		SPI1_CLOSE();
		SPI1_PORT_EXIT_INIT();
		break;
		default:
		break;
	}
}

/*********************************************************************
	funcname:	SPIP_enable
	contents:	SPIコントローラ動作を許可する
	引    数:	なし
	返    値:	なし
	備    考:	なし
*********************************************************************/
package void
SPIP_enable(unsigned char ch)
{
	switch(ch)
	{
		case SPIP_CH0:
		case SPIP_CH2:
		case SPIP_CH3:
		case SPIP_CH4:
		case SPIP_CH5:
		case SPIP_CH6:
		case SPIP_CH7:
		case SPIP_CH8:
		case SPIP_CH9:
		break;
		case SPIP_CH1:
		SPI1_OPEN();
		break;
		default:
		break;
	}
}

/*********************************************************************
	funcname:	SPIP_disable
	contents:	SPIコントローラ動作を停止する
	引    数:	なし
	返    値:	なし
	備    考:	停止前にバスを開放する
*********************************************************************/
package void
SPIP_disable(unsigned char ch)
{
	switch(ch)
	{
		case SPIP_CH0:
		case SPIP_CH2:
		case SPIP_CH3:
		case SPIP_CH4:
		case SPIP_CH5:
		case SPIP_CH6:
		case SPIP_CH7:
		case SPIP_CH8:
		case SPIP_CH9:	
		break;
		case SPIP_CH1:
		SPI1_CLOSE();
		break;
		default:
		break;
	}
}
/*********************************************************************
	funcname:	SPIP_changeEdge
	contents:	SPIコントローラ動作を停止する
	引    数:	なし
	返    値:	なし
	備    考:	停止前にバスを開放する
*********************************************************************/
package void
SPIP_changeEdge(unsigned char ch,unsigned char edge)
{
	switch(ch)
	{
		case SPIP_CH0:
		case SPIP_CH2:
		case SPIP_CH3:
		case SPIP_CH4:
		case SPIP_CH5:
		case SPIP_CH6:
		case SPIP_CH7:
		case SPIP_CH8:			
		case SPIP_CH9:
		break;
		case SPIP_CH1:
			if(edge == 0)/*rising edge sample*/
			{
				bCPU_SC1RSTN = 0;				/*Register SC1MD3,Serial Reset*/
				bCPU_SC1RSRN = 0;				/*Register SC1MD3,Serial Reset*/
				bCPU_BRTM_S1_EN = 0;			/*BuadRate Timer Off*/								
				ucCPU_SC1MD0 = 0x07;			/*0000 0111
												Clock polarity "H";
												Communication Mode "Normal Mode";
												MSB Fisrst;Disable Start Conditon;
												8bits Transmit*/
				bCPU_BRTM_S1_EN = 1;			/*BuadRate Timer On*/																	
				bCPU_SC1RSTN = 1;				/*Register SC1MD3,Serial Open*/
				bCPU_SC1RSRN = 0;				/*Register SC1MD3,This Bit Must be 0*/	
			}
			else/*falling edge sample*/
			{
				bCPU_SC1RSTN = 0;				/*Register SC1MD3,Serial Reset*/
				bCPU_SC1RSRN = 0;				/*Register SC1MD3,Serial Reset*/
				bCPU_BRTM_S1_EN = 0;			/*BuadRate Timer Off*/								
				ucCPU_SC1MD0 = 0x87;			/*1000 0111
												Clock polarity "L";
												Communication Mode "Normal Mode";
												MSB Fisrst;Disable Start Conditon;
												8bits Transmit*/
				bCPU_BRTM_S1_EN = 1;			/*BuadRate Timer On*/																	
				bCPU_SC1RSTN = 1;				/*Register SC1MD3,Serial Open*/
				bCPU_SC1RSRN = 0;				/*Register SC1MD3,This Bit Must be 0*/	
			}
		break;
		default:
		break;
	}
}

/*********************************************************************
	funcname:	SPIP_transmitByte
	contents:	データ送信を行う
	引    数:	data : 送信するバイトデータ
	返    値:	なし
	備    考:	なし
*********************************************************************/
package void
SPIP_transmitByte(unsigned char ch,unsigned char data)
{
	unsigned short i;
	unsigned char dummy;
	i = 0;
	dummy = 0;
	switch(ch)
	{
		case SPIP_CH0:
		case SPIP_CH2:
		case SPIP_CH3:
		case SPIP_CH4:
		case SPIP_CH5:
		case SPIP_CH6:
		case SPIP_CH7:
		case SPIP_CH8:
		case SPIP_CH9:
		break;
		case SPIP_CH1:
		while (bCPU_SC1TEMP)
		{
			if(i<SPI_WAIT_CNT_MAX)
			{
				i++;
			}
			else
			{
				i = 0;
				break;
			}		
		}
		dummy = SPI1_RecDataReg; /*dummy read for clear read flag*/
		SPI1_TraDataReg =data; /*send byte data*/
	   while(!bCPU_SC1REMP)
	   {
		   	if(i<SPI_WAIT_CNT_MAX)
			{
				i++;
			}
			else
			{
				i = 0;
				break;
			}		
	   }
	   dummy = SPI1_RecDataReg; /*dummy read for clear read flag*/
		break;
		default:
		break;
	}
	
	
}
/*********************************************************************
	funcname:	SPIP_ReceiveByte
	contents:	データ送信を行う
	引    数:	なし
	返    値:	data : 送信するバイトデータ
	備    考:	なし
*********************************************************************/

package unsigned char 
SPIP_ReceiveByte(unsigned char ch)
{
	unsigned char recdata;
	unsigned char dummy;
	unsigned short i;
	i = 0;

	switch(ch)
	{
		case SPIP_CH0:
		case SPIP_CH2:
		case SPIP_CH3:
		case SPIP_CH4:
		case SPIP_CH5:
		case SPIP_CH6:
		case SPIP_CH7:
		case SPIP_CH8:		
		case SPIP_CH9:
		break;
		case SPIP_CH1:
			while (bCPU_SC1TEMP)
			{
				if(i<SPI_WAIT_CNT_MAX)
				{
					i++;
				}
				else
				{
					i = 0;
					break;
				}		
			}
			dummy = SPI1_RecDataReg; /*dummy read for clear read flag*/
			SPI1_TraDataReg =0xff; /*send byte data*/
		   while(bCPU_SC1RBSY&&(!bCPU_SC1REMP))
		   {
				if(i<SPI_WAIT_CNT_MAX){
					i++;
				}
				else{
					i = 0;
					break;
				}	
		   }
			recdata = SPI1_RecDataReg;
			break;
		default: 
			break;
	}
	
	return recdata;   
}


/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	内部関数定義　[Internal Linkage]
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
/*********************************************************************
	funcname:	SPIP_nopLoop
	contents:	短いウェイト時間を作る
	引    数:	n : 回す回数
	返    値:	なし
	備    考:	回している間、CPUを占有するので小さな値を
			指定すること。
*********************************************************************/
private void
SPIP_nopLoop(unsigned short n)
{
	while (n > 0) {
		n--;
	}
}

