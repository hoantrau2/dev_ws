#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Set default your window when start GUI
    init_window();

//    connect(&serial,SIGNAL(readyRead()), this, SLOT(rxMessage()));
//    connect(serial,SIGNAL(readyRead()), this, SLOT(rxMessage()));
    connect(&uartThread, &UART::response, this, &MainWindow::rxMessageThread);
    connect(&uartThread, &UART::errorConnect, this, &MainWindow::showMess);
    connect(&uartThread, &UART::timeout,this, &MainWindow::showMess);
}

MainWindow::~MainWindow()
{
    serial.close();
    delete ui;
}


void MainWindow::on_connect_butt_clicked()

{
    if (ui->connect_butt->text() == "Connect")
    {
//        QString port = ui->port_cb->currentText();
//        serial.setPortName(port);
//        serial.open(QIODevice::ReadWrite);

//        if (!serial.isOpen())
//        {
//            showMess("!!!! Something went Wrong !!!!",Qt::red);
//        }
//        else
//        {
//            //Set Baudrate
//            QString strBaud = ui->baud_cb->currentText();
//            serial.setBaudRate(strBaud.toInt());

//            //Set data bits
//            switch (ui->dataBit_cb->currentIndex()) {
//            case 1:
//                serial.setDataBits(QSerialPort::Data5);
//                break;
//            case 2:
//                serial.setDataBits(QSerialPort::Data6);
//                break;
//            case 3:
//                serial.setDataBits(QSerialPort::Data7);
//                break;
//            case 4:
//                serial.setDataBits(QSerialPort::Data8);
//                break;
//            default:
//                showMess("!!!! Choose data bits !!!!",Qt::red);
//                break;
//            }

//            //Set stop bit
//            switch (ui->stopBit_cb->currentIndex()) {
//            case 1:
//                serial.setStopBits(QSerialPort::OneStop);
//                break;
//            case 2:
//                serial.setStopBits(QSerialPort::OneAndHalfStop);
//                break;
//            case 3:
//                serial.setStopBits(QSerialPort::TwoStop);
//                break;
//            default:
//                showMess("!!!! Choose stop bits !!!!",Qt::red);
//                break;
//            }

//            //Set parity
//            switch (ui->parity_cb->currentIndex()) {
//            case 1:
//                serial.setParity(QSerialPort::NoParity);
//                break;
//            case 2:
//                serial.setParity(QSerialPort::EvenParity);
//                break;
//            case 3:
//                serial.setParity(QSerialPort::OddParity);
//                break;
//            case 4:
//                serial.setParity(QSerialPort::MarkParity);
//                break;
//            case 5:
//                serial.setParity(QSerialPort::SpaceParity);
//                break;
//            default:
//                showMess("!!!! Choose parity !!!!",Qt::red);
//                break;
//            }

//            ui->connect_butt->setText("Disconnect");
//            ui->connect_butt->setStyleSheet("QPushButton {color: red;}");
//            ui->port_cb->setDisabled(true);
//            ui->baud_cb->setDisabled(true);
//            ui->dataBit_cb->setDisabled(true);
//            ui->stopBit_cb->setDisabled(true);
//            ui->parity_cb->setDisabled(true);
//            ui->send_butt->setDisabled(false);

//        }

        if(!uartThread.connect(ui->port_cb->currentText(),ui->baud_cb->currentText().toInt()))
        {
            ui->connect_butt->setText("Disconnect");
            ui->connect_butt->setStyleSheet("QPushButton {color: red;}");
            ui->port_cb->setDisabled(true);
            ui->baud_cb->setDisabled(true);
            ui->dataBit_cb->setDisabled(true);
            ui->stopBit_cb->setDisabled(true);
            ui->parity_cb->setDisabled(true);
            ui->send_butt->setDisabled(false);
        }
    }
    else
    {       
        uartThread.disconnect();

//        serial.close();
        ui->connect_butt->setText("Connect");
        ui->connect_butt->setStyleSheet("QPushButton {color: green;}");
        ui->port_cb->setDisabled(false);
        ui->baud_cb->setDisabled(false);
        ui->dataBit_cb->setDisabled(false);
        ui->stopBit_cb->setDisabled(false);
        ui->parity_cb->setDisabled(false);
        ui->send_butt->setDisabled(true);
    }
}


void MainWindow::on_send_butt_clicked()
{  
    QList<QString> tmp = {QString("1"),
                          ui->dataSend_txt->toPlainText(),
                          ui->dataSend_txt->toPlainText(),
                          ui->dataSend_txt->toPlainText(),

                          QString('\n')};

    uartThread.transmit(tmp);
    QString mess = tmp.join(' ');
    showMess(mess, Qt::blue);
//    ui->message_txt->append(mess);
//    serial.write(mess.toUtf8());
}


