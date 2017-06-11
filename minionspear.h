#ifndef MINIONSPEAR_H
#define MINIONSPEAR_H

#include "minion.h"

class MinionSpear : public Minion
{
public:
    MinionSpear(int _type, int _side, int _no, int _level);
    virtual void attack();
};

#endif // MINIONSPEAR_H
