/*
Bullet Continuous Collision Detection and Physics Library
Copyright (c) 2015 Google Inc. http://bulletphysics.org

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose, 
including commercial applications, and to alter it and redistribute it freely, 
subject to the following restrictions:b

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/


#include "Experiment.h"


/*
struct Experiment : public CommonRigidBodyBase
{
	Experiment(struct GUIHelperInterface* helper)
		:CommonRigidBodyBase(helper)
	{
	}
	virtual ~Experiment(){
		m_guiHelper->removeCurrentPhysicsDebugDrawer();
	}
	virtual void initPhysics();
	virtual void renderScene();
	Robot* rob;
	virtual void setGravity(int x, int y, int z);
	void resetCamera()
	{
		float dist = 4;
		float pitch = 52;
		float yaw = 35;
		float targetPos[3]={0,0,0};
		m_guiHelper->resetCamera(dist,pitch,yaw,targetPos[0],targetPos[1],targetPos[2]);
	}
};
*/
Experiment::Experiment(struct GUIHelperInterface* helper)
	:CommonRigidBodyBase(helper)
{
}

Experiment::~Experiment() {
	m_guiHelper->removeAllGraphicsInstances();
	m_guiHelper->removeCurrentPhysicsDebugDrawer();
}

void Experiment::resetCamera()
{
	float dist = 4;
	float pitch = 52;
	float yaw = 35;
	float targetPos[3] = { 0,0,0 };
	m_guiHelper->resetCamera(dist, pitch, yaw, targetPos[0], targetPos[1], targetPos[2]);
}

void Experiment::initPhysics()
{
	m_guiHelper->setUpAxis(1);

	createEmptyDynamicsWorld();
	//m_dynamicsWorld->setGravity(btVector3(0,0,0));
	m_guiHelper->createPhysicsDebugDrawer(m_dynamicsWorld);

	if (m_dynamicsWorld->getDebugDrawer())
		m_dynamicsWorld->getDebugDrawer()->setDebugMode(btIDebugDraw::DBG_DrawWireframe+btIDebugDraw::DBG_DrawContactPoints);

	///create a few basic rigid bodies
	btBoxShape* groundShape = createBoxShape(btVector3(btScalar(50.),btScalar(50.),btScalar(50.)));
	

	//groundShape->initializePolyhedralFeatures();
	//btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0,1,0),50);
	
	m_collisionShapes.push_back(groundShape);

	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(0,-50,0));

	{
		btScalar mass(0.);
		createRigidBody(mass,groundTransform,groundShape, btVector4(0,0,1,1));
	}
	

	{
		//create a few dynamic rigidbodies
		// Re-using the same collision is better for memory usage and performance

		//btBoxShape* colShape = createBoxShape(btVector3(.1,.1,.1));
		


		/// Create Dynamic Objects
		btTransform startTransform;
		startTransform.setIdentity();

		btScalar	mass(1.f);

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0,0,0);
	    /*
		auto_ptr<Robot> p(new Robot(m_dynamicsWorld, btVector3(
			btScalar(0.2),
			btScalar(2 + .2),
			btScalar(0.2)), 1));
		*/

		Robot* ragdoll = new Robot(m_dynamicsWorld, btVector3(
			btScalar(0.2),
			btScalar(2 + .2),
			btScalar(0.2)), 1);
		rob = ragdoll;
		
			
	}

	//RagDoll* ragdoll = new RagDoll(m_dynamicsWorld, btVector3(0,0,0), 1);
	m_guiHelper->autogenerateGraphicsObjects(m_dynamicsWorld);
	
}


void Experiment::renderScene()
{
	CommonRigidBodyBase::renderScene();
	
}


void Experiment::setGravity(int x, int y, int z) {
	m_dynamicsWorld->setGravity(btVector3(x, y, z));
}




CommonExampleInterface*    BasicExampleCreateFunc(CommonExampleOptions& options)
{
	return new Experiment(options.m_guiHelper);

}


B3_STANDALONE_EXAMPLE(BasicExampleCreateFunc)



