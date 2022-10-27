#include "elevator.h"

Elevator::Elevator(ECS* ecs, int carNum)
    :QObject(ecs), m_carNum(carNum)
{}

std::set<int> Elevator::getDestinations() const
{
    return m_destinations;
}

void Elevator::stop()
{

}

void Elevator::emergencyStop()
{

}

void Elevator::start(char direction)
{

}

void Elevator::newFloor(int floorNum)
{

}

void Elevator::carRequest(int floorNum)
{

}


int Elevator::getCarNum() const
{
    return m_carNum;
}
