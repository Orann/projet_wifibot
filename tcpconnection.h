#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <QTcpSocket>
#include <QByteArray>
#include <iostream>
#include <QTimer>
#include <QThread>

#include <sensors.h>

class TcpConnection : public QObject
{
Q_OBJECT
public:
    TcpConnection();
    ~TcpConnection();
    void connectTo(QString host, int port);
    void disconnect();
    void moveRobot(QString direction, int speed = 0);
    void sendEmptyFrame();
    quint16 crc16(QByteArray buffer);
    void getSensors();

private:
    QTcpSocket* socket;
    QTimer* timer;

private slots:
    void connection();
    void disconnection();
    void refreshConnection();
    void handleError();

signals:
    void sensorsValues(Sensors s);
};

#endif // TCPCONNECTION_H
