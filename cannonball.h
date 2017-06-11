#ifndef CANNONBALL_H
#define CANNONBALL_H
#include <QGraphicsPixmapItem>
#include "minion.h"

class CannonBall : public QGraphicsPixmapItem
{
public:
    CannonBall(int _side);
    qreal z;
    bool reach;
    int side;
    void setZ(qreal _z);
    QPointF targetPos;
    void timeTicker();
};

#endif // CANNONBALL_H
