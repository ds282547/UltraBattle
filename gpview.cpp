#include "gpview.h"
#include <QDebug>

GpView::GpView (QWidget *parent=nullptr) : QGraphicsView(parent)
{
    setMouseTracking(true);
}
void GpView::mouseMoveEvent(QMouseEvent * event){
    QGraphicsView::mouseMoveEvent(event);
}
