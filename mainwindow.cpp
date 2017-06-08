#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tcpSocket = new TcpConnection();

    //Camera :
    QWebEngineView* streamView = new QWebEngineView();
    ui->gridLayout_6->addWidget(streamView);
    streamView->load(QUrl("http://192.168.1.106:8080/?action=stream"));
    streamView->show();


    //Signals :
    connect(ui->forwardButton, SIGNAL(released()), this, SLOT (releaseButton()));
    connect(ui->backwardButton, SIGNAL(released()), this, SLOT (releaseButton()));
    connect(ui->leftButton, SIGNAL(released()), this, SLOT (releaseButton()));
    connect(ui->rightButton, SIGNAL(released()), this, SLOT (releaseButton()));
    connect(tcpSocket, SIGNAL(sensorsValues(Sensors)), this, SLOT(updateSensorsValues(Sensors)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete tcpSocket;
}

void MainWindow::on_connectButton_clicked(){
    bool ok;
    if(ui->connectButton->text() == "Connect"){
        tcpSocket->connectTo(ui->hostEdit->text(), ui->portEdit->text().toInt(&ok, 10));
        ui->connectButton->setText("Disconnect");
    } else{
        tcpSocket->disconnect();
        ui->connectButton->setText("Connect");
    }
}

void MainWindow::on_forwardButton_pressed(){
    tcpSocket->moveRobot("forward", ui->speedSlider->value());
    std::cout << "[Info] Robot go forward." << std::endl;
}

void MainWindow::on_backwardButton_pressed(){
    tcpSocket->moveRobot("backward", ui->speedSlider->value());
    std::cout << "[Info] Robot go backward." << std::endl;
}

void MainWindow::on_leftButton_pressed(){
    tcpSocket->moveRobot("left", ui->speedSlider->value());
    std::cout << "[Info] Robot go to the left." << std::endl;
}

void MainWindow::on_rightButton_pressed(){
    tcpSocket->moveRobot("right", ui->speedSlider->value());
    std::cout << "[Info] Robot go to the right." << std::endl;
}
void MainWindow::releaseButton(){
    tcpSocket->moveRobot("stop");
    std::cout << "[Info] Stop robot." << std::endl;
}

void MainWindow::on_camUpButton_clicked(){
    std::cout << "[Info] Camera robot up." << std::endl;
    QNetworkRequest request;
    QNetworkAccessManager* man = new QNetworkAccessManager();
    request.setUrl(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=-200"));
    man->get(request);
    man=NULL ; free(man);
}

void MainWindow::on_camDownButton_clicked(){
    std::cout << "[Info] Camera robot down." << std::endl;
    QNetworkRequest request;
    QNetworkAccessManager* man = new QNetworkAccessManager();
    request.setUrl(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=200"));
    man->get(request);
    man=NULL ; free(man);
}

void MainWindow::on_camLeftButton_clicked(){
    std::cout << "[Info] Camera robot left." << std::endl;
    QNetworkRequest request;
    QNetworkAccessManager* man = new QNetworkAccessManager();
    request.setUrl(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=200"));
    man->get(request);
    man=NULL ; free(man);
}

void MainWindow::on_camRightButton_clicked(){
    std::cout << "[Info] Camera robot right." << std::endl;
    QNetworkRequest request;
    QNetworkAccessManager* man = new QNetworkAccessManager();
    request.setUrl(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=-200"));
    man->get(request);
    man=NULL ; free(man);
}

void MainWindow::on_camResetButton_clicked(){
    std::cout << "[Info] Camera robot reset." << std::endl;
    QNetworkRequest request;
    QNetworkAccessManager* man = new QNetworkAccessManager();

    request.setUrl(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094855&group=1&value=1"));
    man->get(request);

    man=NULL ; free(man);
}

void MainWindow::keyPressEvent(QKeyEvent *ev)
{
    switch(ev->key()){
    case Qt::Key_Up:
        tcpSocket->moveRobot("forward", ui->speedSlider->value());
        std::cout << "[Info] Robot go forward." << std::endl;
        break;
    case Qt::Key_Down:
        tcpSocket->moveRobot("backward", ui->speedSlider->value());
        std::cout << "[Info] Robot go backward." << std::endl;
        break;
    case Qt::Key_Left:
        tcpSocket->moveRobot("left", ui->speedSlider->value());
        std::cout << "[Info] Robot go to the left." << std::endl;
        break;
    case Qt::Key_Right:
        tcpSocket->moveRobot("right", ui->speedSlider->value());
        std::cout << "[Info] Robot go to the right." << std::endl;
        break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *ev)
{
    tcpSocket->moveRobot("stop");
    std::cout << "[Info] Stop robot." << std::endl;
}

void MainWindow::on_speedSlider_valueChanged(){
    ui->speedLCD->display(ui->speedSlider->value());
}

void MainWindow::updateSensorsValues(Sensors s){
    ui->odoL->display(s.getOdoL());
    ui->odoR->display(s.getOdoR());
    ui->speedL->display(s.getSpeedL());
    ui->speedR->display(s.getSpeedR());


}
