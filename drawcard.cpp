#include "drawcard.h"

DrawCard::DrawCard():QGraphicsPixmapItem(QPixmap(":/gameui/drawcard/card.png"))
{
    setOpacity(0.01);
    msg = new Msg();
}
DrawCard::~DrawCard(){
    delete msg;
}
void DrawCard::setY(qreal y){
    if(y<=-200){
        setOpacity(0.01);
    }else if(y>350){
        setOpacity(1);
    }else{
        setOpacity((y+200)/550);
    }
    QGraphicsPixmapItem::setY(y);
}
void DrawCard::mousePressEvent(QGraphicsSceneMouseEvent * event){
    msg->press(event->scenePos().x(),event->scenePos().y());
}
void DrawCard::mouseMoveEvent(QGraphicsSceneMouseEvent * event){
    msg->move(event->scenePos().x(),event->scenePos().y());
}
void DrawCard::mouseReleaseEvent(QGraphicsSceneMouseEvent * event){
    msg->release(event->scenePos().x(),event->scenePos().y());
}
