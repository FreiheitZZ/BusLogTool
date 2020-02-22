#include "widget.h"
#include <QLayout>
#include <QTextCursor>
#include <QColorDialog>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QPainter>

#include <QDebug>

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

/* Start 17my add crc check --001*/

QStringList strList;
unsigned char s_aTransmitBuf[400];
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

void Widget::USB_sendData(unsigned char * pData, unsigned char size)
{
    unsigned char rp,wp,crc_H,crc_L;
    unsigned short crc;

    wp = 0;
    memset(s_aTransmitBuf, 0, sizeof(s_aTransmitBuf));
    s_aTransmitBuf[wp++] = USB_VAL_DLE;

    s_aTransmitBuf[wp++] = USB_VAL_STX;

    for (rp = 0 ; rp < size ; rp++) {
        s_aTransmitBuf[wp++] = *(pData+rp);
        if(*(pData+rp) == USB_VAL_DLE) {
            s_aTransmitBuf[wp++] = USB_VAL_DLE;
        }
    }
    crc = nfPacketCrc16(pData,size);
    crc_H = ( unsigned char )( ( crc & 0xff00 ) >> 8 );
    crc_L = ( unsigned char )( crc & 0x00ff );

    s_aTransmitBuf[wp++] = crc_H;

    if(crc_H==USB_VAL_DLE){
        s_aTransmitBuf[wp++] = USB_VAL_DLE;
    }
    s_aTransmitBuf[wp++] = crc_L;

    if(crc_L==USB_VAL_DLE){
        s_aTransmitBuf[wp++] = USB_VAL_DLE;
    }

    s_aTransmitBuf[wp++] = USB_VAL_DLE;
    s_aTransmitBuf[wp++] = USB_VAL_ETX;

    m_serialPort->write(reinterpret_cast<const char*>(s_aTransmitBuf));/*使用reinterpret_cast进行强制转换*/
}

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
    m_serialPort = new QSerialPort();
    timer = new QTimer(this);

    initUI();

    m_portNameList = getPortNameList();

    m_PortNameComboBox->addItems(m_portNameList);

    connect(m_OpenPortButton,&QPushButton::clicked,this,&Widget::openPort);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpDate()));

}

Widget::~Widget()
{
    if (m_serialPort->isOpen())
    {
        m_serialPort->close();
    }
    delete m_serialPort;

    delete ui;
}

void Widget::initUI()
{
    this->setWindowTitle("码农小明 test QSerialPort");


    m_OpenPortButton = new QPushButton();
    m_OpenPortButton->setText("打开串口");

    m_PortNameComboBox  = new QComboBox();
    m_BaudRateComboBox  = new QComboBox();
    m_StopBitsComboBox  = new QComboBox();
    m_ParityComboBox    = new QComboBox();
    m_DataBitsComboBox  = new QComboBox();

    strList << "1382400" << "921600" << "460800"
            << "256000" << "230400" << "128000"
            << "115200" << "76800" << "57600"
            << "43000" << "38400" << "19200"
            << "14400" << "9600" << "4800"
            << "2400" << "1200";
    m_BaudRateComboBox->addItems(strList);



    textEdit = new QTextEdit();

    QHBoxLayout *m_layout = new QHBoxLayout();
    QVBoxLayout *m_layout_V = new QVBoxLayout();

    m_layout->addWidget(m_PortNameComboBox);
    m_layout->addWidget(m_BaudRateComboBox);
    m_layout->addWidget(m_StopBitsComboBox);
    m_layout->addWidget(m_ParityComboBox  );
    m_layout->addWidget(m_DataBitsComboBox);

    m_layout->addWidget(m_OpenPortButton);

    m_layout_V->addLayout(m_layout);
    m_layout_V->addWidget(textEdit);
    this->setLayout(m_layout_V);
}

QStringList Widget::getPortNameList()
{
    QStringList m_serialPortName;
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        m_serialPortName << info.portName();
        qDebug()<<"serialPortName:"<<info.portName();
    }
    return m_serialPortName;
}

