#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsRectItem>
#include <QGraphicsScene>

#include "canvas.h"
#include "physics.h"
#include "point.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this -> InitMainWindow();

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

    this -> m_canvas = new Canvas;
    scene -> addItem(this -> m_canvas);
}

/*!
 * \brief Init physics model of the application
 */
void MainWindow::Init()
{
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
