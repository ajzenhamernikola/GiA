#include "../Headers/mainmenu.h"
#include "ui_mainmenu.h"

#include <iostream>

// public

int numberOfActiveNodes = 0;
Node *first = 0;
Node *second = 0;

MainMenu::MainMenu(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::MainMenu)
{
    m_ui->setupUi(this);

    m_scene = new QGraphicsScene();
    m_ui->gv_graph->setScene(m_scene);
    m_ui->gv_graph->setRenderHint(QPainter::Antialiasing);
    m_ui->gv_graph->setRenderHint(QPainter::HighQualityAntialiasing);
}

MainMenu::~MainMenu()
{
    delete m_ui;
    delete m_scene;
}

// private slots

void MainMenu::on_pb_addNode_clicked()
{
    int value = m_nodes.size() + 1;
    Node* newNode = new Node(value);
    QObject::connect(newNode, SIGNAL(activated(Node*)),   this, SLOT(nodeActivated(Node*)));
    QObject::connect(newNode, SIGNAL(deactivated(Node*)), this, SLOT(nodeDeactivated(Node*)));
    m_scene->addItem(newNode);
    m_nodes.push_back(newNode);
}

void MainMenu::nodeActivated(Node *node)
{
    if(!numberOfActiveNodes)
    {
        first = node;
        numberOfActiveNodes++;
    }
    else
    {
        second = node;
        numberOfActiveNodes++;
        Edge *newEdge = new Edge(first, second);
        QObject::connect(first,  SIGNAL(xChanged()), newEdge, SLOT(nodeMoved()));
        QObject::connect(first,  SIGNAL(yChanged()), newEdge, SLOT(nodeMoved()));
        QObject::connect(second, SIGNAL(xChanged()), newEdge, SLOT(nodeMoved()));
        QObject::connect(second, SIGNAL(yChanged()), newEdge, SLOT(nodeMoved()));
        m_scene->addItem(newEdge);
        m_edges.push_back(newEdge);
        first->deactivate();
        second->deactivate();
        first = second = 0;
        numberOfActiveNodes = 0;
    }
}

void MainMenu::nodeDeactivated(Node *node)
{
    if(*first == *node)
    {
        first = second;
    }
    second = 0;
    numberOfActiveNodes--;
}