void MainWindow::on_clear_butt_clicked()
{
    saveFile();
    ui->message_txt->clear();
}


void MainWindow::on_refresh_butt_clicked()
{
    QList<QSerialPortInfo> ports = info.availablePorts();
    QList<QString> strPorts;
    for (int i = 0; i < ports.size();i++)
    {
        strPorts.append(ports.at(i).portName());
    }
    ui->port_cb->addItems(strPorts);
}


void MainWindow::on_plot_butt_clicked()
{
    QVector<double> x = {1,2,3,4,5,6,7,8,9},y= {4,6,5,3,2,7,3,8,9};

    ui->graph->graph(0)->setData(x,y);
    ui->graph->rescaleAxes();
    ui->graph->replot();
    ui->graph->update();
}


void MainWindow::on_clearGraph_butt_clicked()
{
    ui->graph->graph(0)->data()->clear();
    ui->graph->replot();
    ui->graph->update();
}


void MainWindow::on_lineStyle_cb_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        ui->graph->graph()->setLineStyle(QCPGraph::lsNone);
        break;
    case 1:
        ui->graph->graph()->setLineStyle(QCPGraph::lsLine);
        break;
    case 2:
        ui->graph->graph()->setLineStyle(QCPGraph::lsStepLeft);
        break;
    case 3:
        ui->graph->graph()->setLineStyle(QCPGraph::lsStepRight);
        break;
    case 4:
        ui->graph->graph()->setLineStyle(QCPGraph::lsStepCenter);
        break;
    case 5:
        ui->graph->graph()->setLineStyle(QCPGraph::lsImpulse);
        break;
    default:
        ui->graph->graph()->setLineStyle(QCPGraph::lsNone);
        break;
    }
    ui->graph->replot();
    ui->graph->update();
}


void MainWindow::on_scatterStyle_cb_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        ui->graph->graph(0)->setScatterStyle(QCPScatterStyle::ssNone);
        break;
    case 1:
        ui->graph->graph(0)->setScatterStyle(QCPScatterStyle::ssDot);
        break;
    case 2:
        ui->graph->graph(0)->setScatterStyle(QCPScatterStyle::ssCross);
        break;
    case 3:
        ui->graph->graph(0)->setScatterStyle(QCPScatterStyle::ssPlus);
        break;
    case 4:
        ui->graph->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
        break;
    case 5:
        ui->graph->graph(0)->setScatterStyle(QCPScatterStyle::ssDisc);
        break;
    case 6:
        ui->graph->graph(0)->setScatterStyle(QCPScatterStyle::ssSquare);
        break;
    case 7:
        ui->graph->graph(0)->setScatterStyle(QCPScatterStyle::ssDiamond);
        break;
    case 8:
        ui->graph->graph(0)->setScatterStyle(QCPScatterStyle::ssStar);
        break;
    case 9:
        ui->graph->graph(0)->setScatterStyle(QCPScatterStyle::ssTriangle);
        break;
    case 10:
        ui->graph->graph(0)->setScatterStyle(QCPScatterStyle::ssTriangleInverted);
        break;
    case 11:
        ui->graph->graph(0)->setScatterStyle(QCPScatterStyle::ssCrossSquare);
        break;
    case 12:
        ui->graph->graph(0)->setScatterStyle(QCPScatterStyle::ssPlusCircle);
        break;
    case 13:
        ui->graph->graph(0)->setScatterStyle(QCPScatterStyle::ssPeace);
        break;
    default:
        break;
    }
    ui->graph->replot();
    ui->graph->update();
}


void MainWindow::rxMessage()
{
    quint64 currentTime = time.elapsed() + preTime;
    timeBuff.append(currentTime);
    preTime = currentTime;
    time.start();

    QByteArray dataRX_ba = serial.readAll();   //Read all data from Serial port
    serial.write(dataRX_ba);
    QString code = ui->code_txt->toPlainText();//Get byte stop frame
    int index = dataRX_ba.indexOf(code.toUtf8());
    dataRX_ba = dataRX_ba.mid(0,index);//remove byte stop in frame

    //Split and convert data
    QList<QByteArray> buff = dataRX_ba.split(' ');

    resSysBuff.append(buff[1].toFloat());
    ctrlValBuff.append(buff[2].toFloat());
    qDebug()<<buff[1].toFloat()<<","<< buff[2].toFloat();

    QString dataRX_str(dataRX_ba);
    if (index != -1)
    {
        showValue(dataRX_str);
    }

    if (ui->run_butt->text() == "Stop")
        plotResponse();
}

