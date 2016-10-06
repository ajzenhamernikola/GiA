//#define _GRAPH_DEBUG_

#include <iostream>

#include "Headers/graph.h"

// public

Graph::Graph(QGraphicsScene *scene) :
    m_scene(scene)
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

void Graph::loadGraph(const QString &file)
{
    readXml(file);
}

QVector<Node *> Graph::nodes() const
{
    QVector<Node *> nodes;
    for(auto &iter: m_adjacentList)
    {
        nodes.push_back(iter.first);
    }
    return nodes;
}

QVector<Edge *> Graph::edges() const
{
    QVector<Edge *> edges;
    for(auto &iter: m_adjacentList)
    {
        for(auto &iter2: iter.second)
        {
            edges.push_back(iter2);
        }
    }
    return edges;
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

void Graph::readXml(const QString &file)
{
    QFile data(file);
    if(!data.open(QFile::ReadOnly))
    {
        return;
    }

    QXmlStreamReader xml(&data);
    while(!xml.atEnd())
    {
        xml.readNext();
        if(xml.isStartElement())
        {
            if(xml.name() == "Node")
            {
                QXmlStreamAttributes attributes = xml.attributes();

                qreal x, y;
                int value = attributes.value("value").toInt();
                x =         attributes.value("x").toDouble();
                y =         attributes.value("y").toDouble();
                QPointF pos(x, y);

                Node *newNode = new Node(m_scene, value);
                newNode->setPos(pos);
                m_scene->addItem(newNode);
                addNode(newNode);
            }
            else if(xml.name() == "Edge")
            {
                QXmlStreamAttributes attributes = xml.attributes();
                int value, first, second;
                value =  attributes.value("value").toInt();
                first =  attributes.value("first").toInt();
                second = attributes.value("second").toInt();
                Node *from, *to;

                for(auto &iterNode : m_adjacentList)
                {
                    if(iterNode.first->value() == first)
                    {
                        from = iterNode.first;
                    }
                    else if(iterNode.first->value() == second)
                    {
                        to = iterNode.first;
                    }
                    else
                    {}
                }
                Edge *newEdge = EdgeFactory::getEdge(from, to, value);
                m_scene->addItem(newEdge);
                addEdge(newEdge);
            }
            else
            {}
        }
    }

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
