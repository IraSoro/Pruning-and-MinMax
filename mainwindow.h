#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QGraphicsScene>

#include <QFile>
#include <QString>
#include <QDebug>

#include "iostream"

#include "BuildTree.h"
#include "DrawingObjects.h"

const int WIDTH = 1000;
const int HEIGHT = 300;

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QVector <int> arrayValNodes;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void DrawingNode(QVector <int> levels);
    void DrawingTree();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QPainter *painter;
    QVector <DrawingObjects*> items;
    void Start();

};
#endif // MAINWINDOW_H
