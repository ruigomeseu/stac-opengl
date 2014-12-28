#include "ANFInterpreter.h"

/** Loads ambient, diffuse and specular components **/
void loadLightComponents(Light* light,  TiXmlElement * componentElement){
    while(componentElement)
    {
        if(strcmp(componentElement->Attribute("type"), "ambient") == 0)
        {
            float ambient[4];
            
            std::string ambientString = componentElement->Attribute("value");
            
            sscanf(ambientString.c_str(), "%f %f %f %f", &ambient[0], &ambient[1], &ambient[2], &ambient[3]);
            
            light->setAmbient(ambient);
        } else if(strcmp(componentElement->Attribute("type"), "diffuse") == 0)
        {
            float diffuse[4];
            
            std::string diffuseString = componentElement->Attribute("value");
            
            sscanf(diffuseString.c_str(), "%f %f %f %f", &diffuse[0], &diffuse[1], &diffuse[2], &diffuse[3]);
            
            light->setDiffuse(diffuse);
        } else if(strcmp(componentElement->Attribute("type"), "specular") == 0)
        {
            float specular[4];
            
            std::string specularString = componentElement->Attribute("value");
            
            sscanf(specularString.c_str(), "%f %f %f %f", &specular[0], &specular[1], &specular[2], &specular[3]);
            
            light->setSpecular(specular);
        }
        
        componentElement = componentElement->NextSiblingElement();
    }
}



std::map<std::string, Animation*> * ANFInterpreter::loadAnimations(){
    std::map<std::string, Animation*> * animations = new std::map<std::string, Animation*>();
    
    if(animationsElement){
        
        TiXmlElement * animationElement = animationsElement->FirstChildElement("animation");
        
        while (animationElement) {
            std::string id = animationElement->Attribute("id");
            std::string span_string = animationElement->Attribute("span");
            std::string type = animationElement->Attribute("type");
            
            float span;
            
            sscanf(span_string.c_str(), "%f", &span);
            
            if (strcmp(type.c_str(), "linear") ==0 ){
                
                LinearAnimation * linearAnimation = new LinearAnimation(id, span);
                
                TiXmlElement * animationComponent = animationElement->FirstChildElement("controlpoint");
                
                while (animationComponent){
                    std::string x_string = animationComponent->Attribute("xx");
                    std::string y_string = animationComponent->Attribute("yy");
                    std::string z_string = animationComponent->Attribute("zz");
                
                    float x, y, z;
                
                
                    sscanf(x_string.c_str(), "%f", &x);
                    sscanf(y_string.c_str(), "%f", &y);
                    sscanf(z_string.c_str(), "%f", &z);
                    
                    ControlPoint controlPoint(x,y,z);
                    
                    linearAnimation->addControlPoint(controlPoint);
                    
                    animationComponent = animationComponent->NextSiblingElement("controlpoint");
                    
                }
                
                linearAnimation->calculateTotalDistance();
                
                animations->insert(std::pair<std::string, Animation *> (linearAnimation->getId(), linearAnimation));
                
            }
            
            if (strcmp(type.c_str(), "circular") ==0 ){
                
                CircularAnimation * circularAnimation = new CircularAnimation(id, span);
                
                std::string centerString = animationElement->Attribute("center");
                
                float center[3];
                
                sscanf(centerString.c_str(), "%f %f %f", &center[0], &center[1], &center[2]);
                
                circularAnimation->setCenter(center[0], center[1], center[2]);
                
                float radius, startAng, rotAng;
                
                std::string radiusString = animationElement->Attribute("radius");
                std::string startAngString = animationElement->Attribute("startang");
                std::string rotAngString = animationElement->Attribute("rotang");
                
                sscanf(radiusString.c_str(), "%f", &radius);
                sscanf(startAngString.c_str(), "%f", &startAng);
                sscanf(rotAngString.c_str(), "%f", &rotAng);
                
                circularAnimation->setStartAng(startAng);
                circularAnimation->setRotAng(rotAng);
                circularAnimation->setRadius(radius);
                
                animations->insert(std::pair<std::string, Animation *> (circularAnimation->getId(), circularAnimation));
                
                cout << "Inserted circular animation with ID " << circularAnimation->getId() << endl;
                
            }
            
            animationElement = animationElement->NextSiblingElement("animation");
        }
    }
    return animations;
}





