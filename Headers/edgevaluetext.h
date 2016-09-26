#ifndef EDGEVALUETEXT_H
#define EDGEVALUETEXT_H

#include <QGraphicsTextItem>
#include "edge.h"

class EdgeValueText : public QGraphicsTextItem
{
    Q_OBJECT

public:
    /* TODO:
     * implement a mechanism that allows the user to edit the edge value by clicking on the text
     */
    EdgeValueText(Edge *edge);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

public slots:
    void edgeMoved();
    void updateValue();

private:
    Edge *m_edge;
};

#endif // EDGEVALUETEXT_H
