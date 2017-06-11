#ifndef MINIONBOWMAN_H
#define MINIONBOWMAN_H

#include "minion.h"

class MinionBowman : public Minion
{
public:
    MinionBowman(int _type, int _side, int _no, int _level);
    virtual void attack();
};

#endif // MINIONBOWMAN_H
