#include "minionking.h"

MinionKing::MinionKing(int _type, int _side, int _no, int _level):Minion(_type,_side,_no,_level)
{

}
void MinionKing::attack(){
    attackTarget->damage(attackPower);
}
