#ifndef PIXMAPS_H
#define PIXMAPS_H


#include <QPixmap>
#include <QVector>
#include <QList>

class Pixmaps
{
public:
    QVector<QPixmap> pixmaps;
    QVector<QString> paths;
    Pixmaps(const QString _prefix,const QString _postfix);
    // using index to fill the path string,we can process like 04 by setting zeros arg.
    void getPixmapsWithIndex(int from,int end,int zeros);
    void scaleAllPixmaps(qreal w,qreal h);
    QPixmap at(int i);
    QString pathAt(int i);
private:
    QString prefix;
    QString postfix;
};



#endif // PIXMAPS_H
