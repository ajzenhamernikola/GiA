#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QVector>
#include <QtAlgorithms>
#include <QInputDialog>
#include <QFileDialog>
#include <QStandardPaths>

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

    void on_pb_addNode_clicked();
    void on_pb_new_clicked();
    void on_pb_save_clicked();

private:
    Ui::MainMenu *m_ui;
    QGraphicsScene *m_scene;
    QVector<Node*> m_nodes;
    QVector<Edge*> m_edges;
    Graph *m_graph;
};

#endif // MAINMENU_H
