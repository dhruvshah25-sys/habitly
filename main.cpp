#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTimer>
#include "secondwindow.h"
#include "signupscreen.h"
#include "databasemanager.h"
#include "SessionManager.h"
#include"loginscreen.h"
// ← NEW: include our manager

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // ← NEW: These two lines tell Qt what folder name to use
    // when QStandardPaths builds the AppData path.
    // "Habitly" means your .db lives at:
    // C:\Users\ACER NITRO\AppData\Roaming\Habitly\habittracker.db
    a.setApplicationName("Habitly");
    a.setOrganizationName("DhruvShah");

    // ← NEW: Initialize the database BEFORE showing any UI.
    // If this fails, we stop immediately rather than crash later
    // with a confusing error deep inside some repository.
    if (!DatabaseManager::initialize()) {
        qDebug() << "[FATAL] Database failed to initialize. Exiting.";
        return 1;
    }

    // Everything below is your existing code — unchanged.
    QSize targetSize(701, 601);
    QPixmap pixmap("C:/Users/ACER NITRO/OneDrive/Documents/HabitTracker/images/splash.png.png");
    QPixmap scaledImage = pixmap.scaled(targetSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QSplashScreen splash(scaledImage);
    splash.show();
    splash.showMessage("Loading modules...", Qt::AlignBottom | Qt::AlignCenter, Qt::black);
    a.processEvents();



    loginscreen s1;

    QTimer::singleShot(3000, &splash, &QWidget::close);
    QTimer::singleShot(3000, &s1, &QWidget::show);
    signupscreen s2;
    QObject::connect(&s1, &loginscreen::goToSignup,
                     [&s2]() { s2.show(); });
     MainWindow w;
    QObject::connect(&s2, &signupscreen::openmainwindow,
                      [&w]() { w.show(); });
    SecondWindow s;
    QObject::connect(&s1, &loginscreen::loginSuccess,
                     [&s]() { s.show(); });
    bool isConnected = QObject::connect(&w, &MainWindow::sender,
                                        &s, &SecondWindow::setHabitData);
    QObject::connect(&w, &MainWindow::opensecondwindow,
                     [&s]() { s.show(); });

    if (isConnected) {
        qDebug() << "Connection established!";
    } else {
        qWarning() << "Failed to connect signal and slot.";
    }

    return a.exec();
}
