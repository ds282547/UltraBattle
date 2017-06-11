#ifndef MINION_H
#define MINION_H

#include <QGraphicsPixmapItem>
#include <QGraphicsColorizeEffect>
#include <QVector>
#include <QtMath>

#include "gameconstdata.h"
#include "typedata.h"
#include "miniondata.h"
#include "actionframes.h"
#include "hpbar.h"
#include "msg.h"
#include "attackableobject.h"


class Minion : public AttackableObject
{

public:
    Minion(int _type, int _side, int _no, int _level);
    ~Minion();
    int level;
    int type; // the type of minion
    int direction; /*
                0
           (7)      (4)
        3       M       1
           (6)      (5)
                2
    */

    int side; // 0 - Red , 1 - Blue
    int currentAction;
    // 0 - walk 1 - attack 2 - death
    int currentTime;
    int hp; // HP
    int radius; // Radius
    int attackRange;
    int high; // Minion's high
    int frameIndex; // Current action's frame index
    int frameLength; // Current action's length
    int attackPower;
    qreal angle; // the angle of walking
    qreal speed; // the moving speed

    void init(QVector<TypeData *> &datas); //initialize

    MinionData *minionData; // load Data
    ActionFrames *currentActionFrames; // load Frame data
    void attachHpBar(HpBar* hpb);

    QVector<Minion*>* enemies;
    QVector<Minion*>* teammates;
    void attachEnemiesTeammates(QVector<Minion *> &_enemies,QVector<Minion *> &_team);
    QVector<AttackableObject*>* enemyTowers;
    void attachEnemyTowers(QVector<AttackableObject *> &_enemyTowers);

    QVector<qreal> eneDistance;

    void nextFrame(); // for ticker switch frame
    void timerTicker(); // for gametimer
    void move(); // move minion
    void turnAttack(); // turn to attack
    void damage(int n); // be damaged
    void heal(int i);
    void death(); // death
    void updateCurrentAction(); // get data from actionframes
    void updatePixmap(); // update frame for action

    QPointF targetPoint;
    QPointF targetPointRandOffset;
    const int no;
    HpBar* hpbar;
    Msg* deathMsg;
    AttackableObject* attackTarget; // Attack Target

    virtual void attack(); // for inheritance


private:
    int hpMax;
    void updateHpBar();
    void calcAngle();
    void calcTargetPoint();

    void hitted(); //be hitted
    void checkHitBlink(); //for time ticker
    int hitBlinkNumber; // 0 - none
    QGraphicsColorizeEffect *hitEffect;

    int closestMinion();
};

#endif // MINION_H
