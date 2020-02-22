#include <string.h>				/* memcpy(),memset()etc */
#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"
#include "Communicate.h"
#include "../../Driver/Uart/Uart.h"
#include "../../Driver/Uart/Uart_STM32F407/UartSTM32F407.h"
#include "../../Common/Common.h"
#include "../../Common/RingBuffer.h"
#include "../../Device/LED/LED.h"

extern EventGroupHandle_t EventGroupHandler;
extern unsigned char		s_EntryNo_usart1;

unsigned char s_aTransmitBuf[DAMC_TRANS_BUF_SIZE];

unsigned char		s_aRxData[DAMC_TRANS_BUF_SIZE];	/* 受信バッファ(リングバッファ)	*/

unsigned char		s_ReceiveCnt;				/* 受信データカウント		*/

EDAMCReceiveStatus	s_eRxStatus;				/* 収集状態			*/

void USB_sendData(unsigned char * pData, unsigned char size);

void TSK_USBReceive(void *pvParameters)
{
	while(1)
	{
		delay_ms(1000);
	}
}

void USB_sendData(unsigned char * pData, unsigned char size)
{
	unsigned char rp,wp,crc_H,crc_L;
	unsigned short crc;

	wp = 0;
	memset(s_aTransmitBuf, 0, sizeof(s_aTransmitBuf));
	s_aTransmitBuf[wp++] = USB_VAL_DLE;

	s_aTransmitBuf[wp++] = USB_VAL_STX;

	for (rp = 0 ; rp < size ; rp++) {
		s_aTransmitBuf[wp++] = *(pData+rp);
		if(*(pData+rp) == USB_VAL_DLE) {
			s_aTransmitBuf[wp++] = USB_VAL_DLE;
		}
	}
	crc = nfPacketCrc16(pData,size);
	crc_H = ( unsigned char )( ( crc & 0xff00 ) >> 8 );
	crc_L = ( unsigned char )( crc & 0x00ff );
	
	s_aTransmitBuf[wp++] = crc_H;

	if(crc_H==USB_VAL_DLE){
		s_aTransmitBuf[wp++] = USB_VAL_DLE;
	}
	s_aTransmitBuf[wp++] = crc_L;

	if(crc_L==USB_VAL_DLE){
		s_aTransmitBuf[wp++] = USB_VAL_DLE;
	}
	
	s_aTransmitBuf[wp++] = USB_VAL_DLE;
	s_aTransmitBuf[wp++] = USB_VAL_ETX;
	
	usb_printf("%s", s_aTransmitBuf); 
}

void USB_waitSendEnd(void)
{
	unsigned char loop;
	
	for (loop = 0; loop < 30; loop++){
		if (UART_getUARTTransferState(0) == UART_STAT_STOP){
			break;
		}
		delay_ms(2);
	}
}

void TSK_USBSend(void *pvParameters)
{
	unsigned char str1[] = "uart1: USB connect";
	unsigned char str2[] = "uart2: USB connect";
	while(1)
	{
		delay_ms(500);
		USB_sendData(str1, sizeof(str1)-1);
		delay_ms(500);
		USB_sendData(str2, sizeof(str2)-1);
		
	}
}

/*********************************************************************
	funcname：DAMC_initRxInfo()
	contents：受信情報を初期化しろ
	引    数：なし
	戻 り 値：なし
	備    考：なし
*********************************************************************/
private void
DAMC_initRxInfo(void)
{
	/*************************************************************
		自動変数定義
	*************************************************************/
	/* nothing */
	/*************************************************************
		受信状態をクリアする
	*************************************************************/
	/* 収集状態			*/
	s_eRxStatus = DAMC_STS_DLE_RECEIVE_WAIT;
	/* CheckSum			*/
	/* 受信データカウント		*/
	s_ReceiveCnt = 0x00;
}

