#ifndef ALLOCATIONSTRATEGY_H
#define ALLOCATIONSTRATEGY_H

#include <QObject>
#include "ecs.h"


class ECS;

class AllocationStrategy : QObject
{
    Q_OBJECT
public:
    AllocationStrategy(QObject* parent = 0);
    virtual void makeDecision(ECS &ecs, int floorNum, int carNum) = 0;
};

#endif // ALLOCATIONSTRATEGY_H
