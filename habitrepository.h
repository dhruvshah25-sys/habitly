#ifndef HABITREPOSITORY_H
#define HABITREPOSITORY_H

#include <QString>
#include <QVector>
#include <QPair>

// No Qt, no SessionManager included here.
// This class only does database operations.
// The caller decides which userId to pass in.

class HabitRepository {
public:
    static bool addHabit(int userId, const QString& name);
    static QVector<QPair<int,QString>> getHabits(int userId);
    static bool markDone(int habitId);
    static bool deleteHabit(int habitId);
};

#endif
