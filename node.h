#ifndef NODE_H
#define NODE_H

#include <QtGui>
#include <QtCore>
#include <QGraphicsItem>

class Node : public QGraphicsItem
{
public:
    explicit Node(int value);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

private:
    int m_value;
};

#endif // NODE_H
