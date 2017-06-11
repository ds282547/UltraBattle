#include "game.h"
#include "ui_game.h"

#include <QDebug>



game::game(QWidget *parent, QVector<CardDeckItem *>&_myCardDeck) :
    QWidget(parent),
    myCardDeck(&_myCardDeck),
    ui(new Ui::game)
{
    qsrand(QTime::currentTime().msec());
    ui->setupUi(this);

    // Scene & View
    gpScene = new GpScene();
    ui->graphicsView->setScene(gpScene);
    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    ui->graphicsView->setSceneRect(-GD::GROUND_X,-GD::GROUND_Y,1000,1000);
    // disable scroll bar
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);




    //process gamedata
    gd = new gamedata();

    //RCardLabels[0]->setStyleSheet("border-image:url(:/pic/type0/logo/card_test_logo_04.png) 0 0 0 stretch stretch;");

    gametimer = new QTimer(this);
    gametimer->start(30);
    connect(gametimer,SIGNAL(timeout()),this,SLOT(timerTicker()));
    secTimer = new QTimer(this);
    secTimer->start(1000);
    connect(secTimer,SIGNAL(timeout()),this,SLOT(secTicker()));
    gameSec = GD::GAME_TIME;
    ui->lcdNumber->display(gameSec);

    //initialize Card
    for(int i=0;i<8;i++){
        RCardDeck.append(i);

    }
    for(int i=0;i<myCardDeck->length();i++){
        BCardDeck.append(i);
    }
    for(int i=0;i<4;i++){
        int chos;
        RCards.append(new Card(gd->datas[0]->cardPixmaps,false,gd->datas[0]->minionDatas));
        RCards.last()->setPos(GD::RCARD_POS[i]);
        //get a card from Red deck
        RCards.last()->setIndex(giveARandomCardFromDeck(0));
        // set no
        RCards.last()->no = i;
        // set level
        RCards.last()->level = 8;

        BCards.append(new Card(gd->datas[0]->cardPixmaps,true,gd->datas[0]->minionDatas));
        BCards.last()->setPos(GD::BCARD_POS[i]);
        //get a card from Blue deck
        int idx = giveARandomCardFromDeck(1);
        CardDeckItem *myCard = myCardDeck->at(idx);
        BCards.last()->indexInCardDeck = idx;
        BCards.last()->setIndex(myCard->id);
        BCards.last()->level = myCard->level;
        // set no
        BCards.last()->no = i;

        connect(BCards.last()->msg,SIGNAL(cardPressed(int)),this,SLOT(cardPressed(int)));

        gpScene->addItem(RCards.last());
        gpScene->addItem(BCards.last());
    }
    choosedCard = -1; // No choose any card

    //Mana Bar
    RMana = BMana = GD::INITAL_MANA;
    RManaBar = new ManaBar(0);
    RManaBar->setPos(GD::R_MANABAR_POS);
    BManaBar = new ManaBar(1);
    BManaBar->setPos(GD::B_MANABAR_POS);
    gpScene->addItem(RManaBar);
    gpScene->addItem(BManaBar);

    //Tower
    hpbars.append(new HpBar(0));
    hpbars.append(new HpBar(0));
    hpbars.append(new HpBar(0));
    hpbars.append(new HpBar(1));
    hpbars.append(new HpBar(1));
    hpbars.append(new HpBar(1));


    RLeftTower = new Tower(0,1);
    RLeftTower->setPos(GD::R_LEFT_TOWER_POS);
    RLeftTower->attachHpBar(hpbars[0]);
    RRightTower = new Tower(0,1);
    RRightTower->setPos(GD::R_RIGHT_TOWER_POS);
    RRightTower->attachHpBar(hpbars[1]);
    RCenterTower = new Tower(0,2);
    RCenterTower->setPos(GD::R_CENTER_TOWER_POS);
    RCenterTower->attachHpBar(hpbars[2]);
    BLeftTower = new Tower(1,1);
    BLeftTower->setPos(GD::B_LEFT_TOWER_POS);
    BLeftTower->attachHpBar(hpbars[3]);
    BRightTower = new Tower(1,1);
    BRightTower->setPos(GD::B_RIGHT_TOWER_POS);
    BRightTower->attachHpBar(hpbars[4]);
    BCenterTower = new Tower(1,2);
    BCenterTower->setPos(GD::B_CENTER_TOWER_POS);
    BCenterTower->attachHpBar(hpbars[5]);


    gpScene->addItem(RLeftTower);gpScene->addItem(RRightTower);gpScene->addItem(RCenterTower);
    gpScene->addItem(BLeftTower);gpScene->addItem(BRightTower);gpScene->addItem(BCenterTower);

    RTowers.append(RLeftTower);RTowers.append(RRightTower);RTowers.append(RCenterTower);
    BTowers.append(BLeftTower);BTowers.append(BRightTower);BTowers.append(BCenterTower);

    //add tower hpbar
    for(int i=0;i<6;i++){
        if(i==2||i==5){
            hpbars[i]->resize(100,7);
        }else
            hpbars[i]->resize(80,7);

        gpScene->addItem(hpbars[i]);
    }

    connect(gpScene->msg,SIGNAL(pressed(int,int)),this,SLOT(pressedScene(int,int)));

    // bgm & sound
    player.setMedia(QUrl("qrc:/snd/sound/battle_bgm.mp3"));
    player.play();
    winSpeech.setSource(QUrl("qrc:/snd/sound/win_speech.wav"));
    loseSpeech.setSource(QUrl("qrc:/snd/sound/lose_speech.wav"));

    //end result
    ui->widget->setGraphicsEffect(&widgetEffect);
    widgetEffect.setBlurRadius(100);
    ui->widget->setVisible(false);
}
void game::timerTicker(){
    //qDebug() << "processDeath";
    processDeath();
    //Tower DESTROY
    //qDebug() << "TowerDestory";
    Tower *tower;
    foreach(AttackableObject* t,RTowers){
        tower = (Tower*)t;
        if(tower->dead){
            tower->hpbar->setVisible(false);
            tower->setOpacity(0.5);
        }
    }
    foreach(AttackableObject* t,BTowers){
        tower = (Tower*)t;
        if(tower->dead){
            tower->hpbar->setVisible(false);
            tower->setOpacity(0.5);
        }
    }
    if(RTowers[2]->dead){
        endGame();
    }
    if(BTowers[2]->dead){
        endGame();
    }
    //qDebug() << "TowerAttack";
    towerAttack();
    //qDebug() << "Computer put minion";
    computerPutMinionForTimer1();
    //qDebug() << "calcDistance";
    calcDistance();
    //qDebug() << "MinionTicker";
    Minion* m;
    //qDebug() << "minionB";
    foreach(m,minionB){
        m->timerTicker();
    }
    //qDebug() << "minionR";
    foreach(m,minionR){
        m->timerTicker();
    }
    //qDebug() << "deathMinion";
    int counter = 0;
    foreach(m,deathMinion){
        counter++;
        //qDebug() << counter;
        m->timerTicker();
    }

     //qDebug() << "setMana";
    if(RMana<=10){
        RMana+=GD::MANA_INCRE_SPEED;
        RManaBar->setMana(RMana);
    }
    if(BMana<=10){
        BMana+=GD::MANA_INCRE_SPEED;
        BManaBar->setMana(BMana);
    }
    //qDebug() << "Zorder";
    processItemZOrder();
}
void game::secTicker(){
    gameSec--;
    if(gameSec==0){
        endGame();
    }
    ui->lcdNumber->display(gameSec);

}
//----Tower Attack
void game::towerAttack(){
    //process cannon ball
    foreach(CannonBall *c,cannonballs){
        c->timeTicker();
    }

    qreal minDist[6]={1000,1000,1000,1000,1000,1000};

    Minion *cloestMinion[6];
    static const int cd = 50;
    static int attackColdDown[6]={cd,cd,cd,cd,cd,cd};
    QPointF d;
    qreal dist;
    // blue tower
    foreach(Minion *m,minionR){
        for(int i=0;i<3;i++){
            d=m->pos()-BTowers.at(i)->pos();
            dist = qSqrt(QPointF::dotProduct(d,d));
            if(dist<minDist[i]){
                minDist[i] = dist;
                cloestMinion[i]=m;
            }
        }
    }
    //red tower
    foreach(Minion *m,minionB){
        for(int i=3;i<6;i++){
            d=m->pos()-RTowers.at(i-3)->pos();
            dist = qSqrt(QPointF::dotProduct(d,d));
            if(dist<minDist[i]){
                minDist[i] = dist;
                cloestMinion[i]=m;
            }
        }
    }
    //blue tower
    for(int i=0;i<3;i++){
        if(minDist[i]<100 && attackColdDown[i]==cd && !BTowers[i]->dead){
            CannonBall *c = new CannonBall(1);
            c->setPos(BTowers[i]->pos()+QPointF(0,-40));
            c->targetPos = cloestMinion[i]->pos()-QPointF(0,20);
            cannonballs.append(c);
            gpScene->addItem(c);
            attackColdDown[i] = 0;
        }
    }
    //red tower
    for(int i=3;i<6;i++){
        if(minDist[i]<100 && attackColdDown[i]==cd && !RTowers[i-3]->dead){
            CannonBall *c = new CannonBall(0);
            c->setPos(RTowers[i-3]->pos()+QPointF(0,-40));
            c->targetPos = cloestMinion[i]->pos()-QPointF(0,20);
            cannonballs.append(c);
            gpScene->addItem(c);

            attackColdDown[i] = 0;
        }
    }
    for(int i=0;i<6;i++){
        if(attackColdDown[i]<cd){
            attackColdDown[i]++;
        }
    }
    //cannon attack
    foreach(CannonBall* c,cannonballs){
        if(c->reach){
            Minion* mm;
            QRectF canRect = QRectF(c->x()-40,c->y()-40,80,80);

            if(c->side==1){
                foreach(Minion *m,minionR){
                    if(canRect.contains(m->pos())){
                        m->damage(randbtw(120,180));
                    }
                }
            }else{
                foreach(Minion *m,minionB){
                    if(canRect.contains(m->pos())){
                        m->damage(randbtw(120,180));
                    }
                }
            }

            cannonballs.removeOne(c);
            gpScene->removeItem(c);
        }
    }
}

