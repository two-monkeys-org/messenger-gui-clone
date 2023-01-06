#ifndef MAINSERVICE_H
#define MAINSERVICE_H

#include <QWebSocket>
#include <QNetworkReply>
#include <QtWebSockets/QtWebSockets>
#include <QMessageBox>
#include <QStandardItem>
#include <QPushButton>

#include <vector>

#include <ui_mainwindow.h>
#include <entity/ChatBubble.h>
#include <utils/ConnectivityUtils.h>


class MainService {

public:
    MainService(Ui::MainWindow *ui, QWebSocket* m_webSocket);
    ~MainService();

    void sendTextMessage();
    void processMessage(QString message);
    void processHttpResponse(QNetworkReply*);
    void sendMessage();
    void fetchConversations();
    QJsonDocument createConversation(QString title);

private:
    Ui::MainWindow *ui;
    QWebSocket* m_webSocket;

    std::vector<ChatBubble*> chatBubbles;

    void createConversations(QNetworkReply*);
    void onBubbleClick(QString UUID);
};

#endif // MAINSERVICE_H
