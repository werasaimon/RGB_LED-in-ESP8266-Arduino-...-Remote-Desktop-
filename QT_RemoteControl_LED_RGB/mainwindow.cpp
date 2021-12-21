#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QHostAddress>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("RemoteControl LED RGB");

    m_SocketUPD = new QUdpSocket(this); // Ñîêåò äëÿ UDP
    m_Port = 8888; // Ïîðò

    // Êîíåêòèì èíòåðôåéñ
    connect(ui->dial_RED, SIGNAL(valueChanged(int)), this, SLOT(DialValueChangedRED(int)));
    connect(ui->dial_GREEN, SIGNAL(valueChanged(int)), this, SLOT(DialValueChangedGREEN(int)));
    connect(ui->dial_BLUE, SIGNAL(valueChanged(int)), this, SLOT(DialValueChangedBLUE(int)));
    connect(m_SocketUPD, SIGNAL(readyRead()), this, SLOT(onReadyRead()));

    // Íà÷èíàåì ñëóøàòü ïîðò N ÷åðåç UDP-ñîêåò
    m_SocketUPD->bind(m_Port);

}

MainWindow::~MainWindow()
{
    delete ui;
}


// Ïðèíèìàåì ïàêåòû äàííûõ ÷åðåç UDP
void MainWindow::onReadyRead()
{
    QString data = "";
    while(m_SocketUPD->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(m_SocketUPD->pendingDatagramSize());
        QHostAddress senderIP;
        quint16 senderPort;
        m_SocketUPD->readDatagram(datagram.data(), datagram.size(), &senderIP, &senderPort);
        data += QString(datagram);
    }
}

// Îòñûëàåì ïàêåòû äàííûõ ÷åðåç UDP
void MainWindow::SendWrite()
{
    QString str_ip = ui->lineEdit_IP->text();
    QHostAddress IP(str_ip);
    m_SocketUPD->writeDatagram( (char*)&color_info , sizeof(C_COLOR_INFO) , IP , m_Port);
}

// PWM - äëÿ êðàñíîãî öâåòà
void MainWindow::DialValueChangedRED(int value)
{
    ui->label_R->setText("R : " + QString::number(value));
    color_info.r = value;
    if(ui->checkBox_RealTime->isChecked()) SendWrite();
}

// PWM - äëÿ çåë¸íîãî öâåòà
void MainWindow::DialValueChangedGREEN(int value)
{
    ui->label_G->setText("G : " + QString::number(value));
    color_info.g = value;
    if(ui->checkBox_RealTime->isChecked()) SendWrite();
}

// PWM - äëÿ ñèíèãî öâåòà
void MainWindow::DialValueChangedBLUE(int value)
{
    ui->label_B->setText("B : " + QString::number(value));
    color_info.b = value;
    if(ui->checkBox_RealTime->isChecked()) SendWrite();
}

