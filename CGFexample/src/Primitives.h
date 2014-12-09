#ifndef __CGFExample__Primitives__
#define __CGFExample__Primitives__

#include <stdio.h>
#include <string>
#include "CGFscene.h"
#include "CGFshader.h"
#include "CGFaxis.h"
#include "CGFapplication.h"
#include "CGFappearance.h"
#include <iostream>
#include "ControlPoint.h"
#include "Appearance.h"


class Primitives{
public:
    
    virtual std::string getType() = 0;
    virtual void draw() = 0;
};

class Rectangle : public Primitives{
private:
    float x1, y1;
    float x2, y2;
    
public:
    
    float getX1(){ return this->x1;}
    float getX2(){ return this->x2;}
    float getY1(){ return this->y1;}
    float getY2(){ return this->y2;}
    
    void setX1(float x1){ this->x1 = x1; }
    void setX2(float x2){ this->x2 = x2; }
    void setY1(float y1){ this->y1 = y1; }
    void setY2(float y2){ this->y2 = y2; }
    
    std::string getType() { return "rectangle"; }
    
    void draw();
};

class Triangle : public Primitives{
private:
    float x1, y1, z1;
    float x2, y2, z2;
    float x3, y3, z3;
    
public:
    
    float getX1(){ return this->x1;}
    float getX2(){ return this->x2;}
    float getX3(){ return this->x3;}
    float getY1(){ return this->y1;}
    float getY2(){ return this->y2;}
    float getY3(){ return this->y3;}
    float getZ1(){ return this->z1;}
    float getZ2(){ return this->z2;}
    float getZ3(){ return this->z3;}
    
    void setX1(float x1){ this->x1 = x1; }
    void setX2(float x2){ this->x2 = x2; }
    void setX3(float x3){ this->x3 = x3; }
    void setY1(float y1){ this->y1 = y1; }
    void setY2(float y2){ this->y2 = y2; }
    void setY3(float y3){ this->y3 = y3; }
    void setZ1(float z1){ this->z1 = z1; }
    void setZ2(float z2){ this->z2 = z2; }
    void setZ3(float z3){ this->z3 = z3; }

    std::string getType() { return "triangle"; }
    
    
    void draw();
};

class Cylinder : public Primitives{
private:
    float base, top, height;
    int slices, stacks;
public:
    float getBase(){ return this->base; }
    float getTop(){ return this->top; }
    float getHeight(){ return this->height; }
    int getSlices(){ return this->slices; }
    int getStacks(){ return this->stacks; }
    
    void setBase(float base){ this->base = base; }
    void setTop(float top){ this->top = top; }
    void setHeight(float height){ this->height = height; }
    void setSlices(int slices){ this->slices = slices; }
    void setStacks(int stacks){ this->stacks = stacks; }
    std::string getType() { return "cylinder"; }
    
    
    void draw();

};

class Sphere : public Primitives{
private:
    float radius;
    int slices, stacks;
public:
    float getRadius(){ return this->radius; }
    int getSlices(){ return this->slices; }
    int getStacks(){ return this->stacks; }
    
    void setRadius(float radius){ this->radius = radius; }
    void setSlices(int slices){ this->slices = slices; }
    void setStacks(int stacks){ this->stacks = stacks; }
    std::string getType() { return "sphere"; }
    
    
    
    void draw();
};

class Torus : public Primitives{
private:
    float inner, outer;
    int slices, loops;
    
public:
    float getInner(){ return this->inner; }
    float getOuter(){ return this->outer; }
    int getSlices(){ return this->slices; }
    int getLoops(){ return this->loops; }
    
    void setInner(float inner){ this->inner = inner; }
    void setOuter(float outer){ this->outer = outer; }
    void setSlices(int slices){ this->slices = slices; }
    void setLoops(int loops){ this->loops = loops; }
    std::string getType() { return "torus"; }
    
    
    
    
    void draw();
};




class Plane : public Primitives{
private:
    int parts;
    
    GLfloat ctrlpoints[4][3] = {
        {-0.5, 0.0, 0.5}, {-0.5, 0.0 ,-0.5},
        {0.5, 0.0, 0.5}, {0.5, 0.0, -0.5}};
    
    GLfloat texturepoints[4][2] = {
        {0.0, 0.0}, {0.0, 1.0},
        {1.0, 0.0}, {1.0, 1.0}};
    
