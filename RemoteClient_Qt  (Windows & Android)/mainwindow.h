#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

   // ���������� ��������� ���
   // �������� ����� � ������� �������
    struct C_COLOR_INFO
    {
        int r;
        int g;
        int b;

        C_COLOR_INFO(int _r = 0 , int _g = 0 , int _b = 0)
            : r(_r) , g(_g) , b(_b)
        {}

    } color_info;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void onReadyRead(); // ��������� ������ ������ ����� UDP
    void SendWrite();   // �������� ������ ������ ����� UDP

    void DialValueChangedRED(int value); // PWM - ��� �������� �����
    void DialValueChangedGREEN(int value); // PWM - ��� ������� �����
    void DialValueChangedBLUE(int value); // PWM - ��� ������ �����

private:
    Ui::MainWindow *ui;

    QUdpSocket *m_SocketUPD;
    quint16     m_Port;
};
#endif // MAINWINDOW_H
