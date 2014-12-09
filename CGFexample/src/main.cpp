#include <iostream>
#include <exception>

#include "CGFapplication.h"
#include "Scene.h"
#include "TPInterface.h"
#include "PickInterface.h"

using std::cout;
using std::exception;


int main(int argc, char* argv[]) {

	CGFapplication app = CGFapplication();

	try {
		app.init(&argc, argv);
        Scene * scene = new Scene();
		app.setScene(scene);
        app.setInterface(new CGFinterface());
        app.setInterface(new TPInterface(scene));
        app.setInterface(new PickInterface());
		
		app.run();
	}
	catch(GLexception& ex) {
		cout << "Error: " << ex.what();
		return -1;
	}
	catch(exception& ex) {
		cout << "Unexpected error: " << ex.what();
		return -1;
	}

	return 0;
}