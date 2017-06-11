#include "minionbowman.h"

MinionBowman::MinionBowman(int _type, int _side, int _no,int _level):Minion(_type,_side,_no,_level)
{

}
void MinionBowman::attack(){
    attackTarget->damage(attackPower);
}
