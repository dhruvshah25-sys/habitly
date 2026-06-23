#include "databasemanager.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>

bool DatabaseManager::initialize() {

    // QStandardPaths::AppDataLocation gives you the right folder
    // on every operating system automatically.
    // On your Windows machine this resolves to:
    // C:\Users\ACER NITRO\AppData\Roaming\HabitTracker\
    //
    // We store our .db file there — not on the Desktop, not next
    // to the .exe. This is how every real app stores user data.

    QString dataDir = QStandardPaths::writableLocation(
        QStandardPaths::AppDataLocation
        );

    // mkpath creates the folder if it doesn't exist yet.
    // If it already exists, nothing happens. Safe to call every time.
    QDir().mkpath(dataDir);

    QString dbPath = dataDir + "/habittracker.db";

    // Print the path so you can see it in the Application Output panel.
    // Later we will remove this debug line.
    qDebug() << "[DB] Opening database at:" << dbPath;

    // "QSQLITE" is the driver name. Qt ships this driver built-in —
    // no extra installation needed. We just tell Qt to use it.
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        // If this fails, something is seriously wrong with
        // the file system. Print the error so we can debug it.
        qDebug() << "[DB] ERROR — cannot open database:"
                 << db.lastError().text();
        return false;
    }

    qDebug() << "[DB] Opened successfully.";
    return createTables();
}

bool DatabaseManager::createTables() {
    QSqlQuery query;

    // ── TABLE: users ────────────────────────────────────────────
    // One row per registered user.
    // password_hash: we NEVER store the actual password.
    //   We store a hash — a one-way scrambled version.
    //   Even if someone reads the .db file, they cannot recover passwords.
    // created_at: SQLite fills this automatically with the current time.

    bool ok = query.exec(
        "CREATE TABLE IF NOT EXISTS users ("
        "  id            INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  name          TEXT    NOT NULL,"
        "  email         TEXT    UNIQUE NOT NULL,"
        "  password_hash TEXT    NOT NULL,"
        "  created_at    TEXT    DEFAULT (datetime('now'))"
        ")"
        );
    if (!ok) {
        qDebug() << "[DB] ERROR creating users table:"
                 << query.lastError().text();
        return false;
    }

    // ── TABLE: habits ────────────────────────────────────────────
    // One row per habit per user.
    // user_id links back to the users table —
    //   "this habit belongs to the user with this id."
    // FOREIGN KEY enforces this link.
    //   You cannot create a habit with a user_id that doesn't exist.

    ok = query.exec(
        "CREATE TABLE IF NOT EXISTS habits ("
        "  id          INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  user_id     INTEGER NOT NULL,"
        "  name        TEXT    NOT NULL,"
        "  frequency   TEXT    DEFAULT 'daily',"
        "  color       TEXT    DEFAULT '#4CAF50',"
        "  created_at  TEXT    DEFAULT (datetime('now')),"
        "  FOREIGN KEY (user_id) REFERENCES users(id)"
        ")"
        );
    if (!ok) {
        qDebug() << "[DB] ERROR creating habits table:"
                 << query.lastError().text();
        return false;
    }

    // ── TABLE: habit_logs ────────────────────────────────────────
    // One row every time a habit is marked as done.
    // This is how we calculate streaks and history.
    // Example: if habit_id=3 has rows for 5 consecutive days,
    //   that is a 5-day streak.

    ok = query.exec(
        "CREATE TABLE IF NOT EXISTS habit_logs ("
        "  id         INTEGER PRIMARY KEY AUTOINCREMENT,"
        "  habit_id   INTEGER NOT NULL,"
        "  logged_at  TEXT    DEFAULT (datetime('now')),"
        "  FOREIGN KEY (habit_id) REFERENCES habits(id)"
        ")"
        );
    if (!ok) {
        qDebug() << "[DB] ERROR creating habit_logs table:"
                 << query.lastError().text();
        return false;
    }

    qDebug() << "[DB] All tables ready.";
    return true;
}
