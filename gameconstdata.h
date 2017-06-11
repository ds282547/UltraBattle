#ifndef GAMECONSTDATA_H
#define GAMECONSTDATA_H
#include <QColor>
#include <QPointF>
#include <QRectF>
#include <QVector>

namespace GD{
    const int GROUND_X = 135;
    const int GROUND_Y = 213;
    const QPointF GROUND_ORI = QPointF(GROUND_X,GROUND_Y);
    const int GROUND_W = 416;
    const int GROUND_H = 568;
    //area
    const QRectF GROUND_R_AREA = QRectF(0,0,416,261);
    const QRectF GROUND_B_AREA = QRectF(0,301,416,267);

    const int GAME_TIME = 120;

    const int LEFT_TOWER_X = 217 - GROUND_X;
    const int RIGHT_TOWER_X = 469 - GROUND_X;
    const int CENTER_TOWER_X = GROUND_W / 2;
    const int FRONT_TOWER_W = 68;
    const int FRONT_TOWER_H = 50;
    const int BACK_TOWER_W = 86;
    const int BACK_TOWER_H = 70;
    const int R_FRONT_TOWER_Y = 332 - GROUND_Y;
    const int R_BACK_TOWER_Y = 269 - GROUND_Y;
    const int B_FRONT_TOWER_Y = 668 - GROUND_Y;
    const int B_BACK_TOWER_Y = 735 - GROUND_Y;
    //Tower Pos
    const QPointF R_LEFT_TOWER_POS = QPointF(LEFT_TOWER_X,R_FRONT_TOWER_Y);
    const QPointF R_RIGHT_TOWER_POS = QPointF( RIGHT_TOWER_X,R_FRONT_TOWER_Y);
    const QPointF R_CENTER_TOWER_POS = QPointF(CENTER_TOWER_X,R_BACK_TOWER_Y);
    const QPointF B_LEFT_TOWER_POS = QPointF(LEFT_TOWER_X,B_FRONT_TOWER_Y);
    const QPointF B_RIGHT_TOWER_POS = QPointF(RIGHT_TOWER_X,B_FRONT_TOWER_Y);
    const QPointF B_CENTER_TOWER_POS = QPointF(CENTER_TOWER_X,B_BACK_TOWER_Y);
    //Tower HP
    const int FRONT_TOWER_HPMAX = 1000;
    const int BACK_TOWER_HPMAX = 1500;

    const int CARD_W = 60;
    const int CARD_HH = 78;
    const int HP_BAR_W = 30;
    const int HP_BAR_H = 7;
    const int HP_BAR_BORDER = 2;
    const QColor HP_RED_SIDE_COLOR = QColor::fromRgb(255,0,0);
    const QColor HP_BLUE_SIDE_COLOR = QColor::fromRgb(0,200,255);
    const QRectF BRIDGE_LEFT(47,261,70,40);
    const QRectF BRIDGE_RIGHT(298,261,70,40);
    const int HIT_BLINK_FRAME_LENGTH = 5;
    const int HIT_BLINK_TIME = 4;
    const QColor HIT_BLINK_COLOR = QColor::fromRgb(255,0,0);
    //card
    const QPointF RCARD_POS[4] = {QPointF(184,89)-GROUND_ORI,QPointF(253,89)-GROUND_ORI,
                            QPointF(322,89)-GROUND_ORI,QPointF(391,89)-GROUND_ORI};
    const QPointF BCARD_POS[4] = {QPointF(184,850)-GROUND_ORI,QPointF(253,850)-GROUND_ORI,
                            QPointF(322,850)-GROUND_ORI,QPointF(391,850)-GROUND_ORI};
    //mana
    const QPointF B_MANABAR_POS = QPointF(-21,691);
    const QPointF R_MANABAR_POS = QPointF(-21,-180);
    const qreal INITAL_MANA = 5;
    const qreal MANA_INCRE_SPEED = 0.05;


}

#endif // GAMECONSTDATA_H

