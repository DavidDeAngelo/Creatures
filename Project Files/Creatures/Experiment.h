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

#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include "RagDoll.h"
#include "Robot.h"
//#include <memory>

#include "btBulletDynamicsCommon.h"

#include "LinearMath/btVector3.h"
#include "LinearMath/btAlignedObjectArray.h"

#include "../CommonInterfaces/CommonRigidBodyBase.h"

struct Experiment : public CommonRigidBodyBase
{

	Experiment(struct GUIHelperInterface* helper);
	virtual ~Experiment();
	virtual void initPhysics();
	virtual void renderScene();
	Robot* rob;
	virtual void setGravity(int x, int y, int z);
	virtual bool keyboardCallback(int key, int state);
	virtual void stepSimulation(float deltaTime);
	void resetCamera();

	private:
		bool isPaused=false;
};


class CommonExampleInterface*    BasicExampleCreateFunc(struct CommonExampleOptions& options);


#endif //BASIC_DEMO_PHYSICS_SETUP_H
