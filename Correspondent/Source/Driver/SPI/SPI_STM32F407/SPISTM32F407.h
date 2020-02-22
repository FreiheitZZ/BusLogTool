#ifndef	SPIP_HEADER_DEFINED
#define	SPIP_HEADER_DEFINED

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	define定義
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
/* nothing */
#define	SPIP_CH0		0			/* ????儖0 */
#define	SPIP_CH1		1			/* ????儖1 */
#define	SPIP_CH2		2			/* ????儖2 */
#define	SPIP_CH3		3			/* ????儖3 */
#define	SPIP_CH4		4			/* ????儖4 */
#define	SPIP_CH5		5			/* ????儖5 */
#define	SPIP_CH6		6			/* ????儖6 */
#define	SPIP_CH7		7			/* ????儖7 */
#define	SPIP_CH8		8			/* ????儖8 */
#define	SPIP_CH9		9			/* ????儖9 */
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	マクロ関数定義
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
/*┌────────┐
　│チャンネルの定義│
　└────────┘*/
#define SPI_CH0_USE 0
#define SPI_CH1_USE 1
#define SPI_CH2_USE 0
#define SPI_CH3_USE 0
#define SPI_CH4_USE 0
#define SPI_CH5_USE 0
#define SPI_CH6_USE 0
#define SPI_CH7_USE 0
#define SPI_CH8_USE 0
#define SPI_CH9_USE 0

#define SPI_WAIT_CNT_MAX 10000


/*┌──────────────────┐
　│使用するチャンネルをSPI_CHに指定する│
　└──────────────────┘*/


/*┌─────────┐
　│ポートタイプの定義│
　└─────────┘*/

/*┌───────────────────────┐
　│使用するポートタイプをSPI_PORT_TYPEに指定する │
　└───────────────────────┘*/


/*┌──────┐
  │チャンネル０│
  └──────┘*/
#if (SPI_CH0_USE)
	#error : please write SPI_CH0 channel define
#endif
	/*┌──────┐
  │チャンネル１│
  └──────┘*/
#if (SPI_CH1_USE)
#define SPI1_RecDataReg	ucCPU_SC1RB
#define SPI1_TraDataReg	ucCPU_SC1TB
#define SPI1_EEPROMCLK	bCPU_P32OD
#define SPI1_EEPROMDI	bCPU_P31ID
#define SPI1_EEPROMDO	bCPU_P30OD
	
#define	SPI1_PORT_ENTRY_INIT()  {\
									/*Nomarl Mode set*/ 						   \
									bCPU_P3M0 = 0;								   \
									bCPU_P3M1 = 0;								   \
									bCPU_P3M2 = 0;								   \
																				   \
																				   \
									/*Output Enable*/							   \
									bCPU_P30OE = 1; 							   \
									bCPU_P31OE = 0; 							   \
									bCPU_P32OE = 1; 							   \
																				   \
																				   \
									/*Iutput Enable*/							   \
									bCPU_P30IE = 0; 							   \
									bCPU_P31IE = 1; 							   \
									bCPU_P32IE = 0; 							   \
																				   \
									/*SPI Mode set*/							   \
									bCPU_P3M0 = 2;								   \
									bCPU_P3M1 = 2;								   \
									bCPU_P3M2 = 2;								   \
																				   \
									}\
	
#define	SPI1_PORT_EXIT_INIT() 	{\
							/*Output data 0*/				   \
							bCPU_P30OD = 0; 	/*HU DO*/	   \
							bCPU_P31OD = 0; 	/*HU DI*/	   \
							bCPU_P32OD = 0; 	/*CLK*/ 	   \
															   \
															   \
							/*Output Enable*/				   \
							bCPU_P30OE = 1; 				   \
							bCPU_P31OE = 0; 				   \
							bCPU_P32OE = 1; 				   \
															   \
															   \
							bCPU_P30IE = 0; 				   \
							bCPU_P31IE = 1; 				   \
							bCPU_P32IE = 0; 				   \
															   \
															   \
							bCPU_P30PU = 0; 				   \
							bCPU_P31PU = 0; 				   \
							bCPU_P32PU = 0; 				   \
															   \
															   \
							bCPU_P30ODC = 0;				   \
							bCPU_P32ODC = 0;				   \
															   \
							bCPU_P3M0 = 0;					   \
							bCPU_P3M1 = 0;					   \
							bCPU_P3M2 = 0;					   \
															   \
							}\
							
#define SPI1_CLOSE()	{\
								bCPU_SC1RSTN = 0;				/*Register SC1MD3,Serial Reset*/ \
								bCPU_SC1RSRN = 0;				/*Register SC1MD3,Serial Reset*/ \
								bCPU_BRTM_S1_EN = 0;			/*BuadRate Timer Off*/			 \
							}\
							
