
#ifndef HABIT_ENGINE_H
#define HABIT_ENGINE_H

#include <QString>
#include <QDate>
#include <map>
#include <vector>

struct Habit
{
    int id;
    QString name;
    int streak;
    int total;
    QDate lastDone;
};

class HabitEngine
{
public:
    HabitEngine();

    bool login(QString email, QString pass);
    bool signup(QString email, QString pass);

    void loadHabits();
    void saveHabits();

    void addHabit(QString name);
    void deleteHabit(int id);
    void markDone(int id);

    std::map<int,Habit> habits;
    int currentUserId;

private:
    QString dataPath();
};

#endif
