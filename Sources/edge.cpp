#include "Headers/edge.h"

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
    m_from->addOutEdge(this);
}

QRectF Edge::boundingRect() const
{
    qreal penWidth = 4 * m_to->radius();
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
    (void)option; (void)widget;

    QLineF edge(m_from->pos(), m_to->pos());
    int len = edge.length();

    Edge *e;
    if ((e = m_to->edgeTo(m_from)) != nullptr)
    {
        setCurved(true);
        e->setCurved(true);
    }

    // Arrowhead dimensions
    qreal h = 0.8 * m_to->radius();
    QPointF tip = edge.pointAt((len - m_to->radius()) / len);


    if (!m_curved)
    {
        qreal angle = -1 * edge.angle();

        painter->setPen(Qt::black);
        painter->drawLine(edge);

        qreal x = 15;
        QPointF t1 = tip - QPointF(
                    qCos(qDegreesToRadians(angle + x)) * h,
                    qSin(qDegreesToRadians(angle + x)) * h);
        QPointF t2 = tip - QPointF(
                    qCos(qDegreesToRadians(angle - x)) * h,
                    qSin(qDegreesToRadians(angle - x)) * h);

        painter->setBrush(Qt::black);
        painter->drawPolygon(QPolygonF() << tip << t1 << t2);
    }
    else
    {
        qreal angle = -1 * edge.normalVector().angle();
        QPointF ctrlPt = edge.pointAt(0.5) + QPointF(
                    qCos(qDegreesToRadians(angle)) * 30,
                    qSin(qDegreesToRadians(angle)) * 30);

        QPainterPath curve(m_from->pos());
        curve.quadTo(ctrlPt, tip);

        painter->setPen(Qt::black);
        painter->drawPath(curve);

        qreal arrowAngle = -1 * QLineF(tip, ctrlPt).angle();
        qreal x = 15;
        QPointF t1 = tip + QPointF(
                    qCos(qDegreesToRadians(arrowAngle + x)) * h,
                    qSin(qDegreesToRadians(arrowAngle + x)) * h);

        QPointF t2 = tip + QPointF(
                    qCos(qDegreesToRadians(arrowAngle - x)) * h,
                    qSin(qDegreesToRadians(arrowAngle - x)) * h);

        painter->setBrush(Qt::black);
        painter->drawPolygon(QPolygonF() << tip << t1 << t2);
    }
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

void Edge::setCurved(bool val)
{
    m_curved = val;
    update();
    emit moved();
}

bool Edge::isCurved() const
{
    return m_curved;
}

QPointF Edge::valueTextAnchor() const
{
    if (!m_curved)
    {
        return QLineF(m_from->pos(), m_to->pos()).pointAt(0.5);
    }
    else
    {
        QLineF edge(m_from->pos(), m_to->pos());
        qreal angle = -1 * edge.normalVector().angle();
        QPointF c = edge.pointAt(0.5) + QPointF(
                    qCos(qDegreesToRadians(angle)) * 15,
                    qSin(qDegreesToRadians(angle)) * 15);
        return c;
    }
}

// public slots

void Edge::nodeMoved()
{
    prepareGeometryChange();
    emit moved();
    update();
}
