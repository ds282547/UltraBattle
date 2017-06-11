#include "minion.h"
#include <QDebug>

Minion::Minion(int _type, int _side, int _no, int _level):no(_no)
{
    type = _type;
    side = _side;
    level = _level;
    // death msg
    deathMsg = new Msg();
    // hit blank
    hitBlinkNumber = 0;
    hitEffect = new QGraphicsColorizeEffect();
    hitEffect->setColor(GD::HIT_BLINK_COLOR);
    hitEffect->setStrength(0);
    setGraphicsEffect(hitEffect);
}
void Minion::init(QVector<TypeData*>& datas){
    minionData = datas.at(type)->getMinion(no);
    currentAction = 0; // walk
    currentTime = 0;
    updateCurrentAction();
    updatePixmap();
    //set Offset
    setOffset(-minionData->offsetX,-minionData->offsetY);
    //set level calc
    qreal levelRatio = level;
    levelRatio = 1+levelRatio/10;
    //set hp

    hpMax = minionData->hpMax*levelRatio;
    hp = hpMax; // full hp
    //set high & radius
    radius = minionData->radius;
    high = minionData->high;
    //set speed & radous
    speed = minionData->speed;
    if(side==0){
        angle=0;
    }else if(side==1){
        angle=180;
    }
    //set attackRange
    attackRange = minionData->attackRange;
    attackPower = minionData->attackPower*levelRatio;
}
void Minion::updateCurrentAction(){

    currentActionFrames = minionData->getAction(currentAction);
    frameLength = currentActionFrames->frameLength;
    frameIndex = 0;
    currentTime = 0;
}
void Minion::nextFrame(){
    //qDebug() << "nextFrameStart";
    if(currentTime>=(currentActionFrames->getFrameDelay(frameIndex))){
        //qDebug() << "In the If 1";
        frameIndex++;
        //attack
        if(currentAction==1 && frameIndex==currentActionFrames->actionPoint){
            //qDebug() << "In the If 2";
            attack();
        }

        //death animation
        if(currentAction==2 && frameIndex==frameLength){
            //qDebug() << "In the If 3";
            deathMsg->death((QGraphicsPixmapItem*)this,1); // remove from scene
            return;
        }
        //qDebug() << "out of If";
        frameIndex%=frameLength;
        updatePixmap();
        currentTime=0;
    }
    currentTime++;
    //death blink
    /*if(currentAction==2 && frameIndex==frameLength-1){
        setOpacity(currentTime%8<4);
    }*/
    //qDebug() << "nextFrameEnd";
}
void Minion::updatePixmap(){
    setPixmap(currentActionFrames->framePixmaps->at(frameIndex));
}
void Minion::updateHpBar(){
    hpbar->setPos(x(),y()-high);
}
void Minion::attachHpBar(HpBar* hpb){
    hpbar = hpb;
    updateHpBar();
    //kill HP-Bar
}
void Minion::timerTicker(){
    //qDebug() << "minionStartTicker";
    //qDebug() << "checkHitBlink";
    checkHitBlink();
    if(currentAction!=2){
        //qDebug() << "calcAngle";
        calcAngle();

    }
    if(currentAction==0){
        //qDebug() << "move";
        move();
    }else if(currentAction==1){
    }
    //qDebug() << "nextFrame";
    nextFrame();
    //qDebug() << "minionFinishTicker";
}
void Minion::move(){
    double rad = qDegreesToRadians(angle);
    qreal _speed = speed + (qrand()%4/20) + 0.1;
    moveBy(_speed*qSin(rad),_speed*qCos(rad));
    updateHpBar();
}
void Minion::damage(int n){
    if(hp-n>0){
        hp-=n;
        hpbar->ratio=(qreal)hp/hpMax;
        hpbar->update();
        hitted();
    }else if(hp!=0){
        hp=0;
        hpbar->ratio=(qreal)hp/hpMax;
        hpbar->update();
        dead = true;
        death();
    }

}
void Minion::heal(int n){
    hp+=n;
    if(hp>hpMax)
        hp = hpMax;
    hpbar->ratio=(qreal)hp/hpMax;
    hpbar->update();
}
void Minion::death(){
    currentAction = 2;
    updateCurrentAction();
    deathMsg->death((QGraphicsPixmapItem*)this,0);
}
void Minion::hitted(){
    hitBlinkNumber=(GD::HIT_BLINK_FRAME_LENGTH+GD::HIT_BLINK_TIME);
}
void Minion::checkHitBlink(){

    if(hitBlinkNumber>0){
        hitBlinkNumber--;
        hitEffect->setStrength((qreal)hitBlinkNumber/GD::HIT_BLINK_FRAME_LENGTH);
    }
}

