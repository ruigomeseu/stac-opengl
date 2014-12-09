#ifndef _ANFInterpreter_H_
#define _ANFInterpreter_H_

#include "tinyxml.h"

#include "Globals.h"
#include "Scene.h"

#include <string>
#include <iostream>
#include <vector>
#include <map>

#include "Transforms.h"
#include "Texture.h"
#include "Primitives.h"
#include "Appearance.h"
#include "Light.h"
#include "Animation.h"
#include "Board.h"


class ANFInterpreter
{
public:
	ANFInterpreter(char *filename, Scene * scene);
	~ANFInterpreter();

	static TiXmlElement *findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val);
    
    void loadGraph();
    void loadLights();
    void replaceEmptyNodes();
    void replaceEmptyAnimations();
    std::map<std::string, Node*> * loadDescendants(TiXmlElement * descendantsElements);
    std::vector<Transforms *> * loadTransforms(TiXmlElement * transformsElements);
    std::vector<Primitives *> * loadPrimitives(TiXmlElement * primitivesElement);
    std::map<std::string, Texture*> * loadTextures();
    std::map<std::string, Appearance*> * loadAppearances();
    std::map<std::string, Animation*> * loadAnimations();
    
protected:
    Scene * scene;
	TiXmlDocument* doc;
    
    TiXmlElement* globalsElement;
    TiXmlElement* camerasElement;
    TiXmlElement* graphElement;
    TiXmlElement* texturesElement;
    TiXmlElement* appearancesElement;
    TiXmlElement* animationsElement;
    TiXmlElement* lightsElement;
};

#endif