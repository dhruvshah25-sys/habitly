#ifndef SIGNUPSCREEN_H
#define SIGNUPSCREEN_H
#include"habit_engine.h"
#include"SessionManager.h"
#include <QDialog>

namespace Ui {
class signupscreen;
}

class signupscreen : public QDialog
{
    Q_OBJECT

public:
    explicit signupscreen(QWidget *parent = nullptr);
    ~signupscreen();
signals:
    void openmainwindow();

private slots:


    void on_lineEdit_2_editingFinished();

    void on_confirmpass_editingFinished();

    void on_lineEdit_editingFinished();

    void on_pushButton_2_clicked();

private:
    Ui::signupscreen *ui;
};

#endif // SIGNUPSCREEN_H
