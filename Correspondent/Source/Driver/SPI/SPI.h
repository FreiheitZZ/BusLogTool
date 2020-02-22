/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	ヘッダーファイル取り込み
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
/* nothing */

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	define定義
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
#define	SPI_CH0		0			/* チャンネル0 */
#define	SPI_CH1		1			/* チャンネル1 */
#define	SPI_CH2		2			/* チャンネル2 */
#define	SPI_CH3		3			/* チャンネル3 */
#define	SPI_CH4		4			/* チャンネル4 */
#define	SPI_CH5		5			/* チャンネル5 */
#define	SPI_CH6		6			/* チャンネル6 */
#define	SPI_CH7		7			/* チャンネル7 */
#define	SPI_CH8		8			/* チャンネル8 */
#define	SPI_CH9		9			/* チャンネル9 */



/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	typedef宣言
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
/* nothing */

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	外部関数へのリンク　[External Linkage]
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
public void SPI_execResume(unsigned char ch);				/* SPIドライバのResume処理をする	*/
public void SPI_execSuspend(unsigned char ch);				/* SPIドライバのSuspend処理をする	*/
public void SPI_enable(unsigned char ch);					/* SPIドライバ動作を許可する		*/
public void SPI_disable(unsigned char ch);					/* SPIドライバ動作を停止する		*/
public unsigned char SPI_transmitData(unsigned char ch, unsigned char Data);	/* データ送信を行う			*/
public signed char SPI_receiveData(unsigned char ch, unsigned char *Data);
public void SPI_changeEdge(unsigned char ch,unsigned char edge);


/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	マクロ関数定義
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
/* nothing */
