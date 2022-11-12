#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_floorButton_clicked()
{
    int floorChoice = ui->floorSelector->value();
    emit m_ecs->getElevators()[0]->getButtonPanel()->destButtonPressed(floorChoice);
}

ECS *MainWindow::getEcs() const
{
    return m_ecs;
}

void MainWindow::setEcs(ECS *value)
{
    m_ecs = value;
}
