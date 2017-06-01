#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tcpSocket = new TcpConnection();

    //Signals :
    connect(ui->forwardButton, SIGNAL(released()), this, SLOT (releaseButton()));
    connect(ui->backwardButton, SIGNAL(released()), this, SLOT (releaseButton()));
    connect(ui->leftButton, SIGNAL(released()), this, SLOT (releaseButton()));
    connect(ui->rightButton, SIGNAL(released()), this, SLOT (releaseButton()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete tcpSocket;
}

void MainWindow::on_connectButton_clicked(){
    bool ok;
    if(ui->connectButton->text() == "Connect"){
        tcpSocket->connectTo(ui->host_edit->text(), ui->port_edit->text().toInt(&ok, 10));
        ui->connectButton->setText("Disconnect");
    } else{
        tcpSocket->disconnect();
        ui->connectButton->setText("Connect");
    }
}

void MainWindow::on_forwardButton_pressed(){
    tcpSocket->moveRobot("forward");
    std::cout << "[Info] Robot go forward." << std::endl;
}

void MainWindow::on_backwardButton_pressed(){
    tcpSocket->moveRobot("backward");
    std::cout << "[Info] Robot go backward." << std::endl;
}

void MainWindow::on_leftButton_pressed(){
    tcpSocket->moveRobot("left");
    std::cout << "[Info] Robot go to the left." << std::endl;
}

void MainWindow::on_rightButton_pressed(){
    tcpSocket->moveRobot("right");
    std::cout << "[Info] Robot go to the right." << std::endl;
}
void MainWindow::releaseButton(){
    tcpSocket->moveRobot("stop");
    std::cout << "[Info] Stop robot." << std::endl;
}

void MainWindow::keyPressEvent(QKeyEvent *ev)
{
    switch(ev->key()){
    case Qt::Key_Up:
        tcpSocket->moveRobot("forward");
        std::cout << "[Info] Robot go forward." << std::endl;
        break;
    case Qt::Key_Down:
        tcpSocket->moveRobot("backward");
        std::cout << "[Info] Robot go backward." << std::endl;
        break;
    case Qt::Key_Left:
        tcpSocket->moveRobot("left");
        std::cout << "[Info] Robot go to the left." << std::endl;
        break;
    case Qt::Key_Right:
        tcpSocket->moveRobot("right");
        std::cout << "[Info] Robot go to the right." << std::endl;
        break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *ev)
{
    tcpSocket->moveRobot("stop");
    std::cout << "[Info] Stop robot." << std::endl;
}

