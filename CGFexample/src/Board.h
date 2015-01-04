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
#include <utility>
#include "Node.h"
#include "Piece.h"
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <regex>
#include "Position.h"

using namespace std;


class Board : public Primitives{
private:
    int sizex, sizey;
    Node * node;
    
    Appearance * appearance_white = new Appearance();
    
    Appearance * appearance_black = new Appearance();
    
    Appearance * appearance_white_bright = new Appearance();
    
    Appearance * appearance_black_bright = new Appearance();
    Piece * piece;
    std::string board[5][5];
    
    // current player
    std::string currentPlayer;
    
    bool carry;
    bool hasAnimation;
    int pieceToAnimate[2];
    LinearAnimation * animation;
    
    
    std::vector<std::string> * boardsHistory;
    
    std::vector<std::string> carryHistory;
    std::vector<int> moves_x_History;
    std::vector<int> moves_y_History;
    
    
public:
    Board(){
        node = new Node(true);
        piece = new Piece();
        node->addPrimitives(piece);
        
        appearance_white->setTexture("../data/white_wood.jpg");
        appearance_black->setTexture("../data/black_wood.jpg");
        appearance_black_bright->setTexture("../data/black_wood_bright.png");
        appearance_white_bright->setTexture("../data/white_wood_bright.png");
        
        this->loadFromString("[[p1,p1,p1,p1,b1],[p1,p1,p1,p1,p1],[p1,p1,p1,p1,p1],[p1,p1,p1,p1,p1],[a1,p1,p1,p1,p1]].");
        this->currentPlayer="a1";
        this->carry=false;
        this->hasAnimation = false;
        boardsHistory = new std::vector<std::string> ();
        
        boardsHistory->push_back(this->toString());
        
    }
    
    void addCarryToHistory(std::string carry){
        this->carryHistory.push_back(carry);
    }
    
    std::vector<std::string > getCarryHistory(){
        return this->carryHistory;
    }
    
    void removeLastCarryFromHistory(){
        this->carryHistory.pop_back();
    }
    
    void addMoveToHistory(int toX, int toY)
    {
        this->moves_x_History.push_back(toX);
        this->moves_y_History.push_back(toY);
    }
    
    void removeLastMoveFromHistory()
    {
        this->moves_x_History.pop_back();
        this->moves_y_History.pop_back();
    }
    
    std::vector<int> getMoves_X_History(){
        return this->moves_x_History;
    }
    std::vector<int> getMoves_Y_History(){
        return this->moves_y_History;
    }
    
    
    
    bool getHasAnimation(){
        return this->hasAnimation;
    }
    
    void animateIfExists(int i, int j, int pieceToAnimate[2]);
    
    ControlPoint getOpenGlPosition(int x, int y);
    
    int getSizeX(){return this->sizex; }
    int getSizeY(){ return this->sizey; }
    
    void setSizeX(int sizex){this->sizex = sizex;}
    void setSizeY(int sizey){this->sizey = sizey;}
    
    std::string getType() { return "board"; }
    void draw();
    
    
    void animate(int toX, int toY);
    
    std::string toString();
    void loadFromString(std::string board_string);
    
    
    void resetBoard(){
        this->loadFromString("[[p1,p1,p1,p1,b1],[p1,p1,p1,p1,p1],[p1,p1,p1,p1,p1],[p1,p1,p1,p1,p1],[a1,p1,p1,p1,p1]].");
        this->currentPlayer="a1";
        this->carry=false;
        this->boardsHistory->clear();
        this->boardsHistory->push_back(toString());
    }
    
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
    void setPlayer(std::string player){
        this->currentPlayer.clear();
        this->currentPlayer = player;
    }
    void changePlayer(){
        if(currentPlayer.compare("a1") == 0){
            currentPlayer="b1";
        }else{
            currentPlayer="a1";
        }
    }
    
    std::vector<Position> calculatePossibleMoves();
    
    void setBoardHistory(std::vector<std::string> * boardsHistory){
        this->boardsHistory = boardsHistory;
    }
    
    std::vector<std::string> * getBoardsHistory(){
        return this->boardsHistory;
    }
    
    void addBoardToHistory(std::string board){
        boardsHistory->push_back(board);
    }
    

};

#endif /* defined(__CGFExample__Board__) */
