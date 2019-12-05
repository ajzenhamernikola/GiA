#ifndef NODE_H
#define NODE_H

#define NODE_Z_VALUE 1

#include <QGraphicsObject>

class Edge;

class Node : public QGraphicsObject
{
    Q_OBJECT

public:
    explicit Node(int value);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;

    int value() const;
    bool operator== (const Node& other) const;
    bool operator< (const Node& other) const;

    void deactivate();

    void setRadius(qreal x = 10);
    qreal radius() const;

    QVector<Edge *> outgoingEdges() const;
    void addOutEdge(Edge *e);
    Edge *edgeTo(Node *oth);

signals:
    void activated(Node* node);
    void deactivated(Node* node);
    void moved();

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
    int m_value;
    bool m_active;
    qreal m_radius;
    static qreal DEFAULT_RADIUS;

    QVector<Edge *> m_outEdges;
};

#endif // NODE_H
