#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

#include <QDialog>
#include"PasswordUtil.h"
#include"SessionManager.h"
#include<QSqlQuery>
#include<QSqlError>
namespace Ui {
class loginscreen;
}

class loginscreen : public QDialog
{
    Q_OBJECT

public:
    explicit loginscreen(QWidget *parent = nullptr);
    ~loginscreen();
signals:
    void loginSuccess();
    void goToSignup();
private slots:

    void on_signInButton_clicked();

    void on_signUpButton_clicked();

private:
    Ui::loginscreen *ui;
};

#endif // LOGINSCREEN_H
