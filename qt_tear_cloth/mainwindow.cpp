#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsRectItem>
#include <QGraphicsScene>

#include "canvas.h"
#include "physics.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_physicsAccuracy(3),
    m_mouseInfluence(20),
    m_mouseCut(6),
    m_gravity(900),
    m_clothHeight(30),
    m_clothWidth(50),
    m_startY(20),
    m_spacing(7),
    m_tearDistance(60)
{
    ui->setupUi(this);
    this -> InitMainWindow();
    this -> m_mouse.down = false;
    this -> m_mouse.button = 1;
    this -> m_mouse.x = 0;
    this -> m_mouse.y = 0;
    this -> m_mouse.px = 0;
    this -> m_mouse.py = 0;

    this -> Init();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete this -> m_canvas;
}

void MainWindow::InitMainWindow()
{
    QGraphicsScene* scene = new QGraphicsScene(this);
    this -> ui -> canvasGraphicsView->setScene(scene);

    this -> m_canvas = new Canvas(&(this -> m_mouse));
    this -> m_canvas -> setRect(0, 0,this -> m_clothWidth * this -> m_spacing, this -> m_clothHeight * this -> m_spacing);
    scene -> addItem(this -> m_canvas);
}

/*!
 * \brief Init physics model of the application
 */
void MainWindow::Init()
{
    this -> m_physics = new Physics;

    this -> BuildCloth();
    this -> Update();
}

/*!
 * \brief Request the display refresh (Invalid area)
 */
void MainWindow::Update()
{

}

/*!
 *
 */
void MainWindow::BuildCloth()
{

}
