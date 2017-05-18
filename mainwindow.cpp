#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tcpSocket = new TcpConnection();
    connect(ui->connect_button, SIGNAL(clicked(bool)), this, SLOT(connectButtonClick()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete tcpSocket;
}

void MainWindow::connectButtonClick(){

    if(ui->connect_button->text() == "Connect"){
        bool ok;
        if(!tcpSocket->connect(ui->host_edit->text(), ui->port_edit->text().toInt(&ok, 10)))
        {
            std::cout << "[Error] Timeout request : connection to the host could not be established." << std::endl;
        }
        else
        {
            ui->connect_button->setText("Disconnect");
            std::cout << "[Successfull] Connection established." << std::endl;
        }
    }
    else{
        tcpSocket->disconnect();
        ui->connect_button->setText("Connect");
        std::cout << "[Successfull] Disconnect from host." << std::endl;
    }
}
