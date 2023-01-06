#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QNetworkReply>
#include <QMessageBox>

#include <StageManager.h>
#include <utils/ClientContext.h>
#include <views/MainWindow.h>


QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindow; }
QT_END_NAMESPACE

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    LoginWindow(StageManager* stageManager, QWidget *parent = nullptr);
    ~LoginWindow();


private slots:
    void on_registerButton_clicked();
    void on_loginButton_clicked();
    void on_submitButton_clicked();
    void onfinish(QNetworkReply *reply);

private:
    Ui::LoginWindow *ui;
    StageManager* stageManager;
    void onRegisterButtonClicked();
    void onLoginButtonClicked();
    void sendLoginRequest();
};

#endif // LOGINWINDOW_H
