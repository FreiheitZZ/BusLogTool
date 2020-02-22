/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	ヘッダーファイル取り込み
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
/*┌─────────┐
　│System Information│
　└─────────┘*/
/*#include <string.h>*/				/* memcpy(),memset()etc */
/*┌────────────┐
　│Environment Information │
　└────────────┘*/
#include "./Common.h"
/*┌────────┐
　│User Information│
　└────────┘*/
/* nothing */

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	外部変数定義と外部変数へのリンク　[External Linkage]
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
/* nothing */

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	内部変数定義　[Internal Linkage]
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
/* nothing */
static const unsigned short CRC16Table[256] =
{
	0x0000,0x1021,0x2042,0x3063,0x4084,0x50a5,0x60c6,0x70e7,
	0x8108,0x9129,0xa14a,0xb16b,0xc18c,0xd1ad,0xe1ce,0xf1ef,
	0x1231,0x0210,0x3273,0x2252,0x52b5,0x4294,0x72f7,0x62d6,
	0x9339,0x8318,0xb37b,0xa35a,0xd3bd,0xc39c,0xf3ff,0xe3de,
	0x2462,0x3443,0x0420,0x1401,0x64e6,0x74c7,0x44a4,0x5485,
	0xa56a,0xb54b,0x8528,0x9509,0xe5ee,0xf5cf,0xc5ac,0xd58d,
	0x3653,0x2672,0x1611,0x0630,0x76d7,0x66f6,0x5695,0x46b4,
	0xb75b,0xa77a,0x9719,0x8738,0xf7df,0xe7fe,0xd79d,0xc7bc,
	0x48c4,0x58e5,0x6886,0x78a7,0x0840,0x1861,0x2802,0x3823,
	0xc9cc,0xd9ed,0xe98e,0xf9af,0x8948,0x9969,0xa90a,0xb92b,
	0x5af5,0x4ad4,0x7ab7,0x6a96,0x1a71,0x0a50,0x3a33,0x2a12,
	0xdbfd,0xcbdc,0xfbbf,0xeb9e,0x9b79,0x8b58,0xbb3b,0xab1a,
	0x6ca6,0x7c87,0x4ce4,0x5cc5,0x2c22,0x3c03,0x0c60,0x1c41,
	0xedae,0xfd8f,0xcdec,0xddcd,0xad2a,0xbd0b,0x8d68,0x9d49,
	0x7e97,0x6eb6,0x5ed5,0x4ef4,0x3e13,0x2e32,0x1e51,0x0e70,
	0xff9f,0xefbe,0xdfdd,0xcffc,0xbf1b,0xaf3a,0x9f59,0x8f78,
	0x9188,0x81a9,0xb1ca,0xa1eb,0xd10c,0xc12d,0xf14e,0xe16f,
	0x1080,0x00a1,0x30c2,0x20e3,0x5004,0x4025,0x7046,0x6067,
	0x83b9,0x9398,0xa3fb,0xb3da,0xc33d,0xd31c,0xe37f,0xf35e,
	0x02b1,0x1290,0x22f3,0x32d2,0x4235,0x5214,0x6277,0x7256,
	0xb5ea,0xa5cb,0x95a8,0x8589,0xf56e,0xe54f,0xd52c,0xc50d,
	0x34e2,0x24c3,0x14a0,0x0481,0x7466,0x6447,0x5424,0x4405,
	0xa7db,0xb7fa,0x8799,0x97b8,0xe75f,0xf77e,0xc71d,0xd73c,
	0x26d3,0x36f2,0x0691,0x16b0,0x6657,0x7676,0x4615,0x5634,
	0xd94c,0xc96d,0xf90e,0xe92f,0x99c8,0x89e9,0xb98a,0xa9ab,
	0x5844,0x4865,0x7806,0x6827,0x18c0,0x08e1,0x3882,0x28a3,
	0xcb7d,0xdb5c,0xeb3f,0xfb1e,0x8bf9,0x9bd8,0xabbb,0xbb9a,
	0x4a75,0x5a54,0x6a37,0x7a16,0x0af1,0x1ad0,0x2ab3,0x3a92,
	0xfd2e,0xed0f,0xdd6c,0xcd4d,0xbdaa,0xad8b,0x9de8,0x8dc9,
	0x7c26,0x6c07,0x5c64,0x4c45,0x3ca2,0x2c83,0x1ce0,0x0cc1,
	0xef1f,0xff3e,0xcf5d,0xdf7c,0xaf9b,0xbfba,0x8fd9,0x9ff8,
	0x6e17,0x7e36,0x4e55,0x5e74,0x2e93,0x3eb2,0x0ed1,0x1ef0
};/* ADD CRC CHECK --17_MY_001*/
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	内部関数プロトタイプ宣言　[Internal Linkage]
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
/* nothing */

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	外部関数定義　[External Linkage]
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
#if 0
/*********************************************************************
	funcname：CMN_inArrayUCHAR()
	contents：unsigned charの配列に値が存在すればTRUEを返します
	引    数：searchValue		: 検索する値
		  sizeofArray		: 配列数
		  pArray		: unsigned charの配列の先頭アドレスです。
	戻 り 値：配列の中でsearchValueと一致する値があればTRUEを返します。
		  存在しない場合は、FALSEを返します。
	備    考：C++,STL::vector<uchar>を検索するイメージです。

		const unsigned char array[] = { 1, 2, 3, 4 };
		if (CMN_inArrayUCHAR(2, sizeof(array), (const unsigned char*)array)) {
			; // exist
		} else {
			; // not exist
		}
*********************************************************************/
public unsigned char
CMN_inArrayUCHAR(const unsigned char searchValue,
                 const size_t sizeofArray,
                 const unsigned char* pArray) {
	/*************************************************************
		自動変数定義
	*************************************************************/
	unsigned long i;		/* イテレータ */

	/* 検索 */
	for (i = 0; i < sizeofArray / sizeof(unsigned char); ++i) {
		if (searchValue == *(pArray + i)) {
			return TRUE;
		}
	}
	return FALSE;
}

