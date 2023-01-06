#include <views/RegisterWindow.h>
#include "./ui_registerwindow.h"

#include <iostream>

RegisterWindow::RegisterWindow(StageManager* stageManager, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RegisterWindow)
{
    ui->setupUi(this);
    this->stageManager = stageManager;
}

RegisterWindow::~RegisterWindow()
{
    delete ui;
}


void RegisterWindow::on_registerButton_clicked() {
    return;
}


void RegisterWindow::on_loginButton_clicked() {
    this->stageManager->setCurrentWindow(LOGIN_SCREEN);
}


void RegisterWindow::on_submitButton_clicked() {
    this->sendRegisterRequest();
}

void RegisterWindow::sendRegisterRequest() {

    QNetworkAccessManager * manager = new QNetworkAccessManager(this);
    connect(manager,SIGNAL(finished(QNetworkReply*)), this, SLOT(onfinish(QNetworkReply*)));
    connect(manager,SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));

    std::string json = "{\"email\":\"" + this->ui->emailInput->text().toStdString() + "\",\
    \"name\":\"" + this->ui->nameInput->text().toStdString() + "\"\
    ,\"surname\":\"" + this->ui->surnameInput->text().toStdString() + "\"\
    ,\"password\":\"" + this->ui->passwordInput->text().toStdString() + "\"}";


    qDebug() << QString::fromStdString(json);
    QNetworkRequest request(QUrl("http://localhost:8050/user"));
    request.setRawHeader("Content-Type", "application/json");


    manager->post(request, QByteArray::fromStdString(json));
}

void RegisterWindow::onfinish(QNetworkReply *reply) {
    if (reply->error()) {
        QByteArray bts = reply->readAll();
        QString str(bts);
        QMessageBox::information(this,"error",str,"ok");
        qDebug() << reply->errorString();
        return;
    }

    qDebug() << "finished\n";
    QString str("Please now proceed to login");
    QMessageBox::information(this,"error",str,"ok");
}

