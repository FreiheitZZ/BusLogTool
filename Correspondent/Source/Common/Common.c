/*������������������������������������������������������������������������������
	�w�b�_�[�t�@�C����荞��
������������������������������������������������������������������������������*/
/*����������������������
�@��System Information��
�@����������������������*/
/*#include <string.h>*/				/* memcpy(),memset()etc */
/*����������������������������
�@��Environment Information ��
�@����������������������������*/
#include "./Common.h"
/*��������������������
�@��User Information��
�@��������������������*/
/* nothing */

/*������������������������������������������������������������������������������
	�O���ϐ���`�ƊO���ϐ��ւ̃����N�@[External Linkage]
������������������������������������������������������������������������������*/
/* nothing */

/*������������������������������������������������������������������������������
	�����ϐ���`�@[Internal Linkage]
������������������������������������������������������������������������������*/
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
/*������������������������������������������������������������������������������
	�����֐��v���g�^�C�v�錾�@[Internal Linkage]
������������������������������������������������������������������������������*/
/* nothing */

/*������������������������������������������������������������������������������
	�O���֐���`�@[External Linkage]
������������������������������������������������������������������������������*/
#if 0
/*********************************************************************
	funcname�FCMN_inArrayUCHAR()
	contents�Funsigned char�̔z��ɒl�����݂����TRUE��Ԃ��܂�
	��    ���FsearchValue		: ��������l
		  sizeofArray		: �z��
		  pArray		: unsigned char�̔z��̐擪�A�h���X�ł��B
	�� �� �l�F�z��̒���searchValue�ƈ�v����l�������TRUE��Ԃ��܂��B
		  ���݂��Ȃ��ꍇ�́AFALSE��Ԃ��܂��B
	��    �l�FC++,STL::vector<uchar>����������C���[�W�ł��B

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
		�����ϐ���`
	*************************************************************/
	unsigned long i;		/* �C�e���[�^ */

	/* ���� */
	for (i = 0; i < sizeofArray / sizeof(unsigned char); ++i) {
		if (searchValue == *(pArray + i)) {
			return TRUE;
		}
	}
	return FALSE;
}

/*********************************************************************
	funcname�FCMN_inArrayUSHORT()
	contents�FCMN_inArrayUCHAR()��unsigned short�łł��B
	��    ���FCMN_inArrayUCHAR()�Ɠ���
	�� �� �l�FCMN_inArrayUCHAR()�Ɠ���
	��    �l�FCMN_inArrayUCHAR()�Ɠ���
*********************************************************************/
public unsigned char
CMN_inArrayUSHORT(const unsigned short searchValue,
                  const size_t sizeofArray,
                  const unsigned short* pArray) {
	/*************************************************************
		�����ϐ���`
	*************************************************************/
	unsigned long i;		/* �C�e���[�^ */

	/* ���� */
	for (i = 0; i < sizeofArray / sizeof(unsigned short); ++i) {
		if (searchValue == *(pArray + i)) {
			return TRUE;
		}
	}
	return FALSE;
}

/*********************************************************************
	funcname�FCMN_inArrayLONG()
	contents�FCMN_inArrayUCHAR()��long�łł��B
	��    ���FCMN_inArrayUCHAR()�Ɠ���
	�� �� �l�FCMN_inArrayUCHAR()�Ɠ���
	��    �l�FCMN_inArrayUCHAR()�Ɠ���
*********************************************************************/
public unsigned char
CMN_inArrayLONG(const long searchValue,
               const size_t sizeofArray,
               const long* pArray) {
	/*************************************************************
		�����ϐ���`
	*************************************************************/
	long i;		/* �C�e���[�^ */

	/* ���� */
	for (i = 0; i < sizeofArray / sizeof(long); ++i) {
		if (searchValue == *(pArray + i)) {
			return TRUE;
		}
	}
	return FALSE;
}

