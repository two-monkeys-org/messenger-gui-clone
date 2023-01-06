#ifndef CHATBUBBLE_H
#define CHATBUBBLE_H

#include <QObject>
#include <QPushButton>
#include <functional>


class ChatBubble: public QPushButton
{
public:
    ChatBubble();
    ChatBubble(QString title);
    ChatBubble* setUUID(QString s) { this->UUID = s; return this; };
    QString getUUID() { return this->UUID; };

private:
    QString title;
    QString UUID;
    void setConfig();
};

#endif // CHATBUBBLE_H
