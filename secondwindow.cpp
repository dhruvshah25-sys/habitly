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
    for (const auto& it : std::as_const(v)) {
        HabitCard* card = new HabitCard(it.first, it.second,
                                        HabitRepository::getStreak(it.first),
                                        this);
        // Connect delete signal so SecondWindow knows to refresh
        connect(card, &HabitCard::deleteRequested,
                this, [this](int habitId) {
                    HabitRepository::deleteHabit(habitId);
                    loadHabits();
                });
        ui->habitsLayout->addWidget(card);  // ← actually add it to the layout
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










