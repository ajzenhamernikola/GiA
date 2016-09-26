#include "Headers/edgevaluetext.h"

EdgeValueText::EdgeValueText(Edge *edge)
    : QGraphicsTextItem(QString::number(edge->value()), edge),
      m_edge(edge)
{
    QObject::connect(edge, SIGNAL(moved()), this, SLOT(edgeMoved()));
    QObject::connect(edge, SIGNAL(valueChanged()), this, SLOT(updateValue()));
    setFlag(QGraphicsItem::ItemIsSelectable);
    edgeMoved();
}

QRectF EdgeValueText::boundingRect() const
{
    return QGraphicsTextItem::boundingRect();
}

void EdgeValueText::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsTextItem::paint(painter, option, widget);
}

void EdgeValueText::edgeMoved()
{
    setPos(m_edge->boundingRect().center());
    qreal angle = QLineF(m_edge->nodes().first->pos(),
                              m_edge->nodes().second->pos()).angle();
    if ((angle > 90 && angle <= 180) || (angle > 270 && angle <= 360))
    {
        moveBy(0, -boundingRect().height());
    }
}

void EdgeValueText::updateValue()
{
    setPlainText(QString::number(m_edge->value()));
}
