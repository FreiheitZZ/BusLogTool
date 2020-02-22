#include "../../Common/Common.h"		/* Common Information	*/
#include "../../Platform/Platform.h"		/* Platform Information	*/

#include "./Platform/IICPlatform.h"		/* 機種依存機能のヘッダ		*/
#include "./IIC.h"

/*********************************************************************
	funcname: IIC_execResume
	contents: IICドライバのResume処理をする
	引    数: なし
	返    値: なし
	備    考: プラットホームの使用ポート初期化
*********************************************************************/
public void
IIC_Init(void)
{
	IIC_execResume();
}

/*********************************************************************
	funcname: IIC_execResume
	contents: IICドライバのResume処理をする
	引    数: なし
	返    値: なし
	備    考: プラットホームの使用ポート初期化
*********************************************************************/
public void
IIC_execResume(void)
{
	IICP_execResume();
}

/*********************************************************************
	funcname: IIC_suspend
	contents: IICドライバのSuspend処理をする
	引    数: なし
	返    値: なし
	備    考: なし
*********************************************************************/
public void
IIC_execSuspend(void)
{
	IICP_disable();
	IICP_execSuspend();
}

/*********************************************************************
	funcname: IIC_enable
	contents: IICドライバの動作を許可する
	引    数: なし
	返    値: なし
	備    考: MPUのIICドライバ機能を有効にするだけにしました。
		  その代わり､イネーブル後の最初のデータ転送の際(IIC_transmitData)、
		  バスがＳＰかどうかチェックするところで引っかかるので、そこで
		  ＳＰを生成してバスを開放することにします。
*********************************************************************/
public void
IIC_enable(void)
{
	IICP_enable();
}

/*********************************************************************
	funcname: IIC_disable
	contents: IICドライバの動作を停止する
	引    数: なし
	返    値: なし
	備    考: なし
*********************************************************************/
public void
IIC_disable(void)
{
	IICP_disable();
}

/*********************************************************************
	funcname: IIC_transmitData
	contents: データ送信を行う
	引    数: byteNum : 送信データ数
		  pdata   : 送信データ先頭へのポインタ
	返    値: 0: 正常終了
		 -1: ACKが返ってこなかった
		 -2: ストップコンディションにならなかった
		 -3: スタートコンディションにならなかった
		 -4: 資源を獲得できなかった
	備    考: 送信データ先頭はスレーブアドレスとする
		  IICスレーブの電源を入れてから安定するまで時間が
		  かかります(1msec位)。そのため、電源投入後10msec位
		  たった後にこの関数を呼んでください。
*********************************************************************/
public long
IIC_transmitData(unsigned long byteNum, unsigned char *pData)
{
	/*************************************************************
		自動変数定義
	*************************************************************/
	long			result = 0;		/* エラーの有無情報 */
	unsigned char	*p;				/* データへのポインタ */
	unsigned char	retry;
	unsigned char	num;
	/*************************************************************
		IICドライバ データ送信
	*************************************************************/
	if( IICnBUSBSY == 1 ){			/* バスが解放されていない	*/
		IICP_createStopCondition(); /* STOP CONDITIONを生成する */
		for( retry = IIC_MAX_LOOP_COUNT; retry > 0; retry-- ){

		
			if( IICP_isStopCondition() == 1 ){
				break;				/* STOP CONDITIONになった	*/
			}
		}
		/* リトライカウントが 0 → STOP CONDITIONにならなかった */
		if( retry == 0 ){
			result = -2;			/* STOP CONDITIONにならなかった */
		}
	}
	#if 0
	EN_RESTART;
	#endif
	if( !result ){
		num = byteNum - 1;
		p = (unsigned char *)pData; 	/* char型のポインタにキャスト	*/
		while ( byteNum > 0 ) {
			if(byteNum <= num)
				DISABLE_START;
			IICP_transmitByte(*p);	/* 1バイト送信					*/
			p++;
			if ( !IICP_detectACK() ) {
				result = -1;			/* ACKが返ってこない			*/
				break;
			}
			byteNum--;
		}

		EN_RESTART;
		if(num > 1) {
			IICP_createStopCondition(); /* STOP CONDITIONを生成する */
			for( retry = IIC_MAX_LOOP_COUNT; retry > 0; retry-- ){
				if( IICP_isStopCondition() == 1 ){
					break;				/* STOP CONDITIONになった	*/
				}
			}
			/* リトライカウントが 0 → STOP CONDITIONにならなかった */
			if( retry == 0 ){
				result = -2;			/* STOP CONDITIONにならなかった */
			}
		}
	}

	return result;					/* エラー情報を返す		*/
}

public long
IIC_receiveData(unsigned long byteNum, 
						 unsigned char ucCmdData,  
						 unsigned char *pRcvData)
{
	/*************************************************************
		自動変数定義
	*************************************************************/
	long			result = 0;		/* エラーの有無情報 */
	unsigned char	retry;
	#if 0
	if ( !IICP_isStopCondition() ) {		/* STOP CONDITIONでない */
			for ( retry = IIC_MAX_LOOP_COUNT; retry > 0; retry-- ) {
				IICP_createStopCondition(); /* STOP CONDITIONを生成する */
				if ( IICP_isStopCondition() == 1 ) {
					break;			/* STOP CONDITIONになった	*/
				}
			}
			/* リトライカウントが 0 → STOP CONDITIONにならなかった */
			if ( retry == 0 ) {
				result = -2;			/* STOP CONDITIONにならなかった */
			}
		}
	#endif
	if ( !result ) {
		IICP_transmitByte(ucCmdData);
		if ( !IICP_detectACK() ) {
				IICP_set_receive_err();
				return  (-1);		/* ACKが返ってこない		*/
		}
		while ( byteNum > 0 ) {
			if(byteNum==1)
				*((unsigned char*)pRcvData)= IICP_receiveByte(0x0B);
			else
				*((unsigned char*)pRcvData)= IICP_receiveByte(0x0A);
			pRcvData++;
			byteNum--;
		}
		
		IICP_createStopCondition();		/* STOP CONDITIONを生成する	*/
		
	}
}

