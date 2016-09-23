#include "../Headers/mainmenu.h"
#include "ui_mainmenu.h"

MainMenu::MainMenu(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::MainMenu)
{
    m_ui->setupUi(this);

    m_scene = new QGraphicsScene();
    m_ui->gv_graph->setScene(m_scene);
}

MainMenu::~MainMenu()
{
    delete m_ui;
    delete m_scene;
}

void MainMenu::on_pb_addNode_clicked()
{
    int value = m_nodes.size() + 1;
    Node* newNode = new Node(value);
    m_scene->addItem(newNode);
    m_nodes.push_back(newNode);
}
