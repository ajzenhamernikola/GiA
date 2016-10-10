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

    QObject::connect(m_ui->aNewGraph,    SIGNAL(triggered()), this, SLOT(newGraph()));
    QObject::connect(m_ui->aSaveGraph,   SIGNAL(triggered()), this, SLOT(saveGraph()));
    QObject::connect(m_ui->aLoadGraph,   SIGNAL(triggered()), this, SLOT(loadGraph()));
    QObject::connect(m_ui->aExportImage, SIGNAL(triggered()), this, SLOT(exportImage()));
    QObject::connect(m_ui->aExit,        SIGNAL(triggered()), this, SLOT(close()));
    QObject::connect(m_ui->aAddNode,     SIGNAL(triggered()), this, SLOT(addNode()));
}

MainMenu::~MainMenu()
{
    delete m_ui;
    delete m_scene;
    delete m_graph;
}

// private slots

void MainMenu::addNode()
{
    int value = m_graph->numberOfNodes() + 1;
    Node* newNode = new Node(m_scene, value);
    QObject::connect(newNode, SIGNAL(activated(Node*)),   this, SLOT(nodeActivated(Node*)));
    QObject::connect(newNode, SIGNAL(deactivated(Node*)), this, SLOT(nodeDeactivated(Node*)));

    m_scene->addItem(newNode);
    m_graph->addNode(newNode);

    resizeAllNodes();
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
        newEdge = new Edge(first, second);

        m_scene->addItem(newEdge);
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

void MainMenu::newGraph()
{
    m_scene->clear();
    m_ui->gv_graph->viewport()->update();

    delete m_graph;
    m_graph = new Graph(m_scene);

    first = second = 0;
    numberOfActiveNodes = 0;

    resizeAllNodes();
}

void MainMenu::saveGraph()
{
    QString file = QFileDialog::getSaveFileName(this, tr("Save graph to a file"), QStandardPaths::writableLocation(QStandardPaths::DesktopLocation), tr("XML files (*.xml)"));
    if(m_graph && !file.isNull())
    {
        if(file.endsWith(QString(".xml")))
        {
            m_graph->saveGraph(file);
        }
        else
        {
            m_graph->saveGraph(file + QString(".xml"));
        }
    }
}

void MainMenu::loadGraph()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Load graph from a file"), QStandardPaths::writableLocation(QStandardPaths::DesktopLocation), tr("XML files (*.xml)"));
    if(!file.isNull())
    {
        newGraph();
        if(file.endsWith(QString(".xml")))
        {
            m_graph->loadGraph(file);
        }
        else
        {
            m_graph->loadGraph(file + QString(".xml"));
        }
    }

    auto nodes = m_graph->nodes();

    for(auto &iter : nodes)
    {
        QObject::connect(iter, SIGNAL(activated(Node*)),   this, SLOT(nodeActivated(Node*)));
        QObject::connect(iter, SIGNAL(deactivated(Node*)), this, SLOT(nodeDeactivated(Node*)));
    }

    resizeAllNodes();
}

void MainMenu::exportImage()
{
    QString file = QFileDialog::getSaveFileName(this, tr("Save graph to an image"), QStandardPaths::writableLocation(QStandardPaths::DesktopLocation), tr("PNG files (*.png);;JPEG files (*.jpeg);;BMP files (*.bmp)"));
    if(!file.isNull())
    {
        if(!file.endsWith(QString(".png"), Qt::CaseInsensitive) && !file.endsWith(QString(".JPEG"), Qt::CaseInsensitive) && !file.endsWith(QString(".bmp"), Qt::CaseInsensitive))
        {
            file.append(QString(".png"));
        }

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

// private

void MainMenu::resizeAllNodes()
{
    int num = m_graph->numberOfNodes();
    // Assuming that user won't create more than 9999 nodes
    if(num >= 1000)
    {
        enlargeAllNodes(25);
    }
    else if(num >= 100)
    {
        enlargeAllNodes(20);
    }
    else if(num >= 10)
    {
        enlargeAllNodes(15);
    }
    else
    {
        enlargeAllNodes(10);
    }
}

void MainMenu::enlargeAllNodes(qreal size)
{
    auto nodes = m_graph->nodes();
    for (auto &node : nodes)
        node->setRadius(size);
}
