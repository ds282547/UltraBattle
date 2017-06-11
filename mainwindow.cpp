#include "mainwindow.h"
#include "ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // initalize my card deck
    for(int i=0;i<=10;i++){
        myCardDeck.append(new CardDeckItem(i,1));
    }
    magicStone = 14;
    init();
    player.setMedia(QUrl("qrc:/snd/sound/open_bgm.mp3"));
    player.play();



}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::remake(){
    init();
    useMagicStone(-(gam->awardStone));
}
bool MainWindow::useMagicStone(int n){
    if(magicStone-n<0){
        ui->labelStone->setText(QString("%1").arg(magicStone));
        return false;
    }else{
        magicStone -= n;
        ui->labelStone->setText(QString("%1").arg(magicStone));
        return true;
    }
}
void MainWindow::msgbox(QString msg){
    ui->widgetMsgBox->setVisible(true);
    ui->labelMsg->setText(msg);
}

void MainWindow::init(){
    qsrand(QTime::currentTime().msec());

    ui->setupUi(this);

    connect(ui->pushButtonHidden,SIGNAL(clicked(bool)),this,SLOT(hidden()));
    //magic stone

    ui->labelStone->setText(QString("%1").arg(magicStone));
    ui->label_3->setPixmap(QPixmap(":/gameui/pic/stone.png").scaled(30,30,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    ui->label_stone0->setPixmap(QPixmap(":/gameui/pic/stone.png").scaled(35,35,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    ui->label_stone1->setPixmap(QPixmap(":/gameui/pic/stone.png").scaled(35,35,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    ui->label_stone2->setPixmap(QPixmap(":/gameui/pic/stone.png").scaled(35,35,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    ui->label_stone3->setPixmap(QPixmap(":/gameui/pic/stone.png").scaled(35,35,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    ui->label_stone4->setPixmap(QPixmap(":/gameui/pic/stone.png").scaled(35,35,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    ui->widgetMsgBox->setVisible(false);

    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(StartClick()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(StartDrawCard()));
    connect(ui->pushButtonDrawOk,SIGNAL(clicked()),this,SLOT(CloseDrawCard()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(StartCardM()));
    connect(ui->pushButtonCloseCardM,SIGNAL(clicked()),this,SLOT(CloseCardM()));
    connect(ui->pushButtonCloseMsgBox,SIGNAL(clicked()),this,SLOT(CloseMsgBox()));
    connect(ui->pushButtonExit,SIGNAL(clicked()),this,SLOT(Exit()));
    // draw card
    drawScene = new QGraphicsScene(this);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QGraphicsPixmapItem *d1 = new QGraphicsPixmapItem(QPixmap(":/gameui/drawcard/cardboxbottom.png"));
    dc = new DrawCard();
    drawDrag = false;
    connect(dc->msg,SIGNAL(pressed(int,int)),this,SLOT(DrawCardPress(int,int)));
    connect(dc->msg,SIGNAL(moved(int,int)),this,SLOT(DrawCardMove(int,int)));
    connect(dc->msg,SIGNAL(released(int,int)),this,SLOT(DrawCardRelease(int,int)));
    cardBg = new QGraphicsPixmapItem(QPixmap(":/gameui/drawcard/cardBG.png"));
    QGraphicsPixmapItem *d3 = new QGraphicsPixmapItem(QPixmap(":/gameui/drawcard/cardboxtop.png"));
    cardDrawOut = new QGraphicsPixmapItem();
    cardDrawOut->setOffset(-369/2,0);

    drawScene->addItem(d1);
    drawScene->addItem(cardBg);
    drawScene->addItem(dc);
    drawScene->addItem(d3);
    drawScene->addItem(cardDrawOut);

    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    ui->graphicsView->setSceneRect(0,0,686,931);
    ui->graphicsView->setScene(drawScene);

    timer1 = new QTimer();
    timer1->setInterval(20);
    connect(timer1,SIGNAL(timeout()),this,SLOT(DragTimer()));

    ui->widgetDrawCard->setVisible(false);

    // card manager
    connect(ui->pushButtonCloseLevelSelect,SIGNAL(clicked()),this,SLOT(CloseLevelSelect()));
    connect(ui->pushButtonEasy,SIGNAL(clicked()),this,SLOT(StartEasyGame()));
    connect(ui->pushButtonNormal,SIGNAL(clicked()),this,SLOT(StartNormalGame()));
    connect(ui->pushButtonHard,SIGNAL(clicked()),this,SLOT(StartHardGame()));
    connect(ui->pushButtonCrazy,SIGNAL(clicked()),this,SLOT(StartCrazyGame()));
    connect(ui->pushButtonDiscardCard,SIGNAL(clicked()),this,SLOT(DiscardCard()));

    CMScene = new QGraphicsScene(this);
    ui->graphicsViewCardM->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    ui->graphicsViewCardM->setSceneRect(0,0,ui->graphicsViewCardM->width(),ui->graphicsViewCardM->height());
    ui->graphicsViewCardM->setScene(CMScene);
    ui->graphicsViewCardM->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsViewCardM->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->widgetCardM->setVisible(false);

    // level
    ui->widgetLevelSelect->setVisible(false);
}
void MainWindow::updateCardManager(){
    //reset & clear
    CMScene->clear();
    carditems.clear();
    selectedCardItem = -1;
    // initialize

    QPointF Pos = QPointF(20,20);
    int counter = 0;
    int index = 0;
    foreach(CardDeckItem* c,myCardDeck){
        CardItem *i = new CardItem(gd.datas[0],c->id,c->level,index);
        index++;
        connect(&(i->msg),SIGNAL(cardPressed(int)),this,SLOT(SelectCardItem(int)));
        carditems.append(i);

        i->setPos(Pos);
        Pos += QPointF(120,0);
        if(counter==3){
            Pos.setX(20);
            Pos += QPointF(0,130+20);
        }
        CMScene->addItem(i);
        counter = (counter+1)%4;
    }
    qDebug() << QRectF(QPointF(0,0),carditems.last()->boundingRect().bottomRight()+QPointF(20,20));
    ui->graphicsViewCardM->setSceneRect(QRectF(QPointF(0,0),carditems.last()->pos()+QPointF(100,130)+QPointF(20,20)));
}

void MainWindow::StartClick()
{
    ui->widgetLevelSelect->setVisible(true);
}
void MainWindow::Exit()
{
    this->close();
}
void MainWindow::CloseLevelSelect(){
    ui->widgetLevelSelect->setVisible(false);
}
void MainWindow::StartEasyGame(){
    gam=new game(this,myCardDeck,0);
    connect(gam,SIGNAL(endGameBackToMain()),this,SLOT(remake()));
    player.stop();
    this->setCentralWidget(gam);
}
void MainWindow::StartNormalGame(){
    gam=new game(this,myCardDeck,1);
    connect(gam,SIGNAL(endGameBackToMain()),this,SLOT(remake()));
    player.stop();
    this->setCentralWidget(gam);
}
void MainWindow::StartHardGame(){
    gam=new game(this,myCardDeck,2);
    connect(gam,SIGNAL(endGameBackToMain()),this,SLOT(remake()));
    player.stop();
    this->setCentralWidget(gam);
}
void MainWindow::StartCrazyGame(){
    gam=new game(this,myCardDeck,3);
    connect(gam,SIGNAL(endGameBackToMain()),this,SLOT(remake()));
    player.stop();
    this->setCentralWidget(gam);
}



void MainWindow::DrawCardPress(int x,int y){
    if(drawed)
        return;
    drawDrag = true;
    cardInitPos = dc->pos();
    startDragPoint = QPointF(x,y);
}
void MainWindow::DrawCardMove(int x,int y){
    if(drawDrag){
        dc->setY(y-startDragPoint.y()+cardInitPos.y());
        cardBg->setPos(dc->pos());
    }
}

void MainWindow::DrawCardRelease(int x,int y){
    drawDrag = false;
}
int  MainWindow::DrawNewCard(){
    int id = randbtw(10,0);
    int level = (id>7)?1:randbtw(10,1);
    myCardDeck.append(new CardDeckItem(id,level));
    return id;
}

void MainWindow::DragTimer(){
    if(!drawDrag){
        if(dc->y()>350){
            drawed = true;
            dc->setY(dc->y()+30);
            cardBg->setPos(dc->pos());
            if(dc->y()>950){
                if(cardDrawOut->y()>210){
                    static qreal angle = 0;
                    QTransform transform;
                    angle+=10;
                    transform.rotate(angle,Qt::YAxis);
                    cardDrawOut->moveBy(0,-20);
                    cardDrawOut->setTransform(transform);
                }else{
                    timer1->stop();
                    ui->pushButtonDrawOk->setVisible(true);
                }
            }

        }else if(dc->y()>-241){
            if(dc->y()+241<1){
                dc->setY(-241);

            }else{
                dc->setY((dc->y()+241)*0.96-241);
            }
        }
        cardBg->setPos(dc->pos());
    }
}
void MainWindow::StartDrawCard(){
    if(useMagicStone(5)){
        cardInitPos = QPointF(157,-241);
        dc->setPos(cardInitPos);
        cardBg->setPos(cardInitPos);
        ui->widgetDrawCard->setVisible(true);
        int newcard = DrawNewCard();
        cardDrawOut->setPixmap(gd.datas[0]->cardPixmaps->at(newcard).scaled(369,551,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
        cardDrawOut->setPos(343,930);
        drawed = false;
        ui->pushButtonDrawOk->setVisible(false);
        timer1->start();
    }else{
        msgbox("You don't have enough stones, so you can't draw a card.");
    }
}
void MainWindow::SelectCardItem(int no){
    if(selectedCardItem>-1)
        carditems.at(selectedCardItem)->UnSelect();
    selectedCardItem = no;
    CardItem *i = carditems.at(no);

    ui->labelShowCard->setPixmap(gd.datas[0]->cardPixmaps->at(i->id).scaled(ui->labelShowCard->size()));
    QString str=gd.datas[0]->getMinion(i->id)->name;
    str = str.left(1).toUpper()+str.mid(1);
    ui->labelName->setText(str);
    ui->labelLevel->setText(QString("Level=%1").arg(i->level));
    ui->labelHelp->setText(gd.datas[0]->getMinion(i->id)->help);
    ui->labelMananeed->setText(QString("ManaNeed ---"));
    if(i->id>7){
        ui->labelAttack->setText(QString("Attack ---"));
        ui->labelAttackrange->setText(QString("AttackRange ---"));

        ui->labelMaxhp->setText(QString("MaxHP ---"));

    }else{
        qreal ratio = i->level;
        ratio = 1+(ratio/10);
        ui->labelAttack->setText(QString("Attack=%1").arg(gd.datas[0]->getMinion(i->id)->attackPower*ratio));
        ui->labelAttackrange->setText(QString("AttackRange=%1").arg(gd.datas[0]->getMinion(i->id)->attackRange));
        ui->labelMananeed->setText(QString("ManaNeed=%1").arg(gd.datas[0]->getMinion(i->id)->manaNeed));
        ui->labelMaxhp->setText(QString("MaxHP=%1").arg(gd.datas[0]->getMinion(i->id)->hpMax*ratio));
    }
}
void MainWindow::StartCardM(){
    updateCardManager();
    ui->widgetCardM->setVisible(true);
}
void MainWindow::CloseCardM(){
    ui->widgetCardM->setVisible(false);
}
void MainWindow::DiscardCard(){
    if(myCardDeck.length()==5){
        msgbox("You cannot have number of cards less than 5.");
        return;
    }
    if(selectedCardItem>-1){
        carditems.remove(selectedCardItem);
        myCardDeck.remove(selectedCardItem);
        updateCardManager();
    }
    SelectCardItem(0);
    carditems.first()->Select();

}
void MainWindow::hidden(){
    useMagicStone(-40);
}

void MainWindow::CloseMsgBox(){
    ui->widgetMsgBox->setVisible(false);
}
void MainWindow::CloseDrawCard(){
    ui->widgetDrawCard->setVisible(false);
}
inline int MainWindow::randbtw(int max,int min){
    return qrand() % ((max + 1) - min) + min;
}
