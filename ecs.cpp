#include "ecs.h"


ECS::ECS(QObject* parent, int numFloors, int numElevators)
    :QObject(parent)
{
    for(int i = 0; i < numFloors; ++i){
        m_floors.append(new Floor(this, i));
    }
    for(int i = 0; i < numElevators; ++i){
        m_elevators.append(new Elevator(this, i));
    }
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

}

void ECS::carRequest(int carNum, int floorNum)
{

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