//----Computer
void game::computerPutMinionForTimer1(){
    static const QRectF leftRect = QRectF(11,147,140,64);
    static const QRectF rightRect = QRectF(259,147,140,64);
    static int waitTimes[4] = {0,0,0,0};
    static bool waitingMana = false;
    static int maxPos;
    int max;
    static Card *putCard;
    qreal avgX = 0,avgY = 0;
    if(!minionB.empty()){
        foreach(Minion* m,minionB){
            avgX += m->x();
            avgY += m->y();
        }
        avgX /= minionB.size();
        avgY /= minionB.size();
    }
    //put pos
    QPointF pt = (avgX>GD::GROUND_W/2)?randPt(rightRect):randPt(leftRect);
    //put cards
    // find max waiting time

    if(!waitingMana){
        for(int i=0;i<4;i++){
            waitTimes[i]++;
        }
        max = waitTimes[0];
        maxPos = 0;
        for(int i=1;i<4;i++){
            if(waitTimes[i]>max){
                max = waitTimes[i];
                maxPos = i;
            }
        }
        putCard = RCards.at(maxPos);
        waitTimes[maxPos] = 0;
        waitingMana = true;
    }
    if(RMana>putCard->manaNeed){
        RMana-=putCard->manaNeed;
        putMinionDown(0,putCard->index,pt.toPoint().x(),pt.toPoint().y(),0,8);
        giveNewCard(0,maxPos);
        waitingMana = false;
    }
}

