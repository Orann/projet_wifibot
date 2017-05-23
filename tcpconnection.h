#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <QTcpSocket>
#include <iostream>

class TcpConnection : public QObject
{
Q_OBJECT
public:
    TcpConnection();
    ~TcpConnection();
    void connectTo(QString host, int port);
    void disconnect();

private:
    QTcpSocket* socket;

private slots:
    void connection();
    void disconnection();
    void handleError();
};

#endif // TCPCONNECTION_H
