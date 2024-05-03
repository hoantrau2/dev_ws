#include "../include/uart.h"

UART::UART(QObject *parent)
    : QThread{parent}
{

}

bool UART::connect(QString nameCOM, quint32 baud)
{
    serial.setPortName(nameCOM);
    serial.open(QIODevice::ReadWrite);
    if (!serial.isOpen())
    {
        emit errorConnect(tr("Can't open %1, error code %2")
                          .arg(nameCOM).arg(serial.error()),Qt::red);
        return 1;
    }
    else
    {
        serial.setBaudRate(baud);
        serial.setDataBits(QSerialPort::Data8);
        serial.setStopBits(QSerialPort::OneStop);
        serial.setParity(QSerialPort::NoParity);
        COMConnect = true;
        if (!isRunning())
            start();
        return 0;
    }
}

void UART::disconnect()
{
    COMConnect = false;
    terminate();
    serial.close();
}

void UART::transmit(QList<QString> transData)
{
    QString mess = transData.join(' ');
    serial.write(mess.toUtf8());
}

bool UART::stateConnect()
{
    return COMConnect;
}

void UART::receive()
{
    QByteArray dataRX_ba = serial.readAll();
    int index = dataRX_ba.indexOf(QString("\n").toUtf8());
    dataRX_ba = dataRX_ba.mid(0,index);//remove byte stop in frame

    //Split and convert data
    QList<QByteArray> buff = dataRX_ba.split(' ');
    emit response(buff);
}

void UART::run()
{
    while (COMConnect)
    {
        if(serial.waitForReadyRead(1000))
            receive();
        else
            emit timeout(tr("Wait read request timeout %1")
                         .arg(QTime::currentTime().toString()),Qt::darkMagenta);
    }
}