/*********************************************************************
	funcname：CMN_inArrayUSHORT()
	contents：CMN_inArrayUCHAR()のunsigned short版です。
	引    数：CMN_inArrayUCHAR()と同じ
	戻 り 値：CMN_inArrayUCHAR()と同じ
	備    考：CMN_inArrayUCHAR()と同じ
*********************************************************************/
public unsigned char
CMN_inArrayUSHORT(const unsigned short searchValue,
                  const size_t sizeofArray,
                  const unsigned short* pArray) {
	/*************************************************************
		自動変数定義
	*************************************************************/
	unsigned long i;		/* イテレータ */

	/* 検索 */
	for (i = 0; i < sizeofArray / sizeof(unsigned short); ++i) {
		if (searchValue == *(pArray + i)) {
			return TRUE;
		}
	}
	return FALSE;
}

/*********************************************************************
	funcname：CMN_inArrayLONG()
	contents：CMN_inArrayUCHAR()のlong版です。
	引    数：CMN_inArrayUCHAR()と同じ
	戻 り 値：CMN_inArrayUCHAR()と同じ
	備    考：CMN_inArrayUCHAR()と同じ
*********************************************************************/
public unsigned char
CMN_inArrayLONG(const long searchValue,
               const size_t sizeofArray,
               const long* pArray) {
	/*************************************************************
		自動変数定義
	*************************************************************/
	long i;		/* イテレータ */

	/* 検索 */
	for (i = 0; i < sizeofArray / sizeof(long); ++i) {
		if (searchValue == *(pArray + i)) {
			return TRUE;
		}
	}
	return FALSE;
}

#if 0	/* int版はサイズが処理系に依存するため、使用する場合は確認すること */
/*********************************************************************
	funcname：CMN_inArrayINT()
	contents：CMN_inArrayUCHAR()のint版です。
	引    数：CMN_inArrayUCHAR()と同じ
	戻 り 値：CMN_inArrayUCHAR()と同じ
	備    考：CMN_inArrayUCHAR()と同じ
*********************************************************************/
public unsigned char
CMN_inArrayINT(const int searchValue,
               const size_t sizeofArray,
               const int* pArray) {
	/*************************************************************
		自動変数定義
	*************************************************************/
	int i;		/* イテレータ */

	/* 検索 */
	for (i = 0; i < sizeofArray / sizeof(int); ++i) {
		if (searchValue == *(pArray + i)) {
			return TRUE;
		}
	}
	return FALSE;
}
#endif

