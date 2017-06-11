#ifndef CARDITEM_H
#define CARDITEM_H

#include <QGraphicsItem>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsSceneMouseEvent>
#include <QRectF>
#include <QFont>
#include <QColor>
#include <QPainter>
#include "typedata.h"
#include "msg.h"

class CardItem : public QGraphicsItem
{
public:
    CardItem(TypeData *_td, int _id, int _level, int _no);
    QRectF boundingRect() const;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget);
    TypeData *td;
    int id;
    int level;
    int no;
    Msg msg;
    QGraphicsDropShadowEffect effPress;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void Select();
    void UnSelect();
private:
    QRectF rect;

};

#endif // CARDITEM_H
