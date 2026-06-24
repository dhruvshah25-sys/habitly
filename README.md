# Habitly

A production-grade desktop habit tracker built with C++ and Qt 6.

## Features
- Secure signup and login with SHA-256 password hashing
- SQLite local database — your data never leaves your machine
- Add, track, and delete daily habits
- Streak tracking based on completion history
- Clean architecture: MVC + Repository pattern

## Tech stack
- C++17
- Qt 6 (Widgets, SQL)
- SQLite via Qt SQL module
- CMake build system

## Architecture
The app follows a layered architecture:
- **Views** — Qt Widget screens (Login, Signup, Dashboard)
- **Repositories** — Database access layer (UserRepository, HabitRepository)
- **Services** — SessionManager (singleton), DatabaseManager
- **Utils** — PasswordUtil (SHA-256 hashing)

## Building
1. Install Qt 6 from qt.io
2. Open `CMakeLists.txt` in Qt Creator
3. Build and run

## Status
Active development — first-year engineering project.