void Widget::openPort()
{
    if(m_serialPort->isOpen())//如果串口已经打开了 先给他关闭了
    {
        timer->stop();
        m_OpenPortButton->setText("打开串口");
        m_serialPort->clear();
        m_serialPort->close();
        qDebug()<<"serial close";
    }
    else
    {
        qDebug()<<"zhun bei da kai";
        m_OpenPortButton->setText("关闭串口");
        qDebug()<<"clear kaishi";
        //m_serialPort->clear();
        qDebug()<<"clear jieshu";
        m_serialPort->setPortName(m_PortNameComboBox->currentText());//当前选择的串口名字

        if(!m_serialPort->open(QIODevice::ReadWrite))//用ReadWrite 的模式尝试打开串口
        {
            qDebug()<<"打开失败!";
            return;
        }
        qDebug()<<"串口打开成功!";
        qDebug()<<"serial open";
        m_serialPort->setBaudRate(QSerialPort::Baud115200,QSerialPort::AllDirections);//设置波特率和读写方向
        m_serialPort->setDataBits(QSerialPort::Data8);      //数据位为8位
        m_serialPort->setFlowControl(QSerialPort::NoFlowControl);//无流控制
        m_serialPort->setParity(QSerialPort::NoParity); //无校验位
        m_serialPort->setStopBits(QSerialPort::OneStop); //一位停止位
        m_serialPort->clear();
        timer->start(1000);
        connect(m_serialPort,SIGNAL(readyRead()),this,SLOT(receiveInfo()));
    }

}

//接收到单片机发送的数据进行解析
void Widget::receiveInfo()
{
    unsigned char rp,wp,sum,crc_H,crc_L,fillwp;
    unsigned short crc;
    unsigned char a,b;

    QByteArray info = m_serialPort->readAll();
    unsigned char *temp = (unsigned char *)malloc(info.size()-6);

    qDebug() << "receive info:" << info.toHex();
    if(info != NULL)
    {
        for(int i = 0; i < (info.size()-6); i++)
        {
            *(temp+i) = info.toHex().at(i*2+4);
            if((*(temp+i) >= 0x30) && (*(temp+i) <= 0x39))
                a = *(temp+i) - 0x30;
            else if((*(temp+i) >= 0x61) && (*(temp+i) <= 0x66))
                a = (*(temp+i)-0x61) + 10;
            else
                ;

            *(temp+i) = info.toHex().at(i*2+1+4);
            if((*(temp+i) >= 0x30) && (*(temp+i) <= 0x39))
                b = *(temp+i) - 0x30;
            else if((*(temp+i) >= 0x61) && (*(temp+i) <= 0x66))
                b = (*(temp+i)-0x61) + 10;
            else
                ;
            *(temp+i) = a*16 + b;
            qDebug() << "temp = " << *(temp+i);

        }

      //  temp = (unsigned char *)(info.toHex().mid(2,info.size()-6).data());
        crc = nfPacketCrc16(temp, info.size()-6);

        qDebug() << "temp:" << *temp;
        qDebug() << "CRC16:" << crc;

        crc_H = ( unsigned char )( ( crc & 0xff00 ) >> 8 );
        crc_L = ( unsigned char )( crc & 0x00ff );

        if(info != NULL)
        {

            {
                if(info.mid(2, 5) == "uart1")
                {
                    textEdit->append("<font color=\"#FF0000\">" + info.mid(2,info.size()-6) + "</font> ");
                }
                else if(info.mid(2, 5) == "uart2")
                {
                    textEdit->append("<font color=\"#0000FF\">" + info.mid(2,info.size()-6) + "</font> ");
                }
                else
                {
                    textEdit->append("<font color=\"#000000\">" + info.mid(2,info.size()-6) + "</font> ");
                }

                textEdit->moveCursor(QTextCursor::End);
            }
        }
    }
    free(temp);
}

void Widget::timerUpDate()
{
    unsigned char str[] = "PC send";
    USB_sendData(str, 7);
}

void Widget::update_com_num()
{
    getPortNameList();
}

