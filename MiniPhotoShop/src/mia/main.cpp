//
//  main.cpp
//  Originally created by the CSci-3081W TAs.
//


#include "MIAApp.h"
#include "MIACommandApp.h"
#include "ColorData.h"
#include <iostream>

int main(int argc, char* argv[]) 
{
// 	MIAApp *app = new MIAApp(argc, argv, 800, 800, ColorData(1,1,0.95));
// 	if(argc == 1)
// 	{
// 		app->runMainLoop();
// 	}
// 	//delete app;
// 	exit(0);
// 	//return 1;
// }

	if(argc == 1)
	{
		// runMainLoop returns when the user closes the graphics window.
		MIAApp *app = new MIAApp(argc, argv, 800, 800, ColorData(1,1,0.95));
		app->runMainLoop();
		delete app;
	}
	else
	{
		MIACommandApp *capp = new MIACommandApp(argc, argv);
		capp->executeCommand(argc, argv);		
		//delete capp;
	}

	exit(0);
}
