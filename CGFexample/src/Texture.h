//
//  Texture.h
//  CGFExample
//

#ifndef __CGFExample__Texture__
#define __CGFExample__Texture__

#include <stdio.h>
#include <string>
#include "CGFtexture.h"

class Texture: public CGFtexture{
private:
    std::string id;
    std::string file;
    float texlength_s;
    float texlength_t;
    
public:
    
    Texture(){}
    
    void setId(std::string id){ this->id = id; }
    void setFile(std::string file){ this->file = file;}
    void setTexLengthS(float texlength_s){this->texlength_s = texlength_s;
        texWidth=texlength_s;
    }
    void setTexLengthT(float texlength_t){this->texlength_t = texlength_t;
        texHeight=texlength_t;
    }
    
    std::string getId(){ return this->id;}
    std::string getFile(){ return this->file; }
    float getTexLengthS(){ return this->texlength_s; }
    float getTexLengthT(){ return this->texlength_t; }
    
};

#endif /* defined(__CGFExample__Texture__) */
