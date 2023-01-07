#include "AddConversationModal.h"

AddConversationModal::AddConversationModal() {
    this->httpManager = new HttpManager();

    this->httpManager
            ->setUrl("http://localhost:8050/user")
            ->setMethod(HTTP_METHOD::GET)
            ->onFinish([this](QNetworkReply* reply) { this->initWidget(reply); })
            ->send();

}

AddConversationModal::~AddConversationModal() {
    delete httpManager;
    delete this->vbox;
    delete this->label;
    delete this->conversationNameInput;
//    delete users;
}

QJsonDocument createConversation(QString title, QJsonArray listOfUsers) {

    QJsonObject conf;
    conf.insert("title", title);

    conf.insert("listOfUsers", listOfUsers);

    QJsonDocument jsonDoc;

    jsonDoc.setObject(conf);

    return jsonDoc;
}

void AddConversationModal::onOkPress() {
    QNetworkAccessManager * manager = new QNetworkAccessManager(this);
    connect(manager,SIGNAL(finished(QNetworkReply*)), this, SLOT(onfinish(QNetworkReply*)));
    connect(manager,SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));

    QJsonArray listOfUsers;

    QJsonObject loggedInUserData;
    loggedInUserData.insert("email", ClientContext::getEmail());
    listOfUsers.push_back(loggedInUserData);

    for(int i=0; i < users.size(); i++) {

        if(users.at(i)->isChecked()) {
            QJsonObject tmp;
            QString userEmail = users.at(i)->text();

            tmp.insert("email", userEmail);

            listOfUsers.push_back(tmp);
        }
    }

    QJsonDocument obj = createConversation(conversationNameInput->text(), listOfUsers);

    httpManager
            ->setUrl("http://localhost:6969/chat")
            ->setMethod(HTTP_METHOD::POST)
            ->addHeader("Content-Type", "application/json")
            ->setBody(obj)
            ->onFinish([=](QNetworkReply* reply) { this->onfinish(reply); })
            ->send();
}

void AddConversationModal::onfinish(QNetworkReply* reply) {
    this->close();
    this->deleteLater();
}

void AddConversationModal::initWidget(QNetworkReply* reply) {
    this->vbox = new QVBoxLayout();
    this->label = new QLabel("Insert name and pick users!");
    this->conversationNameInput = new QLineEdit();
    QPushButton* okButton = new QPushButton("OK");
    connect(okButton, &QPushButton::clicked, [=]() {
        this->onOkPress();
    });

    vbox->addWidget(label);
    vbox->addWidget(conversationNameInput);

    QByteArray bts = reply->readAll();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(bts);
    QJsonArray arrOfUsers = jsonDocument.array();

    for(int i=0; i < arrOfUsers.size(); i++) {
        QString email = arrOfUsers.at(i).toObject().value("email").toString();

        if(email == ClientContext::getEmail()) {
            continue;
        }

        QCheckBox* userCheckBox = new QCheckBox(email);

        this->users.push_back(userCheckBox);
        vbox->addWidget(userCheckBox);
    }

    vbox->addWidget(okButton);
    vbox->addStretch(1);
    this->setLayout(vbox);
}
