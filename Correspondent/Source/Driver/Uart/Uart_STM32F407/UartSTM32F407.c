#include "stm32f4xx_usart.h"
#include "./UartSTM32F407.h"
#include "..\..\..\Common\ringbuffer.h"
#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"

extern TaskHandle_t DAMReceiverTask_Handler;

EventGroupHandle_t EventGroupHandler;

unsigned char		s_EntryNo_usart1;
unsigned char		s_EntryNo_usart2;

static	void	F407_changeMode(unsigned char, F407PortMode);
static	void	F407_setPortMode(unsigned char);
static	void	F407_setUARTMode(unsigned char);
static	void	F407_setUartConfigration(F407UARTChannel, unsigned long, unsigned int, unsigned int, unsigned int);
static	void	F407_setUartITConfig(F407UARTChannel ch);

static void UART_SendDataCH1(unsigned char *data, u16 len);
static void UART_SendDataCH2(unsigned char *data, u16 len);
static void UART_SendDataCH3(unsigned char *data, u16 len);
static void UART_SendDataCH4(unsigned char *data, u16 len);
static void UART_SendDataCH5(unsigned char *data, u16 len);
static void UART_SendDataCH6(unsigned char *data, u16 len);

/*********************************************************************
	funcname�FMN103_entryUart()
	contents�FUART�́�ch���g�p����(UartA:0�`5�AUartB:6,7)
	��    ���F unsigned char	UART ch		<IN>
		   unsigned long	�{�[���[�g	<IN>
		   EUARTParityType	�p���e�B	<IN>
		   unsigned char	BIT��		<IN>
		   unsigned char	�X�g�b�vBIT	<IN>
		   ID (*)(void)		��M�n���h��	<IN>
	�� �� �l�F�Ȃ�
	��    �l�F�Ȃ�
*********************************************************************/
extern void
F407_entryUart( unsigned char	ch,			/* ch		*/
		unsigned long	baudrate,		/* �{�[���[�g	*/
		F407ParityType	eParity,		/* �p���e�B	*/
		unsigned char	bitLength,		/* BIT��	*/
		unsigned char	stopbit		/* �X�g�b�vBIT	*/
			 )
{
	/*************************************************************
		�����ϐ���`
	*************************************************************/
	/* nothing */
	
	/*************************************************************
		UART�́�ch���g�p����
	*************************************************************/
	F407_changeMode(ch, F407_MODE_UART);	/* �|�[�g���[�h���uUART�v�ɐ؂�ւ�	*/
	F407_setUartConfigration(ch,baudrate, eParity,bitLength,stopbit);
	F407_setUartITConfig(ch);
}

/*********************************************************************
	funcname�FMN103_entryUart()
	contents�FUART�́�ch�𖢎g�p����
	��    ���Funsigned char		UART ch		<IN>
	�� �� �l�F�Ȃ�
	��    �l�F�Ȃ�
*********************************************************************/
extern void
F407_exitUart(unsigned char ch)
{
	/*************************************************************
		�����ϐ���`
	*************************************************************/
	/* nothing */
	
	/*************************************************************
		UART�́�ch�𖢎g�p����
	*************************************************************/
	F407_changeMode(ch, F407_MODE_PORT);	/* �|�[�g���[�h���uPORT�v�ɐ؂�ւ�	*/
}

/*********************************************************************
	funcname�FMN103_stopUart()
	contents�F��ch�̓�����~����
	��    ���Funsigned char		UART ch		<IN>
	�� �� �l�F�Ȃ�
	��    �l�F
		�y�J�n/��~�����z
		    �J�n���F���荞�݂̋���UART����J�n������M����J�n
		    ��~���F����M�����~��UART�����~�����荞�݂̋֎~
*********************************************************************/
extern void
F407_stopUart(F407UARTChannel ch)
{
	/*************************************************************
		�����ϐ���`
	*************************************************************/
	/* nothing */
	/*************************************************************
		��ch�̓�����~����
	*************************************************************/
	switch ( ch ) {
	case F407_UART_CH1:
		USART_DeInit(USART1);
		break;
	case F407_UART_CH2:
		USART_DeInit(USART2);
		break;
	case F407_UART_CH3:
		USART_DeInit(USART3);
		break;
	case F407_UART_CH4:
		USART_DeInit(UART4);
		break;
	case F407_UART_CH5:
		USART_DeInit(UART5);
		break;
	case F407_UART_CH6:
		USART_DeInit(USART6);
		break;
	default:
		break;

	}
}

