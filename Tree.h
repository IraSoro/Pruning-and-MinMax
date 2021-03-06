#ifndef TREE_H
#define TREE_H

#include "iostream"
#include "QVector"
#include "QDebug"

#include <QGraphicsScene>

#include "DrawingObjects.h"

const int WIDTH = 1000;
const int HEIGHT = 300;

struct Node{
    Node(){
    }
    int countChilds = 0;
    QVector <Node*> childs ;
    Node *parent;
    int data = -1;
    int id = 0;
    int level = 0;
    int x = 0;
    int y = 0;    
    int clipping = 0;
};

struct NodesOnLevels{
    int CurrentCoords = 0;
    int CountNodes = 0;
};

struct NodeForDrawing{
    int x = 0;
    int y = 0;
    int id = 0;
    int IndesParent = 0;
    int data = -1;
    int clipping = 0;
};

class Tree{
public:
    Tree() {

    }
    Node *root;
    QVector <int> arrayDataNodes;
    QVector <NodesOnLevels> CountNodesOnLevel;
    QVector <int> CurrentCoordsOnLevel;
    QVector <NodeForDrawing> NodesDrawing;
    int CountNodes = 0;
    int numArrayDataNode = 0;

    void AddRoot(int id, int countChilds, int data = -1){
        root = new Node();
        root->data = data;
        root->countChilds = countChilds;
        root->id = id;
        root->level = 0;
        NodesOnLevels Value;
        Value.CountNodes = 1;
        CountNodesOnLevel.push_back(Value);
        return;
    }

    bool AddChilNode(int parentId, int id, int countChilds, int data = -1){

        Node *tmp = FindNodeById(root, parentId);
        if(!tmp){
            //qDebug()<<"Return FALSE in AddChilNode";
            return false;
        }

        if(FindNodeById(tmp, id)){
            //qDebug()<<"Return TRUE in AddChilNode";
            return true;
        }

        Node *child = new Node();
        child->id = id;
        child->data = data;
        child->countChilds = countChilds;
        child->level = tmp->level + 1;
        if (CountNodesOnLevel.size() != tmp->level + 2){
            NodesOnLevels Value;
            Value.CountNodes = 1;
            CountNodesOnLevel.push_back(Value);
        }else{
            CountNodesOnLevel[tmp->level + 1].CountNodes++;
        }
        child->parent = tmp;
        tmp->childs.push_back(child);

        return true;
    }
    Node* GetRoot(){
        return root;
    }

    void BypassTree(Node *n){
        if(!n->childs.isEmpty()){
            int temp = n->childs.size();
            for(int i=0; i<temp; i++){
                //qDebug()<<"node - "<<n->id<<" level - "<<n->level<<" child num - "<<n->childs[i]->id<<" count childs "<<n->childs[i]->countChilds<<" fact count childs "<<n->childs[i]->childs.size()<<" data = "<<n->childs[i]->data<<" clipping = "<<n->clipping;
                BypassTree(n->childs[i]);
            }
        }
    }

    void BypassTreeStart(){
        Node *tmp = GetRoot();

        for (int i = 0 ; i < tmp->childs.size(); i++){
            //qDebug()<<"node - "<<tmp->id<<" level - "<<tmp->level<<" child num - "<<tmp->childs[i]->id<<" count childs "<<tmp->childs[i]->countChilds<<" fact count childs "<<tmp->childs[i]->childs.size()<<" data = "<<tmp->childs[i]->data<<" clipping = "<<tmp->clipping;
            BypassTree(tmp->childs[i]);
        }

        GetLeveles();
    }

    void CompleteNodes(Node *n){
        if (!n->childs.size() && n->countChilds){
            int temp = n->countChilds;
            for(int i=0; i<temp; i++){
                AddChilNode(n->id, 101 + numArrayDataNode, 0, arrayDataNodes[numArrayDataNode]);
                numArrayDataNode++;
            }
        } else{
            int val = n->childs.size();
            for(int i=0; i<val; i++)
                CompleteNodes(n->childs[i]);
        }

    }

    void CompleteNodesStart(){
        Node *tmp = GetRoot();

        for (int i = 0 ; i < tmp->childs.size(); i++){
            CompleteNodes(tmp->childs[i]);
        }
    }

    void ForCoordsBypassTree(Node *n){
        CountNodesOnLevel[n->level].CurrentCoords += ( WIDTH / CountNodesOnLevel[n->level].CountNodes);
        n->x = CountNodesOnLevel[n->level].CurrentCoords;
        n->y = 50*(n->level+1);

        NodeForDrawing TempNode;
        TempNode.x = n->x;
        TempNode.y = n->y;
        TempNode.data = n->data;
        TempNode.id = n->id;
        TempNode.IndesParent = n->parent->id;
        NodesDrawing.push_back(TempNode);

        if(!n->childs.isEmpty()){
            int CountChild = n->childs.size();
            for(int i=0; i<CountChild; i++){
                ForCoordsBypassTree(n->childs[i]);
            }
        }
    }

    void ForCoordsBypassTreeStart(){

        Node *tmp = GetRoot();
        CountNodesOnLevel[0].CurrentCoords = WIDTH/2;
        tmp->x = CountNodesOnLevel[0].CurrentCoords;
        tmp->y = (tmp->level+1)*50;

        NodeForDrawing TempNode;
        TempNode.x = tmp->x;
        TempNode.y = tmp->y;
        TempNode.data = tmp->data;
        TempNode.id = tmp->id;
        TempNode.IndesParent = -1;
        NodesDrawing.push_back(TempNode);

        for (int i = 0 ; i < tmp->childs.size(); i++){
            ForCoordsBypassTree(tmp->childs[i]);
        }
    }

    void GetLeveles(){
        int temp = CountNodesOnLevel.size();
        for (int i = 0; i < temp; i++){
            //qDebug()<<"level ["<<i<<"] = "<<CountNodesOnLevel[i].CountNodes;
            CountNodes += CountNodesOnLevel[i].CountNodes;
        }
        //qDebug()<<"CountNodes = "<<CountNodes;
    }

    void DefineDataNodesByMinMaxStart(bool FlagMax){

        if (FlagMax){
            DefineDataNodesByMaxStart();
        }else{
            DefineDataNodesByMimStart();
        }
    }

    void DeleteNode(){
        Node *tmp = GetRoot();

        for (int i = 0 ; i < tmp->childs.size(); i++){
            DeleteNodeAll(tmp->childs[i]);
        }
        delete tmp;
    }

    void DeleteNodeAll(Node *n){
        if(!n->childs.isEmpty()){
            int temp = n->childs.size();
            for(int i=0; i<temp; i++){
                DeleteNodeAll(n->childs[i]);
            }
        }
        delete n;
    }

    void ClippingStart(bool flagMAX){
        Node *tmp = GetRoot();
        if (flagMAX){
            if (tmp->countChilds > 1 && tmp->level < (CountNodesOnLevel.size() - 2)){
                for (int i = 0; i < tmp->countChilds-1; i++){
                    for (int j = 0; j < tmp->childs[i+1]->countChilds-1; j++)
                        if (tmp->childs[i]->data > tmp->childs[i+1]->childs[j]->data){
                            MarkClippingStart(0, flagMAX, tmp->childs[i+1], j+1);
                        }
                    Clipping(0, tmp->childs[i]);
                }
                Clipping(0, tmp->childs[tmp->countChilds-1]);
            }
        }
        else{
            if (tmp->countChilds > 1 && tmp->level < (CountNodesOnLevel.size() - 2)){
                for (int i = 0; i < tmp->countChilds-1; i++){
                    for (int j = 0; j < tmp->childs[i+1]->countChilds-1; j++)
                        if (tmp->childs[i]->data < tmp->childs[i+1]->childs[j]->data){
                            MarkClippingStart(0, flagMAX, tmp->childs[i+1], j+1);
                        }
                    Clipping(1, tmp->childs[i]);
                }
                Clipping(1, tmp->childs[tmp->countChilds-1]);
            }
        }
    }


