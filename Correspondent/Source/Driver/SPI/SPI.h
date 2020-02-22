/*������������������������������������������������������������������������������
	�w�b�_�[�t�@�C����荞��
������������������������������������������������������������������������������*/
/* nothing */

/*������������������������������������������������������������������������������
	define��`
������������������������������������������������������������������������������*/
#define	SPI_CH0		0			/* �`�����l��0 */
#define	SPI_CH1		1			/* �`�����l��1 */
#define	SPI_CH2		2			/* �`�����l��2 */
#define	SPI_CH3		3			/* �`�����l��3 */
#define	SPI_CH4		4			/* �`�����l��4 */
#define	SPI_CH5		5			/* �`�����l��5 */
#define	SPI_CH6		6			/* �`�����l��6 */
#define	SPI_CH7		7			/* �`�����l��7 */
#define	SPI_CH8		8			/* �`�����l��8 */
#define	SPI_CH9		9			/* �`�����l��9 */



/*������������������������������������������������������������������������������
	typedef�錾
������������������������������������������������������������������������������*/
/* nothing */

/*������������������������������������������������������������������������������
	�O���֐��ւ̃����N�@[External Linkage]
������������������������������������������������������������������������������*/
public void SPI_execResume(unsigned char ch);				/* SPI�h���C�o��Resume����������	*/
public void SPI_execSuspend(unsigned char ch);				/* SPI�h���C�o��Suspend����������	*/
public void SPI_enable(unsigned char ch);					/* SPI�h���C�o�����������		*/
public void SPI_disable(unsigned char ch);					/* SPI�h���C�o������~����		*/
public unsigned char SPI_transmitData(unsigned char ch, unsigned char Data);	/* �f�[�^���M���s��			*/
public signed char SPI_receiveData(unsigned char ch, unsigned char *Data);
public void SPI_changeEdge(unsigned char ch,unsigned char edge);


/*������������������������������������������������������������������������������
	�}�N���֐���`
������������������������������������������������������������������������������*/
/* nothing */
