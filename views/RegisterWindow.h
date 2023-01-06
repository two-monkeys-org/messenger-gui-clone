#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QMainWindow>
#include <StageManager.h>
#include <utils/RequestManager.h>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class RegisterWindow; }
QT_END_NAMESPACE

class RegisterWindow : public QMainWindow
{
    Q_OBJECT

public:
    RegisterWindow(StageManager* stageManager, QWidget *parent = nullptr);
    ~RegisterWindow();

private slots:
    void on_registerButton_clicked();
    void on_loginButton_clicked();
    void on_submitButton_clicked();
    void onfinish(QNetworkReply *rep);

private:
    Ui::RegisterWindow *ui;
    StageManager* stageManager;
    void onRegisterButtonClicked();
    void onLoginButtonClicked();
    void sendRegisterRequest();

};
#endif // REGISTERWINDOW_H
