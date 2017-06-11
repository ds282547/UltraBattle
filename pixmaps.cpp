#include "pixmaps.h"
#include <QDebug>


Pixmaps::Pixmaps(const QString _prefix, const QString _postfix)
{
    prefix = _prefix;
    postfix = _postfix;
}
void Pixmaps::getPixmapsWithIndex(int from,int end,int zeros){
    int i;
    QString rule;
    QString zero = QString("%0")+QString::number(zeros)+QString("d");
    QString path;
    rule.append(prefix).append(zero).append(postfix);
    for(i=from;i<=end;i++){
        pixmaps.append(path.sprintf(rule.toStdString().c_str(),i));
        paths.append(path);
    }
}
void Pixmaps::scaleAllPixmaps(qreal w,qreal h){
    QVector<QPixmap>::iterator i;
    for(i = pixmaps.begin();i != pixmaps.end();i++){
        *i = i->scaled(w,h,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    }
}

QPixmap Pixmaps::at(int i){
    return pixmaps.at(i);
}
QString Pixmaps::pathAt(int i){
    return paths.at(i);
}

