QT       += core gui
QT       += websockets

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

CONFIG+=c++17


SOURCES += \
    entity/ChatBubble.cpp \
    utils/ClientContext.cpp \
    CustomException.cpp \
    utils/HttpManager.cpp \
    views/AddConversationModal.cpp \
    views/LoginWindow.cpp \
    views/RegisterWindow.cpp \
    StageManager.cpp \
    entity/ActiveUser.cpp \
    main.cpp \
    views/MainWindow.cpp \
    service/MainService.cpp \
    utils/ConnectivityUtils.cpp \
    utils/RequestManager.cpp


HEADERS += \
    entity/ChatBubble.h \
    utils/ClientContext.h \
    CustomException.h \
    utils/HttpManager.h \
    views/AddConversationModal.h \
    views/LoginWindow.h \
    views/RegisterWindow.h \
    StageManager.h \
    entity/ActiveUser.h \
    views/MainWindow.h \
    service/MainService.h \
    utils/ConnectivityUtils.h \
    utils/RequestManager.h


FORMS += \
    views/loginwindow.ui \
    views/mainwindow.ui \
    views/registerwindow.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
