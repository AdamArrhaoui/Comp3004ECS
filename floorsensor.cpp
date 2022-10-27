#include "floorsensor.h"

FloorSensor::FloorSensor(Elevator* elevator)
    :QObject(elevator), m_elevator(elevator)
{}

void FloorSensor::detectFloor(int floorNum)
{
    emit floorDetected(floorNum);
}
