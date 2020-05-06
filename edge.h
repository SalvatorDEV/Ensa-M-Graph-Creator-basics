#ifndef EDGE_H
#define EDGE_H


#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QWidget>
class sommet;

class edge : public QGraphicsItem
{
public:
    edge(sommet *sourceNode, sommet *destNode,int poid);

    sommet *sourceNode() const;
    sommet *destNode() const;
    sommet *source, *dest;

    QPointF sourcePoint;
    QPointF destPoint;
    int poid=10;

    void adjust();


     bool colorier=false;

//   enum { Type = UserType + 2 };
//    int type() const override { return Type; }


protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:

    qreal arrowSize = 10;

};

#endif // EDGE_H
