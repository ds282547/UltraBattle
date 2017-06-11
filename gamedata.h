#ifndef GAMEDATA_H
#define GAMEDATA_H

#include "gameconstdata.h"
#include "typedata.h"
#include <QVector>
#include "pixmaps.h"

class gamedata {
public:
    QVector<TypeData*> datas; //everything
    gamedata();
};

#endif // GAMEDATA_H
