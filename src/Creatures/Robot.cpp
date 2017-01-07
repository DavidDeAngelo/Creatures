#include "Robot.h"



Robot::Robot(btDynamicsWorld* ownerWorld, const btVector3& positionOffset, btScalar scale)
{
	m_ownerWorld = ownerWorld; //syncronize world

	//m_shapes[0] = new btCapsuleShape(btScalar(0.15)*scale, btScalar(0.20)*scale);
	// Setup all the rigid bodies
	
	btTransform offset; 
	offset.setIdentity();
	offset.setOrigin(positionOffset);
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(scale*btVector3(btScalar(0.), btScalar(1.), btScalar(0.)));

	//m_bodies[0] = createRigidBody(btScalar(1.), offset*transform, m_shapes[0]);

	btVector3* box = new btVector3(1, .1, .1);

	createBox(10, offset, *box,0);

	transform.setIdentity();
	transform.setOrigin(scale*btVector3(btScalar(1.), btScalar(.6), btScalar(1.)));
	createBox(10, offset*transform, *box, 1);
	deleteObject(1);
	btTransform  trans = offset*transform;

	btScalar x = trans.getOrigin().getX();
	btScalar y = trans.getOrigin().getY();
	btScalar z = trans.getOrigin().getZ();

	printf("\n\nposition: %f %f %f\n\n", x, y, z);


}



Robot::~Robot()
{
}


btRigidBody* Robot::createRigidBody(btScalar mass, const btTransform& startTransform, btCollisionShape* shape)
{
	bool isDynamic = (mass != 0.f);

	btVector3 localInertia(0, 0, 0);
	if (isDynamic)
		shape->calculateLocalInertia(mass, localInertia);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, shape, localInertia);
	btRigidBody* body = new btRigidBody(rbInfo);

	m_ownerWorld->addRigidBody(body);
	return body;
}


btBoxShape* Robot::createBox(btScalar mass, const btTransform& startTransform, const btVector3& halfExtents, int index)
{
	btBoxShape* shape = new btBoxShape(halfExtents);
	m_shapes[index] = shape;
	btScalar scale = 1;

	bool isDynamic = (mass != 0.f);

	btVector3 localInertia(0, 0, 0);
	if (isDynamic)
		shape->calculateLocalInertia(mass, localInertia);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, shape, localInertia);
	btRigidBody* body = new btRigidBody(rbInfo);
	m_bodies[index] = body;

	m_ownerWorld->addRigidBody(body);


	return shape;
}

void Robot::deleteObject(int index) {
		
	m_ownerWorld->removeRigidBody(m_bodies[index]);
	delete m_bodies[index]->getMotionState();

	delete m_bodies[index]; m_bodies[index] = 0;
	delete m_shapes[index]; m_shapes[index	] = 0;

}