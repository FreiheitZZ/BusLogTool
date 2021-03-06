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

unsigned char		s_aRxData[DAMC_TRANS_BUF_SIZE];	/* 鞭佚バッファ(リングバッファ)	*/

unsigned char		s_ReceiveCnt;				/* 鞭佚デ�`タカウント		*/

EDAMCReceiveStatus	s_eRxStatus;				/* �Ъ�彜�B			*/

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
	funcname��DAMC_initRxInfo()
	contents�妻榻吐��鵑魍�豚晒しろ
	哈    方�困覆�
	�� り �｣困覆�
	��    深�困覆�
*********************************************************************/
private void
DAMC_initRxInfo(void)
{
	/*************************************************************
		徭���篳�協�x
	*************************************************************/
	/* nothing */
	/*************************************************************
		鞭佚彜�Bをクリアする
	*************************************************************/
	/* �Ъ�彜�B			*/
	s_eRxStatus = DAMC_STS_DLE_RECEIVE_WAIT;
	/* CheckSum			*/
	/* 鞭佚デ�`タカウント		*/
	s_ReceiveCnt = 0x00;
}

/*********************************************************************
	funcname��DAMC_collectData()
	contents�妻榻鼎靴織禰`タを盾裂しろ
	哈    方�困覆�
	�� り �｣困覆�
	��    深��1フレ�`ム蛍�Ъ�したら、鞭佚デ�`タを尅り蛍ける
*********************************************************************/
void DAMC_collectData(void)
{
	/*************************************************************
		徭���篳�協�x
	*************************************************************/
	unsigned char	data,crc_H,crc_L;
	unsigned short crc;
	
	/*************************************************************
		リングバッファが腎になるまでデ�`タを�Ъ�する
	*************************************************************/
	while ( RB_getBufferStatus(s_EntryNo_usart1) != RB_STS_EMPTY ) {
		/*===================================================
			リングバッファから鞭佚デ�`タを�_隠する
		===================================================*/
		data = RB_getRingBuffer(s_EntryNo_usart1);
		
		/*===================================================
			鞭佚デ�`タ登協
		===================================================*/
		switch ( s_eRxStatus ) {
		case DAMC_STS_DLE_RECEIVE_WAIT:		/* DLE鞭佚棋ち彜�B */
			/* DLE鞭佚	*/
			if ( data == DAMC_VAL_DLE ) {
				s_eRxStatus = DAMC_STS_STX_RECEIVE_WAIT;
			}
			else {
				DAMC_initRxInfo();
			}
			break;
		case DAMC_STS_STX_RECEIVE_WAIT:		/* STX鞭佚棋ち彜�B	*/
			/* STX鞭佚 */
			if ( data == DAMC_VAL_STX ) {
				s_eRxStatus	= DAMC_STS_NORMAL_RECEIVE;
				s_ReceiveCnt	= 0;
			}
			else {
				DAMC_initRxInfo();
			}
			break;
		case DAMC_STS_NORMAL_RECEIVE:		/* 宥械鞭佚彜�B		*/
			/* DLE鞭佚 */
			if ( data == DAMC_VAL_DLE ) {
				s_eRxStatus = DAMC_STS_EXT_RECEIVE_WAIT;
			}
			/* DLE參翌のデ�`タ鞭佚 */
			else {
				if (s_ReceiveCnt >= sizeof(s_aRxData)) {
					/* 鞭佚デ�`タとして��械なので、1フレ�`ムを畠て�里討� */
					DAMC_initRxInfo();
				}
				else {
					s_aRxData[s_ReceiveCnt++] = data;
				}
			}
			break;
		case DAMC_STS_EXT_RECEIVE_WAIT:		/* EXT鞭佚棋ち彜�B	*/
			/* DLE鞭佚 */
			if ( data == DAMC_VAL_DLE ) {
				if (s_ReceiveCnt >= sizeof(s_aRxData)) {
					/* 鞭佚デ�`タとして��械なので、1フレ�`ムを畠て�里討� */
					DAMC_initRxInfo();
				}
				else {
					s_aRxData[s_ReceiveCnt++] = data;
					s_eRxStatus = DAMC_STS_NORMAL_RECEIVE;
				}
			}
			/* ETX鞭佚 */
			else if ( data == DAMC_VAL_ETX ) {
				/* チェックサムを�_�J */
				crc_H = s_aRxData[s_ReceiveCnt-2];
				crc_L = s_aRxData[s_ReceiveCnt-1];
				crc = (crc_H << 8) | crc_L;
				if (crc == nfPacketCrc16(&s_aRxData[0],s_ReceiveCnt-2)/*s_CheckSum == 0x00*/ ) {
					/*�逢ぉぉぉぉぉぉぉぉぉ�
					　��1フレ�`ム鞭佚頼阻 ��
					　�県ぉぉぉぉぉぉぉぉぉ�*/
					/* チェックサム蛍を餓し哈く */
					/*s_ReceiveCnt--;*/
					s_ReceiveCnt -= 2;
					/* 鞭佚したデ�`タの盾裂を佩う */
					//DAMC_informReceiveData();
					LED0 = ~LED0;
					/* 鞭佚秤�鵑粒�豚晒 */
					s_eRxStatus = DAMC_STS_DLE_RECEIVE_WAIT;
				}
				else {
					/* チェックサムが��械なので、1フレ�`ムを畠て�里討� */
					DAMC_initRxInfo();
				}
			}
			/* DLE/ETX參翌を鞭佚 */
			else {
				/* 鞭佚デ�`タとして��械なので、1フレ�`ムを畠て�里討� */
				DAMC_initRxInfo();
			}
			break;
		default:
			/*�逢ぉぉぉぉぉぉぉぉぉぉぉぉぉぉぉぉぉぉぉぉぉぉ�
			　�ν┳�ここに送れてくることはないが、		��
			　��栖た��栽は匯業鞭佚した坪否をResetする	��
			　�県ぉぉぉぉぉぉぉぉぉぉぉぉぉぉぉぉぉぉぉぉぉぉ�*/
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

