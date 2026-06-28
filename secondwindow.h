#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H
#include<QObject>
#include "habit_engine.h"
#include <QDialog>
#include"habitrepository.h"
#include"SessionManager.h"
#include"habitcard.h"
namespace Ui {
class SecondWindow;
}

class SecondWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SecondWindow(QDialog *parent = nullptr);
    ~SecondWindow();
public slots:
void setHabitData(const Habit &h);
private slots:



    void on_lineEdit_editingFinished();



private:
    void loadHabits();
    Ui::SecondWindow *ui;

};

#endif // SECONDWINDOW_H
