#include <views/LoginWindow.h>
#include <./ui_loginwindow.h>

#include <iostream>

LoginWindow::LoginWindow( StageManager* stageManager, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow) {

    this->stageManager = stageManager;
    ui->setupUi(this);

    if(ClientContext::getEmail().toStdString() != "Anonymous") {
        stageManager->setCurrentWindow(MAIN_SCREEN);
    }
}


LoginWindow::~LoginWindow() {
    delete ui;
}


void LoginWindow::on_registerButton_clicked() {
    this->stageManager->setCurrentWindow(REGISTER_SCREEN);
}


void LoginWindow::on_loginButton_clicked() {
    return;
}


void LoginWindow::on_submitButton_clicked() {
    this->sendLoginRequest();
}


void LoginWindow::sendLoginRequest() {
    QNetworkAccessManager * manager = new QNetworkAccessManager(this);
    connect(manager,SIGNAL(finished(QNetworkReply*)), this, SLOT(onfinish(QNetworkReply*)));
    connect(manager,SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));

    std::string json = "{\"email\":\"" + this->ui->emailInput->text().toStdString() + "\"\
    ,\"password\":\"" + this->ui->passwordInput->text().toStdString() + "\"}";


    QNetworkRequest request(QUrl("http://localhost:8050/user/validate"));
    request.setRawHeader("Content-Type", "application/json");


    manager->post(request, QByteArray::fromStdString(json));
}


void LoginWindow::onfinish(QNetworkReply *reply) {
    if (reply->error()) {
        QByteArray bts = reply->readAll();
        QString str(bts);
        QMessageBox::information(this, "error", str, "ok");
        qDebug() << reply->errorString();
        return;
    }

    ClientContext::setEmail(this->ui->emailInput->text());
    ClientContext::setPassword(this->ui->passwordInput->text());

    qDebug() << ClientContext::getEmail();
    qDebug() << ClientContext::getPassword();

    this->stageManager->setCurrentWindow(MAIN_SCREEN);
}