   	GLfloat nrmlcompon[4][3] = {
        {0.0, 1.0, 0.0}, {0.0, 1.0, 0.0},
        {0.0, 1.0, 0.0}, {0.0, 1.0, 0.0}};
    
    
    
    // As cores a atribuir a cada ponto de controlo:
    //   Nota: para uma boa percepcao do efeito de iluminacao, é
    //         aconselhável usar, em alternativa, uma cor cinzenta
    GLfloat colorpoints[4][4] = {	{ 0.0, 0.7, 0.7, 0},
								{ 0.0, 0.0, 0.7, 0},
								{ 0.0, 0.7, 0.0, 0},
								{ 0.7, 0.0, 0.0, 0} };
    
public:
    Plane(){}
    Plane(int parts){ this->parts = parts; }
    
    void setParts(int parts){this->parts = parts;}
    int getParts(){ return this->parts; }
    
    std::string getType(){ return "plane"; }
    
    void draw(){
        glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 2, 0.0, 1.0, 2 * 3, 2, &ctrlpoints[0][0]);
        glMap2f(GL_MAP2_NORMAL,   0.0, 1.0, 3, 2,  0.0, 1.0, 6, 2,  &nrmlcompon[0][0]);
        glMap2f(GL_MAP2_COLOR_4,  0.0, 1.0, 4, 2,  0.0, 1.0, 8, 2,  &colorpoints[0][0]);
        glMap2f(GL_MAP2_TEXTURE_COORD_2, 0.0, 1.0, 2, 2, 0.0, 1.0, 2 * 2, 2, &texturepoints[0][0]);
        
        glEnable(GL_MAP2_VERTEX_3);
        glEnable(GL_MAP2_NORMAL);
        glEnable(GL_MAP2_COLOR_4);
        glEnable(GL_MAP2_TEXTURE_COORD_2);
        
        
        
        glMapGrid2f(parts, 0.0, 1.0, parts, 0.0, 1.0);
        glEvalMesh2(GL_FILL,0, parts, 0, parts);
        
        
        glEnable(GL_LIGHTING);
        glEnable(GL_COLOR_MATERIAL);
        glEnable(GL_TEXTURE_2D);
        
    }
    
};



class Patch : public Primitives{
private:
    vector<ControlPoint> cntlpoints;
    
    int partsU, partsV, order;
    std::string compute;
    
    
    GLfloat texturepoints[4][2] = {
        {0.0, 0.0}, {0.0, 1.0},
        {1.0, 0.0}, {1.0, 1.0}};
    
   	GLfloat nrmlcompon[4][3] = {
        {0.0, 1.0, 0.0}, {0.0, 1.0, 0.0},
        {0.0, 1.0, 0.0}, {0.0, 1.0, 0.0}};
    
    
    
    // As cores a atribuir a cada ponto de controlo:
    //   Nota: para uma boa percepcao do efeito de iluminacao, é
    //         aconselhável usar, em alternativa, uma cor cinzenta
    GLfloat colorpoints[4][4] = {	{ 0.0, 0.7, 0.7, 0},
								{ 0.0, 0.0, 0.7, 0},
								{ 0.0, 0.7, 0.0, 0},
								{ 0.7, 0.0, 0.0, 0} };
    

public:
    Patch(){}
    Patch(int order, int partsU, int partsV, std::string compute){
        this->order = order;
        this->partsU = partsU;
        this->partsV = partsV;
        this->compute = compute;
    }
    
    void setOrder(int order){ this->order =order; }
    void setPartsU(int partsU){this->partsU = partsU;}
    void setPartsV(int partsV){this->partsV = partsV;}
    void setCompute(std::string compute){ this->compute = compute;}
    void setCntlPoints(vector<ControlPoint> cntlpoints){this->cntlpoints = cntlpoints;}
    
    int getOrder(){ return this->order;}
    int getPartsU(){ return this->partsU; }
    int getPartsV(){ return this->partsV; }
    std::string getCompute(){ return this->compute;}
    vector<ControlPoint> getCntlPoints(){ return this->cntlpoints; }
    
    
    std::string getType(){ return "patch"; }
    
    void draw(){
        
        float cntlpoints_array[this->cntlpoints.size()][3];
        
        for(unsigned int i = 0; i< cntlpoints.size(); i++){
            cntlpoints_array[i][0] = cntlpoints.at(i).getX();
            cntlpoints_array[i][1] = cntlpoints.at(i).getY();
            cntlpoints_array[i][2] = cntlpoints.at(i).getZ();
        }
        
        glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, order+1, 0.0, 1.0, 3*(order+1), (order+1), &cntlpoints_array[0][0]);
        glEnable(GL_MAP2_VERTEX_3);
        
