#ifndef MINIONSIEGERAM_H
#define MINIONSIEGERAM_H

#include "minion.h"

class MinionSiegeram : public Minion
{
public:
    MinionSiegeram(int _type, int _side, int _no, int _level);
    virtual void attack();
};


#endif // MINIONSIEGERAM_H
