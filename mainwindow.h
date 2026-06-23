#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "habit_engine.h"
#include"secondwindow.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void sender(const Habit &h);
    void opensecondwindow();
private slots:
   void on_pushButton_clicked();

    //void on_progressBar_valueChanged(int value);


   void on_pushButton_2_clicked();

   void on_lineEdit_editingFinished();

  // void on_lineEdit_editingFinished(const QString &arg1);

   //void on_errorlabel_linkActivated(const QString &link);

   private:
    Ui::MainWindow *ui;
    HabitEngine engine;

    void refreshTable();
};
#endif // MAINWINDOW_H
