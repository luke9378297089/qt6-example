#ifndef SERIALHELPER_H
#define SERIALHELPER_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

class SerialHelper
{
public:
    SerialHelper();
    ~SerialHelper();

    void writeData(const QByteArray &data);
    QByteArray readData();
    bool openSerialPort(const QString &portName);
    void closeSerialPort();
    QStringList listCom();

private:
    QSerialPort *m_serialPort;
};

#endif // SERIALHELPER_H
