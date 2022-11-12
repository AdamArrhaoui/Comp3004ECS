#include "mainwindow.h"

#include <QApplication>
#include <QTimer>
#include "ecs.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    ECS test_ecs(&w, 5, 1);
    w.setEcs(&test_ecs);
    w.show();
    // Create and start ECS update loop timer
    QTimer updateLoopTimer(&test_ecs);
    QObject::connect(&updateLoopTimer, &QTimer::timeout, &test_ecs, &ECS::update);
    updateLoopTimer.start(1000);
    return a.exec();
}
