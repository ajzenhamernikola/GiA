#ifndef EDGE_H
#define EDGE_H

#include <QtGui>
#include <QPair>

#include "Headers/node.h"
#include "Headers/edgevaluetext.h"

#define EDGE_Z_VALUE -1

// Forward declaration
class EdgeValueText;
class Node;

class Edge : public QGraphicsObject
{
    Q_OBJECT

public:
    explicit Edge(Node *from, Node *to, const int value = 1);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

    int value() const;
    QPair<int, int> nodeValues() const;

    QPair<Node *, Node *> nodes() const;

    void setValue(const int value);

    EdgeValueText *evt() const;
    void setEvt(EdgeValueText *evt);

    void setCurved(const bool val);
    bool isCurved() const;

    QPointF valueTextAnchor() const;

public slots:
    void nodeMoved();

signals:
    void moved();
    void valueChanged();

private:
    Node *m_from;
    Node *m_to;
    int m_value;
    EdgeValueText *m_evt;

    bool m_curved;
};

#endif // EDGE_H
