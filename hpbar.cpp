#include "hpbar.h"
#include <QDebug>

HpBar::HpBar(int _side):width(GD::HP_BAR_W),height(GD::HP_BAR_H),border(GD::HP_BAR_BORDER)
{
    side = _side;
    if(side==0){
        color = GD::HP_RED_SIDE_COLOR;
    }else if(side==1){
        color = GD::HP_BLUE_SIDE_COLOR;
    }
    rect.setX(-width/2);
    rect.setY(0);
    rect.setWidth(width);
    rect.setHeight(height);
    ratio = 1.0;
}
QRectF HpBar::boundingRect() const{
    return rect;
}
void HpBar::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget )
{
    painter->fillRect(rect,QBrush(QColor(0,0,0)));
    painter->fillRect(rect.adjusted(0,0,(ratio-1)*width,0),QBrush(color));
}
HpBar::~HpBar(){
    qDebug() << "HPBar Die";
}
void HpBar::resize(int w,int h){
    width = w;
    height = h;
    rect.setX(-width/2);
    rect.setY(0);
    rect.setWidth(width);
    rect.setHeight(height);
}
