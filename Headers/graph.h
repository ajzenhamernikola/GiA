#ifndef GRAPH_H
#define GRAPH_H

#include <map>

#include <QVector>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#include "Headers/node.h"
#include "Headers/edge.h"

class Graph
{
public:
    Graph();

    void addEdge(Edge *e);
    void addNode(Node *n);
    void saveGraph(const QString &file);

private:
    class nodeComparator
    {
    public:
        bool operator() (Node *left, Node *right) const
        {
            return left->value() < right->value();
        }
    };

    void writeXml(const QString &file);
    void AppDebug();

    std::map<Node *, QVector<Edge *>, nodeComparator> m_adjacentList;
};

#endif // GRAPH_H
