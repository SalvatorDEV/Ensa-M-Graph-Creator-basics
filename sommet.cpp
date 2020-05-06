#include "edge.h"
#include "sommet.h"
#include "MainWindow.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QWidget>

//! [0]
//static int counter=0;

sommet::sommet(int valeur):number()

{
    this->number=valeur;

    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
     update();
}
//! [0]

//! [1]
void sommet::addEdge(edge *edge)
{
    edgeList << edge;
     edge->adjust();
}

QVector<edge *> sommet::Edges() const
{
    return edgeList;
}
//! [1]

//! [2]

/*bool sommet::advancePosition()
{
    if (newPos == pos())
        return false;

    setPos(newPos);
    return true;
}*/
//! [7]

//! [8]

QRectF sommet::boundingRect() const
{
    qreal adjust = 2;
    return QRectF( -10 - adjust, -10 - adjust, 23 + adjust, 23 + adjust);
}

QPainterPath sommet::shape() const
{
    QPainterPath path;
    path.addEllipse(-10, -10, 20, 20);
    return path;
}

void sommet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    painter->setRenderHint(QPainter::Antialiasing,true);

    painter->setPen(Qt::NoPen);

    painter->setBrush(Qt::yellow);

    painter->drawEllipse(-10, -10, 20, 20);
    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-10, -10, 20, 20);
     painter->drawText(-3, 3, QString::number(number));
}

QVariant sommet::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        for (edge *edge : qAsConst(edgeList))
            edge->adjust();
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}
QVector<sommet*> liaison;
// une autre methode d'ajout d'arrete entre deux sommet  !!ça sera peut etre plus mieux d'utiliser dans cette methode les signals et les slots!!
void sommet::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
    //ajouter une coloration

    if(liaison.size()<2){
    liaison.push_back(this);}
    if(liaison.size()==2){

        edge* newOne = new edge(liaison[0],liaison[1],10);// ajouter une input dialog pour le poid car ici ça sera toujours 10
        scene()->addItem(newOne);
        liaison.clear();
        //acceder a la liste edge dans le mainWindow pour ajouter l'arete dans listeEdge ??


    }

}
