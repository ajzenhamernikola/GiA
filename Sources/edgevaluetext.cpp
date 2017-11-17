#include "Headers/edgevaluetext.h"

#include <QStyleOptionGraphicsItem>

EdgeValueText::EdgeValueText(Edge *edge)
    : QGraphicsTextItem(QString::number(edge->value()), edge),
      m_edge(edge)
{
    QObject::connect(edge, SIGNAL(moved()), this, SLOT(edgeMoved()));
    QObject::connect(edge, SIGNAL(valueChanged()), this, SLOT(updateValue()));
    setFlag(QGraphicsItem::ItemIsFocusable);
    setTextInteractionFlags(Qt::TextEditorInteraction);
    edgeMoved();
}

void EdgeValueText::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsTextItem::paint(painter, option, widget);
}

QRectF EdgeValueText::boundingRect() const
{
    return QGraphicsTextItem::boundingRect();
}

void EdgeValueText::keyPressEvent(QKeyEvent *e)
{
    if (hasFocus())
    {
        switch (e->key())
        {
        case Qt::Key_Return:
        case Qt::Key_Escape:
            clearFocus();
        case Qt::Key_Space:
            return;
        default:
            QGraphicsTextItem::keyPressEvent(e);
        }
    }
}

void EdgeValueText::focusOutEvent(QFocusEvent *e)
{
    QString s = toPlainText().trimmed();
    if (s.size() == 0)
    {
        m_edge->setValue(1);
    }
    else
    {
        bool ok;
        int val = s.toInt(&ok);
        if (ok)
            m_edge->setValue(val);
        else
            m_edge->setValue(m_edge->value());
    }
    QGraphicsTextItem::focusOutEvent(e);
}

void EdgeValueText::edgeMoved()
{
    setPos(m_edge->valueTextAnchor());
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
