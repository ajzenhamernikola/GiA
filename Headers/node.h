#ifndef NODE_H
#define NODE_H

#include <QGraphicsObject>
#include <QGraphicsScene>
#include <QtGui>

#define NODE_Z_VALUE 1

class Node : public QGraphicsObject
{
    Q_OBJECT

public:
    explicit Node(QGraphicsScene *parent, int value);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

    int value() const;
    bool operator== (const Node& other) const;
    bool operator< (const Node& other) const;

    void deactivate();

    void setRadius(qreal x);
    qreal radius() const;

signals:
    void activated(Node* node);
    void deactivated(Node* node);
    void moved();

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

private:
    QGraphicsScene *m_parent;
    int m_value;
    bool m_active;
    qreal m_radius;
    static qreal DEFAULT_RADIUS;
};

#endif // NODE_H
