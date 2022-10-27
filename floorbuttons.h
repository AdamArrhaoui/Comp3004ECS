#ifndef FLOORBUTTONS_H
#define FLOORBUTTONS_H

#include <QObject>

#include "floor.h"


class Floor;

class FloorButtons : public QObject
{
    Q_OBJECT
public:
    FloorButtons(Floor* floor);
    void press(char direction);
    void off(char direction);
private:
    Floor* m_floor;
    bool m_isUpPressed = false;
    bool m_isDownPressed = false;
};

#endif // FLOORBUTTONS_H