/*********************************************************************
	funcname：DAMC_collectData()
	contents：受信したデータを解析しろ
	引    数：なし
	戻 り 値：なし
	備    考：1フレーム分収集したら、受信データを振り分ける
*********************************************************************/
void DAMC_collectData(void)
{
	/*************************************************************
		自動変数定義
	*************************************************************/
	unsigned char	data,crc_H,crc_L;
	unsigned short crc;
	
	/*************************************************************
		リングバッファが空になるまでデータを収集する
	*************************************************************/
	while ( RB_getBufferStatus(s_EntryNo_usart1) != RB_STS_EMPTY ) {
		/*===================================================
			リングバッファから受信データを確保する
		===================================================*/
		data = RB_getRingBuffer(s_EntryNo_usart1);
		
		/*===================================================
			受信データ判定
		===================================================*/
		switch ( s_eRxStatus ) {
		case DAMC_STS_DLE_RECEIVE_WAIT:		/* DLE受信待ち状態 */
			/* DLE受信	*/
			if ( data == DAMC_VAL_DLE ) {
				s_eRxStatus = DAMC_STS_STX_RECEIVE_WAIT;
			}
			else {
				DAMC_initRxInfo();
			}
			break;
		case DAMC_STS_STX_RECEIVE_WAIT:		/* STX受信待ち状態	*/
			/* STX受信 */
			if ( data == DAMC_VAL_STX ) {
				s_eRxStatus	= DAMC_STS_NORMAL_RECEIVE;
				s_ReceiveCnt	= 0;
			}
			else {
				DAMC_initRxInfo();
			}
			break;
		case DAMC_STS_NORMAL_RECEIVE:		/* 通常受信状態		*/
			/* DLE受信 */
			if ( data == DAMC_VAL_DLE ) {
				s_eRxStatus = DAMC_STS_EXT_RECEIVE_WAIT;
			}
			/* DLE以外のデータ受信 */
			else {
				if (s_ReceiveCnt >= sizeof(s_aRxData)) {
					/* 受信データとして異常なので、1フレームを全て捨てる */
					DAMC_initRxInfo();
				}
				else {
					s_aRxData[s_ReceiveCnt++] = data;
				}
			}
			break;
		case DAMC_STS_EXT_RECEIVE_WAIT:		/* EXT受信待ち状態	*/
			/* DLE受信 */
			if ( data == DAMC_VAL_DLE ) {
				if (s_ReceiveCnt >= sizeof(s_aRxData)) {
					/* 受信データとして異常なので、1フレームを全て捨てる */
					DAMC_initRxInfo();
				}
				else {
					s_aRxData[s_ReceiveCnt++] = data;
					s_eRxStatus = DAMC_STS_NORMAL_RECEIVE;
				}
			}
			/* ETX受信 */
			else if ( data == DAMC_VAL_ETX ) {
				/* チェックサムを確認 */
				crc_H = s_aRxData[s_ReceiveCnt-2];
				crc_L = s_aRxData[s_ReceiveCnt-1];
				crc = (crc_H << 8) | crc_L;
				if (crc == nfPacketCrc16(&s_aRxData[0],s_ReceiveCnt-2)/*s_CheckSum == 0x00*/ ) {
					/*┌─────────┐
					　│1フレーム受信完了 │
					　└─────────┘*/
					/* チェックサム分を差し引く */
					/*s_ReceiveCnt--;*/
					s_ReceiveCnt -= 2;
					/* 受信したデータの解析を行う */
					//DAMC_informReceiveData();
					LED0 = ~LED0;
					/* 受信情報の初期化 */
					s_eRxStatus = DAMC_STS_DLE_RECEIVE_WAIT;
				}
				else {
					/* チェックサムが異常なので、1フレームを全て捨てる */
					DAMC_initRxInfo();
				}
			}
			/* DLE/ETX以外を受信 */
			else {
				/* 受信データとして異常なので、1フレームを全て捨てる */
				DAMC_initRxInfo();
			}
			break;
		default:
			/*┌──────────────────────┐
			　│通常ここに流れてくることはないが、		│
			　│来た場合は一度受信した内容をResetする	│
			　└──────────────────────┘*/
			DAMC_initRxInfo();
			break;
		}
	}
}

void TSK_DAMReceiver(void *pvParameters)
{
	BaseType_t xReturn = pdFALSE;
	unsigned int EventValue = 0;
	
	while(1)
	{
		xReturn=xTaskNotifyWait(0x00, 0xFFFFFFFF, &EventValue, portMAX_DELAY);
		if((EventValue & EVENTBIT_1) == EVENTBIT_1)
		{
			EventValue &= ~(EVENTBIT_1);
			DAMC_collectData();
		}

	}
}

void TSK_DAMTransmitter(void *pvParameters)
{
	EventBits_t EventValue;

	while(1)
	{
		vTaskDelay(10);
	}
}