/*********************************************************************
	funcname�FMN103_transmitData()
	contents�F���̃f�[�^�𑗐M����
	��    ���Funsigned char		UART ch		<IN>
		  unsigned char*	�f�[�^�A�h���X	<IN>
	�� �� �l�F�Ȃ�
	��    �l�F�Ȃ�
*********************************************************************/
extern void
F407_transmitData(F407UARTChannel ch ,unsigned char * pData ,unsigned int len)
{
	/*************************************************************
		�����ϐ���`
	*************************************************************/
	/* nothing */
	
	/*************************************************************
		���M����
	*************************************************************/
	switch (ch)
	{
		case F407_UART_CH1:
			UART_SendDataCH1(pData, len);
			break;
		case F407_UART_CH2:
			UART_SendDataCH2(pData, len);
			break;
		case F407_UART_CH3:
			UART_SendDataCH3(pData, len);
			break;
		case F407_UART_CH4:
			UART_SendDataCH4(pData, len);
			break;
		case F407_UART_CH5:
			UART_SendDataCH5(pData, len);
			break;
		case F407_UART_CH6:
			UART_SendDataCH6(pData, len);
			break;
		default:
			break;
	}
}

/*********************************************************************
	funcname�FMN103_checkTransmitReady()
	contents�F���M�\���ǂ������`�F�b�N����
	��    ���Funsigned char		UART ch		<IN>
	�� �� �l�FBOOL		���M�\���ǂ���
		  TRUE :	���M�\
		  FALSE:	���M�s�\
	��    �l�F�Ȃ�
*********************************************************************/
extern unsigned char 
F407_checkTransmitReady(unsigned char ch)
{
	/*************************************************************
		�����ϐ���`
	*************************************************************/
	unsigned char result = 0;	/* �����l�F���M�s�\ */

	return result;
}

/*********************************************************************
	funcname�FMN103_getReceiveData()
	contents�F��M�f�[�^���擾����
	��    ���Funsigned char		UART ch		<IN>
	�� �� �l�F�Ȃ�
	��    �l�F�Ȃ�
*********************************************************************/
extern unsigned char
F407_getReceiveData(unsigned char ch)
{
	/*************************************************************
		�����ϐ���`
	*************************************************************/
	unsigned char	data = 0x00;	/* ��M�f�[�^default�F0x00 */
	
	return	data;
}

/*********************************************************************
	funcname�FMN103_getUARTTransferState()
	contents�FUART�]����Ԃ��擾����
	��    ���Funsigned char		UART ch		<IN>
	�� �� �l�Funsigned char		CH���̓]�����
			0x00 : ���M�\
			0x01 : ���M�s�\(0x00�ȊO�ł���Α��M�s�\�ƈ����Ă���)
	��    �l�F�Ȃ�
*********************************************************************/
extern unsigned char
F407_getUARTTransferState(unsigned char ch)
{
	/*************************************************************
		�����ϐ���`
	*************************************************************/
	unsigned char	status = 0x00;	/* �����l�F���M�\ */
	
	/*************************************************************
		��ԃ��W�X�^�ǂݏo��
	*************************************************************/
	return	status;
}

/*********************************************************************
	funcname�FMN103_getErrorStatus()
	contents�F��M�G���[�����擾����
	��    ���Funsigned char		UART ch		<IN>
	�� �� �l�Funsigned char		CH���̃G���[���
	��    �l�FBit2�F�p���e�B�G���[�ABit1�F�t���[�~���O�G���[�ABit0�F�I�[�o�[�����G���[
	�f�[�^����M�����ۂ͕K���G���[���̎擾���s���Ă��������B
	
*********************************************************************/
extern unsigned char
F407_getErrorStatus(unsigned char ch)
{
	/*************************************************************
		�����ϐ���`
	*************************************************************/
	unsigned char	error = 0x00;
	
	/*************************************************************
		��ԃ��W�X�^�ǂݏo��
	*************************************************************/
	return	error;
}