void ANFInterpreter::loadLights(){
    TiXmlElement * lightElement = lightsElement->FirstChildElement("light");
    while(lightElement){
        std::string lightId = lightElement->Attribute("id");
        cout << "Processing Light: " << lightId << endl;
        
        std::string enabledString = lightElement->Attribute("enabled");
        std::string markerString = lightElement->Attribute("marker");
        
        
        
        float pos[3];
        std::string posString = lightElement->Attribute("pos");
        sscanf(posString.c_str(), "%f %f %f", &pos[0], &pos[1], &pos[2]);
        
        
        
        TiXmlElement * componentElement = lightElement->FirstChildElement("component");
        
        if(strcmp(lightElement->Attribute("type"), "omni") == 0)
        {
            Omni * light = new Omni();
            light->setId(lightId);
            light->setPos(pos);
            
            if(strcmp(enabledString.c_str(),"true") ==0){
                light->setEnabled(true);
            }
            else{
                light->setEnabled(false);
            }
            
            loadLightComponents(light, componentElement);            
            this->scene->getLights()->push_back(light);
            
        } else if(strcmp(lightElement->Attribute("type"), "spot") == 0)
        {
            Spot * light = new Spot();
            
            float target[4];
            
            std::string targetString = lightElement->Attribute("target");
            
            sscanf(targetString.c_str(), "%f %f %f %f", &target[0], &target[1], &target[2], &target[3]);
            
            
            float angle;
            
            std::string angleString = lightElement->Attribute("angle");
            
            sscanf(angleString.c_str(), "%f", &angle);
            
            float exponent;
            
            std::string exponentString = lightElement->Attribute("exponent");
            
            sscanf(exponentString.c_str(), "%f", &exponent);
            
            light->setTarget(target);
            light->setExponent(exponent);
            light->setAngle(angle);
            light->setId(lightId);
            light->setPos(pos);
            
            if(strcmp(enabledString.c_str(),"true") ==0){
                light->setEnabled(true);
            }
            else{
                light->setEnabled(false);
            }
            
            
            if(strcmp(markerString.c_str(), "true"))
                light->setMarker(true);
            else
                light->setMarker(false);
            
            loadLightComponents(light, componentElement);
            this->scene->getLights()->push_back(light);
        }
        
        
        
        lightElement = lightElement->NextSiblingElement();
    }
}

void ANFInterpreter::loadGraph(){
    std::string rootid = graphElement->Attribute("rootid");
    this->scene->getGraph()->setRootId(rootid);
    
    TiXmlElement * nodeElements = graphElement->FirstChildElement("node");
    while(nodeElements){
        Node * node = new Node(true);
        std::string nodeID = nodeElements->Attribute("id");
        
        cout << "Processing " << nodeID << endl;
        
        TiXmlElement * animationRefElement = nodeElements->FirstChildElement("animationref");
        
        while(animationRefElement)
        {
            std::string animationId = animationRefElement->Attribute("id");
            cout << "sim: " << animationId << endl;
            node->setAnimation(scene->getAnimations()->at(animationId));
            
            animationRefElement = animationRefElement->NextSiblingElement("animationref");
        }
        
        TiXmlElement * transformsElements = nodeElements->FirstChildElement("transforms");
        
        TiXmlElement * primitivesElements = nodeElements->FirstChildElement("primitives");
        
        TiXmlElement * descendantsElement = nodeElements->FirstChildElement("descendants");
        
        TiXmlElement * appearanceElement = nodeElements->FirstChildElement("appearanceref");
        
        
        if(primitivesElements)
        {
            node->setPrimitives(loadPrimitives(primitivesElements));
        }
        if(transformsElements)
        {
            node->setTransforms(loadTransforms(transformsElements));
        }
        if(descendantsElement)
        {
            node->setDescendants(loadDescendants(descendantsElement));
        }
        
        
        node->setID(nodeID);
        
        if(nodeElements->Attribute("displaylist"))
        {
            std::string displayList = nodeElements->Attribute("displaylist");
            if(displayList == "true")
            {
                node->setDisplayList(true);
            } else {
                node->setDisplayList(false);
            }
        } else {
            node->setDisplayList(false);
        }
        
        node->setAppearanceRef(appearanceElement->Attribute("id"));
        cout << "appearance ref = " << appearanceElement->Attribute("id");
        if(strcmp(appearanceElement->Attribute("id"), "inherit")!=0){
            cout << "add appearance " << appearanceElement->Attribute("id") <<endl;
            node->addAppearance(scene->getAppearances()->at(appearanceElement->Attribute("id")));
        }
        
        node->calculateMatrix();
        
        this->scene->getGraph()->addNode(node);
        
        nodeElements = nodeElements->NextSiblingElement();
    }
}

