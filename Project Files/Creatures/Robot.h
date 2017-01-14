#pragma once
#ifndef ROBOT_H
#define ROBOT_H

#include "btBulletDynamicsCommon.h"
#include <stdio.h> //printf debugging
#include "BulletCollision/BroadphaseCollision/btDbvtBroadphase.h"

#include "BulletCollision/CollisionDispatch/btSimulationIslandManager.h"

#include "LinearMath/btAlignedObjectArray.h"
#include "LinearMath/btTransform.h"
#include <vector>

using namespace std;

class Robot
{
public:
	btDynamicsWorld* m_ownerWorld;
	//btCollisionShape* m_shapes[BODYPART_COUNT];
	vector<btCollisionShape*> m_shapes= vector<btCollisionShape*>(10);
	vector<btRigidBody*> m_bodies= vector<btRigidBody*>(10);
	vector<btTypedConstraint*> m_joints;

	
	virtual ~Robot();
	Robot(btDynamicsWorld* ownerWorld, const btVector3& positionOffset, btScalar scale);
	btRigidBody* createRigidBody(btScalar mass, const btTransform& startTransform, btCollisionShape* shape);
	btBoxShape* createBox(btScalar mass, const btTransform& startTransform, const btVector3& halfExtents, int index);
	void deleteObject(int index);
};

#endif