/*********************************************************************
	funcname�FMN103_changeMode()
	contents�FUART���[�h��PORT���[�h�̐؂�ւ�������
	��    ���Funsigned char		UART ch		<IN>
		  EMN103PortMode		�|�[�g���[�h	<IN>
	�� �� �l�F�Ȃ�
	��    �l�F�����œ�����~���Ă���؂�ւ��Ă܂��B
*********************************************************************/
static	void
F407_changeMode(unsigned char ch, F407PortMode mode)
{
	/*************************************************************
		�����ϐ���`
	*************************************************************/
	/* nothing */
	
	/*************************************************************
		������~����
	*************************************************************/
	F407_stopUart(ch);

	
	/*************************************************************
		���[�h�ؑ�
	*************************************************************/
	if ( mode == F407_MODE_PORT ) {
		F407_setPortMode(ch);
	}
	else if ( mode == F407_MODE_UART ) {
		F407_setUARTMode(ch);
	}
	else
	{
		F407_setUARTMode(ch);
	}
}

/*********************************************************************
	funcname�FMN103_setPortMode()
	contents�F�|�[�g���[�h�ɂ���
	��    ���Funsigned char		UART ch		<IN>
	�� �� �l�F�Ȃ�
	��    �l�F�K��������~���Ă���ݒ��؂�ւ��邱�ƁB
*********************************************************************/
static	void
F407_setPortMode(F407UARTChannel ch)
{
	/*************************************************************
		�����ϐ���`
	*************************************************************/
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	/*************************************************************
		�|�[�g���[�h�ɂ���
	*************************************************************/
	F407_stopUart(ch);

	switch (ch)
	{
		case F407_UART_CH1:
			if(F407_UART_CH1_PORT == F407_UART_CH1_PORT_PA_9_10)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
				GPIO_Init(GPIOA, &GPIO_InitStructure);//�����
				GPIO_ResetBits(GPIOA,GPIO_Pin_9 | GPIO_Pin_10);//���õ�
			}
			else if(F407_UART_CH1_PORT == F407_UART_CH1_PORT_PB_5_6)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
				GPIO_Init(GPIOB, &GPIO_InitStructure);//�����
				GPIO_ResetBits(GPIOB,GPIO_Pin_5 | GPIO_Pin_6);//���õ�
			}
			else {;}
			break;
		case F407_UART_CH2:
			if(F407_UART_CH2_PORT == F407_UART_CH2_PORT_PA_2_3)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
				GPIO_Init(GPIOA, &GPIO_InitStructure);//�����
				GPIO_ResetBits(GPIOA,GPIO_Pin_2 | GPIO_Pin_3);//���õ�
			}
			else if(F407_UART_CH2_PORT == F407_UART_CH2_PORT_PD_5_6)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
				GPIO_Init(GPIOD, &GPIO_InitStructure);//�����
				GPIO_ResetBits(GPIOD,GPIO_Pin_5 | GPIO_Pin_6);//���õ�
			}
			else {;}
			break;
		case F407_UART_CH3:
			if(F407_UART_CH3_PORT == F407_UART_CH3_PORT_PB_10_11)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
				GPIO_Init(GPIOB, &GPIO_InitStructure);//�����
				GPIO_ResetBits(GPIOB,GPIO_Pin_10 | GPIO_Pin_11);//���õ�
			}
			else if(F407_UART_CH3_PORT == F407_UART_CH3_PORT_PD_8_9)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
				GPIO_Init(GPIOD, &GPIO_InitStructure);//�����
				GPIO_ResetBits(GPIOD,GPIO_Pin_8 | GPIO_Pin_9);//���õ�
			}
			else if(F407_UART_CH3_PORT == F407_UART_CH3_PORT_PC_10_11)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
				GPIO_Init(GPIOC, &GPIO_InitStructure);//�����
				GPIO_ResetBits(GPIOC,GPIO_Pin_10 | GPIO_Pin_11);//���õ�
			}
			else {;}
			break;
		case F407_UART_CH4:
			if(F407_UART_CH4_PORT == F407_UART_CH4_PORT_PA_0_1)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
				GPIO_Init(GPIOA, &GPIO_InitStructure);//�����
				GPIO_ResetBits(GPIOA,GPIO_Pin_0 | GPIO_Pin_1);//���õ�
			}
			else if(F407_UART_CH4_PORT == F407_UART_CH4_PORT_PC_10_11)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
				GPIO_Init(GPIOC, &GPIO_InitStructure);//�����
				GPIO_ResetBits(GPIOC,GPIO_Pin_10 | GPIO_Pin_11);//���õ�
			}
			else {;}
			break;
		case F407_UART_CH5:
			if(F407_UART_CH5_PORT == F407_UART_CH5_PORT_PC_12_PD_2)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
				GPIO_Init(GPIOC, &GPIO_InitStructure);//�����
				GPIO_ResetBits(GPIOC,GPIO_Pin_12);//���õ�
				
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
				GPIO_Init(GPIOD, &GPIO_InitStructure);//�����
				GPIO_ResetBits(GPIOD,GPIO_Pin_2);//���õ�
			}
			else {;}
			break;		
		case F407_UART_CH6:
			if(F407_UART_CH6_PORT == F407_UART_CH6_PORT_PC_6_7)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
				GPIO_Init(GPIOC, &GPIO_InitStructure);//�����
				GPIO_ResetBits(GPIOC,GPIO_Pin_6 | GPIO_Pin_7);//���õ�
			}
			else if(F407_UART_CH6_PORT == F407_UART_CH6_PORT_PG_9_14)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_14;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
				GPIO_Init(GPIOG, &GPIO_InitStructure);//�����
				GPIO_ResetBits(GPIOG,GPIO_Pin_9 | GPIO_Pin_14);//���õ�
			}
			else {;}
			break;
		default:
			break;
	}
}

