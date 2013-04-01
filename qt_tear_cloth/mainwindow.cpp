#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QKeyEvent>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QTimer>

#include "canvas.h"
#include "physics.h"
#include "point.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this -> setFocusPolicy(Qt::StrongFocus);
    this -> InitMainWindow();
    this -> Init();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete this -> m_canvas;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event -> key())
    {
        case Qt::Key_Q:
            this -> m_canvas -> ActiveKeyLeft(true);
        break;
        case Qt::Key_D:
            this -> m_canvas -> ActiveKeyRight(true);
            qDebug() << "Key D pushed";
        break;
        case Qt::Key_Z:
            this -> m_canvas -> ActiveKeyUp(true);
        break;
        case Qt::Key_S:
            this -> m_canvas -> ActiveKeyDown(true);
        break;
    }

    event ->accept();
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    switch(event -> key())
    {
        case Qt::Key_Q:
            this -> m_canvas -> ActiveKeyLeft(false);
        break;
        case Qt::Key_D:
            this -> m_canvas -> ActiveKeyRight(false);
            qDebug() << "Key D released";
        break;
        case Qt::Key_Z:
            this -> m_canvas -> ActiveKeyUp(false);
        break;
        case Qt::Key_S:
            this -> m_canvas -> ActiveKeyDown(false);
        break;
    }

    event ->accept();
}

void MainWindow::InitMainWindow()
{
    QGraphicsScene* scene = new QGraphicsScene(this);
    this -> ui -> canvasGraphicsView->setScene(scene);
    this -> ui -> canvasGraphicsView -> setFocusPolicy(Qt::ClickFocus);

    this -> m_canvas = new Canvas;
    scene -> addItem(this -> m_canvas);
}

/*!
 * \brief Init physics model of the application
 */
void MainWindow::Init()
{
    this -> connect(this -> ui -> ResetSimulation, SIGNAL(clicked()), this, SLOT(ResetSimulation()));
    this -> connect(this -> ui -> physicsSpinBox, SIGNAL(valueChanged(int)), this, SLOT(UpdatePhysicsAccuracy()));
    this -> connect(this -> ui -> mouseInfluenceSpinBox, SIGNAL(valueChanged(int)), this, SLOT(UpdateMouseInfluence()));
    this -> connect(this -> ui -> mouseCutSpinBox, SIGNAL(valueChanged(int)), this, SLOT(UpdateMouseCut()));
    this -> connect(this -> ui -> gravitySpinBox, SIGNAL(valueChanged(int)), this, SLOT(UpdateGravity()));

    QTimer *timer = new QTimer();
    timer->setInterval(1000/60);
    timer -> connect(timer, SIGNAL(timeout()), this, SLOT(Update()));
    timer -> start();
}

/*!
 * \brief Request the display refresh (Invalid area)
 */
void MainWindow::Update()
{
    this -> m_canvas -> Update();
}

void MainWindow::ResetSimulation()
{
    this -> m_canvas -> ResetSimulation();
}

void MainWindow::UpdatePhysicsAccuracy()
{
    this -> m_canvas -> SetPhysicsAccuracy(this -> ui ->physicsSpinBox -> value());

}

void MainWindow::UpdateMouseInfluence()
{
    this -> m_canvas -> SetMouseInfluence(this -> ui -> mouseInfluenceSpinBox -> value());
}

void MainWindow::UpdateMouseCut()
{
    this -> m_canvas -> SetMouseCut(this -> ui -> mouseCutSpinBox -> value());
}

void MainWindow::UpdateGravity()
{
    this -> m_canvas -> SetGravity(this -> ui -> gravitySpinBox -> value());
}
