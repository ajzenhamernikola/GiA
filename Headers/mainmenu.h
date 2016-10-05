#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QGraphicsScene>
#include <QVector>
#include <QtAlgorithms>
#include <QInputDialog>

#include "Headers/node.h"
#include "Headers/edge.h"
#include "Headers/edgevaluetext.h"
#include "Headers/graph.h"

namespace Ui {
class MainMenu;
}

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = 0);
    ~MainMenu();

private slots:
    void on_pb_addNode_clicked();
    void on_pb_new_clicked();

    void nodeActivated(Node *node);
    void nodeDeactivated(Node *node);

private:
    Ui::MainMenu *m_ui;
    QGraphicsScene *m_scene;
    QVector<Node*> m_nodes;
    QVector<Edge*> m_edges;
    Graph *m_graph;
};

#endif // MAINMENU_H
