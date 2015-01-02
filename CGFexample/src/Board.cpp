//
//  Board.cpp
//  CGFExample
//
//  Created by José Miguel  Melo on 02/12/14.
//  Copyright (c) 2014 me. All rights reserved.
//

#include "Board.h"

void Board::draw(){
    
    Rectangle * square = new Rectangle();
    
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
            if(this->hasAnimation && i == pieceToAnimate[0] && j == pieceToAnimate[1])
            {
                this->animation->increment(30);
                glTranslatef(this->animation->getCurrentAnimationPoint().getX(),
                             this->animation->getCurrentAnimationPoint().getY(),
                             this->animation->getCurrentAnimationPoint().getZ());
            }
            glRotated(-90, 1,0,0);
            if(strcmp(board[i][j].c_str(), "vv")==0){
                
            }else if(strcmp(board[i][j].c_str(), "a0") == 0){
                piece->setPiece("a0");
                piece->draw();
            }else if(strcmp(board[i][j].c_str(), "b0") == 0){
                piece->setPiece("b0");
                piece->draw();
            }else if(strcmp(board[i][j].c_str(), "p1") == 0){
                piece->setPiece("p1");
                piece->draw();
            }else if(strcmp(board[i][j].c_str(), "p2") == 0){
                piece->setPiece("p2");
                piece->draw();
            }else if(strcmp(board[i][j].c_str(), "a1") == 0){
                piece->setPiece("a1");
                piece->draw();
            }else if(strcmp(board[i][j].c_str(), "b1") == 0){
                piece->setPiece("b1");
                piece->draw();
            }else if(strcmp(board[i][j].c_str(), "a3") == 0){
                piece->setPiece("p2");
                piece->draw();
                glTranslatef(0, 0, 1);
                piece->setPiece("p1");
                piece->draw();
                glTranslatef(0, 0, 1);
                piece->setPiece("a1");
                piece->draw();
            }else if(strcmp(board[i][j].c_str(), "b3") == 0){
                piece->setPiece("p2");
                piece->draw();
                glTranslatef(0, 0, 1);
                piece->setPiece("p1");
                piece->draw();
                glTranslatef(0, 0, 1);
                piece->setPiece("b1");
                piece->draw();
            }else if(strcmp(board[i][j].c_str(), "a2") == 0){
                piece->setPiece("p1");
                piece->draw();
                glTranslatef(0, 0, 1);
                piece->setPiece("a1");
                piece->draw();
            }else if(strcmp(board[i][j].c_str(), "b2") == 0){
                piece->setPiece("p1");
                piece->draw();
                glTranslatef(0, 0, 1);
                piece->setPiece("b1");
                piece->draw();
            }else if(strcmp(board[i][j].c_str(), "a4") == 0){
                piece->setPiece("p2");
                piece->draw();
                glTranslatef(0, 0, 1);
                piece->setPiece("p2");
                piece->draw();
                glTranslatef(0, 0, 1);
                piece->setPiece("a1");
                piece->draw();
            }else if(strcmp(board[i][j].c_str(), "b4") == 0){
                piece->setPiece("p2");
                piece->draw();
                glTranslatef(0, 0, 1);
                piece->setPiece("p2");
                piece->draw();
                glTranslatef(0, 0, 1);
                piece->setPiece("b1");
                piece->draw();
            }
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

std::string Board::toString(){
    std::string final_string;
    final_string.append("[");
    for (int i = 0; i < 5; i++){
        final_string.append("[");
        for (int j = 0; j< 5; j++){
            final_string.append(board[i][j]);
            if(j < 4)
                final_string.append(",");
        }
        final_string.append("]");
        if(i < 4)
            final_string.append(",");
    }
    final_string.append("]");
    return final_string;
}

void Board::animate(int toX, int toY)
{
    int positionX, positionY;
    
    // find player position
    for(int i=0; i < 5; i++)
    {
        for (int j=0; j<5; j++)
        {
            if(board[i][j][0] == currentPlayer[0] && board[i][j][1] != 4)
            {
                positionX = i;
                positionY = j;
            }
        }
    }
    
    this->pieceToAnimate[0] = positionX;
    this->pieceToAnimate[1] = positionY;
    this->hasAnimation = true;
    
    this->animation = new LinearAnimation("animation", 3);
    
    ControlPoint initialPoint = this->getOpenGlPosition(positionX, positionY);
    ControlPoint finalPoint = this->getOpenGlPosition(toX, toY);
    ControlPoint initialPointHeight = ControlPoint(initialPoint.getX(), initialPoint.getY() + 10, initialPoint.getZ());
    
    ControlPoint finalPointHeight = ControlPoint(finalPoint.getX(), finalPoint.getY() + 10, finalPoint.getZ());
    
    this->animation->addControlPoint(initialPoint);
    this->animation->addControlPoint(initialPointHeight);
    
    this->animation->addControlPoint(finalPointHeight);
    this->animation->addControlPoint(finalPoint);
    
    this->animation->calculateTotalDistance();
    
    cout << positionX << endl;
    cout << positionY << endl;
}
                                     
ControlPoint Board::getOpenGlPosition(int x, int y)
{
    float posX = 2.5 + 5*x;
    
    float posY = 0;
    
    float posZ = 2.5 + 5*y;
    
    return ControlPoint(posX, posY, posZ);
}
                                     
                                     

void Board::loadFromString(std::string board_string)
{
    cout << board_string << endl;
    
    string pieceRegex = "[a-z]+[0-9]*";
    
    regex reg1(pieceRegex, regex_constants::icase);
    
    sregex_iterator it(board_string.begin(), board_string.end(), reg1);
    sregex_iterator it_end;
    
    int pieceNumber = 0;
    
    while(it != it_end) {
        std::smatch match = *it;
        std::string match_str = match.str();
        
        board[pieceNumber/5][pieceNumber%5] = match_str;
        
        ++it;
        pieceNumber++;
    }
    
    for(int y = 0; y < 5; y++){
        for(int x = 0; x < 5; x++){
            cout << board[y][x] << " ";
        }
        cout << endl;
    }
}