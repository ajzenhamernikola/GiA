#ifndef NODE_H
#define NODE_H

#include <QGraphicsObject>
#include <QtGui>

class Node : public QGraphicsObject
{
    Q_OBJECT

public:
    explicit Node(int value);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

    int value() const;
    bool operator==(const Node& other) const;

    void deactivate();

signals:
    void activated(Node* node);
    void deactivated(Node* node);
    void moved();

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

private:
    int m_value;
    bool m_active;
};

#endif // NODE_H
