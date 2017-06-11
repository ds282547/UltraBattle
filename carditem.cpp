#include "carditem.h"

CardItem::CardItem(TypeData *_td,int _id,int _level,int _no)
{
    td = _td;
    id = _id;
    no = _no;
    level = _level;
    rect = QRectF(0,0,100,130);

    effPress.setColor(QColor::fromRgb(255,255,255));
    effPress.setBlurRadius(35);
    effPress.setOffset(0,0);
    effPress.setEnabled(false);
    setGraphicsEffect(&effPress);
}
QRectF CardItem::boundingRect() const {
    return rect;
}
void CardItem::paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawPixmap(0,0,100,130,td->cardPixmaps->at(id));

    painter->setFont(QFont("URW Gothic L",15,100));
    painter->setPen(QColor::fromRgb(0, 0, 0));
    painter->drawText(QRectF(52,102,48,28),Qt::AlignCenter,QString("LV:%1").arg(level));
    painter->setPen(QColor::fromRgb(255, 234, 0));
    painter->drawText(QRectF(50,100,50,30),Qt::AlignCenter,QString("LV:%1").arg(level));

}
void CardItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
    msg.pressCard(no);
    Select();
}
void CardItem::UnSelect(){
    effPress.setEnabled(false);
}
void CardItem::Select(){
    effPress.setEnabled(true);
}
