#ifndef MANABAR_H
#define MANABAR_H

#include <QGraphicsItem>
#include <QPainter>
#include <QBrush>
#include <QRectF>
#include <QColor>
#include <QBitmap>
#include <QImage>
#include <QGraphicsDropShadowEffect>
#include <QStyleOptionGraphicsItem>
#include <QStyle>
#include <QFont>

#include <QRadialGradient>
#include <QLinearGradient>
class ManaBar : public QGraphicsItem
{
public:
    ManaBar(int side);
    QRectF boundingRect() const;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setMana(qreal m);
private:
    qreal mana;
    qreal manaMax;
    QPen pen1;
    QPen pen2;
    QPen pen3;
    QPen pen4;
    QBrush brush1;
    QBrush brush2;
    QBrush brush3;
    QBrush brush4;
    QBrush brush5;
    QRadialGradient grad1;
    QLinearGradient grad2;
    QLinearGradient grad3;
    QRectF rect;
    QRectF textRect;
    QRectF barRect;
    QFont font;

};

#endif // MANABAR_H
