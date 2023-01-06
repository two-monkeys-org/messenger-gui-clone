#include "StageManager.h"
#include "CustomException.h"
#include "views/LoginWindow.h"
#include "views/RegisterWindow.h"
#include "views/MainWindow.h"

StageManager::StageManager()
{

}

QMainWindow* StageManager::getCurrentWidnow() {
    return this->currentWindow;
}

void StageManager::setCurrentWindow(Stage stage) {
    this->currentWindow->deleteLater();

    switch(stage) {
        case LOGIN_SCREEN:
            this->currentWindow = new LoginWindow(this);
            break;
        case REGISTER_SCREEN:
            this->currentWindow = new RegisterWindow(this);
            break;
        case MAIN_SCREEN:
            this->currentWindow = new MainWindow(this);
            break;
        default:
            throw NoAvailableStageException("There is no given stage available");
            break;
    }

    this->currentWindow->show();
}
