#include "mainwindow.h"

#include <QApplication>
#include "ecs.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    ECS test_ecs(&w, 3, 1);
    w.show();
    test_ecs.getElevators()[0]->getButtonPanel()->pressDestButton(1);
    return a.exec();
}
