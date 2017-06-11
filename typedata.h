#ifndef TYPEDATA_H
#define TYPEDATA_H

#include <QString>

#include <QVector>
#include <QDebug>
#include "pixmaps.h"
#include "miniondata.h"

class TypeData
{
public:
    TypeData(QString nm,int id);
    QString name;
    MinionData* newMinion(QString nm);
    MinionData* getMinion(int i);
    Pixmaps* cardPixmaps;
    //for debug
    void showAllMinionData();
    int typeId;
    void loadCardPixmaps(QString prefix,QString postfix,int from,int to,int zeros);
    QVector<MinionData*> minionDatas;
private:

};

#endif // TYPEDATA_H
