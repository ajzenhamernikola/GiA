#ifndef GRAPH_H
#define GRAPH_H

#include <map>

#include "Headers/node.h"
#include "Headers/edge.h"

class Graph
{
public:
    Graph(QGraphicsScene *scene);

    void addNode(Node *n);
    void addEdge(Edge *e);
    void saveGraph(const QString &file);
    void loadGraph(const QString &file);
    QVector<Node *> nodes() const;
    QVector<Edge *> edges() const;
    int numberOfNodes() const;

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
    void readXml(const QString &file);
    void AppDebug();

    QGraphicsScene *m_scene;
    std::map<Node *, QVector<Edge *>, nodeComparator> m_adjacentList;
};

#endif // GRAPH_H
