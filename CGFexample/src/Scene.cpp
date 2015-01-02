#include "Scene.h"
#include "CGFaxis.h"
#include "CGFapplication.h"

#include "ExampleObject.h"

#include <math.h>

#include "CGFappearance.h"
#include "ANFInterpreter.h"

void Scene::setGlobals(){
    // drawing
    
    if(globals->getMode() == GL_FILL)
    {
        setWired(false);
    } else {
        
        setWired(true);
    }
    
    glPolygonMode(GL_FRONT_AND_BACK, globals->getMode());
    glClearColor(globals->getBackground(0), globals->getBackground(1), globals->getBackground(2),globals->getBackground(3));
    glEnable(globals->getShading());
    
    
    // culling
    if(globals->getCulling()!=-1){
        glEnable(GL_NONE);
        glCullFace(globals->getCulling());
        glFrontFace(globals->getOrder());
    }
    if(globals->isLightEnabled()==GL_TRUE){
        glEnable(GL_LIGHTING);
        glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, globals->isDoubleSided());
        glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, globals->isLocalLight());
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globals->getLightAmbient());  // Define ambient light
    }
}

void Scene::activateLights(){
    
    if(cgfLights->size()==0){
    for(unsigned int i=0; i<lights->size(); i++) {
            CGFlight * light = new CGFlight(GL_LIGHT0 + i, lights->at(i)->getPos());
            light->setAmbient(lights->at(i)->getAmbient());
            light->setSpecular(lights->at(i)->getSpecular());
            light->setDiffuse(lights->at(i)->getDiffuse());
        
            if(strcmp(lights->at(i)->getType().c_str(), "spot")==0){
                Spot * spotLight = (Spot*)lights->at(i);
                light->setAngle(spotLight->getAngle());
                
                glLightfv(GL_LIGHT0 +i, GL_POSITION, spotLight->getPos());
                glLightf(GL_LIGHT0 + i,GL_SPOT_CUTOFF,spotLight->getAngle());
                glLightf(GL_LIGHT0 + i,GL_SPOT_EXPONENT,spotLight->getExponent());
                glLightfv(GL_LIGHT0 + i,GL_SPOT_DIRECTION,spotLight->getTarget());
            }
        
            if(lights->at(i)->getEnabled()){
                light->enable();
            }else{
                light->disable();
            }
            light->update();
            cgfLights->push_back(light);
    }
    }
    else{
        for(unsigned int j= 0; j < cgfLights->size(); j++){
            CGFlight * light =  cgfLights->at(j);
            if(lights->at(j)->getEnabled()){
                light->enable();
            }else{
                light->disable();
            }
        }
        for(unsigned int i =0; i < cgfLights->size(); i++){
            CGFlight * light =  cgfLights->at(i);
            light->update();
        }
    }
}


void Scene::init()
{
    
    frameCount = 0;
    lastMilis = 0;
    cameras = new std::vector<Camera *>();
    lights = new std::vector<Light *>();
    
    globals = new Globals();
    
    graph = new Graph();
    char * anfPath = "../data/cena.anf";
    
    ANFInterpreter anfInterpreter = ANFInterpreter(anfPath, this);
    
    cgfLights = new std::vector<CGFlight *>();
    setGlobals();
    activateLights();
    
    cout << "animations = " << animations->size()<<endl;

	// Defines a default normal
	glNormal3f(0,0,1);

    
    
    
	obj=new ExampleObject();
    materialAppearance=new CGFappearance();
	shader=new CGFshader("../data/texshader.vert","../data/texshader.frag");

	setUpdatePeriod(30);
    
    for (std::map<std::string, Appearance*>::iterator it=appearances->begin(); it != appearances->end(); it++) {
        cout << "Appearance ID = " <<  it->second->getId() << endl;
    }
}


void Scene::setActiveCamera(Camera * camera) {
    activeCamera = camera;
}

void Scene::showCamera()
{
    if(activeCamera->getType() == "persp") {
        Perspective * perspCamera = (Perspective *) activeCamera;
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(perspCamera->getAngle(), 1, perspCamera->getNear(), perspCamera->getFar());
     
        gluLookAt(perspCamera->getPos(0), perspCamera->getPos(1), perspCamera->getPos(2), perspCamera->getTarget(0), perspCamera->getTarget(1), perspCamera->getTarget(2), 0.0, 1.0, 0.0);
        glMatrixMode(GL_MODELVIEW);
      
    }
    if(activeCamera->getType() == "ortho") {
        Ortho * orthoCamera = (Ortho *) activeCamera;
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(orthoCamera->getLeft(), orthoCamera->getRight(), orthoCamera->getBottom(), orthoCamera->getTop(), orthoCamera->getNear(), orthoCamera->getFar());
        switch (orthoCamera->getDirection()) {
            case 'x':
                glRotated(90,0,1,0);
                glScaled(1,1,-1);
                break;
            case 'y':
                glRotated(90,1,0,0);
                glScaled(1,-1,1);
                break;
            case 'z':
                break;
            default:
                break;
        }
        glMatrixMode(GL_MODELVIEW);
    }
}


void Scene::update(unsigned long t)
{
    
    if(lastMilis != 0)
    {
        long increment = t - lastMilis;
        
        for (std::map<std::string, Node *>::iterator it = graph->getNodes()->begin(); it != graph->getNodes()->end(); ++it)
        {
            if(it->second->getHasAnimation() )
            {
                Animation * animation = it->second->getAnimation();
                cout << "animated " << it->second->getID() << endl;
                cout << animation->getId() << endl;
                animation->increment(increment);
            }
        }
        
    }   
    
    lastMilis = t;
    
    
	shader->bind();
	shader->update(t/400.0);
	shader->unbind();
	
}
	
void Scene::display() 
{
	// ---- BEGIN Background, camera and axis setup
	
	// Clear image and depth buffer everytime we update the scene
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);   

    if(isWired()){
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    }else{
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    }
    
	// Initialize Model-View matrix as identity (no transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    

    // Apply transformations corresponding to the camera position relative to the origin
    
    CGFscene::activeCamera->applyView();
    //showCamera();

	// Draw axis
	axis.draw();
    
    glDisable(GL_BLEND);
    
	// ---- END Background, camera and axis setup
    for(int i = 0; i < cgfLights->size(); i++) {
        cgfLights->at(i)->draw();
    }
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); glEnable( GL_BLEND );
    
    GLfloat identityMatrix[4][4];
    glGetFloatv(GL_MODELVIEW_MATRIX, &identityMatrix[0][0]);
    
    graph->getNodes()->at(graph->getRootId())->draw(identityMatrix);
 
    
	// We have been drawing in a memory area that is not visible - the back buffer, 
	// while the graphics card is showing the contents of another buffer - the front buffer
	// glutSwapBuffers() will swap pointers so that the back buffer becomes the front buffer and vice-versa
	glutSwapBuffers();
    
    //cout << frameCount << endl;
    frameCount++;
}

Scene::~Scene()
{
    cameras = new std::vector<Camera *>();
    lights = new std::vector<Light *>();
    
    globals = new Globals();
    graph = new Graph();
    
    cgfLights = new std::vector<CGFlight *>();
    
	delete(shader);
	delete(textureAppearance);
	delete(materialAppearance);
	delete(obj);
    for(unsigned int i= 0; i< cameras->size(); i++){
        delete(cameras->at(i));
    }
    for(unsigned int i= 0; i< lights->size(); i++){
        delete(lights->at(i));
    }
    for(unsigned int i= 0; i< cgfLights->size(); i++){
        delete(cgfLights->at(i));
    }
    delete(globals);
    delete(graph);
}
