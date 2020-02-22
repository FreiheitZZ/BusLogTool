#include "./StandByAcceptor.h"				/* */
#include "./StandBySequencer.h"				/* */

typedef struct {
	void	(*callFunc)(void);	/* �R�[�����W���[��	*/
	unsigned long	waitTime;	/* �҂�����		*/
	unsigned char	id;		/* ����ID		*/
	unsigned char	flgPtn;		/* �҂��t���O�p�^�[��	*/
} SSTBYAccExecProc;

void SYS_informAccOn(void);
void SYS_informAccOff(void);

static const SSTBYAccExecProc	s_sAccOnExecProc[] = {
	{SYS_informAccOn,	10,	STBY_ID_SYSTEM,		STBY_FLG_NO_SYSTEM},	/* System		*/
};


static const SSTBYAccExecProc	s_sAccOffExecProc[] = {
	{SYS_informAccOff,	1000,	STBY_ID_SYSTEM,		STBY_FLG_NO_SYSTEM},	/* System		*/		
};

/*********************************************************************
	funcname�FSTBY_exeBootSequence()
	contents�F
	��    ���F�Ȃ�
	�� �� �l�F�Ȃ�
	��    �l�F�Ȃ�
*********************************************************************/
extern	void
STBY_exeBootSequence(unsigned char *waitFlgPtn, SStandByWaitInfo *waitInfo)
{
	/*************************************************************
		�����ϐ���`
	*************************************************************/
	unsigned char	cnt;
	unsigned char	*saveP;

	saveP = waitFlgPtn;
	for (cnt = 0 ; cnt < sizeof(s_sAccOnExecProc) / sizeof(SSTBYAccExecProc) ; cnt++){
		waitInfo->id = s_sAccOnExecProc[cnt].id;
		waitInfo->waitTime = s_sAccOnExecProc[cnt].waitTime;
		waitFlgPtn += (s_sAccOnExecProc[cnt].flgPtn / 8);
		*waitFlgPtn |= (0x01 << (s_sAccOnExecProc[cnt].flgPtn % 8));
		waitFlgPtn = saveP;
		s_sAccOnExecProc[cnt].callFunc();
		waitInfo++;
	}

}

/*********************************************************************
	funcname�FSTBY_exeShutdownSequence()
	contents�F
	��    ���F�Ȃ�
	�� �� �l�F�Ȃ�
	��    �l�F�Ȃ�
*********************************************************************/
extern	void
STBY_exeShutdownSequence(unsigned char *waitFlgPtn, SStandByWaitInfo *waitInfo)
{
	/*************************************************************
		�����ϐ���`
	*************************************************************/
	unsigned char	cnt;
	unsigned char	*saveP;

	saveP = waitFlgPtn;
	for (cnt = 0 ; cnt < sizeof(s_sAccOffExecProc) / sizeof(SSTBYAccExecProc) ; cnt++){
		waitInfo->id = s_sAccOffExecProc[cnt].id;
		waitInfo->waitTime = s_sAccOffExecProc[cnt].waitTime;
		waitFlgPtn += (s_sAccOffExecProc[cnt].flgPtn / 8);
		*waitFlgPtn |= (0x01 << (s_sAccOffExecProc[cnt].flgPtn % 8));
		waitFlgPtn = saveP;
		s_sAccOffExecProc[cnt].callFunc();
		waitInfo++;
	}

}

void SYS_informAccOn(void)
{}

void SYS_informAccOff(void)
{}


