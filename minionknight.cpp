#include "minionknight.h"

MinionKnight::MinionKnight(int _type, int _side, int _no, int _level):Minion(_type,_side,_no,_level)
{

}
void MinionKnight::attack(){
    attackTarget->damage(attackPower);
}
