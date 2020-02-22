/*������������������������������������������������������������������������������
	�w�b�_�[�t�@�C����荞��
������������������������������������������������������������������������������*/
/*����������������������
�@��System Information��
�@����������������������*/
/* nothing */
/*����������������������������
�@��Environment Information ��
�@����������������������������*/
#include "../../../Common/Common.h"		/* Common Information	*/
#include "../../../Platform/Platform.h"		/* Platform Information	*/
/*��������������������
�@��User Information��
�@��������������������*/
#include "./SPIMN103LF15.h"

/*������������������������������������������������������������������������������
	�O���ϐ���`�ƊO���ϐ��ւ̃����N�@[External Linkage]
������������������������������������������������������������������������������*/
/* nothing */

/*������������������������������������������������������������������������������
	�����ϐ���`�@[Internal Linkage]
������������������������������������������������������������������������������*/
private void	SPIP_nopLoop(unsigned short);		/* �Z���E�F�C�g�p	*/

/*������������������������������������������������������������������������������
	�����֐��v���g�^�C�v�錾�@[Internal Linkage]
������������������������������������������������������������������������������*/
/* nothing */

/*������������������������������������������������������������������������������
	�O���֐���`(public)�@[External Linkage]
������������������������������������������������������������������������������*/
/* nothing */

/*������������������������������������������������������������������������������
	�O���֐���`(package)�@[External Linkage]
������������������������������������������������������������������������������*/
/*********************************************************************
	funcname:	SPIP_execResume
	contents:	Resume����
	��    ��:	�Ȃ�
	��    �l:	�Ȃ�
	��    �l:	�Ȃ�
*********************************************************************/
package void
SPIP_execResume(unsigned char ch)
{
	switch(ch)
	{
		case SPIP_CH0:
		case SPIP_CH2:
		case SPIP_CH3:
		case SPIP_CH4:
		case SPIP_CH5:
		case SPIP_CH6:
		case SPIP_CH7:
		case SPIP_CH8:
		case SPIP_CH9:
		break;
		case SPIP_CH1:
		SPI1_PORT_ENTRY_INIT();
		SPI1_BAUTRATE_SET();
		break;
		default:
		break;
	}
}

/*********************************************************************
	funcname:	SPIP_execSuspend
	contents:	Suspend����
	��    ��:	�Ȃ�
	��    �l:	�Ȃ�
	��    �l:	�Ȃ�
*********************************************************************/
package void
SPIP_execSuspend(unsigned char ch)
{
	switch(ch)
	{
		case SPIP_CH0:
		case SPIP_CH2:
		case SPIP_CH3:
		case SPIP_CH4:
		case SPIP_CH5:
		case SPIP_CH6:
		case SPIP_CH7:
		case SPIP_CH8:
		case SPIP_CH9:			
		break;
		case SPIP_CH1:
		SPI1_CLOSE();
		SPI1_PORT_EXIT_INIT();
		break;
		default:
		break;
	}
}

/*********************************************************************
	funcname:	SPIP_enable
	contents:	SPI�R���g���[�������������
	��    ��:	�Ȃ�
	��    �l:	�Ȃ�
	��    �l:	�Ȃ�
*********************************************************************/
package void
SPIP_enable(unsigned char ch)
{
	switch(ch)
	{
		case SPIP_CH0:
		case SPIP_CH2:
		case SPIP_CH3:
		case SPIP_CH4:
		case SPIP_CH5:
		case SPIP_CH6:
		case SPIP_CH7:
		case SPIP_CH8:
		case SPIP_CH9:
		break;
		case SPIP_CH1:
		SPI1_OPEN();
		break;
		default:
		break;
	}
}

