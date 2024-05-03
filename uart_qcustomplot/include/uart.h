#ifndef UART_H
#define UART_H

#include <QThread>
#include <QObject>
#include <QSerialPort>
#include <QByteArray>
#include <QTime>

class UART : public QThread
{
    Q_OBJECT
public:
    explicit UART(QObject *parent = nullptr);

    bool connect(QString nameCOM, quint32 baud);
    void disconnect();
    void transmit(QList<QString> transData);
    bool stateConnect();

signals:
    void response(QList<QByteArray>);
    void errorConnect(QString, const Qt::GlobalColor);
    void timeout(QString, const Qt::GlobalColor);

private slots:
    void receive();

protected:
    void run();

private: 
    QSerialPort serial;
    bool COMConnect = false;
    QList<QByteArray> resMessBuff;
};

#endif // UART_H
