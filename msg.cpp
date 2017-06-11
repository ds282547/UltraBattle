#include "msg.h"

Msg::Msg()
{

}
Msg::~Msg()
{

}
void Msg::press(int x,int y){
    emit pressed(x,y);
}
void Msg::move(int x,int y){
    emit moved(x,y);
}
void Msg::release(int x,int y){
    emit released(x,y);
}
void Msg::death(QGraphicsPixmapItem* x,int step){
    if(step==0){
        emit dead(x);
    }else{
        emit dead2(x);
    }
}
void Msg::pressCard(int no){
    emit cardPressed(no);
}
