#include "../../Common/Common.h"		/* Common Information	*/
#include "../../Platform/Platform.h"		/* Platform Information	*/

#include "./Platform/IICPlatform.h"		/* �@��ˑ��@�\�̃w�b�_		*/
#include "./IIC.h"

/*********************************************************************
	funcname: IIC_execResume
	contents: IIC�h���C�o��Resume����������
	��    ��: �Ȃ�
	��    �l: �Ȃ�
	��    �l: �v���b�g�z�[���̎g�p�|�[�g������
*********************************************************************/
public void
IIC_Init(void)
{
	IIC_execResume();
}

/*********************************************************************
	funcname: IIC_execResume
	contents: IIC�h���C�o��Resume����������
	��    ��: �Ȃ�
	��    �l: �Ȃ�
	��    �l: �v���b�g�z�[���̎g�p�|�[�g������
*********************************************************************/
public void
IIC_execResume(void)
{
	IICP_execResume();
}

/*********************************************************************
	funcname: IIC_suspend
	contents: IIC�h���C�o��Suspend����������
	��    ��: �Ȃ�
	��    �l: �Ȃ�
	��    �l: �Ȃ�
*********************************************************************/
public void
IIC_execSuspend(void)
{
	IICP_disable();
	IICP_execSuspend();
}

/*********************************************************************
	funcname: IIC_enable
	contents: IIC�h���C�o�̓����������
	��    ��: �Ȃ�
	��    �l: �Ȃ�
	��    �l: MPU��IIC�h���C�o�@�\��L���ɂ��邾���ɂ��܂����B
		  ���̑��褃C�l�[�u����̍ŏ��̃f�[�^�]���̍�(IIC_transmitData)�A
		  �o�X���r�o���ǂ����`�F�b�N����Ƃ���ň���������̂ŁA������
		  �r�o�𐶐����ăo�X���J�����邱�Ƃɂ��܂��B
*********************************************************************/
public void
IIC_enable(void)
{
	IICP_enable();
}

/*********************************************************************
	funcname: IIC_disable
	contents: IIC�h���C�o�̓�����~����
	��    ��: �Ȃ�
	��    �l: �Ȃ�
	��    �l: �Ȃ�
*********************************************************************/
public void
IIC_disable(void)
{
	IICP_disable();
}

/*********************************************************************
	funcname: IIC_transmitData
	contents: �f�[�^���M���s��
	��    ��: byteNum : ���M�f�[�^��
		  pdata   : ���M�f�[�^�擪�ւ̃|�C���^
	��    �l: 0: ����I��
		 -1: ACK���Ԃ��Ă��Ȃ�����
		 -2: �X�g�b�v�R���f�B�V�����ɂȂ�Ȃ�����
		 -3: �X�^�[�g�R���f�B�V�����ɂȂ�Ȃ�����
		 -4: �������l���ł��Ȃ�����
	��    �l: ���M�f�[�^�擪�̓X���[�u�A�h���X�Ƃ���
		  IIC�X���[�u�̓d�������Ă�����肷��܂Ŏ��Ԃ�
		  ������܂�(1msec��)�B���̂��߁A�d��������10msec��
		  ��������ɂ��̊֐����Ă�ł��������B
*********************************************************************/
public long
IIC_transmitData(unsigned long byteNum, unsigned char *pData)
{
	/*************************************************************
		�����ϐ���`
	*************************************************************/
	long			result = 0;		/* �G���[�̗L����� */
	unsigned char	*p;				/* �f�[�^�ւ̃|�C���^ */
	unsigned char	retry;
	unsigned char	num;
	/*************************************************************
		IIC�h���C�o �f�[�^���M
	*************************************************************/
	if( IICnBUSBSY == 1 ){			/* �o�X���������Ă��Ȃ�	*/
		IICP_createStopCondition(); /* STOP CONDITION�𐶐����� */
		for( retry = IIC_MAX_LOOP_COUNT; retry > 0; retry-- ){

		
			if( IICP_isStopCondition() == 1 ){
				break;				/* STOP CONDITION�ɂȂ���	*/
			}
		}
		/* ���g���C�J�E���g�� 0 �� STOP CONDITION�ɂȂ�Ȃ����� */
		if( retry == 0 ){
			result = -2;			/* STOP CONDITION�ɂȂ�Ȃ����� */
		}
	}
	#if 0
	EN_RESTART;
	#endif
	if( !result ){
		num = byteNum - 1;
		p = (unsigned char *)pData; 	/* char�^�̃|�C���^�ɃL���X�g	*/
		while ( byteNum > 0 ) {
			if(byteNum <= num)
				DISABLE_START;
			IICP_transmitByte(*p);	/* 1�o�C�g���M					*/
			p++;
			if ( !IICP_detectACK() ) {
				result = -1;			/* ACK���Ԃ��Ă��Ȃ�			*/
				break;
			}
			byteNum--;
		}

		EN_RESTART;
		if(num > 1) {
			IICP_createStopCondition(); /* STOP CONDITION�𐶐����� */
			for( retry = IIC_MAX_LOOP_COUNT; retry > 0; retry-- ){
				if( IICP_isStopCondition() == 1 ){
					break;				/* STOP CONDITION�ɂȂ���	*/
				}
			}
			/* ���g���C�J�E���g�� 0 �� STOP CONDITION�ɂȂ�Ȃ����� */
			if( retry == 0 ){
				result = -2;			/* STOP CONDITION�ɂȂ�Ȃ����� */
			}
		}
	}

	return result;					/* �G���[����Ԃ�		*/
}

public long
IIC_receiveData(unsigned long byteNum, 
						 unsigned char ucCmdData,  
						 unsigned char *pRcvData)
{
	/*************************************************************
		�����ϐ���`
	*************************************************************/
	long			result = 0;		/* �G���[�̗L����� */
	unsigned char	retry;
	#if 0
	if ( !IICP_isStopCondition() ) {		/* STOP CONDITION�łȂ� */
			for ( retry = IIC_MAX_LOOP_COUNT; retry > 0; retry-- ) {
				IICP_createStopCondition(); /* STOP CONDITION�𐶐����� */
				if ( IICP_isStopCondition() == 1 ) {
					break;			/* STOP CONDITION�ɂȂ���	*/
				}
			}
			/* ���g���C�J�E���g�� 0 �� STOP CONDITION�ɂȂ�Ȃ����� */
			if ( retry == 0 ) {
				result = -2;			/* STOP CONDITION�ɂȂ�Ȃ����� */
			}
		}
	#endif
	if ( !result ) {
		IICP_transmitByte(ucCmdData);
		if ( !IICP_detectACK() ) {
				IICP_set_receive_err();
				return  (-1);		/* ACK���Ԃ��Ă��Ȃ�		*/
		}
		while ( byteNum > 0 ) {
			if(byteNum==1)
				*((unsigned char*)pRcvData)= IICP_receiveByte(0x0B);
			else
				*((unsigned char*)pRcvData)= IICP_receiveByte(0x0A);
			pRcvData++;
			byteNum--;
		}
		
		IICP_createStopCondition();		/* STOP CONDITION�𐶐�����	*/
		
	}
}

