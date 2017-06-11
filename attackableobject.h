#ifndef ATTACKABLEOBJECT_H
#define ATTACKABLEOBJECT_H

#include <QGraphicsPixmapItem>
class AttackableObject : public QGraphicsPixmapItem
{
public:
    AttackableObject();
    virtual void damage(int n); // for inheritance
    bool dead;
};

#endif // ATTACKABLEOBJECT_H
