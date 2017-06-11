#include "minionspear.h"

MinionSpear::MinionSpear(int _type, int _side, int _no, int _level):Minion(_type,_side,_no,_level)
{

}
void MinionSpear::attack(){
    attackTarget->damage(attackPower);
}
