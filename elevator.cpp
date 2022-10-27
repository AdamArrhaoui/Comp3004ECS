#include "elevator.h"

Elevator::Elevator(ECS* ecs, int carNum)
    :QObject(ecs)
    ,m_ecs(ecs)
    ,m_carNum(carNum)
    ,m_door(new Door(this))
    ,m_display(new Display(this))
    ,m_floorSensor(new FloorSensor(this))
    ,m_buttonPanel(new ButtonPanel(this))
{
    connect(m_buttonPanel, SIGNAL(destButtonPressed(int)), this, SLOT(addDestination(int)));
    connect(m_buttonPanel, SIGNAL(emergencyButtonPressed()), this, SLOT(emergencyStop()));
}

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
    emit newFloorReached(m_carNum, floorNum);
    // If floor is in m_destinations, stop elevator and remove floor from m_destinations
    auto it = m_destinations.find(floorNum);
    if(it != m_destinations.end()){
        stop();
        m_destinations.erase(it);
    }
}

void Elevator::addDestination(int floorNum)
{
    // If a new destination button for the elevator is pressed,
    // add the floor to elevators set of destinations and emit carRequest signal
    if(m_destinations.count(floorNum) == 0){
        m_destinations.insert(floorNum);
        emit carRequest(m_carNum, floorNum);
    }
}

Door *Elevator::getDoor() const
{
    return m_door;
}

Display *Elevator::getDisplay() const
{
    return m_display;
}

FloorSensor *Elevator::getFloorSensor() const
{
    return m_floorSensor;
}

ButtonPanel *Elevator::getButtonPanel() const
{
    return m_buttonPanel;
}

int Elevator::getCarNum() const
{
    return m_carNum;
}
