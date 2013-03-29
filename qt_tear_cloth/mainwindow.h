#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class Physics;
class QGraphicsRectItem;

typedef struct
{
    bool down;
    qint32 button;
    qint32 x;
    qint32 y;
    qint32 px;
    qint32 py;
} Mouse;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Mouse* mouse();

private slots:
    
private:
    void InitMainWindow();
    void Init();
    void Update();
    void BuildCloth();

    Ui::MainWindow *ui;
    QGraphicsRectItem* m_canvas;
    Mouse m_mouse;
    qint32 m_physicsAccuracy;
    qint32 m_mouseInfluence;
    qint32 m_mouseCut;
    qint32 m_gravity;
    qint32 m_clothHeight;
    qint32 m_clothWidth;
    qint32 m_startY;
    qint32 m_spacing;
    qint32 m_tearDistance;
    Physics* m_physics;
};

#endif // MAINWINDOW_H
