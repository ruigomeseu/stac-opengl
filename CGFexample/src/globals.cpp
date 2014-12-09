#include "Globals.h"
#include <iostream>


GLenum Globals::getMode(){
    if(this->mode == "fill"){
        return GL_FILL;
    }else if(this->mode == "point"){
        return GL_POINT;
    }else if(this->mode == "line"){
        return GL_LINE;
    }
    throw "Not valid globals mode";
}

GLenum Globals::getShading(){
    if(this->shading == "flat"){
        return GL_FLAT;
    }else if(this->shading == "gouraud"){
        return GL_SMOOTH;
    }
    
    //if no shading defined, assume flat shading, but warn in the console
    std::cout << "WARNING: NO SHADING DEFINED - DEFAULTING TO GL_FLAT" << std::endl;
    return GL_FLAT;
}

float Globals::getBackground(int position){
    return this->background[position];
}


GLenum Globals::getCulling(){
    if(this->face=="none"){
        return -1;
    }
    else if(this->face == "back"){
        return GL_BACK;
    }else if(this->face == "front"){
        return GL_FRONT;
    }else if(this->face == "both"){
        return GL_FRONT_AND_BACK;
    }
    throw "Not valid globals culling";
}


GLenum Globals::getOrder(){
    if(this->order == "ccw"){
        return GL_CCW;
    }else if(this->order == "cw"){
        return GL_CW;
    }
    throw "Not valid globals order";
}




float * Globals::getLightAmbient(){
    return ambient;
}

GLenum Globals::isDoubleSided(){
    if(doublesided=="true")
        return GL_TRUE;
    return GL_FALSE;
}

GLenum Globals::isLocalLight(){
    if(local=="true")
        return GL_TRUE;
    return GL_FALSE;
}

GLenum Globals::isLightEnabled(){
    if(enabled=="true")
        return GL_TRUE;
    return GL_FALSE;
}

