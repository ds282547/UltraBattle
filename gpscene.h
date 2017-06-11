#ifndef GPSCENE_H
#define GPSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QPoint>
#include "msg.h"
class GpScene : public QGraphicsScene
{
public:
    GpScene();
    Msg* msg;
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
};

#endif // GPSCENE_H
