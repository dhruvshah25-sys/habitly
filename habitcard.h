#ifndef HABITCARD_H
#define HABITCARD_H
#include<QWidget>
#include <qlabel.h>
#include <qpushbutton.h>
#include"habitrepository.h"
class HabitCard:public QWidget
{
    Q_OBJECT
private:
    int m_habitId;
    QString m_name;
    int m_streak;
    QLabel* nameLabel;
    QLabel* streakLabel;
    QPushButton* doneButton;
    QPushButton* deleteButton;


public:
    HabitCard(int habitId, const QString&name, int streak, QWidget* parent=nullptr);
signals:
    void deleteRequested(int habitId);
private slots:
    void onDoneClicked();
    void onDeleteClicked();

};

#endif // HABITCARD_H
