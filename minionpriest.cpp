#include "minionpriest.h"

MinionPriest::MinionPriest(int _type, int _side, int _no, int _level):Minion(_type,_side,_no,_level)
{

}
void MinionPriest::attack(){
    qreal dist;
    QPointF d;
    foreach(Minion *m,*teammates){
        d = m->pos()-pos();
        dist = qSqrt(QPointF::dotProduct(d,d));
        if(dist<attackRange){
            m->heal(attackPower);
        }
    }
}
