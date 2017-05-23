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

void TcpConnection::moveRobot(String direction){
    QByteArray frame;

    //char1 : 255
    frame.append((char)0xFF);
    //char2 : size
    frame.append((char)0x07);
    //char3-4 : left speed
    frame.apend((char)0x70);
    frame.apend((char)0x00);
    //char5-6 : right speed
    frame.apend((char)0x70);
    frame.apend((char)0x00);

    //char7 : is the Left / Right speed command flag : Forward / Backward and speed control left & right ON/OFF.
    switch(direction){
        case "forward" :
            frame.apend((char)0xF0);
            break;
        case "backward" :
            frame.apend((char)0xA0);
            break;
        case "left" :
            frame.apend((char)0xC0);
            break;
        case "right" :
            frame.apend((char)0x30);
            break;
        default :
            frame.apend((char)0xF0);
    }

    // On détermine le CRC
    quint16 ValeurCrc = crc16(ba);

    frame.append((char)(ValeurCrc));
    frame.append((char)(ValeurCrc>>8));

    socket->write(frame);

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

quint16 TcpConnection::crc16(QByteArray buffer) {
    quint16 crc = 0xFFFF;
    quint16 polynome = 0xA001;
    unsigned int parity = 0;
    unsigned int cptBit;
    unsigned int cptOct;

    for (cptOct = 1; cptOct < 7; cptOct++){

        crc ^= (unsigned char) buffer.at(cptOct);

        for (cptBit = 0; cptBit <= 7 ; cptBit++){

            parity = crc;
            crc >>= 1;

            if (parity % 2 == true) crc ^= polynome;
        }
    }
    return crc;
}
