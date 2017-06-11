#ifndef MINIONWARRIOR_H
#define MINIONWARRIOR_H

#include "minion.h"

class MinionWarrior : public Minion
{
public:
    MinionWarrior(int _type, int _side, int _no, int _level);
    virtual void attack();
};

#endif // MINIONWARRIOR_H