/*********************************************************************
	funcname�FMN103_setUARTMode()
	contents�FUART���[�h�ɂ���
	��    ���Funsigned char		UART ch		<IN>
	�� �� �l�F�Ȃ�
	��    �l�F�K��������~���Ă���ݒ��؂�ւ��邱�ƁB
*********************************************************************/
static	void
F407_setUARTMode(F407UARTChannel ch)
{
	/*************************************************************
		�����ϐ���`
	*************************************************************/
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*************************************************************
		UART���[�h�ɂ���
	*************************************************************/
	switch (ch){
		case F407_UART_CH1:
			if(F407_UART_CH1_PORT == F407_UART_CH1_PORT_PA_9_10)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
				GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
				GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
				
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
				GPIO_Init(GPIOA,&GPIO_InitStructure);
			}
			else if(F407_UART_CH1_PORT == F407_UART_CH1_PORT_PB_5_6)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
				GPIO_PinAFConfig(GPIOB,GPIO_PinSource5,GPIO_AF_USART1);
				GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_USART1);
				
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
				GPIO_Init(GPIOB,&GPIO_InitStructure);
			}
			else {;}
			break;
		case F407_UART_CH2:
			if(F407_UART_CH2_PORT == F407_UART_CH2_PORT_PA_2_3)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
				GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2);
				GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2);
				
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
				GPIO_Init(GPIOA,&GPIO_InitStructure);
			}
			else if(F407_UART_CH2_PORT == F407_UART_CH2_PORT_PD_5_6)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
				GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_USART2);
				GPIO_PinAFConfig(GPIOD,GPIO_PinSource6,GPIO_AF_USART2);
				
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
				GPIO_Init(GPIOD,&GPIO_InitStructure);
			}
			else {;}
			break;
		case F407_UART_CH3:
			if(F407_UART_CH3_PORT == F407_UART_CH3_PORT_PB_10_11)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
				GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3);
				GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3);
				
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
				GPIO_Init(GPIOB,&GPIO_InitStructure);
			}
			else if(F407_UART_CH3_PORT == F407_UART_CH3_PORT_PD_8_9)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
				GPIO_PinAFConfig(GPIOD,GPIO_PinSource8,GPIO_AF_USART3);
				GPIO_PinAFConfig(GPIOD,GPIO_PinSource9,GPIO_AF_USART3);
				
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
				GPIO_Init(GPIOD,&GPIO_InitStructure);
			}
			else if(F407_UART_CH3_PORT == F407_UART_CH3_PORT_PC_10_11)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
				GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_USART3);
				GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_USART3);
				
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
				GPIO_Init(GPIOC,&GPIO_InitStructure);
			}
			else {;}
			break;
		case F407_UART_CH4:
			if(F407_UART_CH4_PORT == F407_UART_CH4_PORT_PA_0_1)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
				GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_UART4);
				GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_UART4);
				
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
				GPIO_Init(GPIOA,&GPIO_InitStructure);
			}
			else if(F407_UART_CH4_PORT == F407_UART_CH4_PORT_PC_10_11)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
				GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_UART4);
				GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_UART4);
				
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
				GPIO_Init(GPIOC,&GPIO_InitStructure);
			}
			else {;}
			break;
		case F407_UART_CH5:
			if(F407_UART_CH5_PORT == F407_UART_CH5_PORT_PC_12_PD_2)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
				GPIO_PinAFConfig(GPIOC,GPIO_PinSource12,GPIO_AF_UART5);
				
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
				GPIO_Init(GPIOC,&GPIO_InitStructure);
				
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
				GPIO_PinAFConfig(GPIOD,GPIO_PinSource2,GPIO_AF_UART5);
				
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
				GPIO_Init(GPIOD,&GPIO_InitStructure);
			}
			else {;}
			break;		
		case F407_UART_CH6:
			if(F407_UART_CH6_PORT == F407_UART_CH6_PORT_PC_6_7)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
				GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_USART6);
				GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_USART6);
				
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
				GPIO_Init(GPIOC,&GPIO_InitStructure);
			}
			else if(F407_UART_CH6_PORT == F407_UART_CH6_PORT_PG_9_14)
			{
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG,ENABLE);
				GPIO_PinAFConfig(GPIOG,GPIO_PinSource9,GPIO_AF_UART4);
				GPIO_PinAFConfig(GPIOG,GPIO_PinSource14,GPIO_AF_UART4);
				
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_14;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
				GPIO_Init(GPIOG,&GPIO_InitStructure);
			}
			else {;}
			break;
		default:
			break;
	}
}

