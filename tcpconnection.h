#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <QTcpSocket>
#include <QByteArray>
#include <iostream>
#include <QTimer>
#include <QThread>

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
    void hack(QString host, int port);
    quint16 crc16(QByteArray buffer);

private:
    QTcpSocket* socket;
    QTimer* timer;

private slots:
    void connection();
    void disconnection();
    void refreshConnection();
    void handleError();
};

#endif // TCPCONNECTION_H
