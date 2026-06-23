#include "habit_engine.h"
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>
#include <QDir>

HabitEngine::HabitEngine()
{
    currentUserId = -1;
}

QString HabitEngine::dataPath()
{
    QString dir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(dir);
    return dir;
}
bool HabitEngine::signup(QString email, QString pass)
{
    QFile f(dataPath()+"/users.txt");
    if(!f.open(QIODevice::Append | QIODevice::Text)) return false;

    QTextStream out(&f);
    int uid = QDateTime::currentSecsSinceEpoch(); // simple unique id
    out << uid << "|" << email << "|" << pass << "\n";
    f.close();

    return true;
}

bool HabitEngine::login(QString email, QString pass)
{
    QFile f(dataPath()+"/users.txt");
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text)) return false;

    QTextStream in(&f);

    while(!in.atEnd())
    {
        QString line = in.readLine();
        auto parts = line.split("|");
        if(parts.size()<3) continue;

        if(parts[1]==email && parts[2]==pass)
        {
            currentUserId = parts[0].toInt();
            loadHabits();
            return true;
        }
    }

    return false;
}
void HabitEngine::loadHabits()
{
    habits.clear();

    QFile f(dataPath()+"/"+QString::number(currentUserId)+"_habits.txt");
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QTextStream in(&f);

    while(!in.atEnd())
    {
        QString line = in.readLine();
        auto p = line.split("|");
        if(p.size()<5) continue;

        Habit h;
        h.id = p[0].toInt();
        h.name = p[1];
        h.streak = p[2].toInt();
        h.total = p[3].toInt();
        h.lastDone = QDate::fromString(p[4],"yyyy-MM-dd");

        habits[h.id] = h;
    }
}

void HabitEngine::saveHabits()
{
    QFile f(dataPath()+"/"+QString::number(currentUserId)+"_habits.txt");

    if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qWarning("Failed to open habits file for writing");
        return;
    }

    QTextStream out(&f);

    for(auto &p : habits)
    {
        auto &h = p.second;

        out << h.id << "|"
            << h.name << "|"
            << h.streak << "|"
            << h.total << "|"
            << h.lastDone.toString("yyyy-MM-dd")
            << "\n";
    }

    f.close();
}

void HabitEngine::addHabit(QString name)
{
    int id = habits.empty() ? 1 : habits.rbegin()->first + 1;

    Habit h;
    h.id=id;
    h.name=name;
    h.streak=0;
    h.total=0;
    h.lastDone=QDate();

    habits[id]=h;
    saveHabits();
}

void HabitEngine::deleteHabit(int id)
{
    habits.erase(id);
    saveHabits();
}

void HabitEngine::markDone(int id)
{
    if(!habits.count(id)) return;

    Habit &h = habits[id];

    QDate today = QDate::currentDate();

    if(h.lastDone.daysTo(today)==1)
        h.streak++;
    else if(h.lastDone!=today)
        h.streak=1;

    if(h.lastDone!=today)
        h.total++;

    h.lastDone=today;

    saveHabits();
}
