#ifndef MINIONARCHMAGE_H
#define MINIONARCHMAGE_H

#include "minion.h"

class MinionArchMage : public Minion
{
public:
    MinionArchMage(int _type, int _side, int _no, int _level);
    virtual void attack();
};

#endif // MINIONARCHMAGE_H