/*********************************************************************
	funcname:	SPIP_disable
	contents:	SPI�R���g���[��������~����
	��    ��:	�Ȃ�
	��    �l:	�Ȃ�
	��    �l:	��~�O�Ƀo�X���J������
*********************************************************************/
package void
SPIP_disable(unsigned char ch)
{
	switch(ch)
	{
		case SPIP_CH0:
		case SPIP_CH2:
		case SPIP_CH3:
		case SPIP_CH4:
		case SPIP_CH5:
		case SPIP_CH6:
		case SPIP_CH7:
		case SPIP_CH8:
		case SPIP_CH9:	
		break;
		case SPIP_CH1:
		SPI1_CLOSE();
		break;
		default:
		break;
	}
}
/*********************************************************************
	funcname:	SPIP_changeEdge
	contents:	SPI�R���g���[��������~����
	��    ��:	�Ȃ�
	��    �l:	�Ȃ�
	��    �l:	��~�O�Ƀo�X���J������
*********************************************************************/
package void
SPIP_changeEdge(unsigned char ch,unsigned char edge)
{
	switch(ch)
	{
		case SPIP_CH0:
		case SPIP_CH2:
		case SPIP_CH3:
		case SPIP_CH4:
		case SPIP_CH5:
		case SPIP_CH6:
		case SPIP_CH7:
		case SPIP_CH8:			
		case SPIP_CH9:
		break;
		case SPIP_CH1:
			if(edge == 0)/*rising edge sample*/
			{
				bCPU_SC1RSTN = 0;				/*Register SC1MD3,Serial Reset*/
				bCPU_SC1RSRN = 0;				/*Register SC1MD3,Serial Reset*/
				bCPU_BRTM_S1_EN = 0;			/*BuadRate Timer Off*/								
				ucCPU_SC1MD0 = 0x07;			/*0000 0111
												Clock polarity "H";
												Communication Mode "Normal Mode";
												MSB Fisrst;Disable Start Conditon;
												8bits Transmit*/
				bCPU_BRTM_S1_EN = 1;			/*BuadRate Timer On*/																	
				bCPU_SC1RSTN = 1;				/*Register SC1MD3,Serial Open*/
				bCPU_SC1RSRN = 0;				/*Register SC1MD3,This Bit Must be 0*/	
			}
			else/*falling edge sample*/
			{
				bCPU_SC1RSTN = 0;				/*Register SC1MD3,Serial Reset*/
				bCPU_SC1RSRN = 0;				/*Register SC1MD3,Serial Reset*/
				bCPU_BRTM_S1_EN = 0;			/*BuadRate Timer Off*/								
				ucCPU_SC1MD0 = 0x87;			/*1000 0111
												Clock polarity "L";
												Communication Mode "Normal Mode";
												MSB Fisrst;Disable Start Conditon;
												8bits Transmit*/
				bCPU_BRTM_S1_EN = 1;			/*BuadRate Timer On*/																	
				bCPU_SC1RSTN = 1;				/*Register SC1MD3,Serial Open*/
				bCPU_SC1RSRN = 0;				/*Register SC1MD3,This Bit Must be 0*/	
			}
		break;
		default:
		break;
	}
}

/*********************************************************************
	funcname:	SPIP_transmitByte
	contents:	�f�[�^���M���s��
	��    ��:	data : ���M����o�C�g�f�[�^
	��    �l:	�Ȃ�
	��    �l:	�Ȃ�
*********************************************************************/
package void
SPIP_transmitByte(unsigned char ch,unsigned char data)
{
	unsigned short i;
	unsigned char dummy;
	i = 0;
	dummy = 0;
	switch(ch)
	{
		case SPIP_CH0:
		case SPIP_CH2:
		case SPIP_CH3:
		case SPIP_CH4:
		case SPIP_CH5:
		case SPIP_CH6:
		case SPIP_CH7:
		case SPIP_CH8:
		case SPIP_CH9:
		break;
		case SPIP_CH1:
		while (bCPU_SC1TEMP)
		{
			if(i<SPI_WAIT_CNT_MAX)
			{
				i++;
			}
			else
			{
				i = 0;
				break;
			}		
		}
		dummy = SPI1_RecDataReg; /*dummy read for clear read flag*/
		SPI1_TraDataReg =data; /*send byte data*/
	   while(!bCPU_SC1REMP)
	   {
		   	if(i<SPI_WAIT_CNT_MAX)
			{
				i++;
			}
			else
			{
				i = 0;
				break;
			}		
	   }
	   dummy = SPI1_RecDataReg; /*dummy read for clear read flag*/
		break;
		default:
		break;
	}
	
	
}
/*********************************************************************
	funcname:	SPIP_ReceiveByte
	contents:	�f�[�^���M���s��
	��    ��:	�Ȃ�
	��    �l:	data : ���M����o�C�g�f�[�^
	��    �l:	�Ȃ�
*********************************************************************/

package unsigned char 
SPIP_ReceiveByte(unsigned char ch)
{
	unsigned char recdata;
	unsigned char dummy;
	unsigned short i;
	i = 0;

	switch(ch)
	{
		case SPIP_CH0:
		case SPIP_CH2:
		case SPIP_CH3:
		case SPIP_CH4:
		case SPIP_CH5:
		case SPIP_CH6:
		case SPIP_CH7:
		case SPIP_CH8:		
		case SPIP_CH9:
		break;
		case SPIP_CH1:
			while (bCPU_SC1TEMP)
			{
				if(i<SPI_WAIT_CNT_MAX)
				{
					i++;
				}
				else
				{
					i = 0;
					break;
				}		
			}
			dummy = SPI1_RecDataReg; /*dummy read for clear read flag*/
			SPI1_TraDataReg =0xff; /*send byte data*/
		   while(bCPU_SC1RBSY&&(!bCPU_SC1REMP))
		   {
				if(i<SPI_WAIT_CNT_MAX){
					i++;
				}
				else{
					i = 0;
					break;
				}	
		   }
			recdata = SPI1_RecDataReg;
			break;
		default: 
			break;
	}
	
	return recdata;   
}


/*������������������������������������������������������������������������������
	�����֐���`�@[Internal Linkage]
������������������������������������������������������������������������������*/
/*********************************************************************
	funcname:	SPIP_nopLoop
	contents:	�Z���E�F�C�g���Ԃ����
	��    ��:	n : �񂷉�
	��    �l:	�Ȃ�
	��    �l:	�񂵂Ă���ԁACPU���L����̂ŏ����Ȓl��
			�w�肷�邱�ƁB
*********************************************************************/
private void
SPIP_nopLoop(unsigned short n)
{
	while (n > 0) {
		n--;
	}
}

