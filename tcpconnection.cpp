#include "tcpconnection.h"

TcpConnection::TcpConnection()
{
    this->socket = new QTcpSocket();
    QObject::connect(this->socket, SIGNAL(connected()), this, SLOT(connection()));
    QObject::connect(this->socket, SIGNAL(disconnected()), this, SLOT(disconnection()));
    QObject::connect(this->socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(handleError()));
}

TcpConnection::~TcpConnection()
{
    delete socket;
}

void TcpConnection::connectTo(QString host, int port)
{
    std::cout <<" Tentative de connexion en cours..." << std::endl;

    socket->abort(); // On désactive les connexions précédentes s'il y en a
    socket->connectToHost(host, port); // On se connecte au serveur demandé
}

void TcpConnection::disconnect()
{
    socket->disconnectFromHost();
}

void TcpConnection::connection()
{
    std::cout << "[Successfull] Connection established." << std::endl;
}

void TcpConnection::disconnection()
{
    std::cout << "[Info] Disconnect from host." << std::endl;
}

void TcpConnection::handleError()
{
    std::cout << "Error Tcpconnection: " << socket->errorString().toStdString() << std::endl;
}
