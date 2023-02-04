#include "serialHelper.h"


SerialHelper::SerialHelper()
    : m_serialPort(new QSerialPort)
{
}

SerialHelper::~SerialHelper()
{
    if (m_serialPort->isOpen())
        m_serialPort->close();
    delete m_serialPort;
}

bool SerialHelper::openSerialPort(const QString &portName)
{
    m_serialPort->setPortName(portName);
    if (!m_serialPort->open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open serial port:" << m_serialPort->errorString();
        return false;
    }

    m_serialPort->setBaudRate(QSerialPort::Baud9600);
    m_serialPort->setDataBits(QSerialPort::Data8);
    m_serialPort->setParity(QSerialPort::NoParity);
    m_serialPort->setStopBits(QSerialPort::OneStop);
    m_serialPort->setFlowControl(QSerialPort::NoFlowControl);

    return true;
}

QStringList SerialHelper::listCom()
{
    /* 遍历可用串口设备 */
    QStringList serialPort_Name;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        qDebug() << info.portName() + ':' + info.description();
        serialPort_Name << info.portName();
    }
    return serialPort_Name;
}

void SerialHelper::writeData(const QByteArray &data)
{
    if (m_serialPort->isOpen() && m_serialPort->isWritable()) {
        m_serialPort->write(data);
        m_serialPort->waitForBytesWritten(-1);
    }
}

QByteArray SerialHelper::readData()
{
    //详细数据读取 https://www.cnblogs.com/zzssdd2/p/14319615.html
    if (m_serialPort->isOpen() && m_serialPort->isReadable()) {
        return m_serialPort->readAll();
    }
    return QByteArray();
}