#define SPI1_OPEN()	{\
									bCPU_BRTM_S1_EN = 1;			/*BuadRate Timer On*/					 \
									bCPU_SC1RSTN = 1;				/*Register SC1MD3,Serial Open*/ 		 \
									bCPU_SC1RSRN = 0;				/*Register SC1MD3,This Bit Must be 0*/	 \
								}\
								
#ifdef  PLT_USE_GS_UNIT
#define	SPI1_BAUTRATE_SET()	{\
	bCPU_SC1RSTN = 0;				/*Register SC1MD3,Serial Reset*/																					  \
	bCPU_SC1RSRN = 0;				/*Register SC1MD3,Serial Reset*/																					  \
	bCPU_BRTM_S1_EN = 0;			/*BuadRate Timer Off*/																								  \
	bCPU_BRTM_S1_MODE = 0;		/*SB1 Configed to SPI Mode*/																							  \
	bCPU_BRTM_S1_CK = 0x01; 	/*clksp/2,clksp = 15Mhz  */ 																							  \
	ucCPU_BRTM_S1_OC = 0x07;		/*clksp/2/(2*(7+1)) = 468.75k, clksp = 15M  */ 																		  \
	ucCPU_SC1MD0 = 0x87;			/*Clock polarity "H";Communication Mode "Normal Mode";MSB Fisrst;Disable Start Conditon;8bits Transmit*/			  \
	ucCPU_SC1MD1 = 0x74;			/*0111 0100*/																										  \
	/*ucCPU_SC9MD3 = 0x*/																																  \
	bCPU_SC1FDC = 0x10; 		/*Output Fixed to 0, Register SC1MD3*/																					  \
}\

#else
#define	SPI1_BAUTRATE_SET()	{\
									bCPU_SC1RSTN = 0;				/*Register SC1MD3,Serial Reset*/																					  \
									bCPU_SC1RSRN = 0;				/*Register SC1MD3,Serial Reset*/																					  \
									bCPU_BRTM_S1_EN = 0;			/*BuadRate Timer Off*/																								  \
									bCPU_BRTM_S1_MODE = 0;		/*SB1 Configed to SPI Mode*/																							  \
									bCPU_BRTM_S1_CK = 0x01; 	/*clksp/2,clksp = 10Mhz  */ 																							  \
									ucCPU_BRTM_S1_OC = 0x04;		/*clksp/2/(2*(4+1)) = 0.5M, clksp = 10M  */ 																		  \
									ucCPU_SC1MD0 = 0x87;			/*Clock polarity "H";Communication Mode "Normal Mode";MSB Fisrst;Disable Start Conditon;8bits Transmit*/			  \
									ucCPU_SC1MD1 = 0x74;			/*0111 0100*/																										  \
									/*ucCPU_SC9MD3 = 0x*/																																  \
									bCPU_SC1FDC = 0x10; 		/*Output Fixed to 0, Register SC1MD3*/																					  \
								}\
								
#endif	
#endif

/*┌──────┐
  │チャンネル２│
  └──────┘*/
#if (SPI_CH2_USE)
	#error : please write SPI_CH2 channel define
#endif
	/*┌──────┐
  │チャンネル3│
  └──────┘*/
#if (SPI_CH3_USE)
	#error : please write SPI_CH3 channel define
#endif
	/*┌──────┐
  │チャンネル4│
  └──────┘*/
#if (SPI_CH4_USE)
	#error : please write SPI_CH4 channel define
#endif
	/*┌──────┐
  │チャンネル5│
  └──────┘*/
#if (SPI_CH5_USE)
	#error : please write SPI_CH5 channel define
#endif
	/*┌──────┐
  │チャンネル6│
  └──────┘*/
#if (SPI_CH6_USE)
	#error : please write SPI_CH6 channel define
#endif
	/*┌──────┐
  │チャンネル7│
  └──────┘*/
#if (SPI_CH7_USE)
	#error : please write SPI_CH7 channel define
#endif
	/*┌──────┐
  │チャンネル8│
  └──────┘*/
#if (SPI_CH8_USE)
	#error : please write SPI_CH8 channel define
#endif
	/*┌──────┐
  │チャンネル9│
  └──────┘*/
#if (SPI_CH9_USE)
#define SPI9_RecDataReg	ucCPU_SC9RB
#define SPI9_TraDataReg	ucCPU_SC9TB
#define SPI9_EEPROMCLK	bCPU_P53OD
#define SPI9_EEPROMDI	bCPU_P52ID
#define SPI9_EEPROMDO	bCPU_P51OD

