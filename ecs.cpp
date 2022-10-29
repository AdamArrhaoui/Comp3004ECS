#include <QDebug>

#include "ecs.h"


ECS::ECS(QObject* parent, int numFloors, int numElevators)
    :QObject(parent)
{
    for(int i = 0; i < numFloors; ++i){
        m_floors.append(new Floor(this, i));
    }
    // set top floors for elevator and button panel
    Elevator::setTopFloor(numFloors - 1);

    for(int i = 0; i < numElevators; ++i){
        Elevator* newElevator = new Elevator(this, i);
        m_elevators.append(newElevator);
        // Connect Elevator signals to ECS slots
        connect(newElevator, &Elevator::newFloorReached, this, &ECS::carReachedFloor);
        connect(newElevator, &Elevator::carRequest, this, &ECS::carRequest);
    }
    qDebug() << "Created ECS for building with" << numFloors << "floors and" << numElevators << "elevators.";
}

QVector<QPair<int, char> > ECS::getFloorRequests() const
{
    return m_floorRequests;
}

QVector<QPair<int, int> > ECS::getCarRequests() const
{
    return m_carRequests;
}

AllocationStrategy *ECS::getAllocationStrategy() const
{
    return m_allocationStrategy;
}

void ECS::setAllocationStrategy(AllocationStrategy *value)
{
    m_allocationStrategy = value;
}

void ECS::floorRequest(int floorNum, char direction)
{
}

void ECS::carReachedFloor(int carNum, int floorNum)
{
    qDebug() << "Car number" << carNum << "has arrived at floor number" << floorNum;
}

void ECS::carRequest(int carNum, int floorNum)
{
    qDebug() << "Car number" << carNum << "has requested floor number" << floorNum;
}

void ECS::readyToMove(int carNum)
{

}

QVector<Floor *> ECS::getFloors() const
{
    return m_floors;
}

QVector<Elevator *> ECS::getElevators() const
{
    return m_elevators;
}
