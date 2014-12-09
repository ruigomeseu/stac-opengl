#include "Transforms.h"


void Translation::apply(){
    glTranslated(this->x, this->y, this->z);
}

void Rotation::apply(){
    
    double x=0, y=0, z=0;
    if(axis == 'x'){
        x=1;
    }
    if(axis == 'y'){
        y=1;
    }
    if(axis == 'z'){
        z=1;
    }
    glRotated(this->angle, x, y, z);
}

void Scale::apply(){
    glScaled(xFactor, yFactor, zFactor);
}