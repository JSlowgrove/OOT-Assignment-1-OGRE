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

/*Sets the actor for the Turret.*/
void Turret::setUpActor(OgreApplication* application)
{
	/*load the mesh and material*/
	auto turret = application->GetSceneManager()->createEntity("Turret " + std::to_string(actorID), "turret.mesh");

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
		->createChildSceneNode("Turret " + std::to_string(actorID) + " "));
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
}