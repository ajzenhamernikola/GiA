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
    void resizeAllNodes();
    void enlargeAllNodes(qreal size);

    Ui::MainMenu *m_ui;
    QGraphicsScene *m_scene;
    Graph *m_graph;
};

#endif // MAINMENU_H
