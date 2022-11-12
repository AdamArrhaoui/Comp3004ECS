#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ecs.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    ECS *getEcs() const;
    void setEcs(ECS *value);

private slots:

    void on_floorButton_clicked();

private:
    Ui::MainWindow *ui;
    ECS* m_ecs;
};
#endif // MAINWINDOW_H
