#include "stdafx.h"
#include "Rotor.h"

/**************************************************************************************************************/

/*Constructs the Rotor object.*/
Rotor::Rotor(Ogre::Vector3 position, Ogre::Vector3 orientation, Ogre::Real scale, 
			 std::shared_ptr<Ogre::SceneNode> helicopterNode, Ogre::String rotorType) 
	: GameActor(position, orientation, scale)
{
	/*initialise rotate speed*/
	rotateSpeed = 0.0f;
	/*load the variables*/
	this->helicopterNode = helicopterNode;
	this->rotorType = rotorType;
}

/**************************************************************************************************************/

/*Destructs the Rotor object.*/
Rotor::~Rotor()
{
}

/**************************************************************************************************************/

/*Sets the rotation speed of the Rotor.*/
void Rotor::setRotateSpeed(float rotateSpeed)
{
	/*set the rotor speed*/
	this->rotateSpeed = rotateSpeed;
}

/**************************************************************************************************************/

/*Sets the rotation axis of the Rotor.*/
void Rotor::setRotateAxis(Ogre::Vector3 rotationAxis)
{
	/*set the rotor axis*/
	this->rotationAxis = rotationAxis;
}

/**************************************************************************************************************/

/*rotates the Rotor.*/
void Rotor::rotateRotor()
{
	/*work out the rotation angle of the rotor*/
	Ogre::Matrix3 rotateMat;
	float rotateAngle = rotateSpeed * 3.141596f / 180.0f;

	/*get the rotation in the form of a Quaternion*/
	Ogre::Quaternion orientationQ = util::covertRotateToQuaternion(rotationAxis, rotateAngle);

	/*rotate the rotor*/
	rotorNode->rotate(orientationQ);
}

/**************************************************************************************************************/

/*Sets the actor for the Rotor.*/
void Rotor::setUpActor(OgreApplication* application)
{
	/*load the mesh and material (original model & texture from http://www.turbosquid.com/FullPreview/Index.cfm/ID/863905) */
	auto rotor = application->GetSceneManager()->createEntity(rotorType, rotorType + ".mesh");

	/*set the lighting*/
	rotor->setCastShadows(false);
	
	/*initialise the rotor node*/
	rotorNode.reset(helicopterNode->createChildSceneNode(rotorType + " " + std::to_string(actorID)));
	rotorNode->setPosition(position);
	rotorNode->attachObject(rotor);
	rotorNode->showBoundingBox(false);
}

/**************************************************************************************************************/

/*Updates the rotor actor.*/
void Rotor::updateActor(float dt)
{
	/*set the rotor to spin*/
	rotateRotor();
}