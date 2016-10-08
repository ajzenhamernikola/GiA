#include "../Headers/mainmenu.h"
#include "../Headers/edgevaluetext.h"
#include "ui_mainmenu.h"

// public

int numberOfActiveNodes = 0;
Node *first = 0;
Node *second = 0;

MainMenu::MainMenu(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::MainMenu)
{
    m_ui->setupUi(this);

    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);

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
    Node* newNode = new Node(m_scene, value);
    QObject::connect(newNode, SIGNAL(activated(Node*)),   this, SLOT(nodeActivated(Node*)));
    QObject::connect(newNode, SIGNAL(deactivated(Node*)), this, SLOT(nodeDeactivated(Node*)));
    m_nodes.push_back(newNode);

    // Assuming that user won't create more than 9999 nodes
    switch (m_nodes.size())
    {
    case 10:
        enlargeAllNodes(20);
        break;
    case 100:
        enlargeAllNodes(30);
        break;
    case 1000:
        enlargeAllNodes(40);
        break;
    }

    m_scene->addItem(newNode);
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

        Edge *newEdge;
        if(m_ui->cb_weighted->isChecked())
        {
            int weight = QInputDialog::getInt(this, QString("Enter weight"), QString("Weight"));;
            newEdge = new Edge(first, second, weight);

        }
        else
        {
            newEdge = new Edge(first, second);
        }

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

void MainMenu::enlargeAllNodes(qreal size)
{
    for (auto& node : m_nodes)
        node->setRadius(size);
}

void MainMenu::on_pb_new_clicked()
{
    m_scene->clear();

    if(!m_edges.empty())
    {
        m_edges.clear();
    }

    if(!m_nodes.empty())
    {
        m_nodes.clear();
    }

    first = second = 0;
    numberOfActiveNodes = 0;
}
