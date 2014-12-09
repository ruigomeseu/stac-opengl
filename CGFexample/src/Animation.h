//
//  Animation.h
//  CGFExample
//


#ifndef __CGFExample__Animation__
#define __CGFExample__Animation__

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "ControlPoint.h"
#include <cmath>

class Animation{
protected:
    std::string id;
    float span;
    bool finished;
    bool initialized;
    bool drawnThisFrame;
public:
    Animation(){}
    Animation(std::string id, float span){
        this->id = id;
        this->span=span;
        this->finished = false;
        this->drawnThisFrame = true;
    }
    
    bool getInitialized()
    {
        return this->initialized;
    }
    
    bool getDrawnThisFrame()
    {
        return this->drawnThisFrame;
    }
    
    void setDrawnThisFrame(bool drawnThisFrame)
    {
        this->drawnThisFrame = drawnThisFrame;
    }
    
    void setInitialized(bool initialized)
    {
        this->initialized = initialized;
    }
    
    bool getFinished()
    {
        return this->finished;
    }
    
    void setId(std::string id){ this->id = id;}
    void setSpan(float span){ this->span = span; }
    
    std::string getId(){ return this->id; }
    float getSpan(){ return this->span; }
    
    virtual void increment(unsigned long t) = 0;
    virtual std::string getType() = 0;
    virtual ControlPoint getCurrentAnimationPoint() = 0;
};


class LinearAnimation: public Animation{
private:
    std::vector<ControlPoint> controlPoints;
    ControlPoint currentAnimationPoint = ControlPoint(0,0,0);
    float totalDistance;
    float speed;
    int currentPoint;
    
    float sumDistanceWalked;
    
public:
    LinearAnimation(std::string id, float span){
        this->id = id;
        this->span = span;
        totalDistance = 0;
        speed = 0;
        currentPoint = 0;
        sumDistanceWalked = 0;
        initialized = false;
        this->drawnThisFrame = true;
        this->finished = false;
    }
    
    ControlPoint getCurrentAnimationPoint()
    {
        return this->currentAnimationPoint;
    }
    
    std::string getType()
    {
        return "linear";
    }
    
    void addControlPoint(ControlPoint controlPoint){ this->controlPoints.push_back(controlPoint); }
    
    void setControlPoints(std::vector<ControlPoint> controlPoints){ this->controlPoints = controlPoints;}
    
    std::vector<ControlPoint> getControlPoints(){ return this->controlPoints;}
    float getTotalDistance(){ return this->totalDistance; }
    float getSpeed(){ return this->speed; }
    
    float distanceBetweenPoints(ControlPoint p1, ControlPoint p2){
        return sqrt( pow(p1.getX()-p2.getX() , 2) + pow(p1.getY() - p2.getY(), 2) + pow(p1.getZ() - p2.getZ(),2 ));
    }
    
    void calculateTotalDistance(){
        totalDistance = 0;
        for (int i = 0; i< controlPoints.size()-1; i++){
            totalDistance += distanceBetweenPoints(controlPoints.at(i), controlPoints.at(i+1));
        }
        
        this->calculateSpeed();
    }
    
    void calculateSpeed() {
        speed = totalDistance / span;
    }
    