void MainWindow::rxMessageThread(const QList<QByteArray> resMess)
{
    quint64 currentTime = time.elapsed() + preTime;
    timeBuff.append(currentTime);
    preTime = currentTime;
    time.start();

    resSysBuff.append(resMess[1].toFloat());
    ctrlValBuff.append(resMess[2].toFloat());
    qDebug()<<resMess[1].toFloat()<<","<< resMess[2].toFloat();

    QString dataRX_str(tr("Value= %1, u_control= %2")
                       .arg(resMess[1].toFloat()).arg(resMess[2].toFloat()));
    showValue(dataRX_str);
    if (ui->run_butt->text() == "Stop")
        plotResponse();
}


void MainWindow::init_window()
{
    setFixedSize(width(), height());
    setWindowTitle("Example UART");
    ui->send_butt->setDisabled(true);

    //Init graph
    ui->graph->addGraph();
    ui->graph->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->graph->graph()->setLineStyle(QCPGraph::lsLine);
    ui->graph->xAxis->setLabel("X");
    ui->graph->yAxis->setLabel("Y");
    ui->graph->xAxis->setRange(-6000,100);
    ui->graph->yAxis->setRange(-6000,8000);
    ui->graph->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    //Set default index
    ui->tabWidget->setCurrentIndex(0);
    ui->lineStyle_cb->setCurrentIndex(1);
    ui->scatterStyle_cb->setCurrentIndex(4);
    ui->parity_cb->setCurrentIndex(1);
    ui->stopBit_cb->setCurrentIndex(1);
    ui->dataBit_cb->setCurrentIndex(4);

    //Find COM on Computer
    QList<QSerialPortInfo> ports = info.availablePorts();
    QList<QString> strPorts;
    for (int i = 0; i < ports.size();i++)
    {
        strPorts.append(ports.at(i).portName());
        qDebug() << "\n"
                        << "Port:" << ports.at(i).portName() << "\n"
                        << "Location:" << ports.at(i).systemLocation() << "\n"
                        << "Description:" << ports.at(i).description() << "\n"
                        << "Manufacturer:" << ports.at(i).manufacturer() << "\n"
                        << "Serial number:" << ports.at(i).serialNumber() << "\n"
                        << "Vendor Identifier:"
                        << (ports.at(i).hasVendorIdentifier()
                            ? QByteArray::number(ports.at(i).vendorIdentifier(), 16)
                            : QByteArray()) << "\n"
                        << "Product Identifier:"
                        << (ports.at(i).hasProductIdentifier()
                            ? QByteArray::number(ports.at(i).productIdentifier(), 16)
                            : QByteArray());

    }
    ui->port_cb->addItems(strPorts);

    // List all Baudrates your computer support
    QList<qint32> baudRates = info.standardBaudRates();
    QList<QString> strBaudRates;
    for(int i = 0 ; i < baudRates.size() ; i++){
        strBaudRates.append(QString::number(baudRates.at(i)));
    }
    ui->baud_cb->addItems(strBaudRates);
}


void MainWindow::on_run_butt_clicked()
{
    if (ui->run_butt->text() == "Run")
    {
        //Another code send run system
        time.start();
        preTime = 0;
        ctrlValBuff.append(0.0);
        timeBuff.append(0.0);
        resSysBuff.append(0.0);
        ui->run_butt->setStyleSheet("QPushButton {color: red;}");
        ui->run_butt->setText("Stop");
    }
    else
    {
        //Another code send stop system
        time.elapsed();
        ctrlValBuff.clear();
        timeBuff.clear();
        resSysBuff.clear();
        ui->run_butt->setStyleSheet("QPushButton {color: green;}");
        ui->run_butt->setText("Run");
    }
}

void MainWindow::plotResponse()
{
    ui->graph->graph(0)->setData(timeBuff,resSysBuff);
    ui->graph->rescaleAxes();
    ui->graph->replot();
    ui->graph->update();
}

void MainWindow::showMess(const QString mess, const Qt::GlobalColor colorTxt)
{
    ui->message_txt->setTextColor(colorTxt);
    ui->message_txt->append(mess);
    ui->message_txt->setTextColor(Qt::black);
}

void MainWindow::saveFile()
{
    QString fileName = "E:\\PIF\\GUI_tutorial\\document\\out.txt";
    QFile file(fileName);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        QString text = ui->receive_txt->toPlainText();
        stream << text << Qt::endl;
        qDebug()<<1;
    }
    else
    {
        qDebug()<<1;
    }
    file.close();
}

void MainWindow::on_saveGraph_butt_clicked()
{
    QString fileName = "E:\\PIF\\GUI_tutorial\\document\\graph.jpg";
    QFile file(fileName);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        ui->graph->saveJpg(fileName);
    }
    file.close();
}

void MainWindow::showValue(const QString mess)
{
    ui->receive_txt->setTextColor(Qt::blue);
    ui->receive_txt->append(mess);
}




