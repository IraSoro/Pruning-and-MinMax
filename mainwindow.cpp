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

        item->Color = drawingNode[i].clipping;

        if (drawingNode[i].data > -1)
            item->text = QString::number(drawingNode[i].data);

        for (int j = 0; j < sizeNode; j++){
            if (drawingNode[j].id == drawingNode[i].IndesParent){
                item->CoordsLine[0] = 0;
                item->CoordsLine[1] = -15;
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

    DrawingLinesAndInf();
}
void MainWindow::DrawingLinesAndInf(){
    QPen pen(qRgb(255,255,0));
    int h = 50;
    for (int i = 0; i < 4; i++){
        scene->addLine(20, h*(i+1), 1100, h*(i+1), pen);
    }

    pen.setColor(qRgb(0,0,0));
    scene->addLine(10, 0, 10, HEIGHT, pen);

    int radius = 30;
    int xEllipse = -80;
    int yEllipse = 35;

    pen.setColor(Qt::black);
    QBrush brush(qRgb(255,255,0));

    brush.setColor(Qt::red);
    scene->addEllipse(xEllipse, yEllipse, radius, radius, pen, brush);
    QGraphicsTextItem *textItem1 = new QGraphicsTextItem();
    textItem1->setPos(xEllipse+30, yEllipse);
    textItem1->setPlainText("альфа");
    scene->addItem(textItem1);

    yEllipse += 50;
    brush.setColor(Qt::green);
    scene->addEllipse(xEllipse, yEllipse, radius, radius, pen, brush);
    QGraphicsTextItem *textItem2 = new QGraphicsTextItem();
    textItem2->setPos(xEllipse+30, yEllipse);
    textItem2->setPlainText("бетта");
    scene->addItem(textItem2);

    yEllipse += 50;
    brush.setColor(Qt::yellow);
    scene->addEllipse(xEllipse, yEllipse, radius, radius, pen, brush);
    QGraphicsTextItem *textItem3 = new QGraphicsTextItem();
    textItem3->setPos(xEllipse+30, yEllipse);
    textItem3->setPlainText("глуб.альфа");
    scene->addItem(textItem3);

    yEllipse += 50;
    brush.setColor(Qt::blue);
    scene->addEllipse(xEllipse, yEllipse, radius, radius, pen, brush);
    QGraphicsTextItem *textItem4 = new QGraphicsTextItem();
    textItem4->setPos(xEllipse+30, yEllipse);
    textItem4->setPlainText("глуб.бетта");
    scene->addItem(textItem4);

}

void MainWindow::OutputText(bool FlagMax){
    int h = 50;
    int w = 20;
    for (int i = 0; i < 4; i++){
        QGraphicsTextItem *textItem = new QGraphicsTextItem();
        textItem->setPos(w, h*(i+1)-20);
        if (i%2 == FlagMax)
            textItem->setPlainText("MIN");
        else
            textItem->setPlainText("MAX");
        scene->addItem(textItem);
    }
}


void MainWindow::on_pushButton_clicked(){
    OnMax = true;
    scene->clear();
    DrawingLinesAndInf();
    OutputText(OnMax);
    BuildTree ttree(arrayValNodes);
    ttree.DefineDataInNode(true);
    DrawingNode(ttree.ReturnNodesForDrawing());
    ttree.ClearTree();
}

void MainWindow::on_pushButton_2_clicked(){
    OnMax = false;
    scene->clear();
    DrawingLinesAndInf();
    OutputText(OnMax);
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

    DrawingLinesAndInf();
    OutputText(OnMax);
    DrawingNode(ttree.ReturnNodesForDrawing());
    ttree.ClearTree();
}
