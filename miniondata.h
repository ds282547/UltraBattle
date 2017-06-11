#ifndef MINIONDATA_H
#define MINIONDATA_H

#include "actionframes.h"
#include <QString>
#include <QVector>

class MinionData
{
public:
    MinionData(QString _name,int id);
    QString name;

    int typeId;
    int offsetX;
    int offsetY;
    int hpMax;
    int radius;
    qreal speed;
    int high;
    int attackRange;
    int attackPower;
    int manaNeed;
    QString help;
    //Cascaded
    MinionData& setHpMax(int hp);
    MinionData& setAttackRange(int rng);
    MinionData& setAttackPower(int pw);
    MinionData& setRadius(int rad);
    MinionData& setHigh(int hi);
    MinionData& setSpeed(qreal sp);
    MinionData& setOffsetXY(int x,int y);
    MinionData& setManaNeed(int mana);
    QVector<ActionFrames*> frames;

    ActionFrames* newAction(QString _aname, int len);
    ActionFrames* getAction(int i);
};

#endif // MINIONDATA_H
