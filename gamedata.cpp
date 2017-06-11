#include "gamedata.h"
gamedata::gamedata(){
    TypeData* current;
    MinionData* m;
    datas.append(new TypeData("Test",0));
    current = datas.last();
    m = current->newMinion("warrior");
    m->setOffsetXY(35,71).setHpMax(700).setAttackPower(50).setAttackRange(50).setRadius(30).setHigh(65).setSpeed(1.2).setManaNeed(3);
    m->newAction("walk",4)->appendFrameDelay(5).appendFrameDelay(5).appendFrameDelay(5).appendFrameDelay(5);
    m->newAction("attack",6)->appendFrameDelay(4).appendFrameDelay(3).appendFrameDelay(3).appendFrameDelay(3).appendFrameDelay(3).appendFrameDelay(10).setActionPoint(4);
    m->newAction("death",5)->appendFrameDelay(3).appendFrameDelay(3).appendFrameDelay(3).appendFrameDelay(3).appendFrameDelay(30);
    m->help = "In an old age, who can pull up the sword, that is, the warriors";

    m = current->newMinion("spear");
    m->setOffsetXY(51.4,83.4).setHpMax(600).setAttackPower(70).setAttackRange(70).setRadius(50).setHigh(70).setSpeed(1.0).setManaNeed(4);
    m->newAction("walk",4)->appendFrameDelay(5).appendFrameDelay(5).appendFrameDelay(5).appendFrameDelay(5);
    m->newAction("attack",6)->appendFrameDelay(4).appendFrameDelay(3).appendFrameDelay(3).appendFrameDelay(3).appendFrameDelay(3).appendFrameDelay(10).setActionPoint(4);
    m->newAction("death",5)->appendFrameDelay(3).appendFrameDelay(3).appendFrameDelay(3).appendFrameDelay(3).appendFrameDelay(30);
    m->help = "Holding a spear of the spear, is the real hero on the battlefield.";

    m = current->newMinion("priest");
    m->setOffsetXY(51.4,83.4).setHpMax(500).setAttackPower(40).setAttackRange(150).setRadius(50).setHigh(70).setSpeed(0.8).setManaNeed(4);
    m->newAction("walk",4)->appendFrameDelay(5).appendFrameDelay(5).appendFrameDelay(5).appendFrameDelay(5);
    m->newAction("attack",6)->appendFrameDelay(4).appendFrameDelay(3).appendFrameDelay(3).appendFrameDelay(3).appendFrameDelay(3).appendFrameDelay(10).setActionPoint(4);
    m->newAction("death",5)->appendFrameDelay(3).appendFrameDelay(3).appendFrameDelay(3).appendFrameDelay(3).appendFrameDelay(30);
    m->help = "Healing the healing power of everything is often a necessary condition for victory.";

    m = current->newMinion("archmage");
    m->setOffsetXY(51.4,83.4).setHpMax(500).setAttackPower(50).setAttackRange(150).setRadius(50).setHigh(70).setSpeed(0.8).setManaNeed(5);
    m->newAction("walk",4)->appendFrameDelay(5).appendFrameDelay(5).appendFrameDelay(5).appendFrameDelay(5);
    m->newAction("attack",6)->appendFrameDelay(4).appendFrameDelay(3).appendFrameDelay(3).appendFrameDelay(5).appendFrameDelay(6).appendFrameDelay(10).setActionPoint(4);
    m->newAction("death",5)->appendFrameDelay(3).appendFrameDelay(3).appendFrameDelay(3).appendFrameDelay(3).appendFrameDelay(30);
    m->help = "Control the magic of snow and ice, with the power to freeze everything.";

    m = current->newMinion("bowman");
    m->setOffsetXY(51.4,83.4).setHpMax(400).setAttackPower(40).setAttackRange(200).setRadius(50).setHigh(70).setSpeed(1.0).setManaNeed(5);
    m->newAction("walk",4)->appendFrameDelay(5).appendFrameDelay(5).appendFrameDelay(5).appendFrameDelay(5);
    m->newAction("attack",6)->appendFrameDelay(3).appendFrameDelay(2).appendFrameDelay(2).appendFrameDelay(2).appendFrameDelay(2).appendFrameDelay(5).setActionPoint(4);
    m->newAction("death",5)->appendFrameDelay(3).appendFrameDelay(3).appendFrameDelay(3).appendFrameDelay(3).appendFrameDelay(30);
    m->help = "When we pick up the bow, it is going to shoot";

    m = current->newMinion("knight");
    m->setOffsetXY(51.4,83.4).setHpMax(700).setAttackPower(60).setAttackRange(70).setRadius(50).setHigh(70).setSpeed(1.5).setManaNeed(6);
    m->newAction("walk",4)->appendFrameDelay(5).appendFrameDelay(5).appendFrameDelay(5).appendFrameDelay(5);
    m->newAction("attack",6)->appendFrameDelay(4).appendFrameDelay(3).appendFrameDelay(3).appendFrameDelay(3).appendFrameDelay(8).appendFrameDelay(10).setActionPoint(4);
    m->newAction("death",5)->appendFrameDelay(3).appendFrameDelay(3).appendFrameDelay(3).appendFrameDelay(3).appendFrameDelay(30);
    m->help = "You are the man who pulls the wind, no matter where, it is like a firefly in the dark, is so clear, so outstanding";

    m = current->newMinion("siegeram");
    m->setOffsetXY(54.7,50.1).setHpMax(900).setAttackPower(60).setAttackRange(70).setRadius(50).setHigh(50).setSpeed(0.5).setManaNeed(7);
    m->newAction("walk",4)->appendFrameDelay(5).appendFrameDelay(5).appendFrameDelay(5).appendFrameDelay(5);
    m->newAction("attack",6)->appendFrameDelay(8).appendFrameDelay(5).appendFrameDelay(3).appendFrameDelay(3).appendFrameDelay(3).appendFrameDelay(10).setActionPoint(4);
    m->newAction("death",5)->appendFrameDelay(3).appendFrameDelay(3).appendFrameDelay(3).appendFrameDelay(3).appendFrameDelay(30);
    m->help = "Has been toot, you know what I mean";

    m = current->newMinion("king");
    m->setOffsetXY(43.2,87.6).setHpMax(1000).setAttackPower(100).setAttackRange(70).setRadius(50).setHigh(90).setSpeed(1.0).setManaNeed(9);
    m->newAction("walk",4)->appendFrameDelay(5).appendFrameDelay(5).appendFrameDelay(5).appendFrameDelay(5);
    m->newAction("attack",10)->appendFrameDelay(3).appendFrameDelay(2).appendFrameDelay(2).appendFrameDelay(2).appendFrameDelay(3) \
            .appendFrameDelay(3).appendFrameDelay(2).appendFrameDelay(2).appendFrameDelay(2).appendFrameDelay(3).setActionPoint(4);
    m->newAction("death",5)->appendFrameDelay(3).appendFrameDelay(3).appendFrameDelay(3).appendFrameDelay(3).appendFrameDelay(30);
    m->help = "Help me hold ten seconds";
    m = current->newMinion("manaCan");
    m->setManaNeed(1);
    m->help = "Fill your Mana, and your wounded heart";
    m = current->newMinion("thunder");
    m->setManaNeed(5);
    m->help = "Bad weather condensed out, bombing your enemies with 999 damage";
    m = current->newMinion("splitbody");
    m->setManaNeed(6);
    m->help = "All the minion cloned, blowing the reversal of the horn";

    //load card-logo pixmaps
    current->loadCardPixmaps(":/pic/type0/logo/card_test_logo_",".png",0,10,2);
}
