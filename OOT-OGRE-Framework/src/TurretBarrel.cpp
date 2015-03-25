#include "stdafx.h"
#include "TurretBarrel.h"

/**************************************************************************************************************/

/*Constructs the TurretBarrel object.*/
TurretBarrel::TurretBarrel(Ogre::Vector3 position, Ogre::Vector3 orientation, Ogre::Real scale, 
			 std::shared_ptr<Ogre::SceneNode> turretNode) 
			 : GameActor(position, orientation, scale)
{
	/*initialise rotate speed*/
	rotateSpeed = 0.0f;
	/*load the variables*/
	this->turretNode = turretNode;
}

/**************************************************************************************************************/

/*Destructs the TurretBarrel object.*/
TurretBarrel::~TurretBarrel()
{
}

/**************************************************************************************************************/

/*Sets the rotation speed of the TurretBarrel.*/
void TurretBarrel::setRotateSpeed(float rotateSpeed)
{
	/*set the rotor speed*/
	this->rotateSpeed = rotateSpeed;
}

/**************************************************************************************************************/

/*Rotates the TurretBarrel.*/
void TurretBarrel::rotateTurretBarrel(float dt)
{
	/*get the rotation in the form of a Quaternion*/
	Ogre::Quaternion orientationQ = util::covertRotateToQuaternion(
		Ogre::Vector3(util::convertAngleToRadian(rotateSpeed * dt), 0.0f, 0.0f));

	/*rotate the TurretBarrel*/
	gameActorNode->rotate(orientationQ, Ogre::Node::TS_LOCAL);
}

/**************************************************************************************************************/

/*Sets the actor for the TurretBarrel.*/
void TurretBarrel::setUpActor(OgreApplication* application)
{
	/*load the mesh and material*/
	auto rotor = application->GetSceneManager()->createEntity("Barrel " + getActorID(), "turretBarrel.mesh");

	/*set the lighting*/
	rotor->setCastShadows(false);

	/*initialise the rotor node*/
	gameActorNode.reset(turretNode->createChildSceneNode("Barrel " + getActorID()));
	gameActorNode->setPosition(position);
	gameActorNode->attachObject(rotor);
	gameActorNode->showBoundingBox(false);

	/*initialise the projectile*/
	projectile.reset(new Projectile(Ogre::Vector3(224.30f, 500.0f, 1985.0f), Ogre::Vector3(0.0f, 0.0f, 0.0f), 1.0f));

	projectile->setUpActor(application);
}

/**************************************************************************************************************/

/*Updates the TurretBarrel actor.*/
void TurretBarrel::updateActor(float dt)
{
	projectile->updateActor(dt);

	/*rotate the TurretBarrel*/
	rotateTurretBarrel(dt);
}