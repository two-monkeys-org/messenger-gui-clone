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

void ChatBubble::setNotified() {
    this->setStyleSheet("QPushButton {"
                        "border-color: red;"
                        "}"
                        "QPushButton:hover {"
                        "border-color: pink;"
                        "}");
    this->setText("New message");
}

void ChatBubble::setRead() {
    this->setStyleSheet("QPushButton {"
                        "border-color: blue;"
                        "}"
                        "QPushButton:hover {"
                        "border-color: pink;"
                        "}");
    this->setText(this->title);
}

void ChatBubble::mousePressEvent(QMouseEvent *event) {
    if(event->button() == Qt::RightButton) {

        QWidget* widget = new QWidget();
        QVBoxLayout* layout = new QVBoxLayout();

        QPushButton* btn = new QPushButton("DELETE CONVERSATION");
        // connect btn delete conversation
        widget->setLayout(layout);
        layout->addWidget(btn);

        widget->show();
    }
    else {
        QPushButton::mousePressEvent(event);
    }
}
