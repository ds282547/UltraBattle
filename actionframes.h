#ifndef ACTIONFRAMES_H
#define ACTIONFRAMES_H

#include <QString>
#include <QVector>
#include "pixmaps.h"
class ActionFrames
{
public:
    ActionFrames(QString _name, int id, QString nName, int len);
    Pixmaps* framePixmaps;
    QVector<int> frameDelay;
    int getFrameDelay(int i);
    ActionFrames& setFrameLength(int len);
    ActionFrames& setActionPoint(int pt); // action tick frame
    ActionFrames& appendFrameDelay(int delay);
    QString name;
    int frameLength;
    int totalTime;
    int typeId;
    int actionPoint;
    QString minionName;
private:

};

#endif // ACTIONFRAMES_H
