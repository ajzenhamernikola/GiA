#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QGraphicsScene>
#include <QVector>
#include <QtAlgorithms>

#include "../Headers/node.h"

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

private:
    Ui::MainMenu *m_ui;
    QGraphicsScene *m_scene;
    QVector<Node*> m_nodes;
};

#endif // MAINMENU_H
