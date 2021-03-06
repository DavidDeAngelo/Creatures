/*
Bullet Continuous Collision Detection and Physics Library
Copyright (c) 2015 Google Inc. http://bulletphysics.org

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose, 
including commercial applications, and to alter it and redistribute it freely, 
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/
//#include<vld.h>
#include"../../Network.h"
/*
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif
*/




#include "../CommonInterfaces/CommonExampleInterface.h"
#include "../CommonInterfaces/CommonGUIHelperInterface.h"
#include "../Creatures/Experiment.h"
#include "../Utils/b3Clock.h"
#include <random>





#include "../OpenGLWindow/SimpleOpenGL3App.h"
#include <stdio.h>
#include <iostream>
#include "../ExampleBrowser/OpenGLGuiHelper.h"

Experiment*    example;
int gSharedMemoryKey=-1;

b3MouseMoveCallback prevMouseMoveCallback = 0;
static void OnMouseMove( float x, float y)
{
	bool handled = false; 
	handled = example->mouseMoveCallback(x,y); 	 
	if (!handled)
	{
		if (prevMouseMoveCallback)
			prevMouseMoveCallback (x,y);
	}
}

b3MouseButtonCallback prevMouseButtonCallback  = 0;
static void OnMouseDown(int button, int state, float x, float y) {
	bool handled = false;

	handled = example->mouseButtonCallback(button, state, x,y); 
	if (!handled)
	{
		if (prevMouseButtonCallback )
			prevMouseButtonCallback (button,state,x,y);
	}
}

b3KeyboardCallback prevKeyPress = 0;
static void OnKeyPress(int button, int state) {
	bool handled = false;
	handled = example->keyboardCallback(button, state);
	if (!handled)
	{
		if (prevKeyPress)
			prevKeyPress(button, state);
	}
}


class LessDummyGuiHelper : public DummyGUIHelper
{
	CommonGraphicsApp* m_app;
public:
	virtual CommonGraphicsApp* getAppInterface()
	{
		return m_app;
	}

	LessDummyGuiHelper(CommonGraphicsApp* app)
		:m_app(app)
	{
	}
};
int main(int argc, char* argv[])
{
	b3Clock clock;

	unsigned long int mApplicationStart = clock.getTimeInSeconds();


	GenericNEAT::Network net = GenericNEAT::Network();
	SimpleOpenGL3App* app = new SimpleOpenGL3App("Creatures",1024,768,true);
	
	prevMouseButtonCallback = app->m_window->getMouseButtonCallback();
	prevMouseMoveCallback = app->m_window->getMouseMoveCallback();
	prevKeyPress = app->m_window->getKeyboardCallback();

	app->m_window->setMouseButtonCallback((b3MouseButtonCallback)OnMouseDown);
	app->m_window->setMouseMoveCallback((b3MouseMoveCallback)OnMouseMove);
	app->m_window->setKeyboardCallback((b3KeyboardCallback)OnKeyPress);
	OpenGLGuiHelper gui(app,false);
	//LessDummyGuiHelper gui(app);
	//DummyGUIHelper gui;

	CommonExampleOptions options(&gui);
	
	for (int i = 0; i < 2; i++){
		//example = StandaloneExampleCreateFunc(options);
		example = new Experiment(&gui);

		example->initPhysics();
		example->resetCamera();
		delete example->rob;
		example->exitPhysics();
		delete example;
		
	}
	example = new Experiment(&gui);
	//example = StandaloneExampleCreateFunc(options);
	example->initPhysics();
	example->resetCamera();


	



	

	do
	{
		//example->setGravity(uniform_dist(e1), uniform_dist(e1), uniform_dist(e1));
		app->m_instancingRenderer->init();
        app->m_instancingRenderer->updateCamera(app->getUpAxis());

		btScalar dtSec = btScalar(clock.getTimeInSeconds());
		example->stepSimulation(dtSec);
		//example->stepSimulation(duration, max_sub_step, simulation_step_size)
		//example->stepSimulation(1.0 / 60.0);
		clock.reset();

		example->renderScene();
		DrawGridData dg;
        dg.upAxis = app->getUpAxis();
		app->drawGrid(dg);
		app->swapBuffer();
		

	} while (!app->m_window->requestedExit());
	
	
	delete example->rob;
	example->exitPhysics();
	delete example;
	delete app;
/*memory leak code*/
	//_CrtDumpMemoryLeaks();

	return 0;
}

