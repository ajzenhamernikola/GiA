#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsObject>
#include <QGraphicsScene>
#include <QtGui>
#include <QPair>

#include "Headers/node.h"
#include "Headers/edgevaluetext.h"

#define EDGE_Z_VALUE -1

// Forward declaration
class EdgeValueText;
class Node;

// TODO: think of a better name
extern const qreal RATIO;

class Edge : public QGraphicsObject
{
    Q_OBJECT

public:
    explicit Edge(Node *from, Node *to, int value = 1);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

    int value() const;
    QPair<int, int> nodeValues() const;

    QPair<Node *, Node *> nodes() const;

    void setValue(int value);

    EdgeValueText *evt() const;
    void setEvt(EdgeValueText *evt);

    void setCurved(bool val);
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
