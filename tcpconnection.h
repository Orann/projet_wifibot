#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <QTcpSocket>
#include <QByteArray>
#include <iostream>

class TcpConnection : public QObject
{
Q_OBJECT
public:
    TcpConnection();
    ~TcpConnection();
    void connectTo(QString host, int port);
    void disconnect();
    void goForward();
    quint16 crc16(QByteArray buffer);

private:
    QTcpSocket* socket;

private slots:
    void connection();
    void disconnection();
    void handleError();
};

#endif // TCPCONNECTION_H
