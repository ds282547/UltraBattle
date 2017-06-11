#ifndef MINIONKNIGHT_H
#define MINIONKNIGHT_H

#include "minion.h"

class MinionKnight : public Minion
{
public:
    MinionKnight(int _type, int _side, int _no, int _level);
    virtual void attack();
};

#endif // MINIONKNIGHT_H
