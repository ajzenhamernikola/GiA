#ifndef EDGEVALUETEXT_H
#define EDGEVALUETEXT_H

#include "Headers/edge.h"

// Forward declaration
class Edge;

class EdgeValueText : public QGraphicsTextItem
{
    Q_OBJECT

public:
    EdgeValueText(Edge *edge);

protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
    virtual QRectF boundingRect() const;
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void focusOutEvent(QFocusEvent *e);

public slots:
    void edgeMoved();
    void updateValue();

private:
    Edge *m_edge;
};

#endif // EDGEVALUETEXT_H
