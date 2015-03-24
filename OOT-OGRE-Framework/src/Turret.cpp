#include "stdafx.h"
#include "Turret.h"

/**************************************************************************************************************/

/*Constructs the Turret object.*/
Turret::Turret(Ogre::Vector3 position, Ogre::Vector3 orientation, Ogre::Real scale) 
			 : GameActor(position, orientation, scale)
{
	/*initialise rotate speeds*/
	rotateSpeed = 0.0f;	
}

/**************************************************************************************************************/

/*Destructs the Rotor object.*/
Turret::~Turret()
{
}

/**************************************************************************************************************/

/*Sets the rotation speed of the Turret.*/
void Turret::setRotateSpeed(float rotateSpeed)
{
	/*set the rotor speed*/
	this->rotateSpeed = rotateSpeed;
}

/**************************************************************************************************************/

/*Rotates the Turret.*/
void Turret::rotateTurret(float dt)
{
	/*get the rotation in the form of a Quaternion*/
	Ogre::Quaternion orientationQ = util::covertRotateToQuaternion(
		Ogre::Vector3(0.0f, util::convertAngleToRadian(rotateSpeed * dt), 0.0f));

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
	barrel.reset(new TurretBarrel(initialPosition, orientation, scale, gameActorNode));
	barrel->setUpActor(application);
}

/**************************************************************************************************************/

/*Updates the Turret actor.*/
void Turret::updateActor(float dt)
{
	/*rotate the Turret*/
	rotateTurret(dt);

	/*update the TurretBarrel*/
	barrel->updateActor(dt);
}