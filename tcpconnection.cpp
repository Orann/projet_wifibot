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

void TcpConnection::moveRobot(QString direction, int speed){
    QByteArray frame;

    //char1 : 255
    frame.append((char)0xFF);
    //char2 : size
    frame.append((char)0x07);

    QStringList directions;
    directions << "forward" << "backward" << "left" << "right" << "topLeft" << "topRight" << "bottomLeft" << "bottomRight" << "turnaway";
    switch(directions.indexOf(direction)){
        case 0 : //forward
            //char3-4 : left speed
            frame.append((char)((int)(240*speed)/100));
            frame.append((char)0x00);
            //char5-6 : right speed
            frame.append((char)((int)(240*speed)/100));
            frame.append((char)0x00);
            //char 7 : is the Left / Right speed command flag : Forward / Backward and speed control left & right ON/OFF.
            frame.append((char)0xF0);
            break;
        case 1 : //backard... idem for the other case
            //char3-4 : left speed
            frame.append((char)((int)(240*speed)/100));
            frame.append((char)0x00);
            //char5-6 : right speed
            frame.append((char)((int)(240*speed)/100));
            frame.append((char)0x00);
            //char 7 : is the Left / Right speed command flag : Forward / Backward and speed control left & right ON/OFF.
            frame.append((char)0xA0);
            break;
        case 2 :
            //char3-4 : left speed
            frame.append((char)0x00);
            frame.append((char)0x00);
            //char5-6 : right speed
            frame.append((char)(int)((240*speed)/100));
            frame.append((char)0x00);
            //char 7 : is the Left / Right speed command flag : Forward / Backward and speed control left & right ON/OFF.
            frame.append((char)0xF0);
            break;
        case 3 :
            //char3-4 : left speed
            frame.append((char)((int)(240*speed)/100));
            frame.append((char)0x00);
            //char5-6 : right speed
            frame.append((char)0x00);
            frame.append((char)0x00);
            //char 7 : is the Left / Right speed command flag : Forward / Backward and speed control left & right ON/OFF.
            frame.append((char)0xF0);
            break;
        case 4 :
            //char3-4 : left speed
            frame.append((char)0x78);
            frame.append((char)0x00);
            //char5-6 : right speed
            frame.append((char)((int)(240*speed)/100));
            frame.append((char)0x00);
            //char 7 : is the Left / Right speed command flag : Forward / Backward and speed control left & right ON/OFF.
            frame.append((char)0x50);
            break;
        case 5 :
            //char3-4 : left speed
            frame.append((char)((int)(240*speed)/100));
            frame.append((char)0x00);
            //char5-6 : right speed
            frame.append(0x78);
            frame.append((char)0x00);
            //char 7 : is the Left / Right speed command flag : Forward / Backward and speed control left & right ON/OFF.
            frame.append((char)0x50);
            break;
        case 6 :
            //char3-4 : left speed
            frame.append(0x78);
            frame.append((char)0x00);
            //char5-6 : right speed
            frame.append((char)((int)(240*speed)/100));
            frame.append((char)0x00);
            //char 7 : is the Left / Right speed command flag : Forward / Backward and speed control left & right ON/OFF.
            frame.append((char)0x00);
            break;
        case 7 :
            //char3-4 : left speed
            frame.append((char)((int)(240*speed)/100));
            frame.append((char)0x00);
            //char5-6 : right speed
            frame.append(0x78);
            frame.append((char)0x00);
            //char 7 : is the Left / Right speed command flag : Forward / Backward and speed control left & right ON/OFF.
            frame.append((char)0x00);
            break;
        case 8 :
            //char3-4 : left speed
            frame.append((char)((int)(240*speed)/100));
            frame.append((char)0x00);
            //char5-6 : right speed
            frame.append(0x78);
            frame.append((char)0x00);
            //char 7 : is the Left / Right speed command flag : Forward / Backward and speed control left & right ON/OFF.
            frame.append((char)0x00);
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
    getSensors();
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

void TcpConnection::getSensors(){
    QByteArray ba = socket->readAll();

    if(ba.size() > 17)
    {
        quint32 odoL,odoR;
        qint16 speedL,speedR;
        quint8 battery,adc0,adc1,adc3,adc4,current,version;

        // Left
        speedL = ba.at(0)+(ba.at(1)<<8);
        battery = ba.at(2);
        adc4 = ba.at(3);
        adc3 = ba.at(4);
        odoL = ba.at(5)+(ba.at(6)<<8)+(ba.at(7)<<16)+(ba.at(8)<<24);

        // Right
        speedR = ba.at(9)+(ba.at(10)<<8);
        adc0 = ba.at(11);
        adc1 = ba.at(12);
        odoR = ba.at(13)+(ba.at(14)<<8)+(ba.at(15)<<16)+(ba.at(16)<<24);
        current = ba.at(17);
        version = ba.at(18);

        //On suppose que la batterie est déchargée à 11.7 V et pleine à 12.8 et et si c'est au dessus, c'est parce qu'il recharge
        Sensors s = Sensors(odoL, odoR, speedL, speedR, battery, adc0, adc1, adc3, adc4, current, version);

        emit sensorsValues(s);
    }
}