#if 0	/* int�ł̓T�C�Y�������n�Ɉˑ����邽�߁A�g�p����ꍇ�͊m�F���邱�� */
/*********************************************************************
	funcname�FCMN_inArrayINT()
	contents�FCMN_inArrayUCHAR()��int�łł��B
	��    ���FCMN_inArrayUCHAR()�Ɠ���
	�� �� �l�FCMN_inArrayUCHAR()�Ɠ���
	��    �l�FCMN_inArrayUCHAR()�Ɠ���
*********************************************************************/
public unsigned char
CMN_inArrayINT(const int searchValue,
               const size_t sizeofArray,
               const int* pArray) {
	/*************************************************************
		�����ϐ���`
	*************************************************************/
	int i;		/* �C�e���[�^ */

	/* ���� */
	for (i = 0; i < sizeofArray / sizeof(int); ++i) {
		if (searchValue == *(pArray + i)) {
			return TRUE;
		}
	}
	return FALSE;
}
#endif

/*********************************************************************
	funcname�FCMN_findMapUCHAR()
	contents�Funsigned char�z���2�v�f��1�y�A(key=��,value=�E)�Ƃ��Akey����������value��Ԃ��܂��B
	��    ���Fcondition		: ��������
		  sizeofArray		: �z��̑S�v�f��(pair���ł͂���܂���)
		  defaultValue		: �}�b�`���Ȃ��ꍇ�ɕԂ��l�ł��B
		  pPair			: unsigned char�̔z��̐擪�A�h���X�ł��B
	�� �� �l�F�z��̒���condition�ƈ�v����key���������A��������value��Ԃ��܂��B
		  ��v���Ȃ��ꍇ�́AdefaultValue��Ԃ��܂��B
	��    �l�FC++,STL::map<uchar, uchar>����������C���[�W�ł��B

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
		�����ϐ���`
	*************************************************************/
	unsigned long i;		/* �C�e���[�^ */

	/* ���� */
	for (i = 0; i < sizeofArray / sizeof(unsigned char); i += 2) {
		if (condition == *(pPair + i)) {
			return *(pPair + i + 1);
		}
	}
	return defaultValue; /* �}�b�`���Ȃ��ꍇ�̓f�t�H���g�l��Ԃ� */
}

/*********************************************************************
	funcname�FCMN_findMapUSHORT()
	contents�FCMN_findMapUCHAR()��unsigned short�łł��B
	��    ���FCMN_findMapUCHAR()�Ɠ���
	�� �� �l�FCMN_findMapUCHAR()�Ɠ���
	��    �l�FCMN_findMapUCHAR()�Ɠ���
*********************************************************************/
public unsigned short
CMN_findMapUSHORT(const unsigned short condition,
                  const size_t sizeofArray,
                  const unsigned short defaultValue,
                  const unsigned short* pPair) {
	/*************************************************************
		�����ϐ���`
	*************************************************************/
	unsigned long i;		/* �C�e���[�^ */

	/* ���� */
	for (i = 0; i < sizeofArray / sizeof(unsigned short); i += 2) {
		if (condition == *(pPair + i)) {
			return *(pPair + i + 1);
		}
	}
	return defaultValue; /* �}�b�`���Ȃ��ꍇ�̓f�t�H���g�l��Ԃ� */
}

#if 0	/* int�ł̓T�C�Y�������n�Ɉˑ����邽�߁A�g�p����ꍇ�͊m�F���邱�� */
/*********************************************************************
	funcname�FCMN_findMapINT()
	contents�FCMN_findMapUCHAR()��int�łł��B
	��    ���FCMN_findMapUCHAR()�Ɠ���
	�� �� �l�FCMN_findMapUCHAR()�Ɠ���
	��    �l�FCMN_findMapUCHAR()�Ɠ���
*********************************************************************/
public int
CMN_findMapINT(const int condition,
               const size_t sizeofArray,
               const int defaultValue,
               const int* pPair) {
	/*************************************************************
		�����ϐ���`
	*************************************************************/
	int i;		/* �C�e���[�^ */

	/* ���� */
	for (i = 0; i < sizeofArray / sizeof(int); i += 2) {
		if (condition == *(pPair + i)) {
			return *(pPair + i + 1);
		}
	}
	return defaultValue; /* �}�b�`���Ȃ��ꍇ�̓f�t�H���g�l��Ԃ� */
}
#endif

