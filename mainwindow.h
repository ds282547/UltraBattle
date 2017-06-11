#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPixmap>
#include "drawcard.h"
#include "gamedata.h"
#include "carddeckitem.h"
#include "game.h"
#include <QtMultimedia/QMediaPlayer>
#include <QPointF>
#include <QTimer>
#include <QTimeLine>
#include <QVector>
#include <QDebug>
#include <QTime>
#include <QTransform>

#include "carditem.h"

namespace Ui {
class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void StartClick();
    void Exit();
    void remake();
    void DrawCardPress(int x,int y);
    void DrawCardMove(int x,int y);
    void DrawCardRelease(int x,int y);
    void CloseDrawCard();
    void DragTimer();
    void StartDrawCard();
    void SelectCardItem(int no);
    void CloseCardM();
    void StartCardM();
    void CloseMsgBox();
    void CloseLevelSelect();
    void StartEasyGame();
    void StartNormalGame();
    void StartHardGame();
    void StartCrazyGame();
    void DiscardCard();
    void hidden();
private:
    Ui::MainWindow *ui;

    game *gam;
    int magicStone;
    void init();
    void msgbox(QString msg);
    bool useMagicStone(int n);
    //draw card
    QGraphicsScene *drawScene;
    DrawCard *dc;
    QGraphicsPixmapItem *cardBg;
    QGraphicsPixmapItem *cardDrawOut;
    bool drawDrag;
    bool drawed;
    QPointF cardInitPos;
    QPointF startDragPoint;
    QTimer *timer1;
    QTimeLine *timeline;
    //card manager
    void updateCardManager();
    gamedata gd;
    QGraphicsScene *CMScene;
    QVector<CardItem*> carditems;
    int selectedCardItem;
    // initial carddeck
    QVector<CardDeckItem*> myCardDeck;
    // music
    QMediaPlayer player;

    inline int randbtw(int max,int min);
    int DrawNewCard();
};

#endif // MAINWINDOW_H
