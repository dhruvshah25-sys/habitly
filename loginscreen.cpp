#include "loginscreen.h"
#include "ui_loginscreen.h"
#include<QDebug>
loginscreen::loginscreen(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::loginscreen)
{
    ui->setupUi(this);
    ui->errorLabel1->setVisible(false);
    ui->errorLabel2->setVisible(false);
}

loginscreen::~loginscreen()
{
    delete ui;
}

void loginscreen::on_signInButton_clicked()
{
    if(ui->emailInput->text().isEmpty())
    {
        ui->errorLabel1->setVisible(true);
        ui->errorLabel1->setText("Field cannot be Empty!");
        ui->errorLabel1->setStyleSheet("color:red");
    }
    else if(ui->passwordInput->text().isEmpty())
    {
        ui->errorLabel2->setVisible(true);
        ui->errorLabel2->setText("Field cannot be Empty!");
        ui->errorLabel2->setStyleSheet("color:red");
    }
    else
    {    ui->errorLabel1->setVisible(false);
        ui->errorLabel2->setVisible(false);
        QString hashed=PasswordUtil::hash(ui->passwordInput->text());
        QSqlQuery query;
        query.prepare("SELECT id, password_hash FROM users WHERE email = ?");
        query.addBindValue(ui->emailInput->text());
        query.exec();
        if(query.next()==false)
        {
            ui->errorLabel1->setVisible(true);
            ui->errorLabel1->setText("User do not exist!");
            ui->errorLabel1->setStyleSheet("color:red");
        }
        else
        {
            int id              = query.value(0).toInt();
            QString storedHash  = query.value(1).toString();
            if(hashed==storedHash)
            {
                SessionManager::instance().setUser(id,ui->emailInput->text());
                qDebug()<<SessionManager::instance().userid();
                emit loginSuccess();
            }
            else
            {
                ui->errorLabel2->setVisible(true);
                ui->errorLabel2->setText("Incorrect Password!");
                ui->errorLabel2->setStyleSheet("color:red");
            }
        }

    }
}


void loginscreen::on_signUpButton_clicked()
{
    emit goToSignup();
}