std::map<std::string, Texture*> * ANFInterpreter::loadTextures(){
    
    std::map<std::string, Texture*> * textures = new std::map<std::string, Texture*>();
    
    if(texturesElement){
        TiXmlElement * textureElement = texturesElement->FirstChildElement("texture");
        
        while(textureElement) {
            std::string id = textureElement->Attribute("id");
            std::string file = textureElement->Attribute("file");
            std::string texlength_s_string = textureElement->Attribute("texlength_s");
            std::string texlength_t_string = textureElement->Attribute("texlength_t");
            float texlength_s, texlength_t;

            sscanf(texlength_s_string.c_str(), "%f", &texlength_s);
            sscanf(texlength_t_string.c_str(), "%f", &texlength_t);
            
            Texture * texture = new Texture();
            texture->setId(id);
            texture->setTexLengthS(texlength_s);
            texture->setTexLengthT(texlength_t);
            texture->setFile(file);
            
            textures->insert(std::pair<std::string,Texture *>(texture->getId(), texture));
            
            
            textureElement = textureElement->NextSiblingElement("texture");
        }
        
    }
    
    return textures;
}

std::map<std::string, Appearance*> * ANFInterpreter::loadAppearances(){
    std::map<std::string, Appearance*> * appearances = new std::map<std::string, Appearance*>();
    
    if(appearancesElement){
        
        TiXmlElement * appearanceElement = appearancesElement->FirstChildElement("appearance");
        
        while (appearanceElement) {
            std::string id = appearanceElement->Attribute("id");
            std::string shininess_string = appearanceElement->Attribute("shininess");
            std::string textureref = appearanceElement->Attribute("textureref");
            float shininess;
            
            sscanf(shininess_string.c_str(), "%f", &shininess);
            
            Appearance * appearance = new Appearance();
            
            appearance->setShininess(shininess);
            appearance->setId(id);
            appearance->setTextureRef(textureref);
            if(strcmp(textureref.c_str(),"")!=0 ){
                cout << "Texture file= " << scene->getTextures()->at(textureref)->getFile()<<endl;
                appearance->setTexture(scene->getTextures()->at(textureref)->getFile());
                
                appearance->setTextureWrap(GL_REPEAT, GL_REPEAT);
            }else{
            }
            
            TiXmlElement * appearanceComponent = appearanceElement->FirstChildElement("component");
            while(appearanceComponent){
                std::string type = appearanceComponent->Attribute("type");
                std::string value_string = appearanceComponent->Attribute("value");
                float value[4];
                
                sscanf(value_string.c_str(), "%f %f %f %f", &value[0], &value[1], &value[2], &value[3]);
                
                
                
                if(strcmp(type.c_str(), "ambient") == 0){
                    appearance->setAmbient(value);
                }if(strcmp(type.c_str(), "diffuse") == 0){
                    appearance->setDiffuse(value);
                }if(strcmp(type.c_str(), "specular") == 0){
                    appearance->setSpecular(value);
                }
                
                appearances->insert(std::pair<std::string, Appearance *> (appearance->getId(), appearance));
                
                appearanceComponent = appearanceComponent->NextSiblingElement("component");
            }
            appearanceElement = appearanceElement->NextSiblingElement("appearance");
        }
        
    }
    return appearances;
}




