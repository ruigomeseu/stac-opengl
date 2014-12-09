//
//  Transforms.h
//  CGFExample
//

#ifndef __CGFExample__Transforms__
#define __CGFExample__Transforms__

#include <iostream>
#include <string>
#include "CGFappearance.h"
#include "CGFapplication.h"

class Transforms{
public:
    
    virtual std::string getType() = 0;
    virtual void apply() = 0;
    
};


class Translation : public Transforms
{
private:
    float x, y, z;
public:
    
    float getX(){ return this->x; }
    float getY(){ return this->y; }
    float getZ(){ return this->z; }
    
    void setX(float x){ this->x = x; }
    void setY(float y){ this->y = y; }
    void setZ(float z){ this->z = z; }
    std::string getType() { return "translation"; }
    
    void apply();
};



class Rotation : public Transforms{
private:
    char axis;
    float angle;
public:
    char getAxis() {return this->axis; }
    float getAngle() {return this->angle; }
    
    void setAxis(char axis) { this->axis = axis; }
    void setAngle(float angle) { this->angle = angle; }
    std::string getType() { return "rotation"; }
    
    void apply();
};


class Scale : public Transforms{
private:
    float xFactor, yFactor, zFactor;
public:

    float getXFactor(){ return this->xFactor; }
    float getYFactor(){ return this->yFactor; }
    float getZFactor(){ return this->zFactor; }
    
    void setXFactor(float xFactor){ this->xFactor = xFactor; }
    void setYFactor(float yFactor){ this->yFactor = yFactor; }
    void setZFactor(float zFactor){ this->zFactor = zFactor; }
    std::string getType() { return "scale"; }
    
    void apply();

};


#endif /* defined(__CGFExample__Transforms__) */
