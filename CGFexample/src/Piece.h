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
public:
    
    std::string getType() { return "piece"; }
    
    void draw();
};

#endif /* defined(__CGFExample__Piece__) */
