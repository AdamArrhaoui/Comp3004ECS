#ifndef BUTTONPANEL_H
#define BUTTONPANEL_H

#include <QObject>
#include <QSet>

#include "elevator.h"


class Elevator;

class ButtonPanel : public QObject
{
    Q_OBJECT
public:
    ButtonPanel(Elevator* elevator);
public slots:
    void pressDestButton(int floorNum);
    void unpressDestButton(int floorNum);
    void pressCloseDoor();
    void holdOpenDoor();
    void releaseOpenDoor();
    void pressEmergencyButton();
private:
    Elevator* m_elevator;
    QSet<int> m_pressedDestButtons;
    bool m_openDoorHeld;
};

#endif // BUTTONPANEL_H
