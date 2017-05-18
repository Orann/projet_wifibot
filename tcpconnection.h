#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <QTcpSocket>

class TcpConnection
{
public:
    TcpConnection();
    ~TcpConnection();
    bool connect(QString host, int port);
    void disconnect();

private:
    QTcpSocket* socket;
};

#endif // TCPCONNECTION_H
