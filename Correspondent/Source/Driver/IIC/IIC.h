#ifndef	IIC_HEADER_DEFINED
#define	IIC_HEADER_DEFINED

#define	IIC_MAX_LOOP_COUNT	255		/* ���[�v�J�E���^�̍ő�l */

public void IIC_execResume(void);				/* IIC�h���C�o��Resume����������	*/
public void IIC_execSuspend(void);				/* IIC�h���C�o��Suspend����������	*/
public void IIC_enable(void);					/* IIC�h���C�o�����������		*/
public void IIC_disable(void);					/* IIC�h���C�o������~����		*/
public long IIC_transmitData(unsigned long byteNum, unsigned char *pData);	/* �f�[�^���M���s��			*/
public long IIC_receiveData(unsigned long byteNum, 
						 unsigned char ucCmdData, 
						 unsigned char *pRcvData);

#endif