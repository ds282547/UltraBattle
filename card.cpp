#include "card.h"
#include <QDebug>
Card::Card(Pixmaps *_pix,bool _selectable,QVector<MinionData*>& _minionDatas)
{

    pixmaps = _pix;
    rect = QRectF(-30,-39,60,78);
    margin = 8;
    roundRadius = 5;

    minionDatas = &_minionDatas;

    index = 0; // 0~7 current

    indexInCardDeck = 0;

    level = 1;
    no = -1; // For Human Player

    effPress = new QGraphicsDropShadowEffect();
    effPress->setColor(QColor::fromRgb(255,255,0));
    effPress->setBlurRadius(35);
    effPress->setOffset(0,0);
    setGraphicsEffect(effPress);

    selected = false;
    effPress->setEnabled(selected);

    selectAble = _selectable;
    setAcceptHoverEvents(selectAble);

    manaRect = QRectF(-27,-37,15,15);
    manaTextRect = QRectF(-27,-37,15,15);
    manaNeed = 0;

    levelRect = QRectF(10,20,15,15);
    levelTextRect = QRectF(10,20,15,15);
    level = 1;

    msg = new Msg();
}
QRectF Card::boundingRect() const{
    return rect;
}
void Card::paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget){
    QColor col;
    QPixmap pic;
    QPen pen;
    pen.setStyle(Qt::NoPen);

    pic = pixmaps->at(index);
    painter->setRenderHint(QPainter::Antialiasing);

    QImage mask(250,325,QImage::Format_RGB32);
    QPainter imgPainter(&mask);
    imgPainter.setPen(pen);
    imgPainter.setBrush(QColor::fromRgb(255,255,255));
    imgPainter.drawRect(0,0,250,325);
    imgPainter.setBrush(QColor::fromRgb(0,0,0));
    imgPainter.drawRoundedRect(0,0,250,325,roundRadius*(250/60),roundRadius*(250/60));
    pic.setMask(QBitmap::fromImage(mask));
    painter->drawPixmap(rect.toRect(),pic);
    if (option->state & QStyle::State_MouseOver){
        //hover
        painter->setPen(pen);
        painter->setBrush(QColor::fromRgb(255,255,255,150));
        painter->drawRoundedRect(rect,roundRadius,roundRadius);     
    }
    //draw mana
    painter->setBrush(QColor::fromRgb(153,52,152,200));
    painter->setPen(QColor::fromRgb(255,255,255));
    painter->setFont(QFont("Arial",10));
    painter->drawEllipse(manaRect);
    painter->drawText(manaTextRect,Qt::AlignCenter,QString("%1").arg(manaNeed));
    //draw level
    painter->setBrush(QColor::fromRgb(52,152,52,200));
    painter->setPen(QColor::fromRgb(255,255,255));
    painter->setFont(QFont("Arial",10));
    painter->drawEllipse(levelRect);
    painter->drawText(levelTextRect,Qt::AlignCenter,QString("%1").arg(level));
}

void Card::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(selectAble){
        selected = true;
        effPress->setEnabled(selected);
        if(selected)
            msg->cardPressed(no);
    }
}
void Card::setSelectable(bool s){
    selectAble = s;
    setAcceptHoverEvents(selectAble);
}
void Card::setSel(bool sel){
    selected = sel;
    effPress->setEnabled(selected);
}
void Card::setIndex(int i){
    index = i;
    manaNeed = minionDatas->at(index)->manaNeed;
    update();
}