    void increment(unsigned long t)
    {
        std::cout << "incrementing" << std::endl;
        float distanceToWalk = (speed * t) / 1000;
        
        if(currentPoint + 1 < controlPoints.size())
        {
            float surfaceTriangleX = abs( controlPoints[currentPoint].getX() - controlPoints[currentPoint+1].getX());
            
            float surfaceTriangleZ = abs( controlPoints[currentPoint].getZ() - controlPoints[currentPoint+1].getZ());
            
            float surfaceAngle;
            if(surfaceTriangleX != 0) {
                surfaceAngle = atan(surfaceTriangleZ / surfaceTriangleX);
            } else {
                //surfaceAngle = 0;
                surfaceAngle = atan(surfaceTriangleZ / controlPoints[currentPoint].getX());
            }
            
            float heightTriangleY = abs( controlPoints[currentPoint].getY() - controlPoints[currentPoint+1].getY());
            
            float surfaceTriangleHypotenuse = sqrt( pow(surfaceTriangleX, 2) + pow(surfaceTriangleZ, 2) );
            
            float heightTriangleAngle = atan(heightTriangleY / surfaceTriangleHypotenuse);
            
            float distanceToWalkY = sin(heightTriangleAngle) * distanceToWalk;
            
            float partialSurfaceTriangleHypotenuse = cos(heightTriangleAngle) * distanceToWalk;
            
            float distanceToWalkX = cos(surfaceAngle) * partialSurfaceTriangleHypotenuse;
            float distanceToWalkZ;
            
            distanceToWalkZ = sin(surfaceAngle) * partialSurfaceTriangleHypotenuse;
           
            std::cout << "angle = " << surfaceAngle<<std::endl;
            std::cout << "distance X = " << distanceToWalkX<<std::endl;
            std::cout << "distance Z = " << distanceToWalkZ<<std::endl;
            
            
            sumDistanceWalked += distanceToWalk;
            
            if(controlPoints[currentPoint].getX() > controlPoints[currentPoint+1].getX())
                distanceToWalkX = -distanceToWalkX;
            
            if(controlPoints[currentPoint].getY() > controlPoints[currentPoint+1].getY())
                distanceToWalkY = -distanceToWalkY;
            
            if(controlPoints[currentPoint].getZ() > controlPoints[currentPoint+1].getZ())
                distanceToWalkZ = -distanceToWalkZ;
            
            ControlPoint pointToAnimate(distanceToWalkX, distanceToWalkY, distanceToWalkZ);
            std::cout << "calculated point2" << std::endl;
            
            this->currentAnimationPoint = pointToAnimate;
            
            std::cout << "drawn = false" << std::endl;
            this->drawnThisFrame = false;
            
            std::cout << "Distanced walked (sum): " << sumDistanceWalked << std::endl;
            std::cout << "Distance between points: " << distanceBetweenPoints(controlPoints[currentPoint], controlPoints[currentPoint+1]) << std::endl;
            
            if(sumDistanceWalked > distanceBetweenPoints(controlPoints[currentPoint], controlPoints[currentPoint+1])) {
                std::cout << "Animation point increased" << std::endl;
                sumDistanceWalked = 0;
                currentPoint++;
                if(currentPoint == controlPoints.size() - 1)
                {
                    this->finished = true;
                }
            }
            
        } else {
            //animation ended
            ControlPoint pointToAnimate(0, 0, 0);
            this->currentAnimationPoint = pointToAnimate;
        }
    }
    
    
};

class CircularAnimation: public Animation{
private:
    float centerX, centerY, centerZ;
    float startAng;
    float rotAng;
    float radius;
    float angularSpeed;
    float currentAngle;
    
public:
    CircularAnimation(std::string id, float span){
        this->id = id;
        this->span = span;
        initialized = false;
        this->drawnThisFrame = true;
        this->finished = false;
    }
    
    ControlPoint getCurrentAnimationPoint()
    {
        return ControlPoint(0,0,0);
    }
    
    std::string getType()
    {
        return "circular";
    }
    
    float getCenterX()
    {
        return this->centerX;
    }
    
    float getCenterY()
    {
        return this->centerY;
    }
    
    float getCenterZ()
    {
        return this->centerZ;
    }
    
    float getStartAng()
    {
        return this->startAng;
    }
    
    float getRotAng()
    {
        return this->rotAng;
    }
    
    float getRadius()
    {
        return this->radius;
    }
    
    void setCenter(float x, float y, float z)
    {
        this->centerX = x;
        this->centerY = y;
        this->centerZ = z;
    }
    
    void setStartAng(float startAng)
    {
        this->startAng = startAng;
        this->currentAngle = startAng;
    }
    
    void setRotAng(float rotAng)
    {
        this->rotAng = rotAng;
        this->angularSpeed = (rotAng/span);
    }
    
    void setRadius(float radius)
    {
        this->radius = radius;
    }
    
    float getCurrentAngle()
    {
        return this->currentAngle;
    }
    
    void increment(unsigned long t)
    {
        if(abs(currentAngle) >= abs(startAng + rotAng))
        {
            this->finished = true;
        } else {
            currentAngle += (angularSpeed * t) / 1000;
            
            std::cout << "currentAngle " << currentAngle << std::endl;
            this->drawnThisFrame = false;
        }
    }
    
};

#endif /* defined(__CGFExample__Animation__) */