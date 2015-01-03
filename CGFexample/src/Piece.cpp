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
    
    appearance_normal->apply();
    
    if(strcmp(piece.c_str(), "p1") ==0) {
        cylinder->draw();
    }else if(strcmp(piece.c_str(), "p2") == 0){
        cylinder->draw();
        glTranslatef(0, 0, 1);
        cylinder->draw();
    }else if(strcmp(piece.c_str(), "a0") == 0){
        appearance_white->apply();
        cylinder->draw();
    }else if(strcmp(piece.c_str(), "b0") == 0){
        appearance_black->apply();
        cylinder->draw();
    }else if(strcmp(piece.c_str(), "a1") == 0){
        appearance_white->apply();
        cylinder->draw();
    }else if(strcmp(piece.c_str(), "b1") == 0){
        appearance_black->apply();
        cylinder->draw();
    }
    
    glPopMatrix();
    
}