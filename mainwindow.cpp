#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QHeaderView>
#include<QMessageBox>
#include<QDebug>
#include"habit_engine.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: white");
    ui->errorlabel->setVisible(false);
    /*ui->HabitTable->setColumnCount(4);
    ui->HabitTable->setHorizontalHeaderLabels(
        {"ID", "Name", "Streak", "Total"}
        );

    ui->HabitTable->horizontalHeader()->setStretchLastSection(true);
    ui->HabitTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->HabitTable->setEditTriggers(QAbstractItemView::NoEditTriggers);


    engine.currentUserId = 1;  // temporary single user
    engine.loadHabits();

    refreshTable();*/
}


Habit h;

MainWindow::~MainWindow()
{
    delete ui;
}
/*void MainWindow::refreshTable()
{
    ui->HabitTable->setRowCount(0);

    int row = 0;
    for(auto &p : engine.habits)
    {
        const Habit &h = p.second;

        ui->HabitTable->insertRow(row);

        ui->HabitTable->setItem(row, 0,
                                new QTableWidgetItem(QString::number(h.id)));

        ui->HabitTable->setItem(row, 1,
new QTableWidgetItem(h.name));


        ui->HabitTable->setItem(row, 2,
                                new QTableWidgetItem(QString::number(h.streak)));

        ui->HabitTable->setItem(row, 3,
                                new QTableWidgetItem(QString::number(h.total)));

        row++;
    }
}*/





void MainWindow::on_pushButton_clicked()
{

    QMessageBox::StandardButton reply= QMessageBox::question(this, "FOCUS","Put your Blinders on Brother",QMessageBox::Yes|QMessageBox::No);
    if(reply==QMessageBox::Yes)
    {
        QApplication::quit();
    }
    else{
        qDebug()<<"No is clicked";
    }
}



int a=0;

void MainWindow::on_lineEdit_editingFinished()
{

    a=1;
    ui->errorlabel->setVisible(false);
    h.name=ui->lineEdit->text();
}




void MainWindow::on_pushButton_2_clicked()
{
    if((ui->lineEdit->text()).trimmed().isEmpty())
    {

        ui->errorlabel->setText(" field cannot be empty");
        ui->errorlabel->setVisible(true);
        ui->errorlabel->setStyleSheet("color:red");
        return;
    }
    if(a==1)
    {

        emit sender(h);
        emit opensecondwindow();
     }

}











