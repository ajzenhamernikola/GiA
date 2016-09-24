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

int Node::value() const
{
    return m_value;
}

bool Node::operator==(const Node& other) const
{
    return value() == other.value();
}

void Node::deactivate()
{
    m_active = false;
    update();
}

// protected

void Node::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mouseDoubleClickEvent(event);
    m_active = !m_active;
    update();

    if(m_active)
    {
        emit this->activated(this);
    }
    else
    {
        emit this->deactivated(this);
    }
}
