#ifndef COMMUNICATE_H
#define COMMUNICATE_H

#define	USB_VAL_DLE	(0x9F)
#define	USB_VAL_STX	(0x02)
#define	USB_VAL_ETX	(0x03)

/* �������Ŷ��x	*/
#define	DAMC_VAL_DLE	(0x9F)
#define	DAMC_VAL_STX	(0x02)
#define	DAMC_VAL_ETX	(0x03)

#define DAMC_TRANS_BUF_SIZE 100

/*������������������������������������������������������������������������������
	typedef����
������������������������������������������������������������������������������*/
/*��������������������������������
��������״�B			��
����������������������������������*/
typedef enum {
	DAMC_STS_DLE_RECEIVE_WAIT,	/* DLE���Ŵ���״�B	*/
	DAMC_STS_STX_RECEIVE_WAIT,	/* STX���Ŵ���״�B	*/
	DAMC_STS_NORMAL_RECEIVE,	/* ͨ������״�B		*/
	DAMC_STS_EXT_RECEIVE_WAIT	/* EXT���Ŵ���״�B	*/
} EDAMCReceiveStatus;

#endif

