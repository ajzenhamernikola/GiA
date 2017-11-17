#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include <QInputDialog>

#include "Headers/node.h"
#include "Headers/edge.h"
#include "Headers/graph.h"

namespace Ui {
class MainMenu;
}

class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);
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