void ANFInterpreter::replaceEmptyNodes() {
    map<std::string,Node*>::iterator node=this->scene->getGraph()->getNodes()->begin();
    
    for(int i = 0;i < this->scene->getGraph()->getNodes()->size();i++,node++) {
        if(node->second->getDescendants())
        {
            cout << node->second->getID();
            map<std::string,Node*>::iterator descendant=node->second->getDescendants()->begin();
            
            for(int j= 0; j < node->second->getDescendants()->size(); j++,descendant++){
                if( ! descendant->second->isInitialized()) {
                    if(this->scene->getGraph()->getNodes()->at(descendant->first)) {
                        descendant->second = this->scene->getGraph()->getNodes()->at(descendant->first);
                    } else {
                        cout << "WARNING: THERE'S NO VALID NODE FOR THE ID: " << descendant->first << endl;
                    }
                }
            }
        }
    }
    
    node=this->scene->getGraph()->getNodes()->begin();
    for(int i = 0;i < this->scene->getGraph()->getNodes()->size();i++,node++) {
        if(node->second->getDescendants())
        {
            node->second->setDescendentsDisplayList();
        }
    }
    
}

std::map<std::string, Node*> * ANFInterpreter::loadDescendants(TiXmlElement * descendantsElements) {
    std::map<std::string, Node*> * descendants = new std::map<std::string, Node*>();
    
    TiXmlElement * nodeRefElement = descendantsElements->FirstChildElement("noderef");
    
    while(nodeRefElement) {
        std::string id = nodeRefElement->Attribute("id");
        Node * node = new Node(false);
        node->setID(id);
        
        descendants->insert(std::pair<std::string,Node *>(node->getID(), node));
        
        nodeRefElement = nodeRefElement->NextSiblingElement("noderef");
    }
    
    return descendants;
    
}



std::vector<Transforms *> * ANFInterpreter::loadTransforms(TiXmlElement * transformsElements) {
    std::vector<Transforms *> * transforms = new std::vector<Transforms*>();
    
    
    TiXmlElement * transformElement = transformsElements->FirstChildElement("transform");
    
    while(transformElement) {
        if(strcmp(transformElement->Attribute("type"), "translate") == 0){
            Translation * translation = new Translation();
            char* to = (char *)transformElement->Attribute("to");
            float x, y, z;
            sscanf(to, "%f %f %f", &x, &y, &z);
            
            translation->setX(x);
            translation->setY(y);
            translation->setZ(z);
            transforms->push_back(translation);
        }
        
        if(strcmp(transformElement->Attribute("type"),"rotate") == 0){
            Rotation * rotation = new Rotation();
            std::string axis = transformElement->Attribute("axis");
            
            char* angle_string = (char *)transformElement->Attribute("angle");
            float angle;
            sscanf(angle_string, "%f", &angle);
            
            rotation->setAngle(angle);
            rotation->setAxis(axis[0]);
            transforms->push_back(rotation);
        }
        
        if(strcmp(transformElement->Attribute("type"),"scale") == 0){
            Scale * scale = new Scale();
            
            char* factor = (char *)transformElement->Attribute("factor");
            float x, y, z;
            sscanf(factor, "%f %f %f", &x, &y, &z);
            
            scale->setXFactor(x);
            scale->setYFactor(y);
            scale->setZFactor(z);
            transforms->push_back(scale);
        }
        
        
        transformElement = transformElement->NextSiblingElement("transform");
    }
    
    return transforms;

}

