#include "floor.h"

Floor::Floor(ECS* ecs, int floorNum)
    :QObject(ecs), m_ecs(ecs), m_floorNum(floorNum)
{}

int Floor::getFloorNum() const
{
    return m_floorNum;
}

void Floor::elevatorRequested(char direction)
{

}
