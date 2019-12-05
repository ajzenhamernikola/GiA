#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>

class QGraphicsScene;
class Graph;
class Node;

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