/*********************************************************************
	funcname：CMN_findMapUCHAR()
	contents：unsigned char配列の2要素を1ペア(key=左,value=右)とし、keyを検索してvalueを返します。
	引    数：condition		: 検索条件
		  sizeofArray		: 配列の全要素数(pair数ではありません)
		  defaultValue		: マッチしない場合に返す値です。
		  pPair			: unsigned charの配列の先頭アドレスです。
	戻 り 値：配列の中でconditionと一致するkeyを検索し、見つかったvalueを返します。
		  一致しない場合は、defaultValueを返します。
	備    考：C++,STL::map<uchar, uchar>を検索するイメージです。

		const unsigned char pair[] = { 1,2,  2,3 }; // two pair
		unsigned char result = 0;
		result = CMN_findMapUCHAR(2, sizeof(pair), 0xfe,
						(const unsigned char*)pair);
		if (result == 0xfe) {
			; // do not match
		} else {
			; // match
		}
*********************************************************************/
public unsigned char
CMN_findMapUCHAR(const unsigned char condition,
                 const size_t sizeofArray,
                 const unsigned char defaultValue,
                 const unsigned char* pPair) {
	/*************************************************************
		自動変数定義
	*************************************************************/
	unsigned long i;		/* イテレータ */

	/* 検索 */
	for (i = 0; i < sizeofArray / sizeof(unsigned char); i += 2) {
		if (condition == *(pPair + i)) {
			return *(pPair + i + 1);
		}
	}
	return defaultValue; /* マッチしない場合はデフォルト値を返す */
}

/*********************************************************************
	funcname：CMN_findMapUSHORT()
	contents：CMN_findMapUCHAR()のunsigned short版です。
	引    数：CMN_findMapUCHAR()と同じ
	戻 り 値：CMN_findMapUCHAR()と同じ
	備    考：CMN_findMapUCHAR()と同じ
*********************************************************************/
public unsigned short
CMN_findMapUSHORT(const unsigned short condition,
                  const size_t sizeofArray,
                  const unsigned short defaultValue,
                  const unsigned short* pPair) {
	/*************************************************************
		自動変数定義
	*************************************************************/
	unsigned long i;		/* イテレータ */

	/* 検索 */
	for (i = 0; i < sizeofArray / sizeof(unsigned short); i += 2) {
		if (condition == *(pPair + i)) {
			return *(pPair + i + 1);
		}
	}
	return defaultValue; /* マッチしない場合はデフォルト値を返す */
}

#if 0	/* int版はサイズが処理系に依存するため、使用する場合は確認すること */
/*********************************************************************
	funcname：CMN_findMapINT()
	contents：CMN_findMapUCHAR()のint版です。
	引    数：CMN_findMapUCHAR()と同じ
	戻 り 値：CMN_findMapUCHAR()と同じ
	備    考：CMN_findMapUCHAR()と同じ
*********************************************************************/
public int
CMN_findMapINT(const int condition,
               const size_t sizeofArray,
               const int defaultValue,
               const int* pPair) {
	/*************************************************************
		自動変数定義
	*************************************************************/
	int i;		/* イテレータ */

	/* 検索 */
	for (i = 0; i < sizeofArray / sizeof(int); i += 2) {
		if (condition == *(pPair + i)) {
			return *(pPair + i + 1);
		}
	}
	return defaultValue; /* マッチしない場合はデフォルト値を返す */
}
#endif

/*********************************************************************
	funcname：CMN_findFlipMapUCHAR()
	contents：CMN_findMapUCHAR()の逆で、valueを検索してkeyを返します。
	引    数：condition		: 検索条件
		  sizeofArray		: 配列の全要素数(pair数ではありません)
		  defaultKey		: マッチしない場合に返す値です。
		  pPair			: unsigned charの配列の先頭アドレスです。
	戻 り 値：配列の中でconditionと一致するvalueを検索し、見つかったkeyを返します。
		  一致しない場合は、defaultKeyを返します。
	備    考：CMN_findMapUCHAR()はkeyからvalueを検索(正引)しますが、
		  CMN_findFlipMapUCHAR()はvalueからkeyを検索(逆引)します。

		const unsigned char pair[] = { 1,2,  2,3 }; // two pair
		unsigned char result = 0;
		result = CMN_findFlipMapUCHAR(2, sizeof(pair), 0xfe,
						(const unsigned char*)pair);
		if (result == 0xfe) {
			; // do not match
		} else {
			; // match
		}
*********************************************************************/
public unsigned char
CMN_findFlipMapUCHAR(const unsigned char condition,
                     const size_t sizeofArray,
                     const unsigned char defaultKey,
                     const unsigned char* pPair) {
	/*************************************************************
		自動変数定義
	*************************************************************/
	unsigned long i;		/* イテレータ */

	/* 検索 */
	for (i = 0; i < sizeofArray / sizeof(unsigned char); i += 2) {
		if (condition == *(pPair + i + 1)) {
			return *(pPair + i);
		}
	}
	return defaultKey; /* マッチしない場合はデフォルト値を返す */
}