std::vector<Primitives *> * ANFInterpreter::loadPrimitives(TiXmlElement * primitivesElement) {
    std::vector<Primitives *> * primitives = new std::vector<Primitives *>();
    
    TiXmlElement * rectangleElement = primitivesElement->FirstChildElement("rectangle");
    
    while(rectangleElement) {
        Rectangle * rectangle = new Rectangle();
        char* xy1 = (char *)rectangleElement->Attribute("xy1");
        char* xy2 = (char *)rectangleElement->Attribute("xy2");
        
        float x1, y1, x2, y2;
        sscanf(xy1, "%f %f", &x1, &y1);
        sscanf(xy2, "%f %f", &x2, &y2);
        
        rectangle->setX1(x1);
        rectangle->setX2(x2);
        rectangle->setY1(y1);
        rectangle->setY2(y2);
        
        primitives->push_back(rectangle);
        rectangleElement = rectangleElement->NextSiblingElement("rectangle");
    }
    
    TiXmlElement * triangleElement = primitivesElement->FirstChildElement("triangle");
    
    while(triangleElement) {
        Triangle * triangle = new Triangle();
        char* xyz1 = (char *)triangleElement->Attribute("xyz1");
        char* xyz2 = (char *)triangleElement->Attribute("xyz2");
        char* xyz3 = (char *)triangleElement->Attribute("xyz3");
        
        float x1, y1, z1, x2, y2, z2, x3, y3, z3;
        sscanf(xyz1, "%f %f %f", &x1, &y1, &z1);
        sscanf(xyz2, "%f %f %f", &x2, &y2, &z2);
        sscanf(xyz3, "%f %f %f", &x3, &y3, &z3);
        
        triangle->setX1(x1);
        triangle->setX2(x2);
        triangle->setX3(x3);
        triangle->setY1(y1);
        triangle->setY2(y2);
        triangle->setY3(y3);
        triangle->setZ1(z1);
        triangle->setZ2(z2);
        triangle->setZ3(z3);
        
        primitives->push_back(triangle);
        triangleElement = triangleElement->NextSiblingElement("triangle");
    }
    
    
    
    TiXmlElement * cylinderElement = primitivesElement->FirstChildElement("cylinder");
    
    while(cylinderElement) {
        Cylinder * cylinder = new Cylinder();
        /** get cylinder parameters from ANF **/
        char* base_char = (char *)cylinderElement->Attribute("base");
        char* top_char = (char *)cylinderElement->Attribute("top");
        char* height_char = (char *)cylinderElement->Attribute("height");
        char* slices_char = (char *)cylinderElement->Attribute("slices");
        char* stacks_char = (char *)cylinderElement->Attribute("stacks");
        
        /** convert char parameters to correct types **/
        float base, top, height;
        int slices, stacks;
        sscanf(base_char, "%f", &base);
        sscanf(top_char, "%f", &top);
        sscanf(height_char, "%f", &height);
        slices = atoi(slices_char);
        stacks = atoi(stacks_char);
        /** set cylinder parameters **/
        cylinder->setBase(base);
        cylinder->setTop(top);
        cylinder->setHeight(height);
        cylinder->setSlices(slices);
        cylinder->setStacks(stacks);
        
        primitives->push_back(cylinder);
        cylinderElement = cylinderElement->NextSiblingElement("cylinder");
    }
    
    
    TiXmlElement * sphereElement = primitivesElement->FirstChildElement("sphere");
    
    while(sphereElement) {
        Sphere * sphere = new Sphere();
        /** get sphere parameters from ANF **/
        char* radius_char = (char *)sphereElement->Attribute("radius");
        char* slices_char = (char *)sphereElement->Attribute("slices");
        char* stacks_char = (char *)sphereElement->Attribute("stacks");
        
        /** convert char parameters to correct types **/
        float radius;
        int slices, stacks;
        sscanf(radius_char, "%f", &radius);
        slices = atoi(slices_char);
        stacks = atoi(stacks_char);
        
        /** set sphere parameters **/
        sphere->setRadius(radius);
        sphere->setSlices(slices);
        sphere->setStacks(stacks);
        
        primitives->push_back(sphere);
        sphereElement = sphereElement->NextSiblingElement("sphere");
    }
    
    TiXmlElement * torusElement = primitivesElement->FirstChildElement("torus");
    
    while(torusElement) {
        Torus * torus = new Torus();
        /** get sphere parameters from ANF **/
        char* inner_char = (char *)torusElement->Attribute("inner");
        char* outer_char = (char *)torusElement->Attribute("outer");
        char* slices_char = (char *)torusElement->Attribute("slices");
        char* loops_char = (char *)torusElement->Attribute("loops");
        
        /** convert char parameters to correct types **/
        float inner, outer;
        int slices, loops;
        sscanf(inner_char, "%f", &inner);
        sscanf(outer_char, "%f", &outer);
        slices = atoi(slices_char);
        loops = atoi(loops_char);
        
        /** set sphere parameters **/
        torus->setInner(inner);
        torus->setOuter(outer);
        torus->setSlices(slices);
        torus->setLoops(loops);
        
        primitives->push_back(torus);
        torusElement = torusElement->NextSiblingElement("torus");
    }
    
    
    TiXmlElement * planeElement = primitivesElement->FirstChildElement("plane");
    while(planeElement) {
        Plane * plane = new Plane();
        /** get sphere parameters from ANF **/
        char* parts_char = (char *)planeElement->Attribute("parts");
        /** convert char parameters to correct types **/
        int parts;
        
        parts = atoi(parts_char);
        
        /** set sphere parameters **/
        plane->setParts(parts);
        
        primitives->push_back(plane);
        planeElement = planeElement->NextSiblingElement("plane");
    }
    
    
    TiXmlElement * patchElement = primitivesElement->FirstChildElement("patch");
    while(patchElement) {
        Patch * patch = new Patch();
        /** get sphere parameters from ANF **/
        char* order_char = (char *)patchElement->Attribute("order");
        char* parts_u_char = (char *)patchElement->Attribute("partsU");
        char* parts_v_char = (char *)patchElement->Attribute("partsV");
        char* compute_char = (char*) patchElement->Attribute("compute");
        /** convert char parameters to correct types **/
        int order, partsU, partsV;
        
        order = atoi(order_char);
        partsU = atoi(parts_u_char);
        partsV = atoi(parts_v_char);
        
        
        std::string compute(compute_char);
        /** set sphere parameters **/
        patch->setOrder(order);
        patch->setPartsU(partsU);
        patch->setPartsV(partsV);
        patch->setCompute(compute);
        
        
        TiXmlElement * controlpointElement = patchElement->FirstChildElement("controlpoint");
        
        vector<ControlPoint> cntlpoints;
        
        while(controlpointElement){
            char* x_char = (char *)controlpointElement->Attribute("x");
            char* y_char = (char *)controlpointElement->Attribute("y");
            char* z_char = (char *)controlpointElement->Attribute("z");
            
            
            float x, y, z;
            
            sscanf(x_char, "%f", &x);
            sscanf(y_char, "%f", &y);
            sscanf(z_char, "%f", &z);
            
            ControlPoint cntlpoint = ControlPoint(x,y,z);
            cntlpoints.push_back(cntlpoint);
            
            controlpointElement = controlpointElement->NextSiblingElement("controlpoint");
            
        }
        
        
        patch->setCntlPoints(cntlpoints);
        
        
        primitives->push_back(patch);
        patchElement = patchElement->NextSiblingElement("patch");
    }
    
    TiXmlElement * vehicleElement = primitivesElement->FirstChildElement("vehicle");
    while(vehicleElement) {
        Vehicle * vehicle = new Vehicle();
        primitives->push_back(vehicle);
        vehicleElement = vehicleElement->NextSiblingElement("vehicle");
    }
    
    TiXmlElement * boardElement = primitivesElement->FirstChildElement("board");
    while(boardElement) {
        Board * board = new Board();
        char* x_char = (char *)boardElement->Attribute("x");
        char* y_char = (char *)boardElement->Attribute("y");
        int x = atoi(x_char);
        int y = atoi(y_char);
        
        board->setSizeY(y);
        board->setSizeX(x);
        
        primitives->push_back(board);
        boardElement = boardElement->NextSiblingElement("board");
    }
    
    return primitives;
    
}


