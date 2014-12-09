//
//  Appearance.h
//  CGFExample
//

#ifndef __CGFExample__Appearance__
#define __CGFExample__Appearance__

#include <stdio.h>
#include "CGFappearance.h"
#include "CGFtexture.h"
#include <string>
#include "Texture.h"

class Appearance: public CGFappearance{
private:
    std::string id;
    std::string textureref;
    
public:
    
    Appearance(){};
    
    void setId(std::string id){ this->id=id;}
    void setTextureRef(std::string textureref){ this->textureref = textureref; }
    
    std::string getId(){ return this->id;}
    std::string getTextureRef(){ return this->textureref; }
    
    
};

#endif /* defined(__CGFExample__Appearance__) */
