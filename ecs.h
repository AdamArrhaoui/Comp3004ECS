#ifndef ECS_H
#define ECS_H

#include <QObject>
#include <QVector>
#include <QPair>

#include "floor.h"
#include "elevator.h"
#include "allocationstrategy.h"


class Floor;
class Elevator;
class AllocationStrategy;

// ECS object is a singleton to ensure only one ECS can be running at one time
class ECS : public QObject
{
    Q_OBJECT
public:
    ECS(QObject* parent = 0, int numFloors = 5, int numElevators = 2);

    QVector<Floor*> getFloors() const;
    QVector<Elevator*> getElevators() const;
    QVector<QPair<int, char> > getFloorRequests() const;
    QVector<QPair<int, int> > getCarRequests() const;

    AllocationStrategy *getAllocationStrategy() const;
    void setAllocationStrategy(AllocationStrategy *value);

public slots:
    void floorRequest(int floorNum, char direction);
    void carReachedFloor(int carNum, int floorNum);
    void carRequest(int carNum, int floorNum);
    void readyToMove(int carNum);

private:
    AllocationStrategy* m_allocationStrategy;
    QVector<Floor*> m_floors;
    QVector<Elevator*> m_elevators;
    QVector<QPair<int, char>> m_floorRequests;
    QVector<QPair<int, int>> m_carRequests;
};

#endif // ECS_H
