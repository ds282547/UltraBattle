#include "manabar.h"

ManaBar::ManaBar(int side)
{
    //Circle
    grad1 = QRadialGradient(0,0,23,-8,-8,1);
    grad1.setColorAt(1,QColor::fromRgb(255,255,255));
    grad1.setColorAt(0.8,QColor::fromRgb(255,111,253));
    grad1.setColorAt(0.5,QColor::fromRgb(255,111,254));
    grad1.setColorAt(0.3,QColor::fromRgb(255,150,255));
    grad1.setColorAt(0,QColor::fromRgb(255,255,255));
    pen1.setStyle(Qt::NoPen);
    pen2.setColor(QColor::fromRgb(255,255,255));
    pen3.setColor(QColor::fromRgb(0,0,0,150));

    brush1 = QBrush(grad1);

    brush2 = QBrush(QColor::fromRgb(255,255,255));
    brush3 = QBrush(QColor::fromRgb(0,0,0,100));

    //Bar
    //Range by which side
    if(side==0){
        barRect = QRectF(10,-16,470,21);

    }else{
        barRect = QRectF(10,-5,470,21);
    }
    //Gray-Bar
    grad2 = QLinearGradient(barRect.topLeft(),barRect.bottomLeft());
    grad2.setColorAt(1,QColor::fromRgb(200,200,200));
    grad2.setColorAt(0,QColor::fromRgb(100,100,100));
    brush4 = QBrush(grad2);
    pen4.setColor(QColor::fromRgb(250,250,250,150));
    pen4.setStyle(Qt::DashLine);
    pen4.setWidth(2);

    //Mana-Bar
    grad3 = QLinearGradient(barRect.topLeft(),barRect.bottomLeft());
    grad3.setColorAt(0,QColor::fromRgb(243,158,242));
    grad3.setColorAt(0.5,QColor::fromRgb(241,103,239));
    grad3.setColorAt(1,QColor::fromRgb(173,38,171));
    brush5 = QBrush(grad3);
    //Some Ranges
    rect = QRectF(-21,-21,500,42);
    textRect = QRectF(-21,-21,42,42);

    font = QFont("Arial",18,75);
    mana = 5.7;
    manaMax = 10;



}
QRectF ManaBar::boundingRect() const{
    return rect;
}
void ManaBar::paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget){
    //draw BAR
    painter->setPen(pen1);
    painter->setBrush(brush4);
    painter->drawRect(barRect);
    //draw Mana-Bar
    painter->setBrush(brush5);
    painter->drawRect(barRect.adjusted(0,0,barRect.width()*(mana/manaMax-1),0));

    painter->setPen(pen4);
    painter->setBrush(Qt::NoBrush);
    QPointF dp=QPointF(barRect.width()/10,0);
    QPointF p1=barRect.topLeft();
    QPointF p2=barRect.bottomLeft()+dp;

    for(int i=0;i<10;i++){
        painter->drawRect(QRectF(p1,p2));
        p1+=dp;
        p2+=dp;
    }


    //draw Circle
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(brush1);
    painter->setPen(pen1);
    painter->drawEllipse(QPoint(0,0),21,21);

    painter->setBrush(brush2);
    painter->setFont(font);
    painter->setPen(pen3);
    painter->drawText(textRect.adjusted(1,1,1,1),Qt::AlignCenter,QString("%1").arg((int)mana));
    painter->setPen(pen2);
    painter->drawText(textRect.adjusted(-1,-1,-1,-1),Qt::AlignCenter,QString("%1").arg((int)mana));



}
void ManaBar::setMana(qreal m){
    mana = m;
    update();
}
