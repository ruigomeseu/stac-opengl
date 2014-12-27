//
//  Piece.h
//  CGFExample
//

#ifndef __CGFExample__Piece__
#define __CGFExample__Piece__

#include <stdio.h>
#include "Primitives.h"

class Piece : public Primitives{
private:
    std::string piece;
    
    
    
    Appearance * appearance_black = new Appearance();
    Appearance * appearance_white = new Appearance();
    
    Appearance * appearance_normal = new Appearance();

    
public:
    Piece(){
        appearance_white->setTexture("/Users/ruigomes/Projects/OpenGL/stac-opengl/CGFexample/data/white_wood.jpg");
        appearance_black->setTexture("/Users/ruigomes/Projects/OpenGL/stac-opengl/CGFexample/data/black_wood.jpg");
        appearance_normal->setTexture("/Users/ruigomes/Projects/OpenGL/stac-opengl/CGFexample/data/normal_wood.jpg");
        
    }
    std::string getType() { return "piece"; }
    
    void draw();
    
    void setPiece(std::string piece){
        this->piece=piece;
    }
    std::string getPiece(){ return this->piece; }
};

#endif /* defined(__CGFExample__Piece__) */
