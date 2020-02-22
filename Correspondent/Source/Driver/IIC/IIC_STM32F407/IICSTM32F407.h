#ifndef	IICP_HEADER_DEFINED
#define	IICP_HEADER_DEFINED

#define		F407_IIC_CH1_PORT		F407_IIC_CH1_PORT_PB_6_7
#define		F407_IIC_CH2_PORT		F407_IIC_CH2_PORT_PB_10_11
#define		F407_IIC_CH3_PORT		F407_IIC_CH3_PORT_PA_8_PC_9

typedef enum{
	F407_IIC_CH1 = 1,
	F407_IIC_CH2,
	F407_IIC_CH3,
	F407_IIC_CH4,
	F407_IIC_CH5,
	F407_IIC_CH6
}	F407IICChannel;

typedef enum{
	F407_IIC_CH1_PORT_PB_6_7 = 0,
	F407_IIC_CH1_PORT_PB_8_9
}	F407_IIC_CH1_USE_PORT;

typedef enum{
	F407_IIC_CH2_PORT_PB_10_11 = 0,
	F407_IIC_CH2_PORT_PF_0_1,
	F407_IIC_CH2_PORT_PH_4_5
}	F407_IIC_CH2_USE_PORT;

typedef enum{
	F407_IIC_CH3_PORT_PA_8_PC_9 = 0,
	F407_IIC_CH3_PORT_PH_7_8
}	F407_IIC_CH3_USE_PORT;

typedef enum{
	F407_MODE_PORT = 0,
	F407_MODE_IIC		
}	F407PortMode;

package void	IICP_enable(void);			/* IIC�R���g���[�������������	*/
package void	IICP_disable(void);			/* IIC�R���g���[��������~����	*/
package int	IICP_isStopCondition(void);		/* �X�g�b�v�R���f�B�V�����ɂȂ����H	*/
package int	IICP_isStartCondition(void);		/* �X�^�[�g�R���f�B�V�����ɂȂ����H	*/
package void	IICP_createStopCondition(void);		/* �X�g�b�v�R���f�B�V�����𐶐�����	*/
package void	IICP_createStartCondition(void);	/* �X�^�[�g�R���f�B�V�����𐶐�����	*/
package void	IICP_setWaitAt9Clock(void);		/* 9�N���b�N�ڂ́��ŃE�F�C�g�ɐݒ�	*/
package int	IICP_detectACK(void);			/* ACK�����o�����H			*/
package void    IICP_crtACK(void);
package void    IICP_crtNACK(void);
package void    IICP_enIICReceive(void);
package void    IICP_enIICTransmit(void);
package void	IICP_transmitByte(unsigned char data);	/* �f�[�^���M���s��			*/
package unsigned char    IICP_receiveByte(unsigned char acklevel);
package void	IICP_execResume(void);
package void	IICP_execSuspend(void);
package void	IICP_set_receive_err(void);
package void	IICP_clear_rceive_err(void);
package unsigned char IICP_get_rceive_err(void);

package void	E2prom_IICP_enable(void);		/* E2PROM IIC enable */


#endif	/* IICP_HEADER_DEFINED	*/
