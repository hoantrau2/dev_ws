#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QObject>
#include <QThread>
#include <QList>
#include <QIODevice>
#include <QVector>
#include <QElapsedTimer>
#include <QFile>
#include <QTextStream>
#include "uart.h"
#include <qcustomplot.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_connect_butt_clicked();

    void on_send_butt_clicked();

    void on_clear_butt_clicked();

    void on_refresh_butt_clicked();

    void on_plot_butt_clicked();

    void on_clearGraph_butt_clicked();

    void on_lineStyle_cb_currentIndexChanged(int index);

    void on_scatterStyle_cb_currentIndexChanged(int index);

    void rxMessage();

    void rxMessageThread(const QList<QByteArray> resMess);

    void init_window();

    void on_run_butt_clicked();

    void plotResponse();

    void showMess(const QString mess, const Qt::GlobalColor colorTxt);

    void saveFile();

    void on_saveGraph_butt_clicked();

    void showValue(const QString mess);


private:
    Ui::MainWindow *ui;

    QSerialPort serial;
    QSerialPortInfo info;

    QElapsedTimer time;
    QList<double> timeBuff, resSysBuff, ctrlValBuff;
    quint64 preTime = 0;
    UART uartThread;

};
#endif // MAINWINDOW_H
