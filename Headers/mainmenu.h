#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QVector>
#include <QInputDialog>
#include <QFileDialog>
#include <QStandardPaths>
#include <QImage>
#include <QPainter>

#include "Headers/node.h"
#include "Headers/edge.h"
#include "Headers/edgevaluetext.h"
#include "Headers/edgefactory.h"
#include "Headers/graph.h"

namespace Ui {
class MainMenu;
}

class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = 0);
    ~MainMenu();

private slots:
    void nodeActivated(Node *node);
    void nodeDeactivated(Node *node);

    void addNode();
    void newGraph();
    void saveGraph();
    void loadGraph();
    void exportImage();

private:
    Ui::MainMenu *m_ui;
    QGraphicsScene *m_scene;
    QVector<Node*> m_nodes;
    QVector<Edge*> m_edges;
    Graph *m_graph;

    void enlargeAllNodes(qreal size);
};

#endif // MAINMENU_H
