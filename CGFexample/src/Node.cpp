#include "Node.h"

void Node::draw(GLfloat previousMatrix[4][4]){
    if(active){
    glLoadIdentity();
    glMultMatrixf(*previousMatrix);
    glMultMatrixf(*this->matrix);
    
    GLfloat multipliedMatrix[4][4];
    glGetFloatv(GL_MODELVIEW_MATRIX, &multipliedMatrix[0][0]);
    
    if(this->displayList) {
        appearance->apply();
        glCallList(this->index);
    } else {
        for(int i = 0; i < primitives->size(); i++){
            appearance->apply();
            primitives->at(i)->draw();
        }
    }
    
    if(descendants)
    {
        map<std::string,Node*>::iterator descendant=this->descendants->begin();
        for(int j= 0; j < this->descendants->size(); j++,descendant++){
            appearance->apply();
            descendant->second->draw(multipliedMatrix, appearance);
        }
    }
    }
}


void Node::draw(GLfloat previousMatrix[4][4], Appearance * previousAppearance){
    if(active){
    if(strcmp(apperanceref.c_str(), "inherit")==0){
        appearance = previousAppearance;
    }
    
    glLoadIdentity();
    
    if(this->getHasAnimation() && ! this->displayList)
    {
        this->calculateAnimations();
    }
    
    glMultMatrixf(*previousMatrix);
    glMultMatrixf(*this->matrix);
    
    GLfloat multipliedMatrix[4][4];
    glGetFloatv(GL_MODELVIEW_MATRIX, &multipliedMatrix[0][0]);
    
    if(this->displayList) {
        appearance->apply();
        glCallList(this->index);
    } else {
        for(int i = 0; i < primitives->size(); i++){
            appearance->apply();
            primitives->at(i)->draw();
        }
    }
    
    if(descendants)
    {
        map<std::string,Node*>::iterator descendant=this->descendants->begin();
        for(int j= 0; j < this->descendants->size(); j++,descendant++){
            appearance->apply();
            descendant->second->draw(multipliedMatrix, appearance);
        }
    }
    }
    
}

void Node::calculateMatrix()
{
    glPushMatrix();
    
    glLoadIdentity();
    
    for(int j = 0; j < transforms->size(); j++){
        transforms->at(j)->apply();
    }
    
    glGetFloatv(GL_MODELVIEW_MATRIX, &this->matrix[0][0]);
    
    
    glPopMatrix();
}

void Node::calculateAnimations()
{
    glPushMatrix();
    
    if(this->getAnimation()->getType() == "linear")
    {
        LinearAnimation * animation = (LinearAnimation *) this->getAnimation();
        // translate to initial point
        if(! animation->getInitialized())
        {
            glPushMatrix();
            
            glLoadIdentity();
            
            glTranslatef(animation->getControlPoints()[0].getX(),
                         animation->getControlPoints()[0].getY(),
                         animation->getControlPoints()[0].getZ()
                         );
            
            glGetFloatv(GL_MODELVIEW_MATRIX, &this->matrix[0][0]);
            
            glPopMatrix();
            
            animation->setInitialized(true);
        }
        
        
        glLoadIdentity();
        
        glMultMatrixf(*this->matrix);
        
        ControlPoint destination = animation->getCurrentAnimationPoint();
        
        if( ! animation->getDrawnThisFrame())
        {
            glTranslatef(destination.getX(), destination.getY(), destination.getZ());
            cout << "animated to point" << endl;
        }
        
        this->getAnimation()->setDrawnThisFrame(true);
        
        if(animation->getFinished())
        {
            currentAnimation++;
        }
        
    } else {
        CircularAnimation * animation = (CircularAnimation *) this->getAnimation();
        
        if(! animation->getInitialized())
        {
            glPushMatrix();
            
            glLoadIdentity();
            
            glGetFloatv(GL_MODELVIEW_MATRIX, &this->matrix[0][0]);
            
            glPopMatrix();
            
            animation->setInitialized(true);
        }
        
        glLoadIdentity();
        
        glMultMatrixf(*this->matrix);
        
        if( ! animation->getDrawnThisFrame())
        {
            glLoadIdentity();
            glTranslatef(animation->getCenterX(),
                         animation->getCenterY(),
                         animation->getCenterZ()
                         );
            
            glRotatef(animation->getCurrentAngle(), 0, 1, 0);
            
            glTranslatef(animation->getRadius(), 0, 0);
        }
        
        this->getAnimation()->setDrawnThisFrame(true);
        
        if(animation->getFinished())
        {
            currentAnimation++;
        }
        
    }
    
    glGetFloatv(GL_MODELVIEW_MATRIX, &this->matrix[0][0]);
    
    glPopMatrix();
}

void Node::saveToDisplayList()
{
    this->index = glGenLists(primitives->size());
    for(int i = 0; i < primitives->size(); i++){
        glNewList(this->index + i, GL_COMPILE);
        primitives->at(i)->draw();
        glEndList();
    }
}

void Node::setDescendentsDisplayList()
{
    if(this->displayList)
    {
        this->saveToDisplayList();
        if(! this->descendants->empty()) {
            map<std::string,Node*>::iterator descendant=this->descendants->begin();
            for(int j= 0; j < this->descendants->size(); j++,descendant++){
                descendant->second->setDisplayList(true);
                descendant->second->setDescendentsDisplayList();
            }
        }
    }
}