        glMap2f(GL_MAP2_COLOR_4,  0.0, 1.0, 4, order+1,  0.0, 1.0, 2*(order+1), 2,  &colorpoints[0][0]);
        glEnable(GL_MAP2_COLOR_4);        
        
        glMap2f(GL_MAP2_NORMAL,   0.0, 1.0, 3, order+1,  0.0, 1.0, 6, 3,  &cntlpoints_array[0][0]);
        glEnable(GL_MAP2_NORMAL);
        
        glMap2f(GL_MAP2_TEXTURE_COORD_2, 0.0, 1.0, 2, 2, 0.0, 1.0, 4, 2, &texturepoints[0][0]);
        glEnable(GL_MAP2_TEXTURE_COORD_2);
        
        
        glMapGrid2f(partsU, 0.0, 1.0, partsV, 0.0, 1.0);
        
        int drawingmode;
        if(strcmp(compute.c_str(), "fill") == 0){
            drawingmode = GL_FILL;
        }else if(strcmp(compute.c_str(), "line") == 0){
            drawingmode = GL_LINE;
        }else{
            drawingmode = GL_POINT;
        }
        
        
        glEvalMesh2(drawingmode,0, partsU, 0, partsV);
        glEnable(GL_DEPTH_TEST);
    }
    
};

class Vehicle: public Primitives{
private:
    Patch * patch;
    
public:
    Vehicle(){
        
        patch = new Patch(3, 20, 20, "fill");
        ControlPoint cntlpoint1 = ControlPoint(0,6,0);
        ControlPoint cntlpoint2 = ControlPoint(2,6,4);
        ControlPoint cntlpoint3 = ControlPoint(4,6,0);
        ControlPoint cntlpoint4 = ControlPoint(6,6,0);
        ControlPoint cntlpoint5 = ControlPoint(0,4,2);
        ControlPoint cntlpoint6 = ControlPoint(2,4,6);
        ControlPoint cntlpoint7 = ControlPoint(4,4,6);
        ControlPoint cntlpoint8 = ControlPoint(6,4,2);
        ControlPoint cntlpoint9 = ControlPoint(0,2,0);
        ControlPoint cntlpoint10 = ControlPoint(2,2,6);
        ControlPoint cntlpoint11 = ControlPoint(4,2,6);
        ControlPoint cntlpoint12 = ControlPoint(6,2,2);
        ControlPoint cntlpoint13 = ControlPoint(0,0,0);
        ControlPoint cntlpoint14 = ControlPoint(2,0,4);
        ControlPoint cntlpoint15 = ControlPoint(4,0,4);
        ControlPoint cntlpoint16 = ControlPoint(6,0,0);
        
        vector<ControlPoint> cntlpoints;
        cntlpoints.push_back(cntlpoint1);
        cntlpoints.push_back(cntlpoint2);
        cntlpoints.push_back(cntlpoint3);
        cntlpoints.push_back(cntlpoint4);
        cntlpoints.push_back(cntlpoint5);
        cntlpoints.push_back(cntlpoint6);
        cntlpoints.push_back(cntlpoint7);
        cntlpoints.push_back(cntlpoint8);
        cntlpoints.push_back(cntlpoint9);
        cntlpoints.push_back(cntlpoint10);
        cntlpoints.push_back(cntlpoint11);
        cntlpoints.push_back(cntlpoint12);
        cntlpoints.push_back(cntlpoint13);
        cntlpoints.push_back(cntlpoint14);
        cntlpoints.push_back(cntlpoint15);
        cntlpoints.push_back(cntlpoint16);
        patch->setCntlPoints(cntlpoints);
    }
    std::string getType() {return "vehicle"; }
    
    virtual void draw(){
        glPushMatrix();
        glTranslated(5, 0, 0);
        glRotated(90, 0, 0, 1);
        patch->draw();
        glPopMatrix();
        
        Torus * torus = new Torus();
        torus->setInner(1);
        torus->setOuter(3);
        torus->setSlices(10);
        torus->setLoops(10);
        glPushMatrix();
        Appearance * app = new Appearance();
        app->apply();
        glRotated(90, 1, 0, 0);
        glTranslated(3, -2, 0);
        torus->draw();
        
        glPopMatrix();
    }
    
};




#endif /* defined(__CGFExample__Primitives__) */
