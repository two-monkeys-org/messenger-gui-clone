#ifndef HTTPMANAGER_H
#define HTTPMANAGER_H

#include <QObject>
#include <QString>
#include <QUrl>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QWidget>
#include <QMessageBox>
#include <QJsonDocument>


namespace HTTP_METHOD {
    enum METHOD {
        POST,
        GET,
        DELETE
    };
}

class HttpHeader {
private:
    QString name;
    QString content;

public:
    HttpHeader(QString name, QString content) { this->name = name; this->content = content; };
    QString getName() { return this->name; };
    QString getContent() { return this->content; };

};

class HttpManager : public QWidget
{
    Q_OBJECT
private:
    std::function<void(QNetworkReply*)> onFinishFunction;
    QNetworkAccessManager* manager;
    std::vector<HttpHeader> headers;
    QString url;
    HTTP_METHOD::METHOD method;
    QJsonDocument body;

public:
    HttpManager();
    ~HttpManager();
    HttpManager* setUrl(QString url) { this->url = url; return this; };
    HttpManager* setMethod(HTTP_METHOD::METHOD method) { this->method = method; return this; };

    HttpManager* setBody(QJsonDocument);
    HttpManager* addHeader(QString, QString);
    HttpManager* onFinish(std::function<void(QNetworkReply*)>);

    void send();
    void post();
    void get();
    void del();

// Not working :c
//    static std::map<HTTP_METHOD::METHOD, void(*)()> actionMap {
//        {HTTP_METHOD::POST, HttpManager::* post},
//        {HTTP_METHOD::GET, HttpManager::* get},
//        {HTTP_METHOD::DELETE, HttpManager::* del},
//    };

private slots:
    void onfinish(QNetworkReply*);
};

#endif // HTTPMANAGER_H
