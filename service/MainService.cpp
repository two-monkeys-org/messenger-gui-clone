#include "MainService.h"

MainService::MainService(Ui::MainWindow *ui, QWebSocket* m_webSocket) {
    this->ui = ui;
    this->m_webSocket = m_webSocket;
}

MainService::~MainService() {

}

void MainService::sendTextMessage() {
    m_webSocket->sendTextMessage(Utils::buildWithNamespace("DISCOVERY", Utils::INFOMRATION));
}

void MainService::processMessage(QString message) {
    qDebug() << message;
}

void MainService::processHttpResponse(QNetworkReply* reply) {
    if (reply->error()) {
        QByteArray bts = reply->readAll();
        QString str(bts);
        QMessageBox::information(0, "error", str, "ok");
        qDebug() << reply->errorString();
        return;
    }

    Utils::HTTP_TYPE type = Utils::retrieveHeader(reply, "NAMESPACE");

    qDebug() << type;

    switch(type) {
        case Utils::FETCH_CONVERSATIONS:
            this->createConversations(reply);
            break;

        case Utils::FETCH_MESSAGES:
            qDebug() << reply->readAll();
            break;

        default:
            return;
    }
}

QJsonDocument MainService::createConversation(QString title) {
    ChatBubble* chatBubble = new ChatBubble(title);
    ChatBubble::connect(chatBubble, &ChatBubble::clicked, [=]() { onBubbleClick("1231"); });

    chatBubbles.push_back(chatBubble);
    QVBoxLayout* layout =  dynamic_cast<QVBoxLayout*>(this->ui->scrollAreaWidgetContents->layout());
    layout->insertWidget(1, chatBubble);

    QJsonObject conf;
    conf.insert("title", "JsonEnojyer");

    QJsonArray listOfUsers;
    QJsonObject obj1, obj2;

    obj1.insert("email", "jamr.mat@gmail.com");
    obj2.insert("email", "jamr.aa@gmail.com");

    listOfUsers.push_back(obj1);
    listOfUsers.push_back(obj2);

    conf.insert("listOfUsers", listOfUsers);

    QJsonDocument jsonDoc;

    jsonDoc.setObject(conf);
    return jsonDoc;
}

void MainService::onBubbleClick(QString UUID) {
    ClientContext::setUuid(UUID);
    // rerender whole messages area
}

void MainService::sendMessage() {
    QString text = this->ui->MessageInput->toPlainText();

    QJsonObject json;
    QJsonObject payload;
    json.insert("namespace", "MESSAGE");
    payload.insert("from", ClientContext::getEmail());
    payload.insert("text", text);
    payload.insert("uuid", ClientContext::getUuid());

    json.insert("payload", payload);

    QJsonDocument jsonDoc;

    jsonDoc.setObject(json);

    m_webSocket->sendTextMessage(jsonDoc.toJson());
}

void MainService::fetchConversations() {
//    if(ClientContext::getUuid() == "NULL")
//        return;

//    QNetworkAccessManager * manager = new QNetworkAccessManager(0);
//    connect(manager, SIGNAL(finished(QNetworkReply*)), 0, SLOT(onfinish(QNetworkReply*)));
//    connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));

//    QNetworkRequest request(QUrl("http://localhost:6969/chat/" + ClientContext::getUuid()));
//    manager->get(request);
}

void MainService::createConversations(QNetworkReply* reply) {
    qDebug() << "Conversations fetched!\n";

    QByteArray bts = reply->readAll();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(bts);

    if(jsonDocument.isArray() == false) {
        qDebug() << "It is not a JSON array";
        return;
    }

    QJsonArray arrOfObjs = jsonDocument.array();

    for(int i=0; i < arrOfObjs.size(); i++) {
        QJsonObject object = arrOfObjs.at(i).toObject();
        QJsonValue title = object.value("title");
        QJsonValue UUID = object.value("uuid");

        ChatBubble* chatBubble = new ChatBubble(title.toString());
        ChatBubble::connect(chatBubble, &ChatBubble::clicked, [=]() { onBubbleClick(UUID.toString()); });

        chatBubbles.push_back(chatBubble);
        QVBoxLayout* layout =  dynamic_cast<QVBoxLayout*>(this->ui->scrollAreaWidgetContents->layout());
        layout->insertWidget(1, chatBubble);
    }
}
