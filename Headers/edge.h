#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsObject>
#include <QtGui>
#include <QPair>

#include "../Headers/node.h"

class Edge : public QGraphicsObject
{
public:
    explicit Edge(Node *from, Node *to, int value = 1);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

    int value() const;
    QPair<int, int> nodes() const;

    void setValue(int value);

private:
    Node *m_from;
    Node *m_to;
    int m_value;
};

#endif // EDGE_H