/*********************************************************************
	funcname�FMN103_setUartConfigration()
	contents�F�����ݒ�
	��    ���F unsigned char	UART ch		<IN>
		   unsigned long	�{�[���[�g	<IN>
		   EUARTParityType	�p���e�B	<IN>
		   unsigned char	BIT��		<IN>
		   unsigned char	�X�g�b�vBIT	<IN>
	�� �� �l�F�Ȃ�
	��    �l�F�Ȃ�
*********************************************************************/
static void
F407_setUartConfigration(F407UARTChannel ch,
			unsigned long		baudrate,
			unsigned int		parity,
			unsigned int		bitLength,
			unsigned int		stopbit	)
{
	
	USART_InitTypeDef USART_InitStructure;
	
	switch (ch){
		case F407_UART_CH1:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//ʹ��USART1ʱ��
			USART_InitStructure.USART_BaudRate = baudrate;
			USART_InitStructure.USART_WordLength = bitLength;
			USART_InitStructure.USART_StopBits = stopbit;
			USART_InitStructure.USART_Parity = parity;
			USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
			USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
			USART_Init(USART1, &USART_InitStructure);
			USART_Cmd(USART1, ENABLE);
			break;
		case F407_UART_CH2:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//ʹ��USART2ʱ��
			USART_InitStructure.USART_BaudRate = baudrate;
			USART_InitStructure.USART_WordLength = bitLength;
			USART_InitStructure.USART_StopBits = stopbit;
			USART_InitStructure.USART_Parity = parity;
			USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
			USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
			USART_Init(USART2, &USART_InitStructure);
			USART_Cmd(USART2, ENABLE);
			break;
		case F407_UART_CH3:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//ʹ��USART3ʱ��
			USART_InitStructure.USART_BaudRate = baudrate;
			USART_InitStructure.USART_WordLength = bitLength;
			USART_InitStructure.USART_StopBits = stopbit;
			USART_InitStructure.USART_Parity = parity;
			USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
			USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
			USART_Init(USART3, &USART_InitStructure);
			USART_Cmd(USART3, ENABLE);
			break;
		case F407_UART_CH4:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);//ʹ��UART4ʱ��
			USART_InitStructure.USART_BaudRate = baudrate;
			USART_InitStructure.USART_WordLength = bitLength;
			USART_InitStructure.USART_StopBits = stopbit;
			USART_InitStructure.USART_Parity = parity;
			USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
			USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
			USART_Init(UART4, &USART_InitStructure);
			USART_Cmd(UART4, ENABLE);
			break;
		case F407_UART_CH5:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);//ʹ��UART5ʱ��
			USART_InitStructure.USART_BaudRate = baudrate;
			USART_InitStructure.USART_WordLength = bitLength;
			USART_InitStructure.USART_StopBits = stopbit;
			USART_InitStructure.USART_Parity = parity;
			USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
			USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
			USART_Init(UART5, &USART_InitStructure);
			USART_Cmd(UART5, ENABLE);
			break;
		case F407_UART_CH6:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6,ENABLE);//ʹ��USART1ʱ��
			USART_InitStructure.USART_BaudRate = baudrate;
			USART_InitStructure.USART_WordLength = bitLength;
			USART_InitStructure.USART_StopBits = stopbit;
			USART_InitStructure.USART_Parity = parity;
			USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
			USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
			USART_Init(USART6, &USART_InitStructure);
			USART_Cmd(USART6, ENABLE);
			break;
		default:
			break;
	}
}

