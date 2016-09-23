#include "node.h"

Node::Node(int value)
    :m_value(value)
{
    setFlag(GraphicsItemFlag::ItemIsMovable);
}

QRectF Node::boundingRect() const
{
    qreal penWidth = 1;
    return QRectF(-10 - penWidth/2, -10 - penWidth/2,
                  20 + penWidth, 20 + penWidth);
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    (void)option;
    (void)widget;
    painter->drawEllipse(boundingRect());
    painter->drawText(-3, 4, QString::number(m_value));
}
