#ifndef STAGEMANAGER_H
#define STAGEMANAGER_H

#include <QMainWindow>

enum Stage {
    LOGIN_SCREEN,
    REGISTER_SCREEN,
    MAIN_SCREEN
};

class StageManager
{
public:
    StageManager();
    void setCurrentWindow(Stage stage);
    QMainWindow* getCurrentWidnow();
private:
    QMainWindow* currentWindow;
};

#endif // STAGEMANAGER_H
