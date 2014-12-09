#ifndef __CGFExample__TPInterface__
#define __CGFExample__TPInterface__

#include <stdio.h>

#include "CGFinterface.h"
#include "Scene.h"

class TPInterface : public CGFinterface{
    Scene * scene;
    std::vector<Camera *> * camerasVector;
    std::vector<Light *> * lightsVector;
    
public:
    TPInterface(Scene * scene);
    void initGUI();
    
    virtual void processGUI(GLUI_Control *ctrl);
    
    int camerasVar;
    int lightsVar[8];
    int represVar;
    
};

#endif /* defined(__CGFExample__TPInterface__) */
