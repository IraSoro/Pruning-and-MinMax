#ifndef DRAWINGOBJECTS_H
#define DRAWINGOBJECTS_H
#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>

#include "Tree.h"

class DrawingObjects : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit DrawingObjects(){}
    ~DrawingObjects(){}

    QString text = "";
    int CoordsLine[4] = {0,0,0,0};
    int Color = 0;

    QRectF boundingRect() const{
        return QRectF (-15,-15,30,30);
    }

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
            painter->setPen(Qt::black);
            switch(Color){
                case 0:
                    painter->setBrush(Qt::white);
                    break;
                case 1:
                    painter->setBrush(Qt::green);
                    break;
                case 2:
                    painter->setBrush(Qt::red);
                    break;
                case 3:
                    painter->setBrush(Qt::blue);
                    break;
                case 4:
                    painter->setBrush(Qt::yellow);
                    break;
                default:
                    painter->setBrush(Qt::white);
                    break;

            }

            painter->drawLine(CoordsLine[0], CoordsLine[1], CoordsLine[2], CoordsLine[3]);

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
