#ifndef PickInterface_H
#define PickInterface_H

#include "CGFinterface.h"
#include "Scene.h"

class PickInterface: public CGFinterface {
private:
    int undo_id;
    int scenariovar;
    
    std::vector<std::string> scenarioVars;
    std::string currentScenario;
    
    std::string currentPlayer = "a1";
	public:
        virtual void processKeyboard(unsigned char key, int x, int y);
		virtual void processMouse(int button, int state, int x, int y);
		void performPicking(int x, int y);
		void processHits(GLint hits, GLuint buffer[]);
    
        void initGUI();
        virtual void processGUI(GLUI_Control *ctrl);
    
    
        void movie();
};


#endif
