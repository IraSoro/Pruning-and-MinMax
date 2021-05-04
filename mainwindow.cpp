#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Start();
    BuildTree tree(arrayValNodes);

    DrawingTree();
    //DrawingNode(tree.CountNodesOnLevel());
    DrawingNode(tree.ReturnNodesForDrawing());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::Start(){
    ui->tableWidget->setRowCount(1);
    ui->tableWidget->setColumnCount(36);

    ui->tableWidget->setVerticalHeaderLabels(QStringList() << "p_i");

    QFile file("C:/Users/User/Desktop/min_max/1.txt");
    file.open(QIODevice::ReadOnly);
    if (!file.isOpen()){
        qDebug()<<"Error open file";
        return;
    }else
        qDebug()<<"File open";

    int row = 0;
    int column = 0;
    while (!file.atEnd()) {
            QByteArray line = file.readLine();
            int num = line[0]-48;
            arrayValNodes.push_back(num);
            QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg(num));
            ui->tableWidget->setItem(row, column, newItem);
            column++;
    }
    file.close();
}
/*
void MainWindow::DrawingNode(QVector <NodesOnLevels> levels){
    int width = 0;
    int height = 0;

    int CountLevels = levels.size();
    for (int n = 0; n < CountLevels; n++) {
        int CountNodes = levels[n].CountNodes;
        for (int i = 0; i < CountNodes; i++){
            DrawingObjects* item = new DrawingObjects();
            item->text = QString::number(i+1);
            if (n == 0){
                width = WIDTH/2;
                height = 50*(n+1);
            }
            else{
                width = (WIDTH)/CountNodes*(i+1);
                height = 50*(n+1);
            }
//            if (n == 1){
//                item->CoordsLine[0] = 0;
//                item->CoordsLine[1] = 0;
//                item->CoordsLine[2] = WIDTH/2-width;
//                item->CoordsLine[3] = -50;
//            }else if (!n){

//            }
            item->setPos(width,height);
            scene->addItem(item);
        }
    }

}
*/

void MainWindow::DrawingNode(QVector <NodeForDrawing> drawingNode){

    DrawingObjects* item = new DrawingObjects();
    item->setPos(drawingNode[0].x,drawingNode[0].y);
    scene->addItem(item);

    int sizeNode = drawingNode.size();
    for (int i = 1; i < sizeNode; i++){
        DrawingObjects* item = new DrawingObjects();
        item->setPos(drawingNode[i].x,drawingNode[i].y);
        for (int j = 0; j < sizeNode; j++){
            if (drawingNode[j].id == drawingNode[i].IndesParent){
                item->CoordsLine[0] = 0;
                item->CoordsLine[1] = 0;
                item->CoordsLine[2] = drawingNode[j].x-drawingNode[i].x;
                item->CoordsLine[3] = -35;
            }
        }
        scene->addItem(item);
    }

}

void MainWindow::DrawingConnection(){

}

void MainWindow::DrawingTree(){

    scene = new QGraphicsScene(this);                               // Инициализируем графическую сцену
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);             // настраиваем индексацию элементов
    ui->graphicsView->resize(WIDTH,HEIGHT);                         // Устанавливаем размер graphicsView
    ui->graphicsView->setScene(scene);                              // Устанавливаем графическую сцену в graphicsView
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);        // Настраиваем рендер
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground); // Кэш фона
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    scene->setSceneRect(0,0,WIDTH,HEIGHT);

}
