//
//  Position.h
//  CGFExample
//
//  Created by José Miguel Melo on 03/01/15.
//  Copyright (c) 2015 me. All rights reserved.
//

#ifndef __CGFExample__Position__
#define __CGFExample__Position__

#include <stdio.h>
#include <vector>

class Position{
public:
    Position(int x, int y){
        this->x = x;
        this->y = y;
    }
    int x, y;
    
    bool isInVector(std::vector<Position> vec){
        for (unsigned int i = 0; i < vec.size(); i++)
        {
            if(vec.at(i).x == this->x && vec.at(i).y == this->y)
                return true;
        }
        return false;
    }
};
#endif /* defined(__CGFExample__Position__) */