    void Clipping(bool flagMax, Node *n){
        if (flagMax){
            if (n->countChilds > 1 && n->level < (CountNodesOnLevel.size() - 2)  && !n->clipping){
                for (int i = 0; i < n->countChilds-1; i++){
                    for (int j = 0; j < n->childs[i+1]->countChilds-1; j++)
                        if (n->childs[i]->data > n->childs[i+1]->childs[j]->data){
                            MarkClippingStart(0, flagMax, n->childs[i+1], j+1);
                        }
                    Clipping(0, n->childs[i]);
                }
                Clipping(0, n->childs[n->countChilds-1]);
            }
        }
        else{
            if (n->countChilds > 1 && n->level < (CountNodesOnLevel.size() - 2)  && !n->clipping){
                for (int i = 0; i < n->countChilds-1; i++){
                    for (int j = 0; j < n->childs[i+1]->countChilds-1; j++)
                        if (n->childs[i]->data < n->childs[i+1]->childs[j]->data){
                            MarkClippingStart(0, flagMax, n->childs[i+1], j+1);
                        }
                    Clipping(1, n->childs[i]);
                }
                Clipping(1, n->childs[n->countChilds-1]);
            }
        }
    }

    void DeepClipping(bool flagMax){
        Node *tmp = GetRoot();
        if (flagMax){
            if (tmp->countChilds > 1 && tmp->level < (CountNodesOnLevel.size() - 4)){
                for (int i = 0; i < tmp->countChilds-1; i++){
                    for (int j = 0; j < tmp->childs[i+1]->countChilds-1; j++)
                        if (tmp->childs[i]->data > tmp->childs[i+1]->childs[0]->childs[0]->childs[j]->data){
                            MarkClippingStart(1, flagMax,  tmp->childs[i+1]->childs[0]->childs[0], j+1);
                        }
                }
            }
        }
        else{
            if (tmp->countChilds > 1 && tmp->level < (CountNodesOnLevel.size() - 4)){
                for (int i = 0; i < tmp->countChilds-1; i++){
                    for (int j = 0; j < tmp->childs[i+1]->countChilds-1; j++)
                        if (tmp->childs[i]->data < tmp->childs[i+1]->childs[0]->childs[0]->childs[j]->data){
                            MarkClippingStart(1, flagMax, tmp->childs[i+1]->childs[0]->childs[0], j+1);
                        }
                }
            }
        }
    }


    void MarkClippingStart(bool flagDeep, bool flagMax, Node *n, int IndChild){
        int color = 0;
        if (flagDeep){
            if (flagMax)
                color = 4;
            else
                color = 3;
        }
        else{
            if (flagMax)
                color = 2;
            else
                color = 1;
        }
        if(!n->childs.isEmpty() && n->clipping == 0){
            for(int i=IndChild; i<n->countChilds; i++){
                MarkClipping(flagDeep, flagMax, n->childs[i]);
                n->childs[i]->clipping = color;

                for (int j = 0; j < NodesDrawing.size(); j++){
                    if (n->childs[i]->id == NodesDrawing[j].id){
                        NodesDrawing[j].clipping = n->childs[i]->clipping;
                        break;
                    }
                }
            }
        }
    }

    void MarkClipping(bool flagDeep, bool flagMax, Node *n){
        int color = 0;
        if (flagDeep){
            if (flagMax)
                color = 4;
            else
                color = 3;
        }
        else{
            if (flagMax)
                color = 2;
            else
                color = 1;
        }
        if(!n->childs.isEmpty() && n->clipping == 0){
            for(int i=0; i<n->countChilds; i++){
                MarkClipping(flagDeep, flagMax, n->childs[i]);
                n->childs[i]->clipping = color;

                for (int j = 0; j < NodesDrawing.size(); j++){
                    if (n->childs[i]->id == NodesDrawing[j].id){
                        NodesDrawing[j].clipping = n->childs[i]->clipping;
                        break;
                    }
                }
            }
        }
    }

private:

