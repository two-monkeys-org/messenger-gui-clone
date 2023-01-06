#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore/QObject>
#include <QtWebSockets/QtWebSockets>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QScrollBar>
#include <QGroupBox>
#include <QCheckBox>
#include <QLineEdit>
#include <QLabel>

#include <StageManager.h>
#include <utils/ConnectivityUtils.h>
#include <utils/ClientContext.h>
#include <service/MainService.h>
#include <views/AddConversationModal.h>
#include <utils/HttpManager.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(StageManager* stageManager = nullptr, QWidget *parent = nullptr);
    ~MainWindow();

Q_SIGNALS:
    void closed();

private slots:
    void onConnected();
    void onTextMessageReceived(QString);
    void onAddConversationButtonClicked();

private:
    void initButtonConnection();
    void initWebsocketConnection();
    void fetchConversations();
    void fetchMessages();
    void sendMessage();
    void rerenderConversations(QString);
    void rerenderMessages();
    void onBubbleClick(QString);
    void fetchConversations(QNetworkReply*);
    void fetchMessages(QNetworkReply*);
    QJsonDocument createConversation(QString, QJsonArray);
    void addMessage(QString);
    void addMessage(QString, QString);

    HttpManager* httpManager;
    Ui::MainWindow *ui;
    QStandardItemModel* model;
    MainService* mainService;
    StageManager* stageManager;
    std::vector<ChatBubble*> chatBubbles;
//    std::vector<QPushButton*> messages;
    std::vector<QLabel*> messages;
    std::vector<QCheckBox*> users;

    QWebSocket m_webSocket;
    QUrl m_url;

    std::map<QString, std::function<void(QString)>> textReceiveActionMap {
        {"NEW_CONVERSATION", [=](QString payload){ this->rerenderConversations(payload); } },
//        {"DISCOVERY", [=](QString payload){ /* nothing */ } },
        {"RECEIVE_MESSAGE", [=](QString payload){ this->addMessage(payload); } },
    };
};


#endif // MAINWINDOW_H
