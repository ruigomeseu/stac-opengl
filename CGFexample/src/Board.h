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
#include "Piece.h"
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <regex>

using namespace std;


class Board : public Primitives{
private:
    int sizex, sizey;
    
    Appearance * appearance_white = new Appearance();
    
    Appearance * appearance_black = new Appearance();
    Piece * piece;
    std::string board[5][5];
    
    
    // current player
    std::string currentPlayer;
    
    bool carry;
    
public:
    Board(){
        piece = new Piece();
        appearance_white->setTexture("/Users/josemiguelmelo/Documents/FEUP/3o Ano/LAIG/Game/CGFexample/data/white_wood.jpg");
        appearance_black->setTexture("/Users/josemiguelmelo/Documents/FEUP/3o Ano/LAIG/Game/CGFexample/data/black_wood.jpg");
        this->loadFromString("[[p1,p1,p1,p1,b1],[p1,p1,p1,p1,p1],[p1,p1,p1,p1,p1],[p1,p1,p1,p1,p1],[a1,p1,p1,p1,p1]].");
        this->currentPlayer="a1";
        this->carry=false;
    }
    
    int getSizeX(){return this->sizex; }
    int getSizeY(){ return this->sizey; }
    
    void setSizeX(int sizex){this->sizex = sizex;}
    void setSizeY(int sizey){this->sizey = sizey;}
    
    std::string getType() { return "board"; }
    void draw();
    
    
    std::string toString();
    void loadFromString(std::string board_string);
    
    
    
    
    std::string getCurrentPlayer(){
        return this->currentPlayer;
    }
    
    bool getCarry(){ return carry; }
    
    void setCarry(bool carry){
        this->carry = carry;
    }
    
    void toggleCarry(){
        if(carry){
            carry = false;
        }else{
            carry = true;
        }
    }
    void changePlayer(){
        if(strcmp(currentPlayer.c_str(), "a1") == 0){
            currentPlayer="b1";
        }else{
            currentPlayer="a1";
        }
    }
    

};

#endif /* defined(__CGFExample__Board__) */
