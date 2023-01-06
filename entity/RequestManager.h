#ifndef REQUESTMANAGER_H
#define REQUESTMANAGER_H


#include <QtCore>
#include <QObject>
#include <QString>
#include <QtNetwork/QTcpSocket>
#include <QIODevice>
#include <QByteArray>
#include <QMap>
#include <QMetaObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QUrl>

class RequestManager : public QObject
{
    Q_OBJECT
public:
    explicit RequestManager(QObject *parent = nullptr);
    ~RequestManager();


    void GET(const QString hostName);
    void POST(const QString hostName, QMap<QString, QString> data);
    void PUT(const QString hostName, QMap<QString, QString> data);
    void HEAD(const QString hostName);


signals:
    void sendSignal(QString data);

public slots:
    void handleFinished(QNetworkReply *networkReply);
    void onError(QNetworkReply::NetworkError code);
    void readyRead();

private:
    QUrlQuery constructPostData(QMap<QString, QString> data);
    QNetworkRequest constructNetworkRequest(const QString hostName, QMap<QString, QString> headers);
    QNetworkAccessManager *networkManager;
    QMap<QString, QString> headers;
};

#endif // REQUESTMANAGER_H
