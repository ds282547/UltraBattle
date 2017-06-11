#include "cannonball.h"

CannonBall::CannonBall(int _side)
{
    side = _side;
    setPixmap(QPixmap(":/gameui/pic/cannon.png"));
    setOffset(-10,-10);
    reach = false;
}
void CannonBall::setZ(qreal _z){
    setOffset(-10,-10-z);
}
void CannonBall::timeTicker(){
    setPos((targetPos-pos())*0.2+pos());
    QPointF d = targetPos-pos();
    if(QPointF::dotProduct(d,d)<5){
        reach = true;
    }
}
