#include "minionarchmage.h"

MinionArchMage::MinionArchMage(int _type, int _side, int _no,int _level):Minion(_type,_side,_no,_level)
{

}
void MinionArchMage::attack(){
    attackTarget->damage(attackPower);
}
