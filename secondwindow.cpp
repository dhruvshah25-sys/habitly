#include "secondwindow.h"
#include "ui_secondwindow.h"
#include "habit_engine.h"

SecondWindow::SecondWindow(QDialog *parent)
    : QDialog(parent)
    , ui(new Ui::SecondWindow)
{
    ui->setupUi(this);
    loadHabits();

}
void SecondWindow::setHabitData(const Habit &h) {
    ui->label->setText("👋<b> Hello " + h.name+"</b>");

}

void SecondWindow::loadHabits()
{   QLayoutItem* item;
    while ((item = ui->habitsLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
    QVector<QPair<int,QString>>v;
    v=HabitRepository::getHabits(SessionManager::instance().userid());
    for(auto it:v)
    {   QLabel *habitLabel=new QLabel(this);
        habitLabel->setText(it.second);
        habitLabel->setStyleSheet("font-size: 16px; padding: 5px;");
        ui->habitsLayout->addWidget(habitLabel);
    }

}
SecondWindow::~SecondWindow()
{
    delete ui;
}

void SecondWindow::on_lineEdit_editingFinished()
{
    HabitRepository::addHabit(SessionManager::instance().userid(),ui->lineEdit->text());
    loadHabits();
}










