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
    void pressDestButton(int floorNum);

public slots:
    void unpressDestButton(int floorNum);

signals:
    void destButtonPressed(int floorNum);
    void closeDoorButtonPressed();
    void openDoorButtonHeld();
    void openDoorButtonReleased();
    void emergencyButtonPressed();


private:
    Elevator* m_elevator;
    QSet<int> m_pressedDestButtons;
    bool m_openDoorHeld;
};

#endif // BUTTONPANEL_H