/*********************************************************************
	funcname�FCMN_findFlipMapUCHAR()
	contents�FCMN_findMapUCHAR()�̋t�ŁAvalue����������key��Ԃ��܂��B
	��    ���Fcondition		: ��������
		  sizeofArray		: �z��̑S�v�f��(pair���ł͂���܂���)
		  defaultKey		: �}�b�`���Ȃ��ꍇ�ɕԂ��l�ł��B
		  pPair			: unsigned char�̔z��̐擪�A�h���X�ł��B
	�� �� �l�F�z��̒���condition�ƈ�v����value���������A��������key��Ԃ��܂��B
		  ��v���Ȃ��ꍇ�́AdefaultKey��Ԃ��܂��B
	��    �l�FCMN_findMapUCHAR()��key����value������(����)���܂����A
		  CMN_findFlipMapUCHAR()��value����key������(�t��)���܂��B

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
		�����ϐ���`
	*************************************************************/
	unsigned long i;		/* �C�e���[�^ */

	/* ���� */
	for (i = 0; i < sizeofArray / sizeof(unsigned char); i += 2) {
		if (condition == *(pPair + i + 1)) {
			return *(pPair + i);
		}
	}
	return defaultKey; /* �}�b�`���Ȃ��ꍇ�̓f�t�H���g�l��Ԃ� */
}

/*********************************************************************
	funcname�FCMN_findFlipMapUSHORT()
	contents�FCMN_findFlipMapUCHAR()��unsigned short�łł��B
	��    ���FCMN_findFlipMapUCHAR()�Ɠ���
	�� �� �l�FCMN_findFlipMapUCHAR()�Ɠ���
	��    �l�FCMN_findFlipMapUCHAR()�Ɠ���
*********************************************************************/
public unsigned short
CMN_findFlipMapUSHORT(const unsigned short condition,
                      const size_t sizeofArray,
                      const unsigned short defaultKey,
                      const unsigned short* pPair) {
	/*************************************************************
		�����ϐ���`
	*************************************************************/
	unsigned long i;		/* �C�e���[�^ */

	/* ���� */
	for (i = 0; i < sizeofArray / sizeof(unsigned short); i += 2) {
		if (condition == *(pPair + i + 1)) {
			return *(pPair + i);
		}
	}
	return defaultKey; /* �}�b�`���Ȃ��ꍇ�̓f�t�H���g�l��Ԃ� */
}

#if 0	/* int�ł̓T�C�Y�������n�Ɉˑ����邽�߁A�g�p����ꍇ�͊m�F���邱�� */
/*********************************************************************
	funcname�FCMN_findFlipMapINT()
	contents�FCMN_findFlipMapUCHAR()��int�łł��B
	��    ���FCMN_findFlipMapUCHAR()�Ɠ���
	�� �� �l�FCMN_findFlipMapUCHAR()�Ɠ���
	��    �l�FCMN_findFlipMapUCHAR()�Ɠ���
*********************************************************************/
public int
CMN_findFlipMapINT(const int condition,
                   const size_t sizeofArray,
                   const int defaultKey,
                   const int* pPair) {
	/*************************************************************
		�����ϐ���`
	*************************************************************/
	int i;		/* �C�e���[�^ */

	/* ���� */
	for (i = 0; i < sizeofArray / sizeof(int); i += 2) {
		if (condition == *(pPair + i + 1)) {
			return *(pPair + i);
		}
	}
	return defaultKey; /* �}�b�`���Ȃ��ꍇ�̓f�t�H���g�l��Ԃ� */
}
#endif

