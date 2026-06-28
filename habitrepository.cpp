#include "habitrepository.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <qdatetime.h>

bool HabitRepository::addHabit(int userId, const QString& name) {
    // Always create QSqlQuery inside the function.
    // Never globally.
    QSqlQuery query;

    // Named placeholders — clear to read with multiple values
    query.prepare(
        "INSERT INTO habits (user_id, name) "
        "VALUES (:userid, :name)"
        );
    query.bindValue(":userid", userId);
    query.bindValue(":name",   name);

    if (!query.exec()) {
        qDebug() << "[HabitRepo] addHabit failed:" << query.lastError().text();
        return false;
    }

    qDebug() << "[HabitRepo] Habit added. ID:" << query.lastInsertId().toInt();
    return true;
}

QVector<QPair<int,QString>> HabitRepository::getHabits(int userId) {
    QVector<QPair<int,QString>> habits;
    QSqlQuery query;

    // SELECT id and name for every habit belonging to this user.
    // value(0) = id (first column in SELECT)
    // value(1) = name (second column in SELECT)
    query.prepare("SELECT id, name FROM habits WHERE user_id = ?");
    query.addBindValue(userId);

    if (!query.exec()) {
        qDebug() << "[HabitRepo] getHabits failed:" << query.lastError().text();
        return habits; // return empty vector
    }

    // Move cursor through every result row
    while (query.next()) {
        int     habitId   = query.value(0).toInt();
        QString habitName = query.value(1).toString();
        habits.push_back({habitId, habitName});
    }

    qDebug() << "[HabitRepo] Loaded" << habits.size() << "habits for user" << userId;
    return habits;
}

bool HabitRepository::markDone(int habitId) {
    QSqlQuery query;

    // One new row in habit_logs = one completion event.
    // logged_at fills itself from DEFAULT (datetime('now')) in the schema.
    // We only need to provide the habit_id.
    query.prepare("INSERT INTO habit_logs (habit_id) VALUES (?)");
    query.addBindValue(habitId);

    if (!query.exec()) {
        qDebug() << "[HabitRepo] markDone failed:" << query.lastError().text();
        return false;
    }

    return true;
}

bool HabitRepository::deleteHabit(int habitId) {
    // Must delete from habit_logs FIRST because of the FOREIGN KEY.
    // habit_logs.habit_id references habits.id
    // If we delete from habits first, the database refuses
    // because habit_logs still has rows pointing to a now-deleted habit.

    QSqlQuery query;

    query.prepare("DELETE FROM habit_logs WHERE habit_id = ?");
    query.addBindValue(habitId);
    if (!query.exec()) {
        qDebug() << "[HabitRepo] deleteHabit (logs) failed:" << query.lastError().text();
        return false;
    }

    query.prepare("DELETE FROM habits WHERE id = ?");
    query.addBindValue(habitId);
    if (!query.exec()) {
        qDebug() << "[HabitRepo] deleteHabit (habit) failed:" << query.lastError().text();
        return false;
    }

    return true;
}
int HabitRepository::getStreak(int habitId) {
    QSqlQuery q;
    q.prepare(
        "SELECT date(logged_at) FROM habit_logs "
        "WHERE habit_id = ? "
        "ORDER BY logged_at DESC"
        );
    q.addBindValue(habitId);;
    q.exec();

    int streak = 0;
    QDate expected = QDate::currentDate();
    while (q.next()) {
        QDate logged = QDate::fromString(q.value(0).toString(), "yyyy-MM-dd");
        if (logged == expected) {
            streak++;
            expected = expected.addDays(-1);
        } else {
            break;
        }
    }
    return streak;
}
