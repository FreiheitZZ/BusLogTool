#ifndef	IIC_HEADER_DEFINED
#define	IIC_HEADER_DEFINED

#define	IIC_MAX_LOOP_COUNT	255		/* ループカウンタの最大値 */

public void IIC_execResume(void);				/* IICドライバのResume処理をする	*/
public void IIC_execSuspend(void);				/* IICドライバのSuspend処理をする	*/
public void IIC_enable(void);					/* IICドライバ動作を許可する		*/
public void IIC_disable(void);					/* IICドライバ動作を停止する		*/
public long IIC_transmitData(unsigned long byteNum, unsigned char *pData);	/* データ送信を行う			*/
public long IIC_receiveData(unsigned long byteNum, 
						 unsigned char ucCmdData, 
						 unsigned char *pRcvData);

#endif