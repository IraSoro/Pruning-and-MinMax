#ifndef TREE_H
#define TREE_H

#include "iostream"
#include "QVector"
#include "QDebug"

#include <QGraphicsScene>

#include "DrawingObjects.h"

struct Node{
    Node(){
    }
    int countChilds = 0;
    QVector <Node*> childs ;
    Node *parent;
    int data = 0;
    int id = 0;
    int level = 0;

};

class Tree{
public:
    Tree() {

    }
    Node *root;
    QVector <int> arrayDataNodes;
    QVector <int> CountNodesOnLevel;
    int numArrayDataNode = 0;

    void AddRoot(int id, int countChilds, int data = 0){
        root = new Node();
        root->data = data;
        root->countChilds = countChilds;
        root->id = id;
        root->level = 0;
        CountNodesOnLevel.push_back(1);
        return;
    }

    bool AddChilNode(int parentId, int id, int countChilds, int val = 0){

        Node *tmp = FindNodeById(root, parentId);
        if(!tmp){
            qDebug()<<"Return FALSE in AddChilNode";
            return false;
        }

        if(FindNodeById(tmp, id)){
            qDebug()<<"Return TRUE in AddChilNode";
            return true;
        }

        Node *child = new Node();
        child->id = id;
        child->data = val;
        child->countChilds = countChilds;
        child->level = tmp->level + 1;
        if (CountNodesOnLevel.size() != tmp->level + 2){
            CountNodesOnLevel.push_back(1);
        }else{
            CountNodesOnLevel[tmp->level + 1]++;
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
                qDebug()<<"node - "<<n->id<<" child num - "<<n->childs[i]->id<<" count childs "<<n->childs[i]->countChilds<<" fact count childs "<<n->childs[i]->childs.size()<<" data = "<<n->childs[i]->data;
                BypassTree(n->childs[i]);
            }
        }
    }

    void BypassTreeStart(){
        Node *tmp = GetRoot();

        for (int i = 0 ; i < tmp->childs.size(); i++){
            qDebug()<<"node - "<<tmp->id<<" child num - "<<tmp->childs[i]->id<<" count childs "<<tmp->childs[i]->countChilds<<" fact count childs "<<tmp->childs[i]->childs.size()<<" data = "<<tmp->childs[i]->data;
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

    void GetLeveles(){
        int temp = CountNodesOnLevel.size();
        for (int i = 0; i < temp; i++){
            qDebug()<<"level ["<<i<<"] = "<<CountNodesOnLevel[i];
        }
    }

private:
    Node* FindNodeById(Node *n, int id){
            if(!n){
                qDebug()<<"Error in 1_FindNodeById";
                return nullptr;
            }

            if(n->id == id){
                qDebug()<<"Return n in FindNodeById";
                return n;
            }

            if(!n->childs.isEmpty()){
                int temp = n->childs.size();
                for(int i=0; i<temp; i++){
                    Node *foundNode = FindNodeById(n->childs[i], id);
                    if(foundNode){
                        qDebug()<<"Return foundNode in FindNodeById";
                        return foundNode;
                    }
                }
            }
            return nullptr;
        }



};


#endif // TREE_H
