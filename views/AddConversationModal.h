#ifndef ADDCONVERSATIONMODAL_H
#define ADDCONVERSATIONMODAL_H

#include <functional>

#include <QObject>
#include <QWidget>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QByteArray>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <utils/ClientContext.h>
#include <QCheckBox>
#include <QPushButton>

#include <utils/HttpManager.h>

class AddConversationModal : public QGroupBox
{
    Q_OBJECT
public:
    AddConversationModal();
    ~AddConversationModal();

private slots:
    void onfinish(QNetworkReply*);

private:
    QVBoxLayout *vbox;
    QLineEdit *conversationNameInput;
    QLabel* label;
    HttpManager* httpManager;

    std::vector<QCheckBox*> users;

    void onOkPress();
    void initWidget(QNetworkReply*);
};

#endif // ADDCONVERSATIONMODAL_H