static void
F407_setUartITConfig(F407UARTChannel ch)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	switch (ch){
#if defined (STM32F40_41xxx) || defined (STM32F427_437xx) || defined (STM32F429_439xx) || defined (STM32F401xx) || defined (STM32F411xE)
		case F407_UART_CH1:
			USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//��������ж�
			
			//Usart1 NVIC ����
			NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//����1�ж�ͨ��
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=7;//��ռ���ȼ�7
			NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//�����ȼ�0
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 		//IRQͨ��ʹ��
			NVIC_Init(&NVIC_InitStructure); //����ָ���Ĳ�����ʼ��VIC�Ĵ�����
			break;
#endif
#if defined (STM32F40_41xxx) || defined (STM32F427_437xx) || defined (STM32F429_439xx) || defined (STM32F401xx) || defined (STM32F411xE)
		case F407_UART_CH2:
			USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//��������ж�
			
			//Usart1 NVIC ����
			NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//����1�ж�ͨ��
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=7;//��ռ���ȼ�7
			NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//�����ȼ�0
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 		//IRQͨ��ʹ��
			NVIC_Init(&NVIC_InitStructure); //����ָ���Ĳ�����ʼ��VIC�Ĵ�����
			break;
#endif
#if defined (STM32F40_41xxx) || defined (STM32F427_437xx) || defined (STM32F429_439xx)
		case F407_UART_CH3:
			USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//��������ж�
			
			//Usart1 NVIC ����
			NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;//����1�ж�ͨ��
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=7;//��ռ���ȼ�7
			NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//�����ȼ�0
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 		//IRQͨ��ʹ��
			NVIC_Init(&NVIC_InitStructure); //����ָ���Ĳ�����ʼ��VIC�Ĵ�����
			break;
#endif
#if defined (STM32F40_41xxx) || defined (STM32F427_437xx) || defined (STM32F429_439xx)
		case F407_UART_CH4:
			USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//��������ж�
			
			//Usart1 NVIC ����
			NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;//����1�ж�ͨ��
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=7;//��ռ���ȼ�7
			NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//�����ȼ�0
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 		//IRQͨ��ʹ��
			NVIC_Init(&NVIC_InitStructure); //����ָ���Ĳ�����ʼ��VIC�Ĵ�����
			break;
#endif
#if defined (STM32F40_41xxx) || defined (STM32F427_437xx) || defined (STM32F429_439xx)
		case F407_UART_CH5:
			USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);//��������ж�
			
			//Usart1 NVIC ����
			NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;//����1�ж�ͨ��
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=7;//��ռ���ȼ�7
			NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//�����ȼ�0
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 		//IRQͨ��ʹ��
			NVIC_Init(&NVIC_InitStructure); //����ָ���Ĳ�����ʼ��VIC�Ĵ�����
			break;
