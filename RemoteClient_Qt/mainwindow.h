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

   // Спецальная структура для
   // хранения цвета в удобном формате
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

    void onReadyRead(); // Принимаем пакеты данных через UDP
    void SendWrite();   // Отсылаем пакеты данных через UDP

    void DialValueChangedRED(int value); // PWM - для красного цвета
    void DialValueChangedGREEN(int value); // PWM - для зелёного цвета
    void DialValueChangedBLUE(int value); // PWM - для синиго цвета

private:
    Ui::MainWindow *ui;

    QUdpSocket *m_SocketUPD;
    quint16     m_Port;
};
#endif // MAINWINDOW_H
