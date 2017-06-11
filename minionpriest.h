#ifndef MINIONPRIEST_H
#define MINIONPRIEST_H

#include <QtMath>
#include "minion.h"

class MinionPriest : public Minion
{
public:
    MinionPriest(int _type, int _side, int _no, int _level);
    virtual void attack();
};

#endif // MINIONPRIEST_H
