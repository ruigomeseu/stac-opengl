//
//  ControlPoint.h
//  CGFExample
//

#ifndef __CGFExample__ControlPoint__
#define __CGFExample__ControlPoint__

#include <stdio.h>


class ControlPoint{
    
private:
    float x, y, z;
    
public:
    ControlPoint(float x, float y, float z){
        this->x=x;
        this->y=y;
        this->z=z;
    }
    
    void setX(float x){ this->x = x;}
    void setY(float y){ this->y = y;}
    void setZ(float z){ this->z = z;}
    
    float getX(){ return this->x; }
    float getY(){ return this->y; }
    float getZ(){ return this->z; }
    
    
};


#endif /* defined(__CGFExample__ControlPoint__) */
