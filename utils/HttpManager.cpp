#include "HttpManager.h"

HttpManager::HttpManager()
{
    manager = new QNetworkAccessManager(0);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onfinish(QNetworkReply*)));
}


HttpManager::~HttpManager()
{
    connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));
}


HttpManager* HttpManager::addHeader(QString name, QString content) {
    HttpHeader header(name, content);
    this->headers.push_back(header);

    return this;
}


HttpManager* HttpManager::onFinish(std::function<void(QNetworkReply*)> func) {
    this->onFinishFunction = func;
    return this;
}


void HttpManager::onfinish(QNetworkReply* reply) {
    if (reply->error()) {
        QByteArray bts = reply->readAll();
        QString str(bts);
        QMessageBox::information(0, "error", str, "ok");
        qDebug() << reply->errorString();
        return;
    }

    this->onFinishFunction(reply);
    this->headers.clear();
}

HttpManager* HttpManager::setBody(QJsonDocument obj) {
    this->body = obj;
    return this;
}


void HttpManager::send() {
    switch(this->method) {
        case HTTP_METHOD::DELETE:
            this->del();
            break;
        case HTTP_METHOD::GET:
            this->get();
            break;
        case HTTP_METHOD::POST:
            this->post();
            break;
        default:
            qDebug() << "Error!";
            break;
    }
}


void HttpManager::del() {

}


void HttpManager::get() {
    QNetworkRequest request(this->url);

    for (auto &header : this->headers) {
        (&request)->setRawHeader(header.getName().toUtf8(), header.getContent().toUtf8());
    }

    this->manager->get(request);
}


void HttpManager::post() {
    QNetworkRequest request(this->url);

    for (auto &header : this->headers) {
        (&request)->setRawHeader(header.getName().toUtf8(), header.getContent().toUtf8());
    }

    this->manager->post(request, this->body.toJson());
}
