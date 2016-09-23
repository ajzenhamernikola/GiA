#include "../Headers/node.h"

// public

Node::Node(int value)
    : m_value(value),
      m_active(false)
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
    QPen pen;
    if(m_active)
    {
        pen.setColor(Qt::red);
    }
    else
    {
        pen.setColor(Qt::black);
    }
    painter->setPen(pen);
    painter->drawEllipse(boundingRect());
    painter->drawText(-3, 4, QString::number(m_value));
}

// protected

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    m_active = !m_active;
    update();
}

void Node::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);
    m_active = false;
    update();
}
