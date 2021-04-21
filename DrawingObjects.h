#ifndef DRAWINGOBJECTS_H
#define DRAWINGOBJECTS_H
#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>

class DrawingObjects : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit DrawingObjects(){}
    ~DrawingObjects(){}

    QString text = "1";

    QRectF boundingRect() const{
        return QRectF (-15,-15,30,30);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
        painter->setPen(Qt::black);
        painter->setBrush(Qt::white);

        QPainterPath path1;
        path1.addEllipse(boundingRect());

        painter->drawPath(path1);

        painter->setPen(qRgb(0,0,0));
        QFont font("Courier", 16, QFont::DemiBold);

        QFontMetrics fm(font);
        int textWidth = fm.width(text);

        painter->translate(0, 0);
        painter->drawText(-textWidth/2, 0, text);

    }

};


#endif // DRAWINGOBJECTS_H
