#ifndef TREE_H
#define TREE_H

#include "iostream"
#include "QVector"
#include "QDebug"

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
    void AddRoot(int id, int countChilds, int data = 0){
        //if (!root){
            root = new Node();
            root->data = data;
            root->countChilds = countChilds;
            root->id = id;
            root->level = 0;
        //}
        return;
    }

    bool AddChilNode(int parentId, int id, int countChalds){

        Node *tmp = FindNodeById(root, parentId);
        //qDebug()<<"--------";
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
        child->countChilds = countChalds;
        child->level = tmp->level + 1;
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
                qDebug()<<"node - "<<n->id<<" child num - "<<n->childs[i]->id;
                BypassTree(n->childs[i]);
            }
        }

    }

    void BypassTreeStart(){
        Node *tmp = GetRoot();

        for (int i = 0 ; i < tmp->childs.size(); i++){
            qDebug()<<"node - "<<tmp->id<<" child num - "<<tmp->childs[i]->id;
            BypassTree(tmp->childs[i]);
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
            //qDebug()<<"------";
            return nullptr;
        }



};


#endif // TREE_H
