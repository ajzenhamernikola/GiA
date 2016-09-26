#include "../Headers/edge.h"

// public

Edge::Edge(Node *from, Node *to, int value)
    : m_from(from), m_to(to), m_value(value)
{
    setZValue(EDGE_Z_VALUE);
}

QRectF Edge::boundingRect() const
{
    qreal penWidth = 1;
    qreal left, top, right, bottom;
    if(m_from->pos().x() < m_to->pos().x())
    {
        left = m_from->pos().x();
        right = m_to->pos().x();
    }
    else
    {
        left = m_to->pos().x();
        right = m_from->pos().x();
    }
    if(m_from->pos().y() < m_to->pos().y())
    {
        top = m_from->pos().y();
        bottom = m_to->pos().y();
    }
    else
    {
        top = m_to->pos().y();
        bottom = m_from->pos().y();
    }
    return QRectF(left - penWidth/2, top - penWidth/2, right - left + penWidth, bottom - top + penWidth);
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    (void)option;
    (void)widget;
    painter->setPen(Qt::black);
    painter->drawLine(m_from->pos(), m_to->pos());
}

int Edge::value() const
{
    return m_value;
}

QPair<int, int> Edge::nodes() const
{
    return QPair<int, int>(m_from->value(), m_to->value());
}

QPair<Node *, Node *> Edge::realNodes() const
{
    return QPair<Node *, Node *>(m_from, m_to);
}

void Edge::setValue(int value)
{
    m_value = value;
    emit valueChanged();
}

// public slots

void Edge::nodeMoved()
{
    prepareGeometryChange();
    emit moved();
    update();
}
