#include <QDebug>

#include "elevator.h"

int Elevator::s_topFloor;

Elevator::Elevator(ECS* ecs, int carNum)
    :QObject(ecs)
    ,m_ecs(ecs)
    ,m_carNum(carNum)
    ,m_door(new Door(this))
    ,m_display(new Display(this))
    ,m_floorSensor(new FloorSensor(this))
    ,m_buttonPanel(new ButtonPanel(this))
{
    connect(m_ecs, SIGNAL(updated()), this, SLOT(update()));
    connect(m_floorSensor, SIGNAL(floorDetected(int)), this, SLOT(newFloor(int)));
    connect(m_buttonPanel, SIGNAL(destButtonPressed(int)), this, SLOT(addDestination(int)));
    connect(m_buttonPanel, SIGNAL(emergencyButtonPressed()), this, SLOT(emergencyStop()));
}

void Elevator::update()
{
    // Elevator Update Loop
    if(m_moveState == Moving){
        qDebug() << "I'm moving! Direction:" << m_currDirection << "Floor:" << m_currFloor << "Progress:" << m_currentProgress;
        // Move elevator
        m_currentProgress += s_moveSpeed;
        // Elevator reached new floor
        if(m_currentProgress >= 1.0){
            m_currentProgress = 0;
            if(m_currDirection == 'd'){
                m_floorSensor->detectFloor(m_currFloor - 1);
            } else {
                m_floorSensor->detectFloor(m_currFloor + 1);
            }
        }
    } else if (m_moveState == Stopped){
        // Wait for door to be closed
        if(m_door->state() == Door::Closed){
            start(m_currDirection);
        }
    } else if (m_moveState == Idle){
        // Wait for door to be closed
        if(m_door->state() == Door::Closed){
            //qDebug() << "Elevator" << m_carNum << "is idle and ready";
        }
    }
    emit updated();
}

void Elevator::start(char direction)
{
    if(direction == 'd'){
        if(m_currFloor == 0){
            qWarning() << "Cannot move down, already on bottom floor!";
            return;
        }
    } else if (direction == 'u'){
        if(m_currFloor == s_topFloor){
            qWarning() << "Cannot move up, already at top floor!";
            return;
        }
    } else {
        qWarning() << "Unrecognised direction '" << direction << "'. Only 'u' and 'd' are supported";
        return;
    }
    m_currDirection = direction;
    m_moveState = Moving;
}

void Elevator::stop()
{
    if(m_destinations.size() == 0){
        // No more destinations, idle the elevator
        m_moveState = Idle;
        m_currDirection = 'i';
    } else {
        // There are still more destinations, temporarily stop the elevator
        m_moveState = Stopped;
        // If elevator stopped at top/bottom floor, reverse currDirection
        if(m_currFloor == s_topFloor){
            m_currDirection = 'd';
        } else if(m_currFloor == 0){
            m_currDirection = 'u';
        }
    }
    m_door->open();
}

void Elevator::emergencyStop()
{

}

void Elevator::newFloor(int floorNum)
{
    m_currFloor = floorNum;
    emit newFloorReached(m_carNum, floorNum);
    // If floor is in m_destinations, remove floor from m_destinations then stop elevator
    auto it = m_destinations.find(floorNum);
    if(it != m_destinations.end()){
        m_destinations.erase(it);
        stop();
        return;
    }
    if(floorNum == s_topFloor or floorNum == 0){
        stop();
    }
}

void Elevator::addDestination(int floorNum)
{
    if(floorNum == m_currFloor){
        stop();
        return;
    }
    // If a new destination button for the elevator is pressed,
    // add the floor to elevators set of destinations and emit carRequest signal
    if(m_destinations.count(floorNum) == 0){
        m_destinations.insert(floorNum);
        emit carRequest(m_carNum, floorNum);
    }
}

char Elevator::getCurrDirection() const
{
    return m_currDirection;
}

void Elevator::openDoor() const
{
    // Check if elevator is stopped
    if(m_moveState == Idle or m_moveState == Stopped){
        m_door->open();
    }
}

int Elevator::getCarNum() const
{
    return m_carNum;
}

bool Elevator::isIdleAndReady() const
{
    return (m_moveState == Idle and m_door->state() == Door::Closed);
}

std::set<int> Elevator::getDestinations() const
{
    return m_destinations;
}


int Elevator::getCurrFloor() const
{
    return m_currFloor;
}


Elevator::MovementState Elevator::getMoveState() const
{
    return m_moveState;
}

void Elevator::setTopFloor(int topFloor)
{
    s_topFloor = topFloor;
    ButtonPanel::setTopFloor(topFloor);
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