ANFInterpreter::ANFInterpreter(char *filename, Scene * scene)
{
    // Read XML from file
    this->scene = scene;
    
    doc=new TiXmlDocument( filename );
    bool loadOkay = doc->LoadFile();
    
    if ( !loadOkay )
    {
        printf( "Could not load file '%s'. Error='%s'. Exiting.\n", filename, doc->ErrorDesc() );
        exit( 1 );
    }
    
    TiXmlElement* anfScene= doc->FirstChildElement( "anf" );
    
    if (anfScene == NULL)
    {
        printf("Main anf block element not found! Exiting!\n");
        exit(1);
    }
    
    globalsElement = anfScene->FirstChildElement( "globals" );
    camerasElement = anfScene->FirstChildElement("cameras");
    graphElement = anfScene->FirstChildElement("graph");
    texturesElement = anfScene->FirstChildElement("textures");
    appearancesElement = anfScene->FirstChildElement("appearances");
    animationsElement = anfScene->FirstChildElement("animations");
    lightsElement = anfScene->FirstChildElement("lights");
    
    Globals * globals = scene->getGlobals();
    std::vector<Camera *> * cameras = scene->getCameras();
    
    cameras->size();
    
    // Init
    // An example of well-known, required nodes
    
    if (globalsElement == NULL)
    {
        printf("Globals block not found!\n");
    }
    else
    {
        printf("Processing globals\n");
        // frustum: example of a node with individual attributes
        TiXmlElement* drawingElement=globalsElement->FirstChildElement("drawing");
        if (drawingElement)
        {
            std::string mode, shading;
            char *background = NULL;
            float r, g, b, alpha;
            mode = drawingElement->Attribute("mode");
            shading = drawingElement->Attribute("shading");
            background = (char * ) drawingElement->Attribute("background");
            globals->mode = mode;
            globals->shading = shading;
            
            sscanf(background, "%f %f %f %f", &r, &g, &b, &alpha);
            
            globals->background[0] = r;
            globals->background[1] = g;
            globals->background[2] = b;
            globals->background[3] = alpha;
            
            
        }
        else {
            printf("drawing not found\n");
        }
        
        
        TiXmlElement* cullingElement=globalsElement->FirstChildElement("culling");
        if(cullingElement){
            std::string face, order;
            face = cullingElement->Attribute("face");
            order = cullingElement->Attribute("order");
            globals->face = face;
            globals->order = order;
            
        }else{
            printf("culling not found");
        }
        printf("Processing lighting\n");
        TiXmlElement* lightingElement=globalsElement->FirstChildElement("lighting");
        if(lightingElement){
            std::string doublesided, local, enabled;
            char *ambientString = NULL;
            float ambient[4];
            doublesided = lightingElement->Attribute("doublesided");
            local = lightingElement->Attribute("local");
            enabled = lightingElement->Attribute("enabled");
            ambientString = (char *) lightingElement->Attribute("ambient");
            
            sscanf(ambientString, "%f %f %f %f", &ambient[0], &ambient[1], &ambient[2], &ambient[3]);
            
            globals->doublesided = doublesided;
            globals->local = local;
            globals->enabled = enabled;
            globals->ambient[0] = ambient[0];
            globals->ambient[1] = ambient[1];
            globals->ambient[2] = ambient[2];
            globals->ambient[3] = ambient[3];
            
            
        }
    }
    
    printf("Processing cameras\n");
    /** GET CAMERAS **/
    std::string initialCameraId = camerasElement->Attribute("initial");
    if(camerasElement==NULL){
        printf("Cameras block not found!\n");
    }else{
        TiXmlElement * orthoElements = camerasElement->FirstChildElement("ortho");
        TiXmlElement * perspectiveElements = camerasElement->FirstChildElement("perspective");
        while(orthoElements){
            Ortho * orthogonalCamera = new Ortho();
            
            orthogonalCamera->right =(float)atof(orthoElements->Attribute("right"));
            orthogonalCamera->left = (float)atof(orthoElements->Attribute("left"));
            orthogonalCamera->top = (float)atof(orthoElements->Attribute("top"));
            orthogonalCamera->bottom = (float)atof(orthoElements->Attribute("bottom"));
            orthogonalCamera->setFar((float)atof(orthoElements->Attribute("far")));
            orthogonalCamera->setNear((float)atof(orthoElements->Attribute("near")));
            orthogonalCamera->setID(orthoElements->Attribute("id"));
            orthogonalCamera->setDirection(orthoElements->Attribute("direction")[0]);
            
            if(initialCameraId == orthogonalCamera->getID()) {
                scene->setActiveCamera(orthogonalCamera);
            }
            
            cameras->push_back(orthogonalCamera);
            
            orthoElements = orthoElements->NextSiblingElement("ortho");
        }
        
        while(perspectiveElements){
            Perspective * perspectiveCamera = new Perspective();
            perspectiveCamera->angle =(float)atof(perspectiveElements->Attribute("angle"));
            
            char *posString = NULL;
            char *targetString = NULL;
            posString = (char *) perspectiveElements->Attribute("pos");
            targetString = (char *) perspectiveElements->Attribute("target");
            
            float pos[3];
            float target[3];
            sscanf(posString, "%f %f %f", &pos[0], &pos[1], &pos[2]);
            sscanf(targetString, "%f %f %f", &target[0], &target[1], &target[2]);
            
            perspectiveCamera->pos[0] = pos[0];
            perspectiveCamera->pos[1] = pos[1];
            perspectiveCamera->pos[2] = pos[2];
            perspectiveCamera->target[0] = target[0];
            perspectiveCamera->target[1] = target[1];
            perspectiveCamera->target[2] = target[2];
            
            perspectiveCamera->setFar((float)atof(perspectiveElements->Attribute("far")));
            perspectiveCamera->setNear((float)atof(perspectiveElements->Attribute("near")));
            perspectiveCamera->setID(perspectiveElements->Attribute("id"));
            
            perspectiveElements = perspectiveElements->NextSiblingElement("perspective");

            if(initialCameraId == perspectiveCamera->getID()) {
                scene->setActiveCamera(perspectiveCamera);
            }
            
            if(cameras==NULL)
                cout << "null cameras";

            cameras->push_back(perspectiveCamera);
        }
    }
    
    printf("Processing textures\n");
    scene->setTextures(loadTextures());
    
    printf("Processing appearances\n");
    scene->setAppearances(loadAppearances());
    
    loadLights();
    
    scene->setAnimations(loadAnimations());
    
    printf("Processing graph\n");
    loadGraph();
    
    cout << "Replacing empty nodes" << endl;
    replaceEmptyNodes();
    cout << endl << "Finished XML Parsing" << endl << endl;
    
}

ANFInterpreter::~ANFInterpreter()
{
    delete(doc);
}

//-------------------------------------------------------

TiXmlElement *ANFInterpreter::findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val)
// Searches within descendants of a parent for a node that has an attribute _attr_ (e.g. an id) with the value _val_
// A more elaborate version of this would rely on XPath expressions
{
    TiXmlElement *child=parent->FirstChildElement();
    int found=0;
    
    while (child && !found)
        if (child->Attribute(attr) && strcmp(child->Attribute(attr),val)==0)
            found=1;
        else
            child=child->NextSiblingElement();
    
    return child;
}