#include "../Headers/edge.h"

const qreal RATIO = 0.6;
// public

Edge::Edge(Node *from, Node *to, int value)
    : m_from(from), m_to(to), m_value(value)
{
    setZValue(EDGE_Z_VALUE);

    QObject::connect(from,  SIGNAL(xChanged()), this, SLOT(nodeMoved()));
    QObject::connect(from,  SIGNAL(yChanged()), this, SLOT(nodeMoved()));
    QObject::connect(to,    SIGNAL(xChanged()), this, SLOT(nodeMoved()));
    QObject::connect(to,    SIGNAL(yChanged()), this, SLOT(nodeMoved()));

    m_evt = new EdgeValueText(this);
}

QRectF Edge::boundingRect() const
{
    qreal penWidth = m_to->radius();
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
    { top = m_from->pos().y();
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
    QLineF edge(m_from->pos(), m_to->pos());
    painter->setPen(Qt::black);
    painter->drawLine(edge);
    //painter->drawRect(boundingRect());

    // Arrowhead dimensions
    qreal h = m_to->radius();
    qreal w = h * RATIO;
    int edgeLen = edge.length();

    // Point where the edge intersects with the node (tip of the arrow)
    QPointF tip = edge.pointAt((edgeLen - h) / edgeLen);

    // Point where arrowhead base will intersect the edge
    QPointF baseMid = edge.pointAt((edgeLen - 2 * h) / edgeLen);

    // Angle between the base of the arrowhead and the edge
    qreal angle = -1 * edge.normalVector().angle();

    // Determine base points of arrowhead using trigonometry
    QPointF bLeft(baseMid.x() + qCos(qDegreesToRadians(angle)) * (w / 2),
                  baseMid.y() + qSin(qDegreesToRadians(angle)) * (w / 2));
    QPointF bRight(baseMid.x() + qCos(qDegreesToRadians(angle)) * -(w / 2),
                  baseMid.y() + qSin(qDegreesToRadians(angle)) * -(w / 2));

    QVector<QPoint> pts{tip.toPoint(), bLeft.toPoint(), bRight.toPoint()};
    painter->setBrush(Qt::black);
    painter->drawPolygon(pts);
}

int Edge::value() const
{
    return m_value;
}

QPair<int, int> Edge::nodeValues() const
{
    return QPair<int, int>(m_from->value(), m_to->value());
}

QPair<Node *, Node *> Edge::nodes() const
{
    return QPair<Node *, Node *>(m_from, m_to);
}

void Edge::setValue(int value)
{
    m_value = value;
    emit valueChanged();
}

EdgeValueText *Edge::evt() const
{
    return m_evt;
}

void Edge::setEvt(EdgeValueText *evt)
{
    m_evt = evt;
}

// public slots

void Edge::nodeMoved()
{
    prepareGeometryChange();
    emit moved();
    update();
}
