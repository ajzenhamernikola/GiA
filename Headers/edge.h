#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsObject>
#include <QtGui>
#include <QPair>

#include "../Headers/node.h"

class Edge : public QGraphicsObject
{
public:
    Edge(Node *from, Node *to, int value = 1);

    int value() const;
    QPair<int, int> nodes() const;

    void setValue(int value);

private:
    Node *m_from;
    Node *m_to;
    int m_value;
};

#endif // EDGE_H
