#ifndef SOMMET_H
#define SOMMET_H
#include <QGraphicsObject>
#include <QMouseEvent>
#include<MainWindow.h>
class edge;
class MainWindow;
class sommet: public QGraphicsObject
{
     Q_OBJECT
signals:

public:
    friend class MainWindow;

        void addEdge(edge *edge);
        QVector<edge *> Edges() const;
    sommet(int valeur);
    int number;
    //int counter;

   // enum { Type = UserType + 1 };
    //int type() const override { return Type; }
   // bool advancePosition();

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;


protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:

    QVector<edge *> edgeList;
    QPointF newPos;

};

#endif // SOMMET_H
