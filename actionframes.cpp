#include "actionframes.h"
#include <QDebug>

ActionFrames::ActionFrames(QString _name, int id, QString nName,int len)
{
    name = _name;
    typeId = id;
    minionName = nName;
    frameLength = len;
    totalTime = 0;
    actionPoint = -1; // no action point
    QString path = QString(":/pic/type%1/ani/%2/%3").arg(id).arg(nName).arg(_name);
    framePixmaps = new Pixmaps(path,".png");
    framePixmaps->getPixmapsWithIndex(0,len-1,1);
}
ActionFrames& ActionFrames::appendFrameDelay(int delay){
    frameDelay.append(delay);
    totalTime += delay;
    return (*this);
}
ActionFrames& ActionFrames::setActionPoint(int pt){
    actionPoint = pt;
}
int ActionFrames::getFrameDelay(int i){
    if(i<frameDelay.size())
        return frameDelay.at(i);
    else
        return 0;
}
