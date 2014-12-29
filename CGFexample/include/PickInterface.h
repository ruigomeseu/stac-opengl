#ifndef PickInterface_H
#define PickInterface_H

#include "CGFinterface.h"

class PickInterface: public CGFinterface {
	public:
    virtual void processKeyboard(unsigned char key, int x, int y);
		virtual void processMouse(int button, int state, int x, int y);
		void performPicking(int x, int y);
		void processHits(GLint hits, GLuint buffer[]); 
};


#endif
