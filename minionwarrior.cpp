#include "minionwarrior.h"

MinionWarrior::MinionWarrior(int _type, int _side, int _no, int _level):Minion(_type,_side,_no,_level)
{

}
void MinionWarrior::attack(){
    attackTarget->damage(attackPower);
}
