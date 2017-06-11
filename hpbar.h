#ifndef HPBAR_H
#define HPBAR_H

#include <QGraphicsItem>
#include <QPainter>
#include <QBrush>
#include <QRectF>
#include <QColor>

#include "gameconstdata.h"
class HpBar : public QGraphicsItem
{
public:
    HpBar(int _side);
    ~HpBar();
    QRectF boundingRect() const;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget);
    int width;
    int height;
    const int border;
    void resize(int w,int h);
    qreal ratio;
    int side;

protected:
    QColor color;
    QBrush brush;
    QRectF rect;
};

#endif // HPBAR_H
