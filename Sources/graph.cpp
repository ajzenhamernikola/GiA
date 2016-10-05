#include <iostream>

#include "Headers/graph.h"

// public

Graph::Graph()
{

}

void Graph::addEdge(Edge *e)
{
    int valueFrom = e->nodes().first->value();
    m_adjacentList[valueFrom].push_back(e);


#ifdef _GRAPH_DEBUG_
    auto b1 = m_adjacentList.cbegin();
    auto e1 = m_adjacentList.cend();
    for(; b1 != e1; b1++)
    {
        std::cout << "Node: "
                  << b1.key()
                  << std::endl
                  << "\tEdges: ";
        auto b2 = b1.value().cbegin();
        auto e2 = b1.value().cend();
        for(; b2 != e2; b2++)
        {
            std::cout << (*b2)->nodes().second->value()
                      << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << "=============================" << std::endl;
#endif
}
