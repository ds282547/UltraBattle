#ifndef GPVIEW_H
#define GPVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>

class GpView : public QGraphicsView
{
public:
    GpView(QWidget *parent);
    void mouseMoveEvent(QMouseEvent * event);
};

#endif // GPVIEW_H
