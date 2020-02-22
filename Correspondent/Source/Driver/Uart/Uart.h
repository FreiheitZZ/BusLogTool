#ifndef _UART_H
#define _UART_H

typedef enum{
	UART_PARITY_NON = 0,
	UART_PARITY_ODD,
	UART_PARITY_EVEN
}	EUARTParityType;

typedef enum{
	UART_BITLENGTH_8BIT = 0,
	UART_BITLENGTH_9BIT
}	EUARTBitLengthType;

typedef enum{
	UART_STOPBIT_1 = 0,
	UART_STOPBIT_0_5,
	UART_STOPBIT_2,
	UART_STOPBIT_1_5
}	EUARTStopBitType;

typedef enum{
	UART_MODE_STOP = 0,	/* ��~		*/
	UART_MODE_RECEIVE,	/* ��M�̂�	*/
	UART_MODE_TRANSMIT,	/* ���M�̂�	*/
	UART_MODE_INTERACTIVE	/* ����M	*/
}	EUARTComMode;

typedef	enum{
	UART_ERR_NONE = 0,	/* �G���[�Ȃ�		*/
	UART_ERR_PARITY,	/* �p���e�B�G���[	*/
	UART_ERR_FRAMING,	/* �t���[�~���O�G���[	*/
	UART_ERR_OVERRUN	/* �I�[�o�[�����G���[	*/
}	EUARTComError;

typedef	enum{
	DMA_STAT_STOP,		/* �]����~��ԁi�]���\��ԁj	*/
	DMA_STAT_RUN		/* �]�������   (�]���s���)	*/
}	EDMATransferState;

typedef	enum{
	UART_STAT_STOP,		/* �]����~��ԁi�]���\��ԁj	*/
	UART_STAT_RUN		/* �]�������   (�]���s���)	*/
}	EUARTTransferState;

typedef	enum{
	DMA_MODE_OFF = 0,	/* DMA���g�p	*/
	DMA_MODE_ON_CH0,	/* DMA CH0�g�p	*/
	DMA_MODE_ON_CH1,	/* DMA CH1�g�p	*/
	DMA_MODE_ON_CH2,	/* DMA CH2�g�p	*/
	DMA_MODE_ON_CH3	/* DMA CH3�g�p	*/
}	EUARTDMAMode;

extern void			UART_entryUart		(unsigned char, unsigned long, EUARTParityType, unsigned char, unsigned char);
extern void			UART_exitUart		(unsigned char);
extern void			UART_stopUart		(unsigned char);
extern void			UART_transmitData(unsigned char ch ,char* fmt,...);
extern EDMATransferState	UART_getDMATransferState(unsigned char);
extern EUARTTransferState	UART_getUARTTransferState(unsigned char);
extern unsigned char		UART_getReceiveData	(unsigned char);
extern EUARTComError		UART_getErrorStatus	(unsigned char);

#endif
