#include "Headers/edgefactory.h"

EdgeFactory::EdgeFactory()
{

}

Edge *EdgeFactory::getEdge(Node *from, Node *to, int weight)
{
    Edge *newEdge = new Edge(from, to, weight);

    QObject::connect(from,  SIGNAL(xChanged()), newEdge, SLOT(nodeMoved()));
    QObject::connect(from,  SIGNAL(yChanged()), newEdge, SLOT(nodeMoved()));
    QObject::connect(to,    SIGNAL(xChanged()), newEdge, SLOT(nodeMoved()));
    QObject::connect(to,    SIGNAL(yChanged()), newEdge, SLOT(nodeMoved()));

    return newEdge;
}
