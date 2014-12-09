#include "TPInterface.h"
#include "Camera.h"
#include <iostream>


#define WIRED 7
#define TEXTURED 8


TPInterface::TPInterface(Scene * scene){
    this->scene = scene;
}

void TPInterface::initGUI(){
    /** MAIN PANEL */
    GLUI_Panel * panel=addPanel("Painel de Controlo");
    
    /** LIGHT PANEL ***/
    GLUI_Panel *camerasPanel = addPanelToPanel(panel, "Camaras", 1);
    addColumnToPanel(panel);
    GLUI_Panel *lightsPanel = addPanelToPanel(panel, "Luzes");
    addColumnToPanel(panel);
    GLUI_Panel *representationPanel = addPanelToPanel(panel, "Representacao");
    
    GLUI_Listbox * camerasList = addListboxToPanel(camerasPanel, "Camaras", &camerasVar , 1);
    
    camerasVector = scene->getCameras();
    lightsVector = scene->getLights();
    
    for ( int i = 0; i< camerasVector->size(); i++){
        camerasList->add_item(i, camerasVector->at(i)->getID().c_str());
        if(strcmp(camerasVector->at(i)->getID().c_str(), scene->getActiveCamera()->getID().c_str()) == 0){
            camerasList->set_int_val(i);
        }
    }
    
    for ( int i = 0; i< lightsVector->size(); i++){
        char* temp_str = new char[lightsVector->at(i)->getId().length() + 1];
        strcpy(temp_str, lightsVector->at(i)->getId().c_str());
        
        if(lightsVector->at(i)->getEnabled()){
            lightsVar[i]=1;
        }else{
            lightsVar[i]=0;
        }
       
        addCheckboxToPanel(lightsPanel, temp_str, &lightsVar[i],0);
    }
    
    
    GLUI_RadioGroup* representation = addRadioGroupToPanel(representationPanel, &represVar, 0);
    if(scene->isWired())
    {
        representation->set_int_val(1);
    } else {
        representation->set_int_val(0);
    }
    
    addRadioButtonToGroup(representation, "Fill");
    addRadioButtonToGroup(representation, "Wired");
    
}


void TPInterface::processGUI(GLUI_Control *ctrl){
    /** CAMERAS HANDLE **/
    scene->setActiveCamera(camerasVector->at(camerasVar));
    /** LIGHTS HANDLE **/
    for(int i =0; i < lightsVector->size(); i++){
        if(lightsVar[i]){
            lightsVector->at(i)->setEnabled(true);
        }else{
            lightsVector->at(i)->setEnabled(false);
        }
    }
    scene->activateLights();
    
    /** REPRESENTATION HANDLE **/
    if(represVar==(WIRED/WIRED)){
        scene->setWired(true);
    }
    
    
    if(represVar==(0/TEXTURED)){
        scene->setWired(false);
    }
    
    
    
}


