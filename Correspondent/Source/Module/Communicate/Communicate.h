#ifndef COMMUNICATE_H
#define COMMUNICATE_H

#define	USB_VAL_DLE	(0x9F)
#define	USB_VAL_STX	(0x02)
#define	USB_VAL_ETX	(0x03)

/* 制御符号定義	*/
#define	DAMC_VAL_DLE	(0x9F)
#define	DAMC_VAL_STX	(0x02)
#define	DAMC_VAL_ETX	(0x03)

#define DAMC_TRANS_BUF_SIZE 100

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	typedef宣言
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
/*┌──────────────┐
　│受信状態			│
　└──────────────┘*/
typedef enum {
	DAMC_STS_DLE_RECEIVE_WAIT,	/* DLE受信待ち状態	*/
	DAMC_STS_STX_RECEIVE_WAIT,	/* STX受信待ち状態	*/
	DAMC_STS_NORMAL_RECEIVE,	/* 通常受信状態		*/
	DAMC_STS_EXT_RECEIVE_WAIT	/* EXT受信待ち状態	*/
} EDAMCReceiveStatus;

#endif

