#ifndef DRAWCARD_H
#define DRAWCARD_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include "msg.h"
#include <QDebug>

class DrawCard : public QGraphicsPixmapItem
{
public:
    DrawCard();
    ~DrawCard();
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
    void setY(qreal y);
    Msg *msg;
};

#endif // DRAWCARD_H
