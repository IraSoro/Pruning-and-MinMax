#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QGraphicsScene>

#include <QFile>
#include <QString>
#include <QDebug>

#include "iostream"

#include "Tree.h"
#include "BuildTree.h"
#include "DrawingObjects.h"

//const int WIDTH = 1000;
//const int HEIGHT = 300;

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:    
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void DrawingNode(QVector <NodeForDrawing> drawingNode);
    void DrawingTree();
    void DrawingConnection();
    BuildTree* ReturnBuildTree();

    BuildTree* tree;

    QVector <int> arrayValNodes;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QPainter *painter;
    QVector <DrawingObjects*> items;
    void Start();
    bool OnMax = false;
    bool FlagClick = false;

};
#endif // MAINWINDOW_H
