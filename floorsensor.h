#ifndef FLOORSENSOR_H
#define FLOORSENSOR_H

#include <QObject>

#include "elevator.h"


class Elevator;

class FloorSensor : public QObject
{
    Q_OBJECT
public:
    FloorSensor(Elevator* elevator);

public slots:
    void detectFloor(int floorNum);

signals:
    void floorDetected(int floorNum);

private:
    Elevator* m_elevator;
};

#endif // FLOORSENSOR_H