/*********************************************************************
	funcname�FCMN_findMap2UCHAR()
	contents�Funsigned char�̔z���3�v�f��1�y�A(key1=��,key2=��,value=�E)�Ƃ��Akey1��key2����������value��Ԃ��܂��B
	��    ���FprimaryKey		: ��������1
		  secondaryKey		: ��������2
		  sizeofArray		: �z��̑S�v�f��(pair���ł͂���܂���)
		  defaultValue		: �}�b�`���Ȃ��ꍇ�ɕԂ��l�ł��B
		  pPair			: pair�̔z��̃A�h���X�ł��B
	�� �� �l�Fpair��primaryKey,secondaryKey��value��1�Z�b�g�Ƃ����P�ʂł��B
		  key��value�͓����^�ł���K�v������܂��B
		  ���̃��\�b�h�́A
		  �z��Ƃ��Ď󂯎����pair�̒�����primaryKey��secondaryKey�Ɉ�v����key���������A
		  ��������value��Ԃ��܂��B
		  ��v���Ȃ��ꍇ�́AdefaultValue��Ԃ��܂��B
	��    �l�FC++,STL::map<vector<uchar, uchar>, uchar>����������C���[�W�ł��B

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
		�����ϐ���`
	*************************************************************/
	unsigned long i;		/* �C�e���[�^ */

	/* ���� */
	for (i = 0; i < sizeofArray / sizeof(unsigned char); i += 3) {
		if (primaryKey == *(pPair + i)) {
			if (secondaryKey == *(pPair + i + 1)) {
				return *(pPair + i + 2);
			}
		}
	}
	return defaultValue; /* �}�b�`���Ȃ��ꍇ�̓f�t�H���g�l��Ԃ� */
}

/*********************************************************************
	funcname�FCMN_findMap2USHORT()
	contents�FCMN_findMap2UCHAR()��unsigned short��
	��    ���FCMN_findMap2UCHAR()�Ɠ���
	�� �� �l�FCMN_findMap2UCHAR()�Ɠ���
	��    �l�FCMN_findMap2UCHAR()�Ɠ���
*********************************************************************/
public unsigned short
CMN_findMap2USHORT(const unsigned short primaryKey,
                   const unsigned short secondaryKey,
                   const size_t sizeofArray,
                   const unsigned short defaultValue,
                   const unsigned short* pPair) {
	/*************************************************************
		�����ϐ���`
	*************************************************************/
	unsigned long i;		/* �C�e���[�^ */

	/* ���� */
	for (i = 0; i < sizeofArray / sizeof(unsigned short); i += 3) {
		if (primaryKey == *(pPair + i)) {
			if (secondaryKey == *(pPair + i + 1)) {
				return *(pPair + i + 2);
			}
		}
	}
	return defaultValue; /* �}�b�`���Ȃ��ꍇ�̓f�t�H���g�l��Ԃ� */
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

#if 0	/* int�ł̓T�C�Y�������n�Ɉˑ����邽�߁A�g�p����ꍇ�͊m�F���邱�� */
/*********************************************************************
	funcname�FCMN_findMap2INT()
	contents�FCMN_findMap2UCHAR()��int��
	��    ���FCMN_findMap2UCHAR()�Ɠ���
	�� �� �l�FCMN_findMap2UCHAR()�Ɠ���
	��    �l�FCMN_findMap2UCHAR()�Ɠ���
*********************************************************************/
public int
CMN_findMap2INT(const int primaryKey,
                const int secondaryKey,
                const size_t sizeofArray,
                const int defaultValue,
                const int* pPair) {
	/*************************************************************
		�����ϐ���`
	*************************************************************/
	int i;		/* �C�e���[�^ */

	/* ���� */
	for (i = 0; i < sizeofArray / sizeof(int); i += 3) {
		if (primaryKey == *(pPair + i)) {
			if (secondaryKey == *(pPair + i + 1)) {
				return *(pPair + i + 2);
			}
		}
	}
	return defaultValue; /* �}�b�`���Ȃ��ꍇ�̓f�t�H���g�l��Ԃ� */
}
#endif

#if 1	
/*********************************************************************
*********************************************************************/
public unsigned char  CMN_Hex2ASCII(unsigned char *HexArray,unsigned char * AscArray, unsigned char lenth) 
{
	/*************************************************************
		�����ϐ���`
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
	funcname�CCMN_ASCII2Hex()
*********************************************************************/
public unsigned char  CMN_ASCII2Hex(unsigned char *AscArray,unsigned char * HexArray, unsigned char lenth) 
{
	/*************************************************************
		�����ϐ���`
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

/*������������������������������������������������������������������������������
	�����֐���`�@[Internal Linkage]
������������������������������������������������������������������������������*/
/* nothing */
