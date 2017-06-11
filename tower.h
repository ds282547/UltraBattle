#ifndef TOWER_H
#define TOWER_H

#include <QPixmap>
#include "gameconstdata.h"
#include "hpbar.h"
#include "attackableobject.h"

class Tower : public AttackableObject
{
public:
    Tower(int _side, int _no);
    int hp;
    int hpmax;
    int side;
    int no;
    qreal getHPRatio();
    HpBar* hpbar;
    void attachHpBar(HpBar* hpb);
    void damage(int n);
};

#endif // TOWER_H
