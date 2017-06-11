#include "gpscene.h"
#include <QDebug>

GpScene::GpScene(){
    msg=new Msg();
}

void GpScene::mousePressEvent(QGraphicsSceneMouseEvent * event){
    QPoint qp=event->scenePos().toPoint();
    msg->press(qp.x(),qp.y());
    QGraphicsScene::mousePressEvent(event);
}
void GpScene::mouseMoveEvent(QGraphicsSceneMouseEvent * event){
    QGraphicsScene::mouseMoveEvent(event);

}

