#ifndef BUILDTREE_H
#define BUILDTREE_H

#include <QFile>
#include <QString>
#include <QDebug>
#include <QRegExp>

#include "Tree.h"

enum Attribute {ID = 0, ID_PARENT, COUNT_CHILDS};

class BuildTree{
private:
    Tree tree;

public:
    BuildTree(QVector <int> arrayDataNodes){
        tree.arrayDataNodes = arrayDataNodes;
        OpenFile();
        tree.BypassTreeStart();
    }

    QVector <NodeForDrawing> ReturnNodesForDrawing(){
        return tree.NodesDrawing;
    }

    QVector <NodesOnLevels> CountNodesOnLevel(){
        return tree.CountNodesOnLevel;
    }

    void DefineDataInNode(bool max){
        tree.DefineDataNodesByMinMaxStart(max);
    }

    void OpenFile(){
        QFile file("C:/Users/User/Desktop/min_max/nodes.txt");
        file.open(QIODevice::ReadOnly);
        if (!file.isOpen()){
            qDebug()<<"Error open file";
            return;
        }else
            qDebug()<<"File open";

        while (!file.atEnd()) {
                QString line = file.readLine();
                QStringList list = line.split(QRegExp("\\s+"));
                list.removeOne("");
                qDebug()<<line;
                if (list[ID_PARENT].toInt() < 0){
                    int temp = list[ID].toInt();
                    int temp2 = list[COUNT_CHILDS].toInt();
                    tree.AddRoot(temp,temp2);
                }else{

                    tree.AddChilNode(list[ID_PARENT].toInt(),list[ID].toInt(),list[COUNT_CHILDS].toInt());
                }


        }
        file.close();

        tree.CompleteNodesStart();
        tree.ForCoordsBypassTreeStart();

    }

};



#endif // BUILDTREE_H
