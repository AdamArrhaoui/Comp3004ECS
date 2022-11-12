#ifndef FLOOR_H
#define FLOOR_H

#include <QObject>

#include "ecs.h"
#include "floorbuttons.h"


class ECS;
class FloorButtons;

class Floor : public QObject
{
    Q_OBJECT
public:
    Floor(ECS* ecs, int floorNum);
    void serviced(char direction);
    void inform(char direction);
    int getFloorNum() const;

public slots:
    void elevatorRequested(char direction);
private:
    ECS* m_ecs;
    FloorButtons* m_floorButtons;
    int m_floorNum;
};

#endif // FLOOR_H
