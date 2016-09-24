#include "../Headers/edge.h"

// public

Edge::Edge(Node *from, Node *to, int value)
    : m_from(from), m_to(to), m_value(value)
{

}

int Edge::value() const
{
    return m_value;
}

QPair<int, int> Edge::nodes() const
{
    return QPair<int, int>(m_from->value(), m_to->value());
}

void Edge::setValue(int value)
{
    m_value = value;
}
