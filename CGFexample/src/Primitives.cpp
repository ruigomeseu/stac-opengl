#include "Primitives.h"
#include <cmath>


void Rectangle::draw(){

    glBegin(GL_QUADS);
    
    glNormal3f(x1, y1, 0);
    glTexCoord2d(0,0);
    glVertex3d(x1,y1,0);
    
    glTexCoord2d(1,0);
    glNormal3f(x2, y1, 0);
    glVertex3d(x2,y1,0);
    
    glTexCoord2d(1,1);
    glNormal3f(x2, y2, 0);
    glVertex3d(x2,y2,0);
    
    glTexCoord2d(0,1);
    glNormal3f(x1, y2, 0);
    glVertex3d(x1,y2,0);
        
    glEnd();
}


void Triangle::draw(){
    
    float xyz1[3] = { this->x1, this->y1, this->z1 };
    float xyz2[3] = { this->x2, this->y2, this->z2 };
    float xyz3[3] = { this->x3, this->y3, this->z3 };
    
    float a,b,c;
    a = sqrt((xyz3[0]-xyz2[0])*(xyz3[0]-xyz2[0])) + (xyz3[1]-xyz2[1])* (xyz3[1]-xyz2[1]) + (xyz3[2]-xyz2[2])*(xyz3[2]-xyz2[2]);
    b = sqrt((xyz1[0]-xyz3[0])*(xyz1[0]-xyz3[0])) + (xyz1[1]-xyz3[1])* (xyz1[1]-xyz3[1]) + (xyz1[2]-xyz3[2])*(xyz1[2]-xyz3[2]);
    c = sqrt((xyz2[0]-xyz1[0])*(xyz2[0]-xyz1[0])) + (xyz2[1]-xyz1[1])* (xyz2[1]-xyz1[1]) + (xyz2[2]-xyz1[2])*(xyz2[2]-xyz1[2]);
    
    float cosA,cosB,cosY;
    cosA = (-(a*a) + b*b + c*c ) / (2 * b * c);
    cosB = ( (a*a) + -(b*b) + c*c) / (2*a*c);
    cosY = ( a*a + b*b -(c*c)) / (2*a*b);
    
    float angA, angB, angY;
    angA = acos(cosA);
    angB = acos(cosB);
    angY = acos(cosY);

    
    glBegin(GL_TRIANGLES);
    // Lower left vertex
    glTexCoord2d(0,0);
    glVertex3f(x1, y1, z1);
    // Lower right vertex
    glTexCoord2d(c,0);
    glVertex3f( x2, y2, z2);
    // Upper vertex
    glTexCoord2d(c - a*cosB, a*sin(angB));
    glVertex3f( x3,  y3, z3);
    glEnd();
    
    
}


void Cylinder::draw(){
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    gluQuadricTexture(quadratic, true);
    
    
    gluCylinder(quadratic,
                this->base,
                this->top,
                this->height,
                this->slices,
                this->stacks);
    
    glRotatef(180, 1,0,0);
    gluDisk(quadratic, 0.0f, base, slices, 1);
    glRotatef(-180, 1,0,0);
    glTranslatef(0.0f, 0.0f, height);
    gluDisk(quadratic, 0.0f, top, slices, 1);
    glTranslatef(0.0f, 0.0f, -height);
}


void Sphere::draw(){
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    gluQuadricTexture(quadratic, true);
    gluSphere(quadratic,
                this->radius,
                this->slices,
                this->stacks);
}


void Torus::draw(){
    float inner = this->inner;
    float outter = this->outer;
    int slices = this->slices;
    int loops = this->loops;
    
    double pi = acos(-1.0);
    float vNormal[3];
    double majorStep = 2.0f*pi / slices;
    double minorStep = 2.0f*pi / loops;
    int i, j;
    
    for (i=0; i<slices; ++i)
    {
        double a0 = i * majorStep;
        double a1 = a0 + majorStep;
        GLfloat x0 = (GLfloat) cos(a0);
        GLfloat y0 = (GLfloat) sin(a0);
        GLfloat x1 = (GLfloat) cos(a1);
        GLfloat y1 = (GLfloat) sin(a1);
        
        glBegin(GL_TRIANGLE_STRIP);
        for (j=0; j<=loops; ++j)
        {
            double b = j * minorStep;
            GLfloat c = (GLfloat) cos(b);
            GLfloat r = inner * c + outter;
            GLfloat z = inner * (GLfloat) sin(b);
            
            // First point
            glTexCoord2f((float)(i)/(float)(loops), (float)(j)/(float)(slices));
            vNormal[0] = x0*c;
            vNormal[1] = y0*c;
            vNormal[2] = z/inner;
            //glNormalizeVector(vNormal);
            glNormal3fv(vNormal);
            glVertex3f(x0*r, y0*r, z);
            
            glTexCoord2f((float)(i+1)/(float)(loops), (float)(j)/(float)(slices));
            vNormal[0] = x1*c;
            vNormal[1] = y1*c;
            vNormal[2] = z/inner;
            glNormal3f(vNormal[0],vNormal[1],vNormal[2]);
            glVertex3f(x1*r, y1*r, z);
        }
        glEnd();
    }

}

