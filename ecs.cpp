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

void ECS::update()
{
    emit updated();
}

QSet<QPair<int, char> > ECS::getFloorRequests() const
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
    // check if there's already an elevator on the floor and it's idle or going in same direction
    foreach (Elevator* elevator, m_elevators) {
        if (elevator->getCurrFloor() == floorNum
                and (elevator->getCurrDirection() == direction
                     or elevator->getCurrDirection() == 'i')){
            elevator->stop();
            return;
        }
    }
    // check if all elevators are idle, if so, make first elevator move to target floor
    QVector<Elevator *> idleElevators = getIdleElevators();
    if (idleElevators.size() == m_elevators.size()){
        Elevator* target = idleElevators[0];
        if(target->getCurrFloor() > floorNum){
            target->start('d');
        } else {
            target->start('u');
        }
    }

    // Add the floor request to list
    m_floorRequests.insert(qMakePair(floorNum, direction));
}

void ECS::carReachedFloor(int carNum, int floorNum)
{
    qDebug() << "Car number" << carNum << "has arrived at floor number" << floorNum;
}

void ECS::carRequest(int carNum, int floorNum)
{
    qDebug() << "Car number" << carNum << "has requested floor number" << floorNum;
    Elevator* targetCar = m_elevators[carNum];
    if(targetCar->getDestinations().size() == 1 and targetCar->getMoveState() == Elevator::Idle){
        if(floorNum > targetCar->getCurrFloor()){
            targetCar->start('u');
            qDebug() << "Moving car number" << carNum <<  "up!";
        } else {
            targetCar->start('d');
            qDebug() << "Moving car number" << carNum <<  "down!";
        }
    }
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

QVector<Elevator *> ECS::getIdleElevators() const
{
    QVector<Elevator *> idleElevators;
    foreach (Elevator* elevator, m_elevators){
        if(elevator->isIdleAndReady()){
            idleElevators.append(elevator);
        }
    }
    return idleElevators;
}
