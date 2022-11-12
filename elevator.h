#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <QObject>
#include <set>

#include "ecs.h"
#include "door.h"
#include "display.h"
#include "floorsensor.h"
#include "buttonpanel.h"


class ECS;
class Door;
class Display;
class FloorSensor;
class ButtonPanel;

class Elevator : public QObject
{
    Q_OBJECT
public:
    Elevator(ECS* ecs, int carNum);

    enum MovementState {Idle, Moving, Stopped};

    void openDoor() const;
    int getCarNum() const;
    bool isIdleAndReady() const;

    std::set<int> getDestinations() const;

    ButtonPanel *getButtonPanel() const;

    FloorSensor *getFloorSensor() const;

    Display *getDisplay() const;

    Door *getDoor() const;

    static void setTopFloor(int topFloor);

    MovementState getMoveState() const;

    int getCurrFloor() const;

    char getCurrDirection() const;

public slots:
    void update();
    void start(char direction);
    void stop();
    void emergencyStop();
    void newFloor(int floorNum);
    void addDestination(int floorNum);

signals:
    void updated();
    void newFloorReached(int carNum, int floorNum);
    void carRequest(int carNum, int floorNum);

private:
    ECS* m_ecs;
    Door* m_door;
    Display* m_display;
    FloorSensor* m_floorSensor;
    ButtonPanel* m_buttonPanel;
    int m_carNum;
    int m_currFloor = 0;
    float m_currentProgress = 0.0;
    static int s_topFloor;
    static constexpr float s_moveSpeed = 0.25;
    /* Elevator Directions:
     * 'i' Idle
     * 'u' Up
     * 'd' Down */
    char m_currDirection = 'i';
    MovementState m_moveState = Idle;
    std::set<int> m_destinations;
};

#endif // ELEVATOR_H
