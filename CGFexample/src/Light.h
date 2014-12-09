//
//  Light.h
//  CGFExample
//
//  Created by José Miguel  Melo on 17/10/14.
//  Copyright (c) 2014 me. All rights reserved.
//

#ifndef __CGFExample__Light__
#define __CGFExample__Light__

#include <stdio.h>
#include "CGFlight.h"
#include <string>

class Light{
private:
    float position[3];
    bool enabled;
    bool marker;
    std::string id;
    float ambient[4]; float diffuse[4]; float specular[4];
    
public:
    
    float * getPos(){ return position; }
    bool getEnabled(){ return this->enabled;}
    bool getMarker(){ return this->marker;}
    std::string getId() const{ return this->id;}
    float * getAmbient(){ return this->ambient;}
    float * getDiffuse(){ return this->diffuse;}
    float * getSpecular(){ return this->specular;}
        
    
    void setPos(float pos[3]){
        this->position[0] = pos[0];
        this->position[1] = pos[1];
        this->position[2] = pos[2];
    }
    void setEnabled(bool enabled){ this->enabled = enabled;}
    void setMarker(bool marker){ this->marker = marker;}
    void setId(std::string id){ this->id = id;}
    void setAmbient(float ambient[4]){
        this->ambient[0] = ambient[0];
        this->ambient[1] = ambient[1];
        this->ambient[2] = ambient[2];
        this->ambient[3] = ambient[3];
    }
    void setDiffuse(float diffuse[4]){
        this->diffuse[0] = diffuse[0];
        this->diffuse[1] = diffuse[1];
        this->diffuse[2] = diffuse[2];
        this->diffuse[3] = diffuse[3];
    }
    
    void setSpecular(float specular[4]){
        this->specular[0] = specular[0];
        this->specular[1] = specular[1];
        this->specular[2] = specular[2];
        this->specular[3] = specular[3];
    }
    
    virtual std::string getType(){}
};

class Omni: public Light{
public:
    std::string getType(){ return "omni";}
};

class Spot: public Light{
    float exponent;
    float target[3];
    float angle;
public:
    
    float * getTarget(){ return target; }
    float getExponent(){ return exponent; }
    
    void setTarget(float target[3]){
        float * position = this->getPos();
        this->target[0] = target[0] - position[0];
        this->target[1] = target[1] - position[1];
        this->target[2] = target[2] - position[2];
    }
    

    void setExponent(float exponent){ this->exponent= exponent;}
    std::string getType(){ return "spot";}
    
    
    
    float getAngle(){ return this->angle;}
    void setAngle(float angle){ this->angle = angle;}
};

#endif /* defined(__CGFExample__Light__) */
