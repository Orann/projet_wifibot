#include "tcpconnection.h"

TcpConnection::TcpConnection()
{
    this->socket = new QTcpSocket();
}

TcpConnection::~TcpConnection()
{
    delete socket;
}

bool TcpConnection::connect(QString host, int port)
{
    bool connected = true;

    socket->connectToHost(host, port);

    if(!socket->waitForConnected(5000))
        connected = false;

    return connected;
}

void TcpConnection::disconnect()
{
    socket->disconnectFromHost();
}
