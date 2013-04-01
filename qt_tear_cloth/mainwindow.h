#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class Canvas;
class Physics;
class QGraphicsRectItem;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void Update();
    void ResetSimulation();
    void UpdatePhysicsAccuracy();
    void UpdateMouseInfluence();
    void UpdateMouseCut();
    void UpdateGravity();
    
private:
    void InitMainWindow();
    void Init();
    void BuildCloth();

    Ui::MainWindow *ui;
    Canvas* m_canvas;
};

#endif // MAINWINDOW_H
