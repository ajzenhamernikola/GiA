#ifndef GRAPH_H
#define GRAPH_H

#include <QMap>
#include <QVector>

#include "Headers/edge.h"

class Graph
{
public:
    Graph();

    void addEdge(Edge *e);

private:
    QMap<int, QVector<Edge *>> m_adjacentList;
};

#endif // GRAPH_H
