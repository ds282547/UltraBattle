#include "minionsiegeram.h"

MinionSiegeram::MinionSiegeram(int _type, int _side, int _no, int _level):Minion(_type,_side,_no,_level)
{
    if(_side==0){
        setRotation(180);
    }
}
void MinionSiegeram::attack(){
    attackTarget->damage(attackPower);
}
