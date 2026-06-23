#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H


// opening the .db file and making sure all tables exist.
// Nothing else touches the database directly — they go through


class DatabaseManager {
public:
    // Call this once in main() before showing any screen.
    // Returns true if DB opened and tables are ready.
    // Returns false if something went wrong (we will handle that in main).
    static bool initialize();

private:
    // Called internally by initialize().
    // Runs CREATE TABLE IF NOT EXISTS for every table.
    static bool createTables();
};

#endif
