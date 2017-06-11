#include "tower.h"
#include <QDebug>

Tower::Tower(int _side, int _no)
{
    side = _side;
    no = _no;
    QString url=":/pic/tower/%1Tower%2.png";
    if(side==0){
        setPixmap(QPixmap(url.arg("R").arg(no)));

    }else{
        setPixmap(QPixmap(url.arg("B").arg(no)));
    }
    if(no==1){
        setOffset(-30.5,-42);
        hp = hpmax = GD::FRONT_TOWER_HPMAX;
    }else{
        setOffset(-40.6,-67);
        hp = hpmax = GD::BACK_TOWER_HPMAX;
    }

}
void  Tower::attachHpBar(HpBar* hpb){
    hpbar = hpb;
    if(no==1){
        hpb->setPos(x()-2,y()-57);
    }else{
        hpb->setPos(x()-2,y()-85);
    }
}

qreal Tower::getHPRatio(){
    return (qreal)hp/hpmax;
}
void Tower::damage(int n){
    if(hp-n>0){
        hp-=n;
        hpbar->ratio=getHPRatio();
        hpbar->update();
    }else if(hp!=0){
        hp=0;
        hpbar->ratio=getHPRatio();
        hpbar->update();
        dead = true;
    }
}
