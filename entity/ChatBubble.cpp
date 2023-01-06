#include "ChatBubble.h"

ChatBubble::ChatBubble() : QPushButton("GigaChad cpp enjoyers!") {
    this->title = "GigaChad cpp enjoyers!";
    this->setConfig();
}


ChatBubble::ChatBubble(QString title) : QPushButton(title) {
    this->title = title;
    this->setConfig();
}


void ChatBubble::setConfig() {
    this->setCursor(Qt::PointingHandCursor);
}
