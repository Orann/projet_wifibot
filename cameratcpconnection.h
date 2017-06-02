#ifndef CAMERATCPCONNECTION_H
#define CAMERATCPCONNECTION_H
#include <tcpconnection.h>
#include <QTimer>
#include <QObject>
#include <QPixmap>

#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>


class CameraTcpConnection
{
public:
    CameraTcpConnection();
    ~CameraTcpConnection();

    void moveCamera(char v);

    void start();
    void stop();

    QPixmap getPixmap();


public slots:
    void cameraError(QNetworkReply::NetworkError);
    void cameraSaveImg();

private slots:
    //void sendRequest();

private:

    QString move;

    TcpConnection* socket;
    QString host;
    QPixmap img;

    bool error;

};

#endif // CAMERATCPCONNECTION_H
