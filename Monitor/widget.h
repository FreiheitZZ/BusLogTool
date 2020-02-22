#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QComboBox>
#include <QPushButton>
#include <QTextEdit>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QTimer>

#define USB_VAL_DLE 0x9F
#define USB_VAL_STX 0x02
#define USB_VAL_ETX 0x03

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void initUI();
    void USB_sendData(unsigned char * pData, unsigned char size);

    QStringList getPortNameList();//获取所有可用的串口列表

    void openPort();//打开串口
    void update_com_num();
public slots:
    void receiveInfo();
//    void BaudRateChange();
    void timerUpDate();

private:
    Ui::Widget *ui;
    QSerialPort* m_serialPort; //串口类
    QStringList m_portNameList;

    QComboBox* m_PortNameComboBox;
    QComboBox* m_BaudRateComboBox;
    QComboBox* m_StopBitsComboBox;
    QComboBox* m_ParityComboBox;
    QComboBox* m_DataBitsComboBox;

    QPushButton* m_OpenPortButton;
    QTextEdit *textEdit;

    QTimer *timer;
};

#endif // WIDGET_H

