#ifndef CARD_H
#define CARD_H
#include <QGraphicsItem>
#include <QPainter>
#include <QBrush>
#include <QRectF>
#include <QColor>
#include <QBitmap>
#include <QImage>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsSceneMouseEvent>
#include <QStyleOptionGraphicsItem>
#include <QStyle>

#include "pixmaps.h"
#include "msg.h"
#include "miniondata.h"
class Card :public QGraphicsItem
{
public:
    Card(Pixmaps *_pix, bool _selectable,QVector<MinionData*>& _minionDatas);
    QRectF rect;
    QGraphicsDropShadowEffect* effPress;

    int margin;
    int index;
    int indexInCardDeck;

    int no;

    int roundRadius;
    bool selected;
    bool selectAble;
    Msg* msg;
    Pixmaps* pixmaps;
    QRectF boundingRect() const;

    QRectF manaRect;
    QRectF manaTextRect;
    int manaNeed;

    QRectF levelRect;
    QRectF levelTextRect;
    int level;

    QVector<MinionData*>* minionDatas;

    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void setSelectable(bool s);
    void setSel(bool sel);
    void setIndex(int i);
};

#endif // CARD_H