//------------------------------------------------------------------
//------------------Minion Processing-------------------------------
void game::putMinionDown(int type,int no,int x,int y,int side,int level=3){ //side 0-Red 1-Blue
    Minion* minion;
    switch(no){
        case 0: //warrior
            minion = new MinionWarrior(type,side,no,level);
            break;
        case 1: //spear
            minion = new MinionSpear(type,side,no,level);
            break;
        case 2: //priest
            minion = new MinionPriest(type,side,no,level);
            break;
        case 3: //archmage
            minion = new MinionArchMage(type,side,no,level);
            break;
        case 4: //bowman
            minion = new MinionBowman(type,side,no,level);
            break;
        case 5: //knight
            minion = new MinionKnight(type,side,no,level);
            break;
        case 6: //siegeram
            minion = new MinionSiegeram(type,side,no,level);
            break;
        case 7: //king
            minion = new MinionKing(type,side,no,level);
            break;

    }
    minion->init(gd->datas);
    minion->setPos(x,y);
    //death signal
    connect(minion->deathMsg,SIGNAL(dead(QGraphicsPixmapItem*)),this,SLOT(removeMinionInVector(QGraphicsPixmapItem*)));
    connect(minion->deathMsg,SIGNAL(dead2(QGraphicsPixmapItem*)),this,SLOT(removeMinionInScene(QGraphicsPixmapItem*)));

    //new hp bar
    hpbars.append(new HpBar(side));
    minion->attachHpBar(hpbars.last());

    gpScene->addItem(minion);
    gpScene->addItem(hpbars.last());

    if(side==0){
        minionR.append(minion);
        minion->attachEnemiesTeammates(minionB,minionR);
        minion->attachEnemyTowers(BTowers);
    }else if(side==1){
        minionB.append(minion);
        minion->attachEnemiesTeammates(minionR,minionB);
        minion->attachEnemyTowers(RTowers);
    }

}
// ZOrder
void game::processItemZOrder(){
    QGraphicsItem* item;
    foreach(item,gpScene->items()){
        item->setZValue(item->y());
    }
    //put HPBAR higher
    foreach(item,hpbars){
        item->setZValue(item->zValue()+2000);
    }
    foreach(item,cannonballs){
        item->setZValue(item->zValue()+1000);
    }
}
// Enemies Distance
void game::calcDistance(){
    Minion* R;
    Minion* B;
    QPointF d;
    int i,j;
    foreach(R,minionR){
        R->eneDistance = QVector<qreal>(minionB.size());
    }
    for(i=0;i<minionB.size();i++){
        B=minionB.at(i);
        B->eneDistance = QVector<qreal>(minionR.size());
        for(j=0;j<minionR.size();j++){
            R=minionR.at(j);
            d = (R->pos())-(B->pos());
            B->eneDistance[j]=qSqrt(QPointF::dotProduct(d, d));
            R->eneDistance[i]=B->eneDistance.at(j);
        }
    }
    /*
    //qDebug() << "distance";
    //qDebug() << "R";
    foreach(R,minionR){
        //qDebug() << R->eneDistance;
    }
    //qDebug() << "B";
    foreach(B,minionB){
        //qDebug() << B->eneDistance;
    }*/
}

