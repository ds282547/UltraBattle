#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QPixmap>
#include <QVector>
#include <QPointF>
#include <QRectF>
#include <QtMath>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QSoundEffect>

#include "minion.h"
#include "minionwarrior.h"
#include "minionspear.h"
#include "minionpriest.h"
#include "minionarchmage.h"
#include "minionbowman.h"
#include "minionknight.h"
#include "minionsiegeram.h"
#include "minionking.h"

#include "typedata.h"
#include "pixmaps.h"
#include "gpscene.h"
#include "hpbar.h"
#include "card.h"
#include "manabar.h"
#include "tower.h"
#include "attackableobject.h"
#include "cannonball.h"

#include <QLabel>
#include <QTimer>
#include <QTimeLine>
#include <QTime>
#include <QGraphicsBlurEffect>

#include "gamedata.h"
#include "carddeckitem.h"
namespace Ui {
class game;
}

class game : public QWidget
{
    Q_OBJECT

public:
    //Scene
    GpScene *gpScene;
    //Test
    Minion *test;
    QPixmap pix;
    //Minions
    QVector<Minion*> minionR;
    QVector<Minion*> minionB;
    QVector<Minion*> removeMinionInVectorStack;
    QVector<Minion*> removeMinionInSceneStack;
    QVector<Minion*> deathMinion;
    QVector<HpBar*> hpbars;
    //gamedata
    gamedata *gd;


    void putMinionDown(int type, int no, int x, int y, int side, int level);

    //Timer
    QTimer* gametimer;

    QTimer* secTimer;
    int gameSec;

    int f;
    //Card
    QVector<Card*> RCards;
    QVector<Card*> BCards;
    QVector<int> RCardDeck;\
    QVector<int> BCardDeck;
    int choosedCard;

    //mana bat
    ManaBar* RManaBar;
    ManaBar* BManaBar;
    qreal RMana;
    qreal BMana;

    //tower
    Tower* RLeftTower;
    Tower* RRightTower;
    Tower* RCenterTower;
    Tower* BLeftTower;
    Tower* BRightTower;
    Tower* BCenterTower;

    //cannonball
    QVector<CannonBall*> cannonballs;

    QVector<AttackableObject*> RTowers;
    QVector<AttackableObject*> BTowers;

    QGraphicsBlurEffect widgetEffect;

    explicit game(QWidget *parent, QVector<CardDeckItem *> &_myCardDeck);
    ~game();
    // carddeck
    QVector<CardDeckItem*>* myCardDeck;
private:
    Ui::game *ui;
    void processItemZOrder();
    void processDeath();
    void calcDistance();
    void giveNewCard(int side,int no);
    int giveARandomCardFromDeck(int side);
    void endGame();
    void towerAttack();
    void computerPutMinionForTimer1();
    inline int randbtw(int max,int min);
    inline QPointF randPt(QRectF rect);
    QMediaPlayer player;
    QMediaPlayer player2;
    QSoundEffect winSpeech;
    QSoundEffect loseSpeech;



public slots:
    void timerTicker();
    void secTicker();
    //mouse pressed in Scene
    void pressedScene(int x,int y);
    void removeMinionInVector(QGraphicsPixmapItem* minion);
    void removeMinionInScene(QGraphicsPixmapItem* minion);
    void cardPressed(int no);
    void displayResult(int i);
    void showResult();
    void backToMenu();
signals:
    void endGameBackToMain();
};

#endif // GAME_H