/*********************************************************************
	funcname：CMN_findFlipMapUSHORT()
	contents：CMN_findFlipMapUCHAR()のunsigned short版です。
	引    数：CMN_findFlipMapUCHAR()と同じ
	戻 り 値：CMN_findFlipMapUCHAR()と同じ
	備    考：CMN_findFlipMapUCHAR()と同じ
*********************************************************************/
public unsigned short
CMN_findFlipMapUSHORT(const unsigned short condition,
                      const size_t sizeofArray,
                      const unsigned short defaultKey,
                      const unsigned short* pPair) {
	/*************************************************************
		自動変数定義
	*************************************************************/
	unsigned long i;		/* イテレータ */

	/* 検索 */
	for (i = 0; i < sizeofArray / sizeof(unsigned short); i += 2) {
		if (condition == *(pPair + i + 1)) {
			return *(pPair + i);
		}
	}
	return defaultKey; /* マッチしない場合はデフォルト値を返す */
}

#if 0	/* int版はサイズが処理系に依存するため、使用する場合は確認すること */
/*********************************************************************
	funcname：CMN_findFlipMapINT()
	contents：CMN_findFlipMapUCHAR()のint版です。
	引    数：CMN_findFlipMapUCHAR()と同じ
	戻 り 値：CMN_findFlipMapUCHAR()と同じ
	備    考：CMN_findFlipMapUCHAR()と同じ
*********************************************************************/
public int
CMN_findFlipMapINT(const int condition,
                   const size_t sizeofArray,
                   const int defaultKey,
                   const int* pPair) {
	/*************************************************************
		自動変数定義
	*************************************************************/
	int i;		/* イテレータ */

	/* 検索 */
	for (i = 0; i < sizeofArray / sizeof(int); i += 2) {
		if (condition == *(pPair + i + 1)) {
			return *(pPair + i);
		}
	}
	return defaultKey; /* マッチしない場合はデフォルト値を返す */
}
#endif

/*********************************************************************
	funcname：CMN_findMap2UCHAR()
	contents：unsigned charの配列の3要素を1ペア(key1=左,key2=中,value=右)とし、key1とkey2を検索してvalueを返します。
	引    数：primaryKey		: 検索条件1
		  secondaryKey		: 検索条件2
		  sizeofArray		: 配列の全要素数(pair数ではありません)
		  defaultValue		: マッチしない場合に返す値です。
		  pPair			: pairの配列のアドレスです。
	戻 り 値：pairはprimaryKey,secondaryKeyとvalueを1セットとした単位です。
		  keyとvalueは同じ型である必要があります。
		  このメソッドは、
		  配列として受け取ったpairの中からprimaryKeyとsecondaryKeyに一致するkeyを検索し、
		  見つかったvalueを返します。
		  一致しない場合は、defaultValueを返します。
	備    考：C++,STL::map<vector<uchar, uchar>, uchar>を検索するイメージです。

		const unsigned uchar pair[] = { 1,2,3,  2,3,4 }; // two pair
		unsigned char result = 0;
		result = CMN_findMap2UCHAR(2,3, sizeof(pair), 0xfe,
						(const unsigned char*)pair);
		if (result == 0xfe) {
			; // do not match
		} else {
			; // match
		}
*********************************************************************/
public unsigned char
CMN_findMap2UCHAR(const unsigned char primaryKey,
                  const unsigned char secondaryKey,
                  const size_t sizeofArray,
                  const unsigned char defaultValue,
                  const unsigned char* pPair) {
	/*************************************************************
		自動変数定義
	*************************************************************/
	unsigned long i;		/* イテレータ */

	/* 検索 */
	for (i = 0; i < sizeofArray / sizeof(unsigned char); i += 3) {
		if (primaryKey == *(pPair + i)) {
			if (secondaryKey == *(pPair + i + 1)) {
				return *(pPair + i + 2);
			}
		}
	}
	return defaultValue; /* マッチしない場合はデフォルト値を返す */
}

