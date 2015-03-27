#include "stdafx.h"
#include "Turret.h"

/*
In my turret class I have its turret barrel as an instance inside of it, with the projectiles from the turret 
instanced within the barrel. As such if I wish to include another turret into the scene all that I need to do 
is initialise and update a new turret, and it will automatically create its own barrel and projectiles without 
me needing to instance them myself. 
*/

/**************************************************************************************************************/

/*Constructs the Turret object.*/
Turret::Turret(Ogre::Vector3 position, Ogre::Vector3 orientation, Ogre::Real scale) 
			 : GameActor(position, orientation, scale)
{
	/*initialise the targets*/
	lastTarget = target = Ogre::Vector3(0.0f, 0.0f, 0.0f);
}

/**************************************************************************************************************/

/*Destructs the Rotor object.*/
Turret::~Turret()
{
}

/**************************************************************************************************************/

/*Sets the target of the Turret.*/
void Turret::setTarget(Ogre::Vector3 target)
{
	/*set the targets*/
	lastTarget = this->target;
	this->target = target;

	/*set the target of the barrel*/
	barrel->setTarget(target);
}

/**************************************************************************************************************/

/*Rotates the Turret.*/
void Turret::rotateTurret()
{
	/*get the rotation in the form of a Quaternion*/
	Ogre::Quaternion orientationQ = 
		util::aim(target, lastTarget, position, Ogre::Vector3(0.0f, 1.0f, 0.0f));

	/*rotate the Turret*/
	gameActorNode->rotate(orientationQ);
}

/**************************************************************************************************************/

/*Sets the actor for the Turret.*/
void Turret::setUpActor(OgreApplication* application)
{
	/*load the mesh and material*/
	auto turret = application->GetSceneManager()->createEntity("Turret " + getActorID(), "turret.mesh");

	/*initialise helicopter rotation*/
	Ogre::Matrix3 rotateMat;
	float angleX = util::convertAngleToRadian(orientation.x);
	float angleY = util::convertAngleToRadian(orientation.x);
	float angleZ = util::convertAngleToRadian(orientation.x);
	rotateMat = util::RotationMatrixXYZ(Ogre::Vector3(angleX, angleY, angleZ));
	Ogre::Quaternion orientationQ;
	orientationQ.FromRotationMatrix(rotateMat);

	/*set the lighting*/
	turret->setCastShadows(false);

	/*initialise the Turret node*/
	gameActorNode.reset(application->GetSceneManager()->getRootSceneNode()
		->createChildSceneNode("Turret " + getActorID() + " "));
	gameActorNode->setScale(Ogre::Vector3(scale, scale, scale));
	gameActorNode->setOrientation(orientationQ);
	gameActorNode->setPosition(position);
	gameActorNode->attachObject(turret);
	gameActorNode->showBoundingBox(false);

	/*initialise the turret barrel*/
	Ogre::Vector3 initialPosition = Ogre::Vector3(0.0f, 0.0f, 0.0f);
	barrel.reset(new TurretBarrel(initialPosition, orientation, scale, gameActorNode, position));
	barrel->setUpActor(application);
}

/**************************************************************************************************************/

/*Updates the Turret actor.*/
void Turret::updateActor(float dt)
{
	/*rotate the Turret*/
	rotateTurret();

	/*update the Barrel*/
	barrel->updateActor(dt);
}

/**************************************************************************************************************/

/*Updates the projectiles.*/
void Turret::updateProjectiles(float dt, OgreApplication* application, std::shared_ptr<Helicopter> helicopter)
{
	/*update the projectiles*/
	barrel->updateProjectiles(dt, application, helicopter);
}