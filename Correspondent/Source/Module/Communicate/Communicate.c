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

unsigned char		s_aRxData[DAMC_TRANS_BUF_SIZE];	/* ���ťХåե�(��󥰥Хåե�)	*/

unsigned char		s_ReceiveCnt;				/* ���ťǩ`���������		*/

EDAMCReceiveStatus	s_eRxStatus;				/* ����״�B			*/

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
	contents������������ڻ�����
	��    �����ʤ�
	�� �� �����ʤ�
	��    �����ʤ�
*********************************************************************/
private void
DAMC_initRxInfo(void)
{
	/*************************************************************
		�ԄӉ������x
	*************************************************************/
	/* nothing */
	/*************************************************************
		����״�B�򥯥ꥢ����
	*************************************************************/
	/* ����״�B			*/
	s_eRxStatus = DAMC_STS_DLE_RECEIVE_WAIT;
	/* CheckSum			*/
	/* ���ťǩ`���������		*/
	s_ReceiveCnt = 0x00;
}

/*********************************************************************
	funcname��DAMC_collectData()
	contents�����Ť����ǩ`�����������
	��    �����ʤ�
	�� �� �����ʤ�
	��    ����1�ե�`��օ��������顢���ťǩ`�������֤���
*********************************************************************/
void DAMC_collectData(void)
{
	/*************************************************************
		�ԄӉ������x
	*************************************************************/
	unsigned char	data,crc_H,crc_L;
	unsigned short crc;
	
	/*************************************************************
		��󥰥Хåե����դˤʤ�ޤǥǩ`���򅧼�����
	*************************************************************/
	while ( RB_getBufferStatus(s_EntryNo_usart1) != RB_STS_EMPTY ) {
		/*===================================================
			��󥰥Хåե��������ťǩ`����_������
		===================================================*/
		data = RB_getRingBuffer(s_EntryNo_usart1);
		
		/*===================================================
			���ťǩ`���ж�
		===================================================*/
		switch ( s_eRxStatus ) {
		case DAMC_STS_DLE_RECEIVE_WAIT:		/* DLE���Ŵ���״�B */
			/* DLE����	*/
			if ( data == DAMC_VAL_DLE ) {
				s_eRxStatus = DAMC_STS_STX_RECEIVE_WAIT;
			}
			else {
				DAMC_initRxInfo();
			}
			break;
		case DAMC_STS_STX_RECEIVE_WAIT:		/* STX���Ŵ���״�B	*/
			/* STX���� */
			if ( data == DAMC_VAL_STX ) {
				s_eRxStatus	= DAMC_STS_NORMAL_RECEIVE;
				s_ReceiveCnt	= 0;
			}
			else {
				DAMC_initRxInfo();
			}
			break;
		case DAMC_STS_NORMAL_RECEIVE:		/* ͨ������״�B		*/
			/* DLE���� */
			if ( data == DAMC_VAL_DLE ) {
				s_eRxStatus = DAMC_STS_EXT_RECEIVE_WAIT;
			}
			/* DLE����Υǩ`������ */
			else {
				if (s_ReceiveCnt >= sizeof(s_aRxData)) {
					/* ���ťǩ`���Ȥ��Ʈ����ʤΤǡ�1�ե�`���ȫ�ƒΤƤ� */
					DAMC_initRxInfo();
				}
				else {
					s_aRxData[s_ReceiveCnt++] = data;
				}
			}
			break;
		case DAMC_STS_EXT_RECEIVE_WAIT:		/* EXT���Ŵ���״�B	*/
			/* DLE���� */
			if ( data == DAMC_VAL_DLE ) {
				if (s_ReceiveCnt >= sizeof(s_aRxData)) {
					/* ���ťǩ`���Ȥ��Ʈ����ʤΤǡ�1�ե�`���ȫ�ƒΤƤ� */
					DAMC_initRxInfo();
				}
				else {
					s_aRxData[s_ReceiveCnt++] = data;
					s_eRxStatus = DAMC_STS_NORMAL_RECEIVE;
				}
			}
			/* ETX���� */
			else if ( data == DAMC_VAL_ETX ) {
				/* �����å������_�J */
				crc_H = s_aRxData[s_ReceiveCnt-2];
				crc_L = s_aRxData[s_ReceiveCnt-1];
				crc = (crc_H << 8) | crc_L;
				if (crc == nfPacketCrc16(&s_aRxData[0],s_ReceiveCnt-2)/*s_CheckSum == 0x00*/ ) {
					/*����������������������
					����1�ե�`���������� ��
					������������������������*/
					/* �����å�����֤����� */
					/*s_ReceiveCnt--;*/
					s_ReceiveCnt -= 2;
					/* ���Ť����ǩ`���ν������Ф� */
					//DAMC_informReceiveData();
					LED0 = ~LED0;
					/* �������γ��ڻ� */
					s_eRxStatus = DAMC_STS_DLE_RECEIVE_WAIT;
				}
				else {
					/* �����å����ब�����ʤΤǡ�1�ե�`���ȫ�ƒΤƤ� */
					DAMC_initRxInfo();
				}
			}
			/* DLE/ETX��������� */
			else {
				/* ���ťǩ`���Ȥ��Ʈ����ʤΤǡ�1�ե�`���ȫ�ƒΤƤ� */
				DAMC_initRxInfo();
			}
			break;
		default:
			/*������������������������������������������������
			����ͨ������������Ƥ��뤳�ȤϤʤ�����		��
			�����������Ϥ�һ�����Ť������ݤ�Reset����	��
			��������������������������������������������������*/
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

