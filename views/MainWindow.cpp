#include "./ui_mainwindow.h"
#include <views/MainWindow.h>

#include <iostream>
#include <QStandardItemModel>

MainWindow::MainWindow(StageManager* stageManager, QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    this->httpManager = new HttpManager();

    this->mainService = new MainService(this->ui, &m_webSocket);
    this->stageManager = stageManager;

    this->initButtonConnection();
    this->initWebsocketConnection();
    this->fetchConversations();
}

MainWindow::~MainWindow() {
    delete httpManager;
}


void MainWindow::initWebsocketConnection() {
    connect(&m_webSocket, &QWebSocket::connected, this, &MainWindow::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &MainWindow::closed);
    m_webSocket.open(QUrl("ws://localhost:2137"));
}


void MainWindow::initButtonConnection() {
    QPushButton* addNewConversationButton = this->ui->AddConversation;
    QPushButton* sendMessageButton = this->ui->SendMessageButton;

    connect(addNewConversationButton, &QPushButton::clicked, this, &MainWindow::onAddConversationButtonClicked);
    connect(sendMessageButton, &QPushButton::clicked, [=]() { this->sendMessage(); });
}


void MainWindow::onConnected() {
    connect(&m_webSocket, &QWebSocket::textMessageReceived,this, &MainWindow::onTextMessageReceived);
    m_webSocket.sendTextMessage(Utils::buildWithNamespace("DISCOVERY", Utils::INFOMRATION));
}


void MainWindow::onTextMessageReceived(QString payload) {
    QJsonDocument json = QJsonDocument::fromJson(payload.toUtf8());
    QJsonObject jsonObject = json.object();
    QString messageNamespace = jsonObject.value("namespace").toString();

    if(textReceiveActionMap.find(messageNamespace) != textReceiveActionMap.end()) {
        textReceiveActionMap[messageNamespace](payload);
    }
}

void MainWindow::onAddConversationButtonClicked() {
    AddConversationModal* conf = new AddConversationModal();
    conf->show();
}


void MainWindow::fetchConversations() {
    httpManager
        ->setUrl("http://localhost:6969/chat")
        ->setMethod(HTTP_METHOD::GET)
        ->addHeader("username", ClientContext::getEmail().toUtf8())
        ->onFinish([=](QNetworkReply* reply) { MainWindow::fetchConversations(reply); } )
        ->send();
}

void MainWindow::fetchMessages() {
    if(ClientContext::getUuid() == "NULL")
        return;

    httpManager
        ->setUrl("http://localhost:6969/chat/" + ClientContext::getUuid())
        ->setMethod(HTTP_METHOD::GET)
        ->onFinish([=](QNetworkReply* reply) { MainWindow::fetchMessages(reply); } )
        ->send();
}

// TODO uzyc template dla tych dwoch funkcji
void MainWindow::rerenderConversations(QString payload) {
    for(int i=0; i < chatBubbles.size(); i++) {
        delete chatBubbles.at(i);
    }

    chatBubbles = std::vector<ChatBubble*>();

    this->fetchConversations();
}

void MainWindow::rerenderMessages() {
    for(int i=0; i < messages.size(); i++) {
        delete messages.at(i);
    }

    messages = std::vector<QLabel*>();

    this->fetchMessages();
}

QJsonDocument MainWindow::createConversation(QString title, QJsonArray listOfUsers) {

    QJsonObject conf;
    conf.insert("title", title);

    conf.insert("listOfUsers", listOfUsers);

    QJsonDocument jsonDoc;

    jsonDoc.setObject(conf);

    return jsonDoc;
}

void MainWindow::fetchConversations(QNetworkReply* reply) {

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

void MainWindow::fetchMessages(QNetworkReply* reply) {

    QByteArray bts = reply->readAll();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(bts);

    if(jsonDocument.isArray() == false) {
        qDebug() << "It is not a JSON array";
        return;
    }

    QJsonArray arrOfObjs = jsonDocument.array();

    for(int i=0; i < arrOfObjs.size(); i++) {
        QJsonObject object = arrOfObjs.at(i).toObject();
        QString from = object.value("from").toString();
        QString text = object.value("text").toString();

        this->addMessage(from, text);
    }
}

void MainWindow::addMessage(QString body) {

    QJsonObject payload = QJsonDocument::fromJson(body.toUtf8()).object();
    QString uuid = payload.value("uuid").toString();

    if(ClientContext::getUuid() != uuid) {

        QMessageBox::information(0, "new mess", "New message!", "ok");


        // todo fix
        for(auto &chat : chatBubbles) {
            if(chat->getUUID() == uuid) {
                chat->setStyleSheet("border-color: red;");
                return;
            }
        }

        return;
    }

    QString from = payload.value("from").toString();
    QString text = payload.value("text").toString();

    this->addMessage(from, text);
}

void MainWindow::addMessage(QString from, QString text) {
    QLabel* label = new QLabel();
    if(from != ClientContext::getEmail()) {
        label->setText("<strong>" + from + ":</strong> " + text.simplified());
        label->setAlignment(Qt::AlignLeft);
        label->setStyleSheet("background-color:blue;");
    } else {
      label->setText(text);
      label->setAlignment(Qt::AlignRight);
    }

    this->ui->scrollAreaMessageLayout->layout()->addWidget(label);
    messages.push_back(label);

    QTimer::singleShot(5, this, ([=] {
        ui->scrollMessageArea->verticalScrollBar()->setValue(
            ui->scrollMessageArea->verticalScrollBar()->maximum()
        );
    }));
}


void MainWindow::onBubbleClick(QString UUID) {
    if(UUID == ClientContext::getUuid()) {
        return;
    }

    ClientContext::setUuid(UUID);
    this->rerenderMessages();
}


void MainWindow::sendMessage() {
    QString text = this->ui->MessageInput->toPlainText();

    if(text.isEmpty())
        return;

    QJsonObject json;
    QJsonObject payload;
    QString from = ClientContext::getEmail();

    json.insert("namespace", "MESSAGE");
    payload.insert("from", from);
    payload.insert("text", text.simplified());
    payload.insert("uuid", ClientContext::getUuid());

    json.insert("payload", payload);

    QJsonDocument jsonDoc;

    jsonDoc.setObject(json);

    this->m_webSocket.sendTextMessage(jsonDoc.toJson());

    this->ui->MessageInput->clear();
}
