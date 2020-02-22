#ifndef COMMON_H
#define COMMON_H

#include <stddef.h>  /* for size_t */

#define	TRUE	1			/* 真	*/
#define	FALSE	0			/* 偽	*/

#define	ON	1
#define OFF	0

#define	HIGH	1
#define LOW	0

#define	NONE	0			/* 何もないという意味	*/

#define	public		extern		/* UMLの" + "	*/
#define	protected	extern		/* UMLの" # "	*/
#define	package		extern		/* UMLの" ~ "	*/
#define	private		static		/* UMLの" - "	*/

typedef unsigned char BOOL;

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	マクロ関数定義
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
/*********************************************************************
	funcname：CMN_changeHexToBCD()
	contents：HexデータをBCDに変換する
	引    数：unsigned short	：変換元Hexデータ
	戻 り 値：unsigned int		：変換後BCDデータ
	備    考：
*********************************************************************/
#define	CMN_changeHexToBCD(C)	((C%10)+(((C/10)%10)<<4)+(((C/100)%10)<<8)+(((C/1000)%10)<<12))

/*********************************************************************
	funcname：CMN_changeBCDToHex()
	contents：BCDデータをHexに変換する
	引    数：unsigned short	：変換元BCDデータ
	戻 り 値：unsigned short	：変換後Hexデータ
	備    考：なし
*********************************************************************/
#define	CMN_changeBCDToHex(C)	(((C>>0)&0x000f)+(((C>>4)&0x000f)*10)+(((C>>8)&0x000f)*100)+(((C>>12)&0x000f)*1000))

/*ASCII -->  HEX*/
#define ISCAPITAL(arg)  (((arg) >= 'a'  && (arg) <= 'z' ) ? (arg) - 'a'   :  (arg) - 'A' )
#define CHAR2HEX(arg)  (((arg) >= '0'  && (arg) <= '9' ) ? ((arg) - '0' )  : (ISCAPITAL(arg) + 0xa ))

/*HEX-->ASCII*/
#define ASCAPITAL(arg)  ((arg)+'A')
#define HEX2CHAR(arg)  (((arg)>=0 &&(arg)<=9)  ? ((arg)+'0')  : ( ASCAPITAL(arg) - 0xa))

/*********************************************************************
	funcname：CMN_changeBCDToHexUL()
	contents：BCDデータをHexに変換する(unsigned long対応)
	引    数：unsigned short	：変換元BCDデータ
	戻 り 値：unsigned short	：変換後Hexデータ
	備    考：なし
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
