#include <QPainter>
#include <QtMath>
#include "Headers/edge.h"
#include "Headers/node.h"
#include "Headers/edgevaluetext.h"

// public

Edge::Edge(Node *from, Node *to, const int value)
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
	const qreal penWidth = 4 * m_to->radius();
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
    const int len = static_cast<int>(edge.length());

	Edge *e;
	if ((e = m_to->edgeTo(m_from)) != nullptr)
	{
		setCurved(true);
		e->setCurved(true);
	}

	// Arrowhead dimensions
	const qreal h = 0.8 * m_to->radius();
	const QPointF tip = edge.pointAt((len - m_to->radius()) / len);

	if (!m_curved)
	{
		const qreal angle = -1 * edge.angle();

		painter->setPen(Qt::black);
		painter->drawLine(edge);

		const qreal x = 15;
		const QPointF t1 = tip - QPointF(
					qCos(qDegreesToRadians(angle + x)) * h,
					qSin(qDegreesToRadians(angle + x)) * h);
		const QPointF t2 = tip - QPointF(
					qCos(qDegreesToRadians(angle - x)) * h,
					qSin(qDegreesToRadians(angle - x)) * h);

		painter->setBrush(Qt::black);
		painter->drawPolygon(QPolygonF() << tip << t1 << t2);
	}
	else
	{
		const qreal angle = -1 * edge.normalVector().angle();
		const QPointF ctrlPt = edge.pointAt(0.5) + QPointF(
					qCos(qDegreesToRadians(angle)) * 30,
					qSin(qDegreesToRadians(angle)) * 30);

		QPainterPath curve(m_from->pos());
		curve.quadTo(ctrlPt, tip);

		painter->setPen(Qt::black);
		painter->drawPath(curve);

		const qreal arrowAngle = -1 * QLineF(tip, ctrlPt).angle();
		const qreal x = 15;
		const QPointF t1 = tip + QPointF(
					qCos(qDegreesToRadians(arrowAngle + x)) * h,
					qSin(qDegreesToRadians(arrowAngle + x)) * h);

		const QPointF t2 = tip + QPointF(
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

void Edge::setValue(const int value)
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

void Edge::setCurved(const bool val)
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
		const qreal angle = -1 * edge.normalVector().angle();
		const QPointF c = edge.pointAt(0.5) + QPointF(
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
