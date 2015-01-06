//
//  Board.cpp
//  CGFExample
//
//  Created by José Miguel  Melo on 02/12/14.
//  Copyright (c) 2014 me. All rights reserved.
//

#include "Board.h"

void Board::animateIfExists(int i, int j, int pieceToAnimate[2])
{
    if(this->hasAnimation && i == pieceToAnimate[0] && j == pieceToAnimate[1])
    {
        cout << "current player = " << currentPlayer<<endl;
        if(this->animation->getFinished()){
            cout << "current player = " << currentPlayer<<endl;
            cout << "animation ended" << endl;
            cout << "current player 1 = " << currentPlayer<<endl;
            this->hasAnimation = false;
            cout << "current player 2 = " << currentPlayer<<endl;
            this->loadFromString(boardsHistory->at(boardsHistory->size()-1));
            cout << "current player 3 = " << currentPlayer<<endl;
            this->carry = false;
            cout << "current player 4 = " << currentPlayer<<endl;
        }
        
        this->animation->increment(30);
        glTranslatef(this->animation->getCurrentAnimationPoint().getX(),
                     -this->animation->getCurrentAnimationPoint().getZ(),
                     this->animation->getCurrentAnimationPoint().getY()
                     );
        
    }
}



std::vector<Position> Board::calculatePossibleMoves(){
    int positionX, positionY;
    std::vector<Position> moves;
    cout << "curretn player moves = " << currentPlayer<<endl;
    // find player position
    for(int i=0; i < 5; i++)
    {
        for (int j=0; j<5; j++)
        {
            if(board[i][j][0] == currentPlayer[0] && board[i][j][1] != '4')
            {
                positionX = i;
                positionY = j;
            }
        }
    }

    std::string otherPlayer ;
    if(currentPlayer.compare("a1")== 0){
        otherPlayer="b1";
    }else{
        otherPlayer="a1";
    }
    
    
    if(carry)
    {
        if( board[positionX][positionY][1] == '2' || board[positionX][positionY][1] == '3' )
        {
            return moves;
        }
        
    }
    

    for( unsigned int i =0 ; i < 5; i++){
        if( board[positionX][i][0] != otherPlayer[0] && board[positionX][i][0] != currentPlayer[0] && i != positionY )
        {
            moves.push_back(Position(positionX, i));
        }
    }
    
    for( unsigned int i =0 ; i < 5; i++){
        if( board[i][positionY][0] != otherPlayer[0] && board[i][positionY][0] != currentPlayer[0] && i != positionX )
        {
            moves.push_back(Position(i, positionY));
        }
    }
    
    return moves;
    
    
    
}

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
            glRotated(-90, 1, 0, 0);
            if(strcmp(board[i][j].c_str(), "vv")==0){
                
            }else if(strcmp(board[i][j].c_str(), "a0") == 0){
                animateIfExists(i, j, pieceToAnimate);
                piece->setPiece("a0");
                piece->draw();
            }else if(strcmp(board[i][j].c_str(), "b0") == 0){
                animateIfExists(i, j, pieceToAnimate);
                piece->setPiece("b0");
                piece->draw();
            }else if(strcmp(board[i][j].c_str(), "p1") == 0){
                piece->setPiece("p1");
                piece->draw();
            }else if(strcmp(board[i][j].c_str(), "p2") == 0){
                piece->setPiece("p2");
                piece->draw();
            }else if(strcmp(board[i][j].c_str(), "a1") == 0){
                if(carry)
                    animateIfExists(i, j, pieceToAnimate);
                piece->setPiece("p1");
                piece->draw();
                glTranslatef(0, 0, 1);
                if(!carry)
                    animateIfExists(i, j, pieceToAnimate);
                piece->setPiece("a1");
                piece->draw();
            }else if(strcmp(board[i][j].c_str(), "b1") == 0){
                if(carry)
                    animateIfExists(i, j, pieceToAnimate);
                piece->setPiece("p1");
                piece->draw();
                glTranslatef(0, 0, 1);
                if(!carry)
                    animateIfExists(i, j, pieceToAnimate);
                
                piece->setPiece("b1");
                piece->draw();
            }else if(strcmp(board[i][j].c_str(), "a3") == 0){
                if(carry)
                    animateIfExists(i, j, pieceToAnimate);
                piece->setPiece("p2");
                piece->draw();
                glTranslatef(0, 0, 2);
                piece->setPiece("p2");
                piece->draw();
                glTranslatef(0, 0, 2);
                if(!carry)
                    animateIfExists(i, j, pieceToAnimate);
                
                piece->setPiece("a1");
                piece->draw();
            }else if(strcmp(board[i][j].c_str(), "b3") == 0){
                if(carry)
                    animateIfExists(i, j, pieceToAnimate);
                piece->setPiece("p2");
                piece->draw();
                glTranslatef(0, 0, 2);
                piece->setPiece("p2");
                piece->draw();
                glTranslatef(0, 0, 2);
                if(!carry)
                    animateIfExists(i, j, pieceToAnimate);
                
                piece->setPiece("b1");
                piece->draw();
            }else if(strcmp(board[i][j].c_str(), "a2") == 0){
                if(carry)
                    animateIfExists(i, j, pieceToAnimate);
                piece->setPiece("p1");
                piece->draw();
                glTranslatef(0, 0, 1);
                piece->setPiece("p1");
                piece->draw();
                glTranslatef(0, 0, 1);
                if(!carry)
                    animateIfExists(i, j, pieceToAnimate);
                
                piece->setPiece("a1");
                piece->draw();
            }else if(strcmp(board[i][j].c_str(), "b2") == 0){
                if(carry)
                    animateIfExists(i, j, pieceToAnimate);
                piece->setPiece("p1");
                piece->draw();
                glTranslatef(0, 0, 1);
                piece->setPiece("p1");
                piece->draw();
                glTranslatef(0, 0, 1);
                if(!carry)
                    animateIfExists(i, j, pieceToAnimate);
                
                piece->setPiece("b1");
                piece->draw();
            }else if(strcmp(board[i][j].c_str(), "a4") == 0){
                if(carry)
                    animateIfExists(i, j, pieceToAnimate);
                piece->setPiece("p2");
                piece->draw();
                glTranslatef(0, 0, 2);
                piece->setPiece("p2");
                piece->draw();
                glTranslatef(0, 0, 2);
                if(!carry)
                    animateIfExists(i, j, pieceToAnimate);
                
                piece->setPiece("a1");
                piece->draw();
            }else if(strcmp(board[i][j].c_str(), "b4") == 0){
                if(carry)
                    animateIfExists(i, j, pieceToAnimate);
                piece->setPiece("p2");
                piece->draw();
                glTranslatef(0, 0, 2);
                piece->setPiece("p2");
                piece->draw();
                glTranslatef(0, 0, 2);
                if(!carry)
                    animateIfExists(i, j, pieceToAnimate);
                
                piece->setPiece("b1");
                piece->draw();
            }
            glPopMatrix();
        }
        
        glPopMatrix();
    }
    
    glPopMatrix();
    
    
    
    
    std::vector<Position> moves = calculatePossibleMoves();
    
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
            
            Position position(r,c);
            
            if((r%2) == 0)
            {
                if((c%2)==0)
                {
                    if(position.isInVector(moves)){
                        appearance_black_bright->apply();
                    }else{
                        appearance_black->apply();
                    }
                } else {
                    if(position.isInVector(moves)){
                        appearance_white_bright->apply();
                    }else{
                        appearance_white->apply();
                    }
                }
            } else {
                if((c%2)==0)
                {
                    if(position.isInVector(moves)){
                        appearance_white_bright->apply();
                    }else{
                        appearance_white->apply();
                    }
                    
                } else {
                    if(position.isInVector(moves)){
                        appearance_black_bright->apply();
                    }else{
                        appearance_black->apply();
                    }
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
    std::string player_aux = currentPlayer;
    // find player position
    for(int i=0; i < 5; i++)
    {
        for (int j=0; j<5; j++)
        {
            if(board[i][j][0] == player_aux[0] && board[i][j][1] != 4)
            {
                positionX = i;
                positionY = j;
            }
        }
    }
    
    this->pieceToAnimate[0] = positionX;
    this->pieceToAnimate[1] = positionY;
    this->hasAnimation = true;
    
    this->animation = new LinearAnimation("animation", 0);
    
    ControlPoint initialPoint = this->getOpenGlPosition(positionX, positionY);
    ControlPoint finalPoint = this->getOpenGlPosition(toX, toY);
    ControlPoint initialPointHeight = ControlPoint(initialPoint.getX(), initialPoint.getY() + 10, initialPoint.getZ());
    ControlPoint finalPointHeight = ControlPoint(finalPoint.getX(), finalPoint.getY() + 10, finalPoint.getZ());
    
    this->animation->addControlPoint(initialPoint);
    this->animation->addControlPoint(initialPointHeight);
    
    this->animation->addControlPoint(finalPointHeight);
    this->animation->addControlPoint(finalPoint);
    
    this->animation->calculateTotalDistance();
    
    //cout << positionX << " to " << toX << endl;
    //cout << positionY << " to " << toY << endl;
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
    //cout << board_string << endl;
    
    
    std::string pieceRegex = "[a-z]+[0-9]*";
    std::string player_aux = currentPlayer;
    
    regex reg1(pieceRegex, regex_constants::icase);
    
    sregex_iterator it(board_string.begin(), board_string.end(), reg1);
    sregex_iterator it_end;
    
    int pieceNumber = 0;
    
    
    while(it != it_end) {
        std::smatch match = *it;
        std::string match_str = match.str();
        
       // cout << match_str << endl;
        
        board[pieceNumber/5][pieceNumber%5] = match_str;
        
        ++it;
        pieceNumber++;
    }
    
    currentPlayer = player_aux;
    
}