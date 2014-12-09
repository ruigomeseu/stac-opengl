#include "PickInterface.h"
#include "PickScene.h"
#include "CGFapplication.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>	// for memcpy()...
#include <stdlib.h>	// for atoi()...
#include <unistd.h>	// for gethostname()...
#include <ctype.h>	// for tolower()...
#include <iostream>

#define BUFS	1024
#define NAMS	64


// buffer to be used to store the hits during picking
#define BUFSIZE 256
GLuint selectBuf[BUFSIZE];

bool openedSocket = false;
int sock_address;

void PickInterface::processMouse(int button, int state, int x, int y) 
{
	CGFinterface::processMouse(button,state, x, y);

	// do picking on mouse press (GLUT_DOWN)
	// this could be more elaborate, e.g. only performing picking when there is a click (DOWN followed by UP) on the same place
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		performPicking(x,y);
}

void PickInterface::performPicking(int x, int y) 
{
	// Sets the buffer to be used for selection and activate selection mode
	glSelectBuffer (BUFSIZE, selectBuf);
	glRenderMode(GL_SELECT);

	// Initialize the picking name stack
	glInitNames();

	// The process of picking manipulates the projection matrix
	// so we will be activating, saving and manipulating it
	glMatrixMode(GL_PROJECTION);

	//store current projmatrix to restore easily in the end with a pop
	glPushMatrix ();

	//get the actual projection matrix values on an array of our own to multiply with pick matrix later
	GLfloat projmat[16];
	glGetFloatv(GL_PROJECTION_MATRIX,projmat);

	// reset projection matrix
	glLoadIdentity();

	// get current viewport and use it as reference for 
	// setting a small picking window of 5x5 pixels around mouse coordinates for picking
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	// this is multiplied in the projection matrix
	gluPickMatrix ((GLdouble) x, (GLdouble) (CGFapplication::height - y), 5.0, 5.0, viewport);

	// multiply the projection matrix stored in our array to ensure same conditions as in normal render
	glMultMatrixf(projmat);

	// force scene drawing under this mode
	// only the names of objects that fall in the 5x5 window will actually be stored in the buffer
	scene->display();

	// restore original projection matrix
	glMatrixMode (GL_PROJECTION);
	glPopMatrix ();

	glFlush();

	// revert to render mode, get the picking results and process them
	GLint hits;
	hits = glRenderMode(GL_RENDER);
	processHits(hits, selectBuf);
}

int openSocket(std::string hostname, int port){
    int sock;
    struct sockaddr_in server;
    struct hostent *hp;
    char buf[BUFS];
    
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("Opening stream socket");
        exit(1);
    }
    
    /* Connect socket using server name indicated in the command line */
    server.sin_family = AF_INET;
    hp = gethostbyname(hostname.c_str());
    
    if (hp == NULL)
    {
        perror("Trying to get host by name");
        exit(2);
    }
    memcpy((char *)&server.sin_addr, (char *)hp->h_addr, hp->h_length);
    server.sin_port = htons(port);
    
    if (connect(sock, (struct sockaddr *)&server, sizeof server) < 0)
    {
        perror("Connecting stream socket");
        exit(1);
    }
    
    return sock;
}

void closeSocket(int socket){
    close(socket);
}

void sendMessageSocket(int socket, std::string message){
    if (write (socket, message.c_str(), strlen(message.c_str())) < 0)
        perror("Writing on stream socket");
    
}

void receiveMessageSocket(int socket){
    int pos = 0;
    char msgRecv[BUFS];
    while(true){
        recv(socket, &msgRecv[pos], 1, 0);
        if(msgRecv[pos]=='\n')
            break;
        pos++;
    }
    std::cout << msgRecv << std::endl;
}

void PickInterface::processHits (GLint hits, GLuint buffer[]) 
{
	GLuint *ptr = buffer;
	GLuint mindepth = 0xFFFFFFFF;
	GLuint *selected=NULL;
	GLuint nselected;

    if(!openedSocket){
        sock_address = openSocket("127.0.0.1", 60070);
        openedSocket=true;
    }
	// iterate over the list of hits, and choosing the one closer to the viewer (lower depth)
	for (int i=0;i<hits;i++) {
		int num = *ptr; ptr++;
		GLuint z1 = *ptr; ptr++;
		ptr++;
		if (z1 < mindepth && num>0) {
			mindepth = z1;
			selected = ptr;
			nselected=num;
		}
		for (int j=0; j < num; j++) 
			ptr++;
	}
	
	// if there were hits, the one selected is in "selected", and it consist of nselected "names" (integer ID's)
	if (selected!=NULL)
	{
		// this should be replaced by code handling the picked object's ID's (stored in "selected"), 
		// possibly invoking a method on the scene class and passing "selected" and "nselected"
		printf("Picked ID's: ");
        sendMessageSocket(sock_address, "comando([[p1,p1,p1,p1,b1],[p1,p1,p1,p1,p1],[p1,p1,p1,p1,p1],[p1,p1,p1,p1,p1],[a1,p1,p1,p1,p1]],a1,1,1,1).\n");
        for (int i=0; i<nselected; i++){
			printf("%d ",selected[i]);
        }
		printf("\n");
        receiveMessageSocket(sock_address);
	}
	else
		printf("Nothing selected while picking \n");	
}
