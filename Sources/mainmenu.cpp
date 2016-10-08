#include "../Headers/mainmenu.h"
#include "../Headers/edgevaluetext.h"
#include "ui_mainmenu.h"

// public

int numberOfActiveNodes = 0;
Node *first = 0;
Node *second = 0;

MainMenu::MainMenu(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainMenu)
{
    m_ui->setupUi(this);

    m_scene = new QGraphicsScene();
    m_ui->gv_graph->setScene(m_scene);
    m_ui->gv_graph->setRenderHint(QPainter::Antialiasing);
    m_ui->gv_graph->setRenderHint(QPainter::HighQualityAntialiasing);

    m_graph = new Graph(m_scene);

    QObject::connect(m_ui->aNewGraph,    SIGNAL(triggered()), this, SLOT(on_pb_new_clicked()));
    QObject::connect(m_ui->aSaveGraph,   SIGNAL(triggered()), this, SLOT(on_pb_save_clicked()));
    QObject::connect(m_ui->aLoadGraph,   SIGNAL(triggered()), this, SLOT(on_pb_load_clicked()));
    QObject::connect(m_ui->aExportImage, SIGNAL(triggered()), this, SLOT(exportImage()));
    QObject::connect(m_ui->aExit,        SIGNAL(triggered()), this, SLOT(close()));
}

MainMenu::~MainMenu()
{
    delete m_ui;
    delete m_scene;
    delete m_graph;
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

        m_graph->addEdge(newEdge);

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

    delete m_graph;
    m_graph = new Graph(m_scene);

    first = second = 0;
    numberOfActiveNodes = 0;
}

void MainMenu::on_pb_save_clicked()
{
    QString file = QFileDialog::getSaveFileName(this, tr("Save graph to a file"), QStandardPaths::writableLocation(QStandardPaths::DesktopLocation), tr("XML files (*.xml)"));
    if(m_graph && !file.isNull())
    {
        m_graph->saveGraph(file);
    }
}

void MainMenu::on_pb_load_clicked()
{
    on_pb_new_clicked();

    QString file = QFileDialog::getOpenFileName(this, tr("Load graph from a file"), QStandardPaths::writableLocation(QStandardPaths::DesktopLocation), tr("XML files (*.xml)"));
    if(!file.isNull())
    {
        m_graph->loadGraph(file);
    }

    m_nodes = m_graph->nodes();
    m_edges = m_graph->edges();

    for(auto &iter : m_nodes)
    {
        QObject::connect(iter, SIGNAL(activated(Node*)),   this, SLOT(nodeActivated(Node*)));
        QObject::connect(iter, SIGNAL(deactivated(Node*)), this, SLOT(nodeDeactivated(Node*)));
    }
}

void MainMenu::exportImage()
{
    QString file = QFileDialog::getSaveFileName(this, tr("Save graph to an image"), QStandardPaths::writableLocation(QStandardPaths::DesktopLocation), tr("PNG files (*.png);;JPEG files (*.JPEG);;BMP files (*.bmp)"));
    if(!file.isNull())
    {
        m_scene->clearSelection();
        QRectF rectf(m_scene->itemsBoundingRect());
        rectf.adjust(-10, -10, 10, 10);
        QPixmap pixmap(rectf.size().toSize());
        pixmap.fill(Qt::white);

        QPainter painter(&pixmap);
        painter.setRenderHint(QPainter::Antialiasing);
        m_scene->render(&painter, pixmap.rect(), rectf);
        pixmap.save(file);
    }
}
