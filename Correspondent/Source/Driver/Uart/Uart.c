#include "stdarg.h"
#include "./Uart_STM32F407/UartSTM32F407.h"
#include "./Uart.h"

/*********************************************************************
	funcname�FUART_entryUart()
	contents�FUART�́�ch���g�p����
	��    ���F unsigned char	UART ch		<IN>
		   unsigned long	�{�[���[�g	<IN>
		   EUARTParityType	�p���e�B	<IN>
		   unsigned char	BIT��		<IN>
		   unsigned char	�X�g�b�vBIT	<IN>
		   ID (*)(void)		��M�n���h��	<IN>
		   EUARTDMAMode		DMA�ݒ�		<IN>
	�� �� �l�F
	��    �l�F�Ȃ�
*********************************************************************/
extern void
UART_entryUart( unsigned char	ch,			/* ch		*/
		unsigned long	baudrate,		/* �{�[���[�g	*/
		EUARTParityType	eParity,		/* �p���e�B	*/
		unsigned char	bitLength,		/* BIT��	*/
		unsigned char	stopbit		/* �X�g�b�vBIT	*/
/*		EUARTDMAMode	eDMAMode	*//* DMA�ݒ�	*/
			 )
{
	/*************************************************************
		�����ϐ���`
	*************************************************************/
	/* noting */
	/*************************************************************
		UART�́�ch���g�p����
	*************************************************************/
	F407_entryUart(ch, baudrate, eParity, bitLength, stopbit);
	//F407_setDMAMode(ch, eDMAMode);
}

/*********************************************************************
	funcname�FUART_entryUart()
	contents�FUART�́�ch�𖢎g�p����
	��    ���Funsigned char		UART ch		<IN>
	�� �� �l�F�Ȃ�
	��    �l�F�Ȃ�
*********************************************************************/
extern void
UART_exitUart(unsigned char ch)
{
	/*************************************************************
		�����ϐ���`
	*************************************************************/
	/* noting */
	/*************************************************************
		UART�́�ch�𖢎g�p����
	*************************************************************/
	F407_exitUart(ch);
}

/*********************************************************************
	funcname�FUART_stopUart()
	contents�F��ch�̓�����~����
	��    ���Funsigned char		UART ch		<IN>
	�� �� �l�F�Ȃ�
	��    �l�F
		�y�J�n/��~�����z
		    �J�n���F���荞�݂̋���UART����J�n������M����J�n
		    ��~���F����M�����~��UART�����~�����荞�݂̋֎~
*********************************************************************/
extern void
UART_stopUart(unsigned char ch)
{
	/*************************************************************
		�����ϐ���`
	*************************************************************/
	/* noting */
	/*************************************************************
		��ch�̓�����~����
	*************************************************************/
	F407_stopUart(ch);
}
/*********************************************************************
	funcname�FUART_transmitData()
	contents�F���̃f�[�^�𑗐M����
	��    ���Funsigned char		UART ch		<IN>
		  unsigned char*	�f�[�^�A�h���X	<IN>
		  unsigned long		�f�[�^�T�C�Y	<IN>
	�� �� �l�F�Ȃ�
	��    �l�F�Ȃ�
*********************************************************************/
extern void
UART_transmitData(unsigned char ch ,char* fmt,...)
{
	unsigned int len;
	unsigned char USART_TX_BUF[400];
	
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char*)USART_TX_BUF,fmt,ap);
	va_end(ap);
	len=strlen((const char*)USART_TX_BUF);
	F407_transmitData(ch , USART_TX_BUF, len);
}
/*********************************************************************
	funcname�FUART_getDMATransferState()
	contents�FDMA�]����Ԃ��擾����
	��    ���Funsigned char		DMA�`���l��	<IN>
	�� �� �l�FEDMATransferState	DMA�]�����
		  DMA_STAT_STOP		�]����~��ԁi�]���\��ԁj
		  DMA_STAT_RUN		�]�������   (�]���s���)
	��    �l�F
	DMA�]�����́A�O��̓]����UART_transmitData(...)�œn����
	�u���M�f�[�^�A�h���X�v�o�b�t�@�ɏ������܂Ȃ��ŉ������B
	
	�y�I�I�I���ӁI�I�I�z
	DMA�]����~��Ԃł����Ă��AUART�]�����I�����Ă��Ȃ��ꍇ������܂��B
	�A���]������ꍇ�͕K��UART_getDMATransferState()�ɂ�
	UART�]���������m�F���Ă��������B
*********************************************************************/
extern EDMATransferState
UART_getDMATransferState(unsigned char dmach)
{
	/*************************************************************
		�����ϐ���`
	*************************************************************/
	EDMATransferState	eState;
	/*************************************************************
		�]����Ԃ��`�F�b�N
		TCn(DCHCn.7)�̏�Ԃ�����B
		DMA�]���̍Ō�̓]�����ɃZ�b�g�i�P�j����A
		�ǂݏo���ɂ���ăN���A�i�O�j����܂��B
	*************************************************************/
	return eState;
}

/*********************************************************************
	funcname�FUART_getUARTTransferState()
	contents�FUART�]����Ԃ��擾����
	��    ���Funsigned char		UART�`���l��	<IN>
	�� �� �l�FEUARTTransferState	UART�]�����
		  UART_STAT_STOP	�]����~��ԁi�]���\��ԁj
		  UART_STAT_RUN		�]�������   (�]���s���)
	��    �l�F�Ȃ�
*********************************************************************/
extern EUARTTransferState
UART_getUARTTransferState(unsigned char dmach)
{
	/*************************************************************
		�����ϐ���`
	*************************************************************/
	EUARTTransferState	eState;
	/*************************************************************
		�]����Ԃ��`�F�b�N
		UAnTSF(UAnSTR.7)�̏�Ԃ�����B
		UAnTX���W�X�^�ւ̏����݂ŃZ�b�g�i�P�j����A
		�]���������UAnTX���W�X�^�Ɏ��̃f�[�^�]�����Ȃ�����
		�Ƃ��ɃN���A�i�O�j����܂��B
		���A���]�����͏��"�P"�ɂȂ��Ă���B
	*************************************************************/
	return eState;
}

/*********************************************************************
	funcname�FUART_getReceiveData()
	contents�F��M�f�[�^���擾����
	��    ���Funsigned char		UART ch		<IN>
	�� �� �l�F�Ȃ�
	��    �l�F�Ȃ�
*********************************************************************/
extern unsigned char
UART_getReceiveData(unsigned char ch)
{
	/*************************************************************
		�����ϐ���`
	*************************************************************/
	/* noting */
	/*************************************************************
		��M�f�[�^���擾����
	*************************************************************/
}

/*********************************************************************
	funcname�FUART_getErrorStatus()
	contents�F��M�G���[�����擾����
	��    ���Funsigned char		UART ch		<IN>
	�� �� �l�F�Ȃ�
	��    �l�F
	�f�[�^����M�����ۂ͕K���G���[���̎擾���s���Ă��������B
*********************************************************************/
extern EUARTComError
UART_getErrorStatus(unsigned char ch)
{
	/*************************************************************
		�����ϐ���`
	*************************************************************/
	unsigned char	error  = 0x00;
	EUARTComError	eError = UART_ERR_NONE;
	/*************************************************************
		��M�G���[�����擾����
	*************************************************************/
	/*************************************************************
		�ϊ�
	*************************************************************/
	
	return	eError;
}

