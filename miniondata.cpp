#include "miniondata.h"

MinionData::MinionData(QString _name,int id)
{
    name = _name;
    typeId = id;
}
MinionData& MinionData::setHpMax(int hp){
    hpMax = hp;
    return (*this);
}

MinionData& MinionData::setAttackRange(int rng){
    attackRange = rng;
    return (*this);
}
MinionData& MinionData::setAttackPower(int pw){
    attackPower = pw;
    return (*this);
}
MinionData& MinionData::setRadius(int rad){
    radius = rad;
    return (*this);
}
MinionData& MinionData::setHigh(int hi){
    high = hi;
    return (*this);
}
MinionData& MinionData::setSpeed(qreal sp){
    speed = sp;
    return (*this);
}
MinionData& MinionData::setManaNeed(int mana){
    manaNeed = mana;
    return (*this);
}
MinionData& MinionData::setOffsetXY(int x,int y){
    offsetX = x;
    offsetY = y;
    return (*this);
}
ActionFrames* MinionData::newAction(QString _aname,int len){
    frames.append(new ActionFrames(_aname,typeId,name,len));
    return frames.last();
}
ActionFrames* MinionData::getAction(int i){
    return frames.at(i);
}
