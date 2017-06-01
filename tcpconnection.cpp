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

void TcpConnection::moveRobot(QString direction){
    QByteArray frame;

    //char1 : 255
    frame.append((char)0xFF);
    //char2 : size
    frame.append((char)0x07);

    QStringList directions;
    directions << "forward" << "backward" << "left" << "right";
    switch(directions.indexOf(direction)){
        case 0 :
            //char3-4 : left speed
            frame.append((char)0x70);
            frame.append((char)0x00);
            //char5-6 : right speed
            frame.append((char)0x70);
            frame.append((char)0x00);
            //char 7 : is the Left / Right speed command flag : Forward / Backward and speed control left & right ON/OFF.
            frame.append((char)0xF0);
            break;
        case 1 :
            //char3-4 : left speed
            frame.append((char)0x70);
            frame.append((char)0x00);
            //char5-6 : right speed
            frame.append((char)0x70);
            frame.append((char)0x00);
            //char 7 : is the Left / Right speed command flag : Forward / Backward and speed control left & right ON/OFF.
            frame.append((char)0xA0);
            break;
        case 2 :
            //char3-4 : left speed
            frame.append((char)0x00);
            frame.append((char)0x00);
            //char5-6 : right speed
            frame.append((char)0x70);
            frame.append((char)0x00);
            //char 7 : is the Left / Right speed command flag : Forward / Backward and speed control left & right ON/OFF.
            frame.append((char)0xF0);
            break;
        case 3 :
            //char3-4 : left speed
            frame.append((char)0x70);
            frame.append((char)0x00);
            //char5-6 : right speed
            frame.append((char)0x00);
            frame.append((char)0x00);
            //char 7 : is the Left / Right speed command flag : Forward / Backward and speed control left & right ON/OFF.
            frame.append((char)0xF0);
            break;
        default :
            //char3-4 : left speed
            frame.append((char)0x00);
            frame.append((char)0x00);
            //char5-6 : right speed
            frame.append((char)0x00);
            frame.append((char)0x00);
            //char 7 : is the Left / Right speed command flag : Forward / Backward and speed control left & right ON/OFF.
            frame.append((char)0x00);
    }

    // On détermine le CRC
    quint16 ValeurCrc = crc16(frame);

    frame.append((char)(ValeurCrc));
    frame.append((char)(ValeurCrc>>8));

    socket->write(frame);

}

void TcpConnection::disconnect()
{
    moveRobot("stop");
    socket->disconnectFromHost();
}

void TcpConnection::connection()
{
    std::cout << "[Successfull] Connection established." << std::endl;

    sendEmptyFrame();
    this->timer = new QTimer(this);
    connect(this->timer, SIGNAL(timeout()), this, SLOT(refreshConnection()));
    timer->setSingleShot(false);
    timer->start(500);
}

void TcpConnection::disconnection()
{
    std::cout << "[Info] Disconnect from host." << std::endl;
    timer->stop();
}

void TcpConnection::sendEmptyFrame()
{
    QByteArray frame;
    frame.append(255);
    this->socket->write(frame);
}

void TcpConnection::refreshConnection()
{
    sendEmptyFrame();
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