// pressedScene SLOT
void game::pressedScene(int x,int y){
    if(GD::GROUND_B_AREA.contains(x,y)){
        if(choosedCard==-1)
            return;
        int minionSel = BCards.at(choosedCard)->indexInCardDeck;
        int minionSelId = myCardDeck->at(minionSel)->id;
        int minionSelLevel = myCardDeck->at(minionSel)->level;
        int manaCost = gd->datas[0]->getMinion(minionSelId)->manaNeed;
        if(BMana-manaCost>=0){
            BMana-=manaCost;
            giveNewCard(1,choosedCard);
            switch(minionSelId){
            case 8:
                BMana=10;
                BManaBar->setMana(BMana);
                break;
            case 9:
                foreach(Minion *m,minionR){
                    m->damage(999);
                }
                break;
            case 10:
                foreach(Minion *m,minionB){
                    putMinionDown(0,m->no,m->x()+randbtw(20,-20),m->y()+randbtw(20,-20),1,m->level);
                }
                break;
            default:
                putMinionDown(0,minionSelId,x,y,1,minionSelLevel);
            }
            BCards.at(choosedCard)->setSel(false);
            choosedCard = -1;
        }
    }
}
// remove Minion for death  2 SLOT + 1 private method
void game::removeMinionInVector(QGraphicsPixmapItem *minion){

    Minion *m = (Minion*)minion;
    removeMinionInVectorStack.append(m);


}
void game::removeMinionInScene(QGraphicsPixmapItem *minion){
    Minion *m = (Minion*)minion;
    removeMinionInSceneStack.append(m);
}
void game::processDeath(){
    Minion *m;
    if(!removeMinionInVectorStack.isEmpty()){

        foreach(m,removeMinionInVectorStack){

            hpbars.removeOne(m->hpbar);
            gpScene->removeItem(m->hpbar);
            if(m->side==0){
                minionR.removeOne(m);
            }else{
                minionB.removeOne(m);
            }
            deathMinion.append(m);
        }
        removeMinionInVectorStack.clear();
    }
    if(!removeMinionInSceneStack.isEmpty()){
        foreach(m,removeMinionInSceneStack){
            gpScene->removeItem(m);
            //disable signal
            disconnect(m->deathMsg,SIGNAL(dead(QGraphicsPixmapItem*)),this,SLOT(removeMinionInVector(QGraphicsPixmapItem*)));
            disconnect(m->deathMsg,SIGNAL(dead2(QGraphicsPixmapItem*)),this,SLOT(removeMinionInScene(QGraphicsPixmapItem*)));
        }

        deathMinion.removeOne(m);
        removeMinionInSceneStack.clear();
    }
}
//------------------------------
//-------------RAND------------
inline QPointF game::randPt(QRectF rect){
    return rect.topLeft()+QPointF(qrand()%(int)rect.width(),qrand()%(int)rect.height());
}
inline int game::randbtw(int max,int min){
    return qrand() % ((max + 1) - min) + min;
}
//------------------------------
//-------------Card-------------
void game::giveNewCard(int side,int no){
    int spawnCard;
    if(side==0){//R
        spawnCard = RCards.at(no)->index;
        RCardDeck.removeOne(spawnCard);
        RCards.at(no)->setIndex(giveARandomCardFromDeck(0));
        RCardDeck.append(spawnCard);
    }else{//B
        spawnCard = BCards.at(no)->indexInCardDeck;
        BCardDeck.removeOne(spawnCard);
        int idx = giveARandomCardFromDeck(1);
        CardDeckItem *myCard = myCardDeck->at(idx);
        BCards.at(no)->indexInCardDeck = idx;
        BCards.at(no)->setIndex(myCard->id);
        BCards.at(no)->level = myCard->level;
        BCardDeck.append(spawnCard);
    }
}
int game::giveARandomCardFromDeck(int side){
    int chos;
    if(side==0){
        chos = RCardDeck[randbtw(RCardDeck.size()-1,0)];
        RCardDeck.removeOne(chos);
    }else{
        chos = BCardDeck[randbtw(BCardDeck.size()-1,0)];
        BCardDeck.removeOne(chos);
    }
    return chos;
}
//Card Pressed Slot
void game::cardPressed(int no){

    if(choosedCard>-1){
        BCards[choosedCard]->setSel(false);
    }
    choosedCard = no;

}

