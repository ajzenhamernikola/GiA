//#define _GRAPH_DEBUG_

#include <iostream>

#include "Headers/graph.h"

// public

Graph::Graph()
{

}

void Graph::addEdge(Edge *e)
{
    Node *key = e->nodes().first;
    m_adjacentList[key].push_back(e);
    #ifdef _GRAPH_DEBUG_
    AppDebug();
    #endif
}

void Graph::addNode(Node *n)
{
    m_adjacentList[n] = QVector<Edge *>();
    #ifdef _GRAPH_DEBUG_
    AppDebug();
    #endif
}

void Graph::saveGraph(const QString &file)
{
    writeXml(file);
}

// private

void Graph::writeXml(const QString &file)
{
    QFile data(file);
    if(!data.open(QFile::WriteOnly | QFile::Truncate))
    {
        return;
    }

    QXmlStreamWriter xml(&data);
    xml.setAutoFormatting(true);

    xml.writeStartDocument();
    xml.writeStartElement("Graph");

    for(auto &iter : m_adjacentList)
    {
        xml.writeStartElement("Node");

        xml.writeAttribute("value", QString::number(iter.first->value()));
        xml.writeAttribute("x",     QString::number(iter.first->pos().x()));
        xml.writeAttribute("y",     QString::number(iter.first->pos().y()));

        xml.writeEndElement();
    }

    for(auto &iter : m_adjacentList)
    {
        for(auto &iter2 : iter.second)
        {
            xml.writeStartElement("Edge");

            xml.writeAttribute("value",  QString::number(iter2->value()));
            xml.writeAttribute("first",  QString::number(iter2->nodes().first->value()));
            xml.writeAttribute("second", QString::number(iter2->nodes().second->value()));

            xml.writeEndElement();
        }
    }

    xml.writeEndElement();
    xml.writeEndDocument();

    data.close();
}

void Graph::AppDebug()
{
    for(auto &iter : m_adjacentList)
    {
        std::cout << "Node: "
                  << iter.first->value()
                  << std::endl
                  << "\t Edges: ";
        for(auto &iter2 : iter.second)
        {
            std::cout << iter2->nodes().second->value()
                      << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << "=============================" << std::endl;
}
