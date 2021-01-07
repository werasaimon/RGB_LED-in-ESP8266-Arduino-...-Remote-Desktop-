#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QDebug>
#include <QHostAddress>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_SocketUPD = new QUdpSocket(this); // ����� ��� UDP
    m_Port = 8888; // ����

    // �������� ���������
    connect(ui->dial_RED, SIGNAL(valueChanged(int)), this, SLOT(DialValueChangedRED(int)));
    connect(ui->dial_GREEN, SIGNAL(valueChanged(int)), this, SLOT(DialValueChangedGREEN(int)));
    connect(ui->dial_BLUE, SIGNAL(valueChanged(int)), this, SLOT(DialValueChangedBLUE(int)));
    connect(m_SocketUPD, SIGNAL(readyRead()), this, SLOT(onReadyRead()));

    // �������� ������� ���� N ����� UDP-�����
    m_SocketUPD->bind(m_Port);

}

MainWindow::~MainWindow()
{
    delete ui;
}


// ��������� ������ ������ ����� UDP
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
        ui->label_send_of_correct->setText(datagram);
        data += QString(datagram);
    }
}

// �������� ������ ������ ����� UDP
void MainWindow::SendWrite()
{
    QString str_ip = ui->lineEdit_IP->text();
    QHostAddress IP(str_ip);
    m_SocketUPD->writeDatagram( (char*)&color_info , sizeof(C_COLOR_INFO) , IP , m_Port);
}

// PWM - ��� �������� �����
void MainWindow::DialValueChangedRED(int value)
{
    color_info.r = value;
    if(ui->checkBox_RealTime->isChecked()) SendWrite();
}

// PWM - ��� ������� �����
void MainWindow::DialValueChangedGREEN(int value)
{
    color_info.g = value;
    if(ui->checkBox_RealTime->isChecked()) SendWrite();
}

// PWM - ��� ������ �����
void MainWindow::DialValueChangedBLUE(int value)
{
    color_info.b = value;
    if(ui->checkBox_RealTime->isChecked()) SendWrite();
}