//End Game
void game::endGame(){
    int win;
    if(RTowers[2]->dead){
        win = 1;
    }else if(BTowers[2]->dead){
        win = 0;
    }else{
        int TowerHpR=0,TowerHpB=0;
        Tower *tower;
        foreach(AttackableObject *t,RTowers){
            tower = (Tower*)t;
            TowerHpR+=tower->hp;
        }
        foreach(AttackableObject *t,BTowers){
            tower = (Tower*)t;
            TowerHpB+=tower->hp;
        }
        //qDebug() << TowerHpR << TowerHpB;
        if(TowerHpR<TowerHpB){
            win = 1;
        }else if(TowerHpR>TowerHpB){
            win = 0;
        }else{
            win = 2; //tie
        }
    }

    disconnect(gametimer,SIGNAL(timeout()),this,SLOT(timerTicker()));
    disconnect(secTimer,SIGNAL(timeout()),this,SLOT(secTicker()));
    disconnect(gpScene->msg,SIGNAL(pressed(int,int)),this,SLOT(pressedScene(int,int)));
    foreach(Card* c,BCards)
        disconnect(c->msg,SIGNAL(cardPressed(int)),this,SLOT(cardPressed(int)));


    QTimeLine *timeline = new QTimeLine(1000,this);
    QTimeLine *timeline2 = new QTimeLine(500,this);

    timeline->setFrameRange(100,0);
    timeline2->setFrameRange(0,100);



    switch(win){
        case 1:
            player2.setMedia(QUrl("qrc:/snd/sound/win_bgm.mp3"));
            connect(timeline,SIGNAL(finished()),&winSpeech,SLOT(play()));
            ui->label_2->setPixmap(QPixmap(":/gameui/pic/Winer.png"));
            break;
        case 0:
            player2.setMedia(QUrl("qrc:/snd/sound/lose_bgm.mp3"));
            connect(timeline,SIGNAL(finished()),&loseSpeech,SLOT(play()));
            ui->label_2->setPixmap(QPixmap(":/gameui/pic/Loser.png"));
            break;
        case 2:
            player2.setMedia(QUrl("qrc:/snd/sound/tie_bgm.mp3"));
            ui->label_2->setPixmap(QPixmap(":/gameui/pic/Tie.png"));
            break;

    }
    player2.setVolume(0);
    player2.play();


    ui->widget->setVisible(true);

    connect(timeline,SIGNAL(frameChanged(int)),&player,SLOT(setVolume(int)));
    connect(timeline,SIGNAL(frameChanged(int)),this,SLOT(displayResult(int)));
    connect(timeline,SIGNAL(finished()),this,SLOT(showResult()));
    connect(timeline2,SIGNAL(frameChanged(int)),&player2,SLOT(setVolume(int)));


    timeline->start();
    timeline2->start();
}
void game::displayResult(int i){
   widgetEffect.setBlurRadius(i);
}

void game::showResult(){
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(backToMenu()));

}
void game::backToMenu(){
    emit endGameBackToMain();
}

game::~game()
{
    delete ui;
}