/*********************************************************************
	funcname：CMN_findMap2USHORT()
	contents：CMN_findMap2UCHAR()のunsigned short版
	引    数：CMN_findMap2UCHAR()と同じ
	戻 り 値：CMN_findMap2UCHAR()と同じ
	備    考：CMN_findMap2UCHAR()と同じ
*********************************************************************/
public unsigned short
CMN_findMap2USHORT(const unsigned short primaryKey,
                   const unsigned short secondaryKey,
                   const size_t sizeofArray,
                   const unsigned short defaultValue,
                   const unsigned short* pPair) {
	/*************************************************************
		自動変数定義
	*************************************************************/
	unsigned long i;		/* イテレータ */

	/* 検索 */
	for (i = 0; i < sizeofArray / sizeof(unsigned short); i += 3) {
		if (primaryKey == *(pPair + i)) {
			if (secondaryKey == *(pPair + i + 1)) {
				return *(pPair + i + 2);
			}
		}
	}
	return defaultValue; /* マッチしない場合はデフォルト値を返す */
}

#endif
/* Start 17my add crc check --001*/
/***********************************************************************************************************
	funcname	:	nfPacketCrc16
	param	:	const unsigned char *pBufferCRC, unsigned int BufferLength
	retval	:	unsigned short
	brief	:	soc<->sys  crc
	note	:   17_my_001
 ***********************************************************************************************************/
unsigned short nfPacketCrc16 (const unsigned char *pBufferCRC, unsigned int BufferLength)
{
	int counter;
	unsigned short crc = 0;
	const unsigned char *p = pBufferCRC;
	
	for( counter = 0; counter < BufferLength; counter++)
	{
		crc = (crc<<8) ^ CRC16Table[((crc>>8) ^ *p++)&0x00FF];
	}
	
	return crc;

}
/* End 17my add crc check --001*/

#if 0	/* int版はサイズが処理系に依存するため、使用する場合は確認すること */
/*********************************************************************
	funcname：CMN_findMap2INT()
	contents：CMN_findMap2UCHAR()のint版
	引    数：CMN_findMap2UCHAR()と同じ
	戻 り 値：CMN_findMap2UCHAR()と同じ
	備    考：CMN_findMap2UCHAR()と同じ
*********************************************************************/
public int
CMN_findMap2INT(const int primaryKey,
                const int secondaryKey,
                const size_t sizeofArray,
                const int defaultValue,
                const int* pPair) {
	/*************************************************************
		自動変数定義
	*************************************************************/
	int i;		/* イテレータ */

	/* 検索 */
	for (i = 0; i < sizeofArray / sizeof(int); i += 3) {
		if (primaryKey == *(pPair + i)) {
			if (secondaryKey == *(pPair + i + 1)) {
				return *(pPair + i + 2);
			}
		}
	}
	return defaultValue; /* マッチしない場合はデフォルト値を返す */
}
#endif

#if 1	
/*********************************************************************
*********************************************************************/
public unsigned char  CMN_Hex2ASCII(unsigned char *HexArray,unsigned char * AscArray, unsigned char lenth) 
{
	/*************************************************************
		自動変数定義
	*************************************************************/
	unsigned char i;
	if((HexArray == NULL) || (AscArray == NULL) || (lenth <= 0) )
	{
		return 0;
	}
	for(i=0;i<lenth;i++)
	{
		AscArray[2*i] = HEX2CHAR((HexArray[i] >>4));
		AscArray[2*i+1] = HEX2CHAR((HexArray[i] & 0x0F));
	}
	return 1;
}

/*********************************************************************
	funcname，CMN_ASCII2Hex()
*********************************************************************/
public unsigned char  CMN_ASCII2Hex(unsigned char *AscArray,unsigned char * HexArray, unsigned char lenth) 
{
	/*************************************************************
		自動変数定義
	*************************************************************/
	unsigned char i;
	if((HexArray == NULL) || (AscArray == NULL) || (lenth <= 0) )
	{
		return 0;
	}
	for(i=0;i<lenth;i++)
	{
		HexArray[i] = (((CHAR2HEX((AscArray[2*i]))  <<4) | (CHAR2HEX(AscArray[2*i +1]) & 0x0F)));
	}
	return 1;
}
#endif

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	内部関数定義　[Internal Linkage]
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
/* nothing */
