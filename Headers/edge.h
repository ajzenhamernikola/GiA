#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsObject>
#include <QGraphicsScene>
#include <QtGui>
#include <QPair>

#include "node.h"

#define EDGE_Z_VALUE -1

class Edge : public QGraphicsObject
{
    Q_OBJECT

public:
    explicit Edge(QGraphicsScene *parent, Node *from, Node *to, int value = 1);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

    int value() const;
    QPair<int, int> nodeValues() const;

    QPair<Node *, Node *> nodes() const;

    void setValue(int value);

public slots:
    void nodeMoved();

signals:
    void moved();
    void valueChanged();

private:
    QGraphicsScene *m_parent;
    Node *m_from;
    Node *m_to;
    int m_value;
};

#endif // EDGE_H
