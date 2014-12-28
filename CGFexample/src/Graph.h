#ifndef __CGFExample__Graph__
#define __CGFExample__Graph__

#include <stdio.h>
#include <vector>
#include "Node.h"
#include <string>
#include <map>



class Graph{
private:
    std::map<std::string, Node *> * nodes;
    std::string rootid;
public:
    Graph(){
        nodes = new std::map<std::string, Node *>;
    }
    
    std::string getRootId() { return rootid; }
    std::map<std::string, Node *> * getNodes(){ return this->nodes; }
    
    void addNode(Node * node){
        this->nodes->insert(std::pair<std::string,Node *>(node->getID(), node));
    }
    
    void setRootId(std::string rootid)
    {
        this->rootid = rootid;
    }
    
    Node* getBoardElement(){
        return nodes->find("board")->second;
    }
    
};


#endif /* defined(__CGFExample__Graph__) */
