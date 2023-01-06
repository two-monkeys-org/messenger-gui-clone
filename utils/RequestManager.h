#ifndef REQUESTMANAGER_H
#define REQUESTMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QtNetwork/qnetworkreply.h>
#include <QHttpPart>


class RequestManager: public QObject
{
    Q_OBJECT
public:
    RequestManager();
    ~RequestManager();
    void GET(std::string requestUrl);
    void POST(std::string requestUrl);

private slots:
    void managerFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager* manager;
};

#endif // REQUESTMANAGER_H
