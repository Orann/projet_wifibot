#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QKeyEvent>
#include <QTimer>
#include <QtWebEngineWidgets>

#include <tcpconnection.h>
#include <sensors.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_connectButton_clicked();
    void on_forwardButton_pressed();
    void on_backwardButton_pressed();
    void on_leftButton_pressed();
    void on_rightButton_pressed();
    void on_forwardLeftButton_pressed();
    void on_forwardRightButton_pressed();
    void on_backwardLeftButton_pressed();
    void on_backwardRightButton_pressed();
    void on_turnAwayButton_pressed();
    void releaseButton();
    void on_filter1Button_clicked();
    void on_filter2Button_clicked();
    void on_filter3Button_clicked();
    void on_resetFilterButton_clicked();
    void on_speedSlider_valueChanged();
    void on_camUpButton_clicked();
    void on_camDownButton_clicked();
    void on_camLeftButton_clicked();
    void on_camRightButton_clicked();
    void on_camResetButton_clicked();
    void updateSensorsValues(Sensors s);

private:
    Ui::MainWindow *ui;
    TcpConnection* tcpSocket;
    QWebEngineView* streamView;

    void keyPressEvent(QKeyEvent* ev);
    void keyReleaseEvent(QKeyEvent* ev);
};

#endif // MAINWINDOW_H
