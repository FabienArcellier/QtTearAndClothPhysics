#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsRectItem>
#include <QGraphicsScene>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_physicsAccuracy(3),
    m_mouseInfluence(20),
    m_mouseCut(6),
    m_gravity(900),
    m_clothHeight(300),
    m_clothWidth(500),
    m_startY(20),
    m_spacing(7),
    m_tearDistance(60)
{
    ui->setupUi(this);
    this -> initMainWindow();
    this -> m_mouse.down = false;
    this -> m_mouse.button = 1;
    this -> m_mouse.x = 0;
    this -> m_mouse.y = 0;
    this -> m_mouse.px = 0;
    this -> m_mouse.py = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initMainWindow()
{
    QGraphicsScene* scene = new QGraphicsScene(this);
    this -> ui -> canvasGraphicsView->setScene(scene);
    QPen pen(Qt::black);

    this -> m_canvas = scene -> addRect((qreal)0, (qreal)this -> m_startY, (qreal)this -> m_clothWidth, (qreal)this -> m_clothHeight, pen);
}