#endif
#if defined (STM32F40_41xxx) || defined (STM32F427_437xx) || defined (STM32F429_439xx) || defined (STM32F401xx) || defined (STM32F411xE)
		case F407_UART_CH6:
			USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);//��������ж�
			
			//Usart1 NVIC ����
			NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;//����1�ж�ͨ��
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=7;//��ռ���ȼ�7
			NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//�����ȼ�0
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 		//IRQͨ��ʹ��
			NVIC_Init(&NVIC_InitStructure); //����ָ���Ĳ�����ʼ��VIC�Ĵ�����
			break;
#endif
		default:
			break;
	}
}

void USART1_IRQHandler(void)                	//����1�жϷ������
{
	u8 data;
	BaseType_t Result,xHigherPriorityTaskWoken=pdFALSE;
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�
	{
		data = USART_ReceiveData(USART1);//(USART1->DR);	//��ȡ���յ�������
		RB_putRingBuffer(s_EntryNo_usart1, data);

		if(DAMReceiverTask_Handler != NULL)
		{
			Result = xTaskNotifyFromISR(DAMReceiverTask_Handler, EVENTBIT_1, eSetBits, &xHigherPriorityTaskWoken);
			if(Result != pdFAIL)
			{
				portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
			}
		}
	}

} 

void USART2_IRQHandler(void)                	//����1�жϷ������
{
	u8 data;
	BaseType_t Result,xHigherPriorityTaskWoken;
	
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		data = USART_ReceiveData(USART2);//(USART1->DR);	//��ȡ���յ�������
		RB_putRingBuffer(s_EntryNo_usart2, data);

		if(DAMReceiverTask_Handler != NULL)
		{
			Result = xTaskNotifyFromISR(DAMReceiverTask_Handler, EVENTBIT_2, eSetBits, &xHigherPriorityTaskWoken);
			if(Result != pdFAIL)
			{
				portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
			}
		}
	}
} 

void USART3_IRQHandler(void)
{
#if 0
	u8 res;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{
		res =USART_ReceiveData(USART3);
		if((USART3_RX_STA&(1<<15))==0)
		{
			if(USART3_RX_STA<USART3_MAX_RECV_LEN)
			{
				TIM_SetCounter(TIM7,0);
				if(USART3_RX_STA==0)
					TIM_Cmd(TIM7, ENABLE);
				USART3_RX_BUF[USART3_RX_STA++]=res;
			}else
			{
				USART3_RX_STA|=1<<15;
			}
		}
	}
#endif
}

static void UART_SendDataCH1(unsigned char *data, u16 len)
{
	u16 j;
	for(j=0;j<len;j++)
	{
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
		USART_SendData(USART1,*(data+j));
	}
}

static void UART_SendDataCH2(unsigned char *data, u16 len)
{
	u16 j;
	for(j=0;j<len;j++)
	{
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);
		USART_SendData(USART2,*(data+j));
	}
}

static void UART_SendDataCH3(unsigned char *data, u16 len)
{
	u16 j;
	for(j=0;j<len;j++)
	{
		while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET);
		USART_SendData(USART3,*(data+j));
	}
}

static void UART_SendDataCH4(unsigned char *data, u16 len)
{
	u16 j;
	for(j=0;j<len;j++)
	{
		while(USART_GetFlagStatus(UART4,USART_FLAG_TC)==RESET);
		USART_SendData(UART4,*(data+j));
	}
}

static void UART_SendDataCH5(unsigned char *data, u16 len)
{
	u16 j;
	for(j=0;j<len;j++)
	{
		while(USART_GetFlagStatus(UART5,USART_FLAG_TC)==RESET);
		USART_SendData(UART5,*(data+j));
	}
}

static void UART_SendDataCH6(unsigned char *data, u16 len)
{
	u16 j;
	for(j=0;j<len;j++)
	{
		while(USART_GetFlagStatus(USART6,USART_FLAG_TC)==RESET);
		USART_SendData(USART6,*(data+j));
	}
}