#define	SPI9_PORT_ENTRY_INIT()  {\
								/*Nomarl Mode set*/                            \
								bCPU_P5M1 = 0;                                 \
								bCPU_P5M2 = 0;                                 \
								bCPU_P5M3 = 0;                                 \
																			   \
                                                                               \
								/*Output Enable*/                              \
								bCPU_P51OE = 1;			                       \
								bCPU_P52OE = 0;                                \
								bCPU_P53OE = 1;                                \
								                                               \
                                                                               \
								/*Iutput Enable*/                              \
								bCPU_P51IE = 0;                                \
								bCPU_P52IE = 1;                                \
								bCPU_P53IE = 0;                                \
								                                               \
								/*SPI Mode set*/                               \
								bCPU_P5M1 = 2;                                 \
								bCPU_P5M2 = 2;                                 \
								bCPU_P5M3 = 2;                                 \
								                                               \
								}\

#define	SPI9_PORT_EXIT_INIT() 	{\
						/*Output data 0*/                  \
						bCPU_P51OD = 0;		/*HU DO*/	   \
						bCPU_P52OD = 0;		/*HU DI*/	   \
						bCPU_P53OD = 0;		/*CLK*/	       \
						                                   \
						                                   \
						/*Output Enable*/                  \
						bCPU_P51OE = 1;			           \
						bCPU_P52OE = 0;                    \
						bCPU_P53OE = 1;                    \
						                                   \
                                                           \
						bCPU_P51IE = 0;                    \
						bCPU_P52IE = 1;                    \
						bCPU_P53IE = 0;                    \
						                                   \
                                                           \
						bCPU_P51PU = 0;                    \
						bCPU_P52PU = 0;                    \
						bCPU_P53PU = 0;                    \
						                                   \
                                                           \
						bCPU_P51ODC = 0;                   \
						bCPU_P53ODC = 0;                   \
                                                           \
						bCPU_P5M1 = 0;                     \
						bCPU_P5M2 = 0;                     \
						bCPU_P5M3 = 0;                     \
						                                   \
						}\
						
#define SPI9_CLOSE()	{\
							bCPU_SC9RSTN = 0;				/*Register SC9MD3,Serial Reset*/ \
							bCPU_SC9RSRN = 0;				/*Register SC9MD3,Serial Reset*/ \
							bCPU_BRTM_S9_EN = 0;			/*BuadRate Timer Off*/           \
						}\
						
#define SPI9_OPEN()	{\
								bCPU_BRTM_S9_EN = 1;			/*BuadRate Timer On*/                    \
								bCPU_SC9RSTN = 1;				/*Register SC9MD3,Serial Open*/          \
								bCPU_SC9RSRN = 0;				/*Register SC9MD3,This Bit Must be 0*/	 \
							}\
							
#define	SPI9_BAUTRATE_SET()	{\
								bCPU_SC9RSTN = 0;				/*Register SC9MD3,Serial Reset*/                                                                                      \
								bCPU_SC9RSRN = 0;				/*Register SC9MD3,Serial Reset*/                                                                                      \
								bCPU_BRTM_S9_EN = 0;			/*BuadRate Timer Off*/                                                                                                \
								bCPU_BRTM_S9_MODE = 0;		/*SB9 Configed to SPI Mode*/                                                                                              \
								bCPU_BRTM_S9_CK = 0x02;		/*clksp/4,clksp = 18Mhz  */                                                                                               \
								ucCPU_BRTM_S9_OC = 0x04;		/*clksp/4/(2*(4+1)) = 0.5M, clksp = 18M  */                                                                           \
								ucCPU_SC9MD0 = 0x87;			/*Clock polarity "H";Communication Mode "Normal Mode";MSB Fisrst;Disable Start Conditon;8bits Transmit*/              \
								ucCPU_SC9MD1 = 0x74;			/*0111 0100*/                                                                                                         \
								/*ucCPU_SC9MD3 = 0x*/                                                                                                                                 \
								bCPU_SC9FDC = 0x10;			/*Output Fixed to 0, Register SC9MD3*/                                                                                    \
							}\

#endif



/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	typedef宣言
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
/* nothing */

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	外部関数へのリンク　[External Linkage]
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
package void	SPIP_enable(unsigned char ch);			/* SPIコントローラ動作を許可する	*/
package void	SPIP_disable(unsigned char ch);			/* SPIコントローラ動作を停止する	*/
package void	SPIP_transmitByte(unsigned char ch,unsigned char data);	/* データ送信を行う			*/
package unsigned char  SPIP_ReceiveByte(unsigned char ch);
package void	SPIP_execResume(unsigned char ch);
package void	SPIP_execSuspend(unsigned char ch);
package void SPIP_changeEdge(unsigned char ch,unsigned char edge);


#endif	/* SPIP_HEADER_DEFINED	*/
