//
//  Board.cpp
//  CGFExample
//
//  Created by José Miguel  Melo AKA doutor melaco on 02/12/14.
//  Copyright (c) 2014 me. All rights reserved.
//

#include "Piece.h"

void Piece::draw(){
    glPushMatrix();
    
    Cylinder * cylinder = new Cylinder();
    
    cylinder->setBase(1);
    cylinder->setHeight(1);
    cylinder->setTop(1);
    cylinder->setStacks(20);
    cylinder->setSlices(20);
    
    cylinder->draw();
    
    glPopMatrix();
    
}