void Minion::calcAngle(){
    calcTargetPoint();
    QPointF d=targetPoint+targetPointRandOffset-pos();
    angle=qRadiansToDegrees(qAtan2(d.x(),d.y()));
}
void Minion::calcTargetPoint(){
    //calc Distance To Enemy Tower
    QVector<qreal> dist2Tower;
    QPointF d;
    for(int i=0;i<3;i++){
        if(enemyTowers->at(i)->dead){
            dist2Tower.append(10000);
        }else{
            d = enemyTowers->at(i)->pos()-pos();
            dist2Tower.append(qSqrt(QPointF::dotProduct(d,d)));
        }
    }
    qreal minDist = dist2Tower[0];
    int closetTower = 0;
    for(int i=1;i<3;i++){
        if(dist2Tower[i]<minDist){
            minDist = dist2Tower[i];
            closetTower = i;
        }
    }
    if(minDist<80){
        if(minDist<attackRange){
            if(currentAction!=1){
                attackTarget = enemyTowers->at(closetTower);
                turnAttack();
            }
            return;
        }
    }else{
        //check enemy in range
        if(!enemies->isEmpty()){
            int c = closestMinion();
            Minion* closest = enemies->at(c);

            if(eneDistance.at(c)<100){
                // there is enemy in range
                targetPoint = closest->pos();
                if(eneDistance.at(c)<attackRange){
                    if(currentAction!=1){
                        attackTarget = closest;
                        turnAttack();
                    }
                }else{
                    // back to walk
                    if(currentAction!=0){
                        currentAction = 0;
                        updateCurrentAction();
                    }
                }
                return;
            }
        }
    }
        // back to walk
    if(currentAction!=0){
        currentAction = 0;
        updateCurrentAction();
    }


    if(x()>GD::GROUND_W/2){
        targetPoint = GD::BRIDGE_RIGHT.center();
    }else{
        targetPoint = GD::BRIDGE_LEFT.center();
    }

    if(side==0){//R side
        if(y()<GD::BRIDGE_LEFT.top()){
            //behind bridge
            targetPoint.setY(GD::BRIDGE_LEFT.top());
        }else if(y()<GD::BRIDGE_LEFT.bottom()){
            //over bridge
            targetPoint.setY(GD::BRIDGE_LEFT.bottom());
        }else{
            //rush to tower
            if(dist2Tower[0]<dist2Tower[1]){
                if(!enemyTowers->at(0)->dead)
                    targetPoint = enemyTowers->at(0)->pos() - QPointF(0,40);
                else if(!enemyTowers->at(1)->dead)
                    targetPoint = enemyTowers->at(1)->pos() - QPointF(0,40);
                else
                    targetPoint = enemyTowers->at(2)->pos() - QPointF(0,50);
            }else{
                if(!enemyTowers->at(1)->dead)
                    targetPoint = enemyTowers->at(1)->pos() - QPointF(0,40);
                else if(!enemyTowers->at(0)->dead)
                    targetPoint = enemyTowers->at(0)->pos() - QPointF(0,40);
                else
                    targetPoint = enemyTowers->at(2)->pos() - QPointF(0,50);
            }

        }
    }else{// B side
        if(y()>GD::BRIDGE_LEFT.bottom()){
            //behind bridge
            targetPoint.setY(GD::BRIDGE_LEFT.bottom());
        }else if(y()>GD::BRIDGE_LEFT.top()){
            //over bridge
            targetPoint.setY(GD::BRIDGE_LEFT.top());
        }else{
            //rush to tower
            if(dist2Tower[0]<dist2Tower[1]){
                if(!enemyTowers->at(0)->dead)
                    targetPoint = enemyTowers->at(0)->pos() + QPointF(0,40);
                else if(!enemyTowers->at(1)->dead)
                    targetPoint = enemyTowers->at(1)->pos() + QPointF(0,40);
                else
                    targetPoint = enemyTowers->at(2)->pos() + QPointF(0,50);
            }else{
                if(!enemyTowers->at(1)->dead)
                    targetPoint = enemyTowers->at(1)->pos() + QPointF(0,40);
                else if(!enemyTowers->at(0)->dead)
                    targetPoint = enemyTowers->at(0)->pos() + QPointF(0,40);
                else
                    targetPoint = enemyTowers->at(2)->pos() + QPointF(0,50);
            }

        }
    }
}
void Minion::turnAttack(){
    currentAction = 1;
    updateCurrentAction();
}

void Minion::attachEnemiesTeammates(QVector<Minion *> &_enemies,QVector<Minion *> &_team){
    enemies = &_enemies;
    teammates = &_team;
}
void Minion::attachEnemyTowers(QVector<AttackableObject *> &_enemyTowers){
    enemyTowers = &_enemyTowers;
}
int Minion::closestMinion(){
    qreal min=eneDistance[0];
    int i,pos=0;
    for(i=1;i<eneDistance.size();i++){
        if(min>eneDistance[i]){
            min=eneDistance[i];
            pos=i;
        }
    }
    return pos;
}
void Minion::attack(){
}

Minion::~Minion(){
}
