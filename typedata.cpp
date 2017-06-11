#include "typedata.h"

TypeData::TypeData(QString nm,int id)
{
    name = nm;
    typeId = id;
}
MinionData* TypeData::newMinion(QString nm){
    minionDatas.append(new MinionData(nm,typeId));
    return minionDatas.last();
}

MinionData* TypeData::getMinion(int i){
    return minionDatas.at(i);

}
void TypeData::showAllMinionData(){
    QVector<MinionData*>::iterator i;
    for(i = minionDatas.begin();i != minionDatas.end();i++){
        qDebug() << ((*i)->name) << "\tHP:" << ((*i)->hpMax);

    }
}
void TypeData::loadCardPixmaps(QString prefix,QString postfix,int from,int to,int zeros){
    cardPixmaps = new Pixmaps(prefix,postfix);
    cardPixmaps->getPixmapsWithIndex(from,to,zeros);
}
