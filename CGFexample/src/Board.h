//
//  Board.h
//  CGFExample
//
//  Created by José Miguel  Melo on 02/12/14.
//  Copyright (c) 2014 me. All rights reserved.
//

#ifndef __CGFExample__Board__
#define __CGFExample__Board__

#include <stdio.h>
#include "Primitives.h"
#include <cstring>


class Board : public Primitives{
private:
    int sizex, sizey;
    
    Appearance * appearance_white = new Appearance();
    
    Appearance * appearance_black = new Appearance();
    
    std::string board[5][5];

public:
    Board(){
        appearance_white->setTexture("/Users/josemiguelmelo/Documents/FEUP/3o Ano/LAIG/Game/CGFexample/data/white_wood.jpg");
        appearance_black->setTexture("/Users/josemiguelmelo/Documents/FEUP/3o Ano/LAIG/Game/CGFexample/data/black_wood.jpg");
        for(int i = 0; i < 5; i++){
            for(int j = 0; j< 5; j++){
                board[i][j] = "p1";
            }
        }
    }
    
    int getSizeX(){return this->sizex; }
    int getSizeY(){ return this->sizey; }
    
    void setSizeX(int sizex){this->sizex = sizex;}
    void setSizeY(int sizey){this->sizey = sizey;}
    
    std::string getType() { return "board"; }
    void draw();
};

#endif /* defined(__CGFExample__Board__) */
