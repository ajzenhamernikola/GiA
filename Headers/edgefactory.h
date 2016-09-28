#ifndef EDGEFACTORY_H
#define EDGEFACTORY_H

#include "../Headers/node.h"
#include "../Headers/edge.h"

class EdgeFactory
{
public:
    EdgeFactory();
    static Edge *getEdge(Node *from, Node *to, int weight = 1);
};

#endif // EDGEFACTORY_H
