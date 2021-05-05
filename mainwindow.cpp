#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Start();
    BuildTree* tree = new BuildTree(arrayValNodes);

    DrawingTree();
    DrawingNode(tree->ReturnNodesForDrawing());

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

void MainWindow::DrawingNode(QVector <NodeForDrawing> drawingNode){

    DrawingObjects* item = new DrawingObjects();
    item->setPos(drawingNode[0].x,drawingNode[0].y);
    if (drawingNode[0].data > -1)
        item->text = QString::number(drawingNode[0].data);
    scene->addItem(item);

    int sizeNode = drawingNode.size();
    for (int i = 1; i < sizeNode; i++){
        DrawingObjects* item = new DrawingObjects();
        item->setPos(drawingNode[i].x,drawingNode[i].y);

        if (drawingNode[i].clipping){
            if (drawingNode[i].clipping == 1)
                item->Color = 1;
            else
                item->Color = 2;
        }
        else{
            item->Color = 0;
        }

        if (drawingNode[i].data > -1)
            item->text = QString::number(drawingNode[i].data);

        for (int j = 0; j < sizeNode; j++){
            if (drawingNode[j].id == drawingNode[i].IndesParent){
                item->CoordsLine[0] = 0;
                item->CoordsLine[1] = 0;
                item->CoordsLine[2] = drawingNode[j].x-drawingNode[i].x;
                item->CoordsLine[3] = -35;
                break;
            }
        }
        scene->addItem(item);
    }

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

void MainWindow::on_pushButton_clicked(){
    FlagClick = true;
    OnMax = true;
    scene->clear();
    BuildTree ttree(arrayValNodes);
    ttree.DefineDataInNode(true);
    DrawingNode(ttree.ReturnNodesForDrawing());
    ttree.ClearTree();
}

void MainWindow::on_pushButton_2_clicked(){
    FlagClick = true;
    OnMax = false;
    scene->clear();
    BuildTree ttree(arrayValNodes);
    ttree.DefineDataInNode(false);
    DrawingNode(ttree.ReturnNodesForDrawing());
    ttree.ClearTree();
}

void MainWindow::on_pushButton_3_clicked(){
    scene->clear();
    BuildTree ttree(arrayValNodes);

    if (OnMax){
        ttree.DefineDataInNode(true);
    }else{
        ttree.DefineDataInNode(false);
    }
    ttree.ClippingTree(OnMax);

    DrawingNode(ttree.ReturnNodesForDrawing());
    ttree.ClearTree();
}
