#ifndef __CGFExample__globals__
#define __CGFExample__globals__

#include <stdio.h>
#include <string>

#include "CGFscene.h"
#include "CGFshader.h"
#include "CGFappearance.h"
#include "CGFapplication.h"
#include "CGFobject.h"
#include "CGFaxis.h"

class Globals {
    
public:
    // drawing
    float background[4];
    std::string mode, shading;
    // culling
    std::string face, order;
    // lighting
    std::string doublesided, local, enabled;
    float ambient[4];
    
    
    
    GLenum getMode();
    GLenum getShading();
    GLenum getCulling();
    GLenum getOrder();
    float * getLightAmbient();
    GLenum isDoubleSided();
    GLenum isLocalLight();
    GLenum isLightEnabled();
    
    float getBackground(int position);
    
    
    
    
};

#endif
