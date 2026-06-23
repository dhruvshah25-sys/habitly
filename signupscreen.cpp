#include "signupscreen.h"
#include "ui_signupscreen.h"
#include "passwordutil.h"    // ← NEW
#include <QSqlQuery>         // ← NEW
#include <QSqlError>         // ← NEW
#include <QDebug>            // ← NEW
#include <QMessageBox>       // ← NEW

signupscreen::signupscreen(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::signupscreen)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: white");
    ui->passerrorlabel->setVisible(false);
    ui->matcherrorlabel->setVisible(false);
    ui->emailerrorlabel->setVisible(false);
}

signupscreen::~signupscreen()
{
    delete ui;
}

int count[3];
int check;
int a1 = 0;

void signupscreen::on_lineEdit_2_editingFinished()
{
    // Your existing password validation — keeping it exactly as-is.
    QString checkpass = ui->lineEdit_2->text();
    for (int i = 0; i < checkpass.size() ; i++) {
        if (checkpass.at(i).unicode() >= 65 && checkpass.at(i).unicode() <= 90) count[0]++;
        else if (checkpass.at(i).unicode() >= 97 && checkpass.at(i).unicode() <= 122) count[1]++;
        else if (checkpass.at(i).unicode() >= 33 && checkpass.at(i).unicode() <= 38) count[2]++;
    }
    if (count[0] >= 1 && count[1] >= 1 && count[2] >= 1) {
        a1 = 1; check++;
        ui->passerrorlabel->setVisible(false);
    } else {
        ui->passerrorlabel->setStyleSheet("color:red");
        ui->passerrorlabel->setVisible(true);
    }
    count[0] = 0; count[1] = 0; count[2] = 0;
}

void signupscreen::on_confirmpass_editingFinished()
{
    // Your existing match check — keeping it exactly as-is.
    if (a1 == 1) {
        if (ui->lineEdit_2->text() == ui->confirmpass->text()) {
            check++;
            ui->matcherrorlabel->setVisible(false);
        } else {
            ui->matcherrorlabel->setStyleSheet("color:red");
            ui->matcherrorlabel->setVisible(true);
        }
    }
}

void signupscreen::on_lineEdit_editingFinished()
{
    check++;
}

void signupscreen::on_pushButton_2_clicked()
{
    // Your existing check: only proceed if all 3 validations passed.
    if (check != 3) return;

    // ── NEW: Save user to database ───────────────────────────────

    QString email    = ui->lineEdit->text().trimmed();
    QString password = ui->lineEdit_2->text();

    // Hash the password. We NEVER store plain text.
    QString hashed = PasswordUtil::hash(password);

    // Build the SQL INSERT using prepared statements.
    // The ? placeholders are filled by addBindValue().
    // This protects against SQL injection — if a user types
    // "'; DROP TABLE users;--" as their email, the ? treats it
    // as a literal string, not SQL code.
    QSqlQuery query;
    query.prepare(
        "INSERT INTO users (name, email, password_hash) "
        "VALUES (?, ?, ?)"
        );
    query.addBindValue(email);   // using email as name for now
    query.addBindValue(email);
    query.addBindValue(hashed);

    if (!query.exec()) {
        // The most likely cause: email already registered (UNIQUE constraint).
        QString err = query.lastError().text();
        qDebug() << "[Signup] DB error:" << err;

        if (err.contains("UNIQUE")) {
            ui->emailerrorlabel->setText("Email already registered.");
            ui->emailerrorlabel->setStyleSheet("color:red");
            ui->emailerrorlabel->setVisible(true);
        } else {
            QMessageBox::critical(this, "Error", "Could not save user: " + err);
        }
        return;
    }

    qDebug() << "[Signup] User saved successfully. ID:"
             << query.lastInsertId().toInt();
    int newid=query.lastInsertId().toInt();
    SessionManager::instance().setUser(newid,email);
    // ── Only emit signal after successful DB save ─────────────────

    emit openmainwindow();
}

