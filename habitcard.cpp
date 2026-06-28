#include "habitcard.h"
#include <qboxlayout.h>

HabitCard::HabitCard(int habitId, const QString&name, int streak, QWidget* parent):QWidget(parent) {
    m_habitId=habitId;
    m_name=name;
    m_streak=streak;
    QHBoxLayout* layout=new QHBoxLayout();
    nameLabel=new QLabel(m_name,this);
    streakLabel = new QLabel("🔥 " + QString::number(m_streak), this);
    doneButton=new QPushButton("MarkDone",this);
    deleteButton= new QPushButton("DeleteHabit",this);
    layout->addWidget(nameLabel);
    layout->addWidget(streakLabel);
    layout->addWidget(doneButton);
    layout->addWidget(deleteButton);
    this->setLayout(layout);
    connect(doneButton,&QPushButton::clicked,this,&HabitCard::onDoneClicked);
    connect(deleteButton,&QPushButton::clicked,this,&HabitCard::onDeleteClicked);
}
void HabitCard::onDoneClicked() {
    HabitRepository::markDone(m_habitId);
    m_streak = HabitRepository::getStreak(m_habitId);
    streakLabel->setText("🔥 " + QString::number(m_streak));
}
void HabitCard::onDeleteClicked()
{
    emit deleteRequested(m_habitId);
}
