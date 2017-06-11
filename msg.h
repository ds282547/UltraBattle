#ifndef MSG_H
#define MSG_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Msg : public QObject
{
    Q_OBJECT
public:
    Msg();
    ~Msg();
    void press(int x,int y);
    void move(int x,int y);
    void release(int x,int y);
    void death(QGraphicsPixmapItem* x, int step);
    void pressCard(int no);
signals:
    void pressed(int x,int y);
    void moved(int x,int y);
    void released(int x,int y);
    void dead(QGraphicsPixmapItem* x);
    void dead2(QGraphicsPixmapItem* x);
    void cardPressed(int no);
};

#endif // MSG_H
