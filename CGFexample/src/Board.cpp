//
//  Board.cpp
//  CGFExample
//
//  Created by José Miguel  Melo on 02/12/14.
//  Copyright (c) 2014 me. All rights reserved.
//

#include "Board.h"
#include "Piece.h"

void Board::draw(){
    Rectangle * square = new Rectangle();
    Piece * piece = new Piece();
    square->setX1(0);
    square->setX2(5);
    square->setY1(0);
    square->setY2(5);
    
    
    
    
    glPushMatrix();
    glTranslatef(2.5, 0, 2.5);
    
    for(int i = 0; i < 5; i++){
        glPushMatrix();
        
        for(int j = 0; j< 5; j++){
            glPushMatrix();
            glTranslatef(5*i, 0, 5*j);
            glRotated(-90, 1,0,0);
            piece->draw();
            glPopMatrix();
        }
        
        glPopMatrix();
    }
    
    glPopMatrix();
    
    glPushName(-1);
    glPushMatrix();
    // example 2: structured naming
    for (int r=0; r < sizex; r++)
    {
        glPushMatrix();
        glTranslatef( r*5,0, 0);
        glLoadName(r);
        for (int c=0; c < sizey; c++)
        {
            glPushMatrix();
            
            glTranslatef(0,0,(c+1)*5);
            glRotatef(-90,1,0,0);
            glPushName(c);
            if((r%2) == 0)
            {
                if((c%2)==0)
                {
                    appearance_black->apply();
                } else {
                    appearance_white->apply();
                }
            } else {
                if((c%2)==0)
                {
                    appearance_white->apply();
                } else {
                    appearance_black->apply();
                }
            }
            square->draw();
            glPopName();
            glPopMatrix();
        }
        glPopMatrix();
    }
    
    glPopMatrix();
    
    
}