#ifndef COMMON_H
#define COMMON_H

#include <stddef.h>  /* for size_t */

#define	TRUE	1			/* �^	*/
#define	FALSE	0			/* �U	*/

#define	ON	1
#define OFF	0

#define	HIGH	1
#define LOW	0

#define	NONE	0			/* �����Ȃ��Ƃ����Ӗ�	*/

#define	public		extern		/* UML��" + "	*/
#define	protected	extern		/* UML��" # "	*/
#define	package		extern		/* UML��" ~ "	*/
#define	private		static		/* UML��" - "	*/

typedef unsigned char BOOL;

/*������������������������������������������������������������������������������
	�}�N���֐���`
������������������������������������������������������������������������������*/
/*********************************************************************
	funcname�FCMN_changeHexToBCD()
	contents�FHex�f�[�^��BCD�ɕϊ�����
	��    ���Funsigned short	�F�ϊ���Hex�f�[�^
	�� �� �l�Funsigned int		�F�ϊ���BCD�f�[�^
	��    �l�F
*********************************************************************/
#define	CMN_changeHexToBCD(C)	((C%10)+(((C/10)%10)<<4)+(((C/100)%10)<<8)+(((C/1000)%10)<<12))

/*********************************************************************
	funcname�FCMN_changeBCDToHex()
	contents�FBCD�f�[�^��Hex�ɕϊ�����
	��    ���Funsigned short	�F�ϊ���BCD�f�[�^
	�� �� �l�Funsigned short	�F�ϊ���Hex�f�[�^
	��    �l�F�Ȃ�
*********************************************************************/
#define	CMN_changeBCDToHex(C)	(((C>>0)&0x000f)+(((C>>4)&0x000f)*10)+(((C>>8)&0x000f)*100)+(((C>>12)&0x000f)*1000))

/*ASCII -->  HEX*/
#define ISCAPITAL(arg)  (((arg) >= 'a'  && (arg) <= 'z' ) ? (arg) - 'a'   :  (arg) - 'A' )
#define CHAR2HEX(arg)  (((arg) >= '0'  && (arg) <= '9' ) ? ((arg) - '0' )  : (ISCAPITAL(arg) + 0xa ))

/*HEX-->ASCII*/
#define ASCAPITAL(arg)  ((arg)+'A')
#define HEX2CHAR(arg)  (((arg)>=0 &&(arg)<=9)  ? ((arg)+'0')  : ( ASCAPITAL(arg) - 0xa))

/*********************************************************************
	funcname�FCMN_changeBCDToHexUL()
	contents�FBCD�f�[�^��Hex�ɕϊ�����(unsigned long�Ή�)
	��    ���Funsigned short	�F�ϊ���BCD�f�[�^
	�� �� �l�Funsigned short	�F�ϊ���Hex�f�[�^
	��    �l�F�Ȃ�
*********************************************************************/
#define	CMN_changeBCDToHexUL(C)	 (( (C>> 0)&0x0000000f)			\
				+ (((C>> 4)&0x0000000f)*10)		\
				+ (((C>> 8)&0x0000000f)*100)		\
				+ (((C>>12)&0x0000000f)*1000)		\
				+ (((C>>16)&0x0000000f)*10000)		\
				+ (((C>>20)&0x0000000f)*100000)		\
				+ (((C>>24)&0x0000000f)*1000000)	\
				+ (((C>>28)&0x0000000f)*10000000)	)


public unsigned short nfPacketCrc16 (const unsigned char *pBufferCRC, unsigned int BufferLength);
public unsigned char  CMN_Hex2ASCII(unsigned char *HexArray,unsigned char * AscArray, unsigned char lenth);
public unsigned char  CMN_ASCII2Hex(unsigned char *AscArray,unsigned char * HexArray, unsigned char lenth);

#endif
