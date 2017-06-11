#ifndef MINIONKING_H
#define MINIONKING_H

#include "minion.h"

class MinionKing : public Minion
{
public:
    MinionKing(int _type, int _side, int _no, int _level);
    virtual void attack();
};

#endif // MINIONKING_H
