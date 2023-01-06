#include "RequestManager.h"

RequestManager::RequestManager() {
}

RequestManager::~RequestManager() {
    if(manager)
        delete this->manager;
}

void RequestManager::managerFinished(QNetworkReply *reply) {
    if (reply->error()) {
        qDebug() << reply->errorString();
        return;
    }

    qDebug() << "finished\n";
    QString answer = reply->readAll();
    qDebug() << answer;

    delete this->manager;
}

void RequestManager::GET(std::string requestUrl) {
    manager = new QNetworkAccessManager();
    auto status = QNetworkAccessManager::connect(manager,
                                                 &QNetworkAccessManager::finished,
                                                 this,
                                                 &RequestManager::managerFinished);

    qDebug() << "Connection status:" << status;
    manager->get(QNetworkRequest(QUrl("http://localhost:8050/user")));
}

void RequestManager::POST(std::string requestUrl) {

    QHttpMultiPart http;

    QHttpPart receiptPart;
    receiptPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("contentType: application/json"));
    receiptPart.setBody("{\"email\":\"jamraa.mat@gmail.com\",\"name\":\"mateusz\",\"surname\":\"jamr\"\"password\":\"12345\"}");

    http.append(receiptPart);
    QNetworkRequest request(QUrl("http://localhost:8050/user"));

    manager->post(request, &http);
}


