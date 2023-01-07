#ifndef CHATBUBBLE_H
#define CHATBUBBLE_H

#include <QObject>
#include <QPushButton>
#include <QMouseEvent>
#include <QFrame>
#include <QVBoxLayout>

#include <functional>


class ChatBubble: public QPushButton
{
public:
    ChatBubble();
    ChatBubble(QString);
    ChatBubble* setUUID(QString s) { this->UUID = s; return this; };
    QString getUUID() { return this->UUID; };
    void setNotified();
    void setRead();

private:
    QString title;
    QString UUID;
    void setConfig();

private slots:
    void mousePressEvent(QMouseEvent*);
};

#endif // CHATBUBBLE_H
