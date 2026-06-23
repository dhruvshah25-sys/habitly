#ifndef SETUPWINDOW_H
#define SETUPWINDOW_H

#include <QWidget>

namespace Ui {
class setupwindow;
}

class setupwindow : public QWidget
{
    Q_OBJECT

public:
    explicit setupwindow(QWidget *parent = nullptr);
    ~setupwindow();

private:
    Ui::setupwindow *ui;
};

#endif // SETUPWINDOW_H