    void DefineDataNodesByMaxStart(){
        Node *tmp = GetRoot();
        qDebug()<<"n->data root = "<<tmp->data;
        int MaxData = -1;
        for (int i = 0; i < tmp->countChilds; i++){
            if (tmp->childs[i]->childs.size() > 0 ){
                DefineDataNodesByMax(tmp->childs[i]);
            }
            if (tmp->childs[i]->data > MaxData && tmp->childs[i]->clipping == 0)
                MaxData = tmp->childs[i]->data;

        }

        tmp->data = MaxData;
        for (int j = 0; j < NodesDrawing.size(); j++){
            if (tmp->id == NodesDrawing[j].id){
                NodesDrawing[j].data = tmp->data;
                break;
            }
        }
    }
    void DefineDataNodesByMax(Node *n){

        if (n->countChilds > 0){
            int MaxData = -1;
            int MinData = 1000;
            bool flag = false;
            if ((n->level)%2 == 0)
                flag = true;


            for (int i = 0; i < n->countChilds; i++){
                if (n->childs[i]->childs.size() > 0 ){
                    DefineDataNodesByMax(n->childs[i]);
                }
                if (n->childs[i]->clipping == 0){
                    if (flag){
                        if(MaxData < n->childs[i]->data){
                            MaxData = n->childs[i]->data;
                        }
                    }else{
                        if(MinData > n->childs[i]->data){
                            MinData = n->childs[i]->data;
                        }
                    }
                }
            }
            if (flag){
                if (MaxData != -1)
                    n->data = MaxData;
            }
            else{
                if (MinData != 1000)
                n->data = MinData;
            }

            for (int j = 0; j < NodesDrawing.size(); j++){
                if (n->id == NodesDrawing[j].id){
                    NodesDrawing[j].data = n->data;
                    break;
                }
            }
        }

    }

    void DefineDataNodesByMimStart(){
        Node *tmp = GetRoot();
        qDebug()<<"n->data root = "<<tmp->data;
        int MinData = 1000;
        for (int i = 0; i < tmp->countChilds; i++){
            if (tmp->childs[i]->childs.size() > 0 ){
                DefineDataNodesByMin(tmp->childs[i]);
            }
            if (tmp->childs[i]->data < MinData && tmp->childs[i]->clipping == 0)
                MinData = tmp->childs[i]->data;

        }

        tmp->data = MinData;
        for (int j = 0; j < NodesDrawing.size(); j++){
            if (tmp->id == NodesDrawing[j].id){
                NodesDrawing[j].data = tmp->data;
                break;
            }
        }
    }

    void DefineDataNodesByMin(Node *n){
        if (n->countChilds > 0){
            int MaxData = -1;
            int MinData = 1000;
            bool flag = false;
            if ((n->level)%2 == 0)
                flag = true;

            for (int i = 0; i < n->countChilds; i++){
                if (n->childs[i]->childs.size() > 0){
                    DefineDataNodesByMin(n->childs[i]);
                }
                if (n->childs[i]->clipping == 0){
                    if (flag){
                        if(MinData > n->childs[i]->data){
                            MinData = n->childs[i]->data;
                        }
                    }else{
                        if(MaxData < n->childs[i]->data){
                            MaxData = n->childs[i]->data;
                        }
                    }
                }
            }
            if (flag){
                if (MinData != 1000)
                    n->data = MinData;
            }
            else{
                if (MaxData != -1)
                    n->data = MaxData;
            }

            for (int j = 0; j < NodesDrawing.size(); j++){
                if (n->id == NodesDrawing[j].id){
                    NodesDrawing[j].data = n->data;
                    break;
                }
            }
        }

    }

    Node* FindNodeById(Node *n, int id){
            if(!n){
                //qDebug()<<"Error in 1_FindNodeById";
                return nullptr;
            }

            if(n->id == id){
                //qDebug()<<"Return n in FindNodeById";
                return n;
            }

            if(!n->childs.isEmpty()){
                int temp = n->childs.size();
                for(int i=0; i<temp; i++){
                    Node *foundNode = FindNodeById(n->childs[i], id);
                    if(foundNode){
                        //qDebug()<<"Return foundNode in FindNodeById";
                        return foundNode;
                    }
                }
            }
            return nullptr;
    }

};


#endif // TREE_H
