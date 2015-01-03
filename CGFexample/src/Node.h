#ifndef __CGFExample__Node__
#define __CGFExample__Node__

#include <stdio.h>
#include <vector>
#include <string>
#include "Transforms.h"
#include "Primitives.h"
#include <map>
#include "CGFappearance.h"
#include "CGFapplication.h"
#include "Appearance.h"
#include "Animation.h"

class Node{
private:
    std::string id;
    std::string apperanceref;
    bool displayList;
    bool hasAnimation;
    bool initialized;
    GLuint index;
    std::vector<Transforms *> * transforms;
    std::vector<Primitives *> * primitives;
    std::map<std::string, Node *> * descendants;
    GLfloat matrix[4][4];
    Appearance * appearance;
    vector<Animation *> animations;
    int currentAnimation;
    
    bool active;
public:
    
    Node(bool initialized) {
        transforms = new std::vector<Transforms *>();
        primitives = new std::vector<Primitives *>();
        this->initialized=initialized;
        this->hasAnimation = false;
        this->displayList = false;
        currentAnimation = 0;
    }
    
    bool isActive(){
        return this->active;
    }
    
    void setActive(bool active){
        this->active = active;
    }
    
    
    bool getHasAnimation() {
        return (
                this->hasAnimation
                &&
                currentAnimation < animations.size()
        );
    }
    
    bool getDisplayList()
    {
        return this->displayList;
    }
    
    void setDisplayList(bool displayList)
    {
        this->displayList = displayList;
    }
    
    std::string getID(){ return this->id; }
    std::string getAppearanceRef() { return this->apperanceref; }
    std::vector<Transforms *> * getTransforms(){ return this->transforms; }
    std::vector<Primitives *> * getPrimitives(){ return this->primitives; }
    std::map<std::string, Node*> * getDescendants(){ return this->descendants; }
    Appearance * getAppearance(){ return this->appearance; }
    
    void setID(std::string id){ this->id = id; }
    void setAppearanceRef(std::string appearanceref){ this->apperanceref = appearanceref; }
    void setTransforms(std::vector<Transforms *> * transforms){ this->transforms=transforms; }
    void setPrimitives(std::vector<Primitives *> * primitives) { this->primitives=primitives;}
    void setDescendants(std::map<std::string, Node*> * descendants) { this->descendants=descendants; }
    
    void addTransforms(Transforms * transform){ transforms->push_back(transform);}
    void addPrimitives(Primitives * primitive){ primitives->push_back(primitive);}
    void addDescendant(Node * node){ descendants->insert(std::pair<std::string,Node *>(node->getID(), node)); }
    void addAppearance(Appearance * appearance){ this->appearance = appearance;}
    
    bool isInitialized() {
        return this->initialized;
    }
    
    Animation * getAnimation()
    {
        return this->animations[currentAnimation];
    }
    
    void setAnimation(Animation * animation) {
        this->animations.push_back(animation);
        this->hasAnimation = true;
    }
    
    void draw(GLfloat previousMatrix[4][4], Appearance * previousAppearance);
    void draw(GLfloat previousMatrix[4][4]);
    
    void calculateMatrix();
    void calculateAnimations();
    void saveToDisplayList();
    void setDescendentsDisplayList();
    
};

#endif /* defined(__CGFExample__Node__) */
