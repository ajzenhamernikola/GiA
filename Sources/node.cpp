#include "Headers/node.h"

#include <QPainter>
#include <QPen>

#include <Headers/edge.h>

qreal Node::DEFAULT_RADIUS = 10;
// public

Node::Node(int value)
    : m_value(value),
      m_active(false),
      m_radius(DEFAULT_RADIUS),
      m_outEdges()
{
    setFlag(GraphicsItemFlag::ItemIsMovable);
    setZValue(NODE_Z_VALUE);
}

QRectF Node::boundingRect() const
{
    qreal penWidth = 1;
    return QRectF(-m_radius - penWidth/2, -m_radius - penWidth/2,
                  2 * m_radius + penWidth, 2 * m_radius + penWidth);
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
    painter->setBrush(Qt::white);

    QString s = QString::number(m_value);
    int w = painter->fontMetrics().width(s);
    int h = painter->fontMetrics().height();

    painter->drawEllipse(boundingRect());
    painter->drawText(-(w / 2), h / 3, QString::number(m_value));
}

int Node::value() const
{
    return m_value;
}

bool Node::operator== (const Node& other) const
{
    return value() == other.value();
}

bool Node::operator < (const Node& other) const
{
    return m_value < other.value();
}

void Node::deactivate()
{
    m_active = false;
    update();
}

void Node::setRadius(qreal x)
{
    prepareGeometryChange();
    m_radius = x;
    DEFAULT_RADIUS = x;
    update();
}

qreal Node::radius() const
{
    return m_radius;
}

QVector<Edge *> Node::outgoingEdges() const
{
    return m_outEdges;
}

void Node::addOutEdge(Edge *e)
{
    m_outEdges.push_back(e);
}

Edge *Node::edgeTo(Node *oth)
{
    if (!oth)
        return nullptr;

    for (Edge *e : m_outEdges)
        if (*(e->nodes().second) == *oth)
            return e;
    return nullptr;
}

// protected

void Node::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mouseMoveEvent(event);
    emit this->moved();
}

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
