#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Start();

    BuildTree tree;
    tree.Building();

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
            QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg(num));
            ui->tableWidget->setItem(row, column, newItem);
            column++;
    }
    file.close();

}
