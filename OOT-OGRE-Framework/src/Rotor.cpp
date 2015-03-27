#include "stdafx.h"
#include "Rotor.h"

/*
The method that I employed to animate the rotors was using percentages. I set a maximum rotation speed for the 
rotor, I then send in a percentage of that speed which I wish the rotors to target. The rotors then 
increase/decrease the speed of the rotors over time until they reach the target speed. This gives the
impression of the rotors speeding up or down, as opposed to just instantly changing speed.
*/

/**************************************************************************************************************/

/*Constructs the Rotor object.*/
Rotor::Rotor(Ogre::Vector3 position, Ogre::Vector3 orientation, Ogre::Real scale, 
			 std::shared_ptr<Ogre::SceneNode> helicopterNode, Ogre::String rotorType) 
	: GameActor(position, orientation, scale)
{
	/*initialise rotate speeds*/
	maxRotorSpeed = 2000.0f;
	targetRotateSpeedPercent = 75.0f;
	rotateSpeed = maxRotorSpeed * (targetRotateSpeedPercent * 0.01f);
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

/*Updates the rotation speed of the Rotor.*/
void Rotor::updateRotateSpeed()
{
	/*test if the rotor speed is less than the target speed*/
	if (rotateSpeed < maxRotorSpeed * (targetRotateSpeedPercent * 0.01f))
	{
		/*increase the rotor speed*/
		rotateSpeed += (0.05f * maxRotorSpeed);
	}

	/*test if the rotor speed is greater than the target speed*/
	if (rotateSpeed > maxRotorSpeed * (targetRotateSpeedPercent * 0.01f))
	{
		/*decrease the rotor speed*/
		rotateSpeed -= (0.05f * maxRotorSpeed);
	}
}

/**************************************************************************************************************/

/*Sets the target percentage rotation speed of the Rotor.*/
void Rotor::setTargetRotateSpeedPercent(Ogre::Real targetRotateSpeedPercent)
{
	/*set the target percent of the rotor speed*/
	this->targetRotateSpeedPercent = targetRotateSpeedPercent;
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
void Rotor::rotateRotor(float dt)
{
	/*get the rotation in the form of a Quaternion*/
	Ogre::Quaternion orientationQ = util::covertRotateToQuaternion(rotationAxis, 
		util::convertAngleToRadian(rotateSpeed * dt));

	/*rotate the rotor*/
	gameActorNode->rotate(orientationQ);
}

/**************************************************************************************************************/

/*Sets the actor for the Rotor.*/
void Rotor::setUpActor(OgreApplication* application)
{
	/*load the mesh and material (original model & texture from http://www.turbosquid.com/FullPreview/Index.cfm/ID/863905) */
	auto rotor = application->GetSceneManager()->createEntity(rotorType + getActorID(), rotorType + ".mesh");

	/*set the lighting*/
	rotor->setCastShadows(false);
	
	/*initialise the rotor node*/
	gameActorNode.reset(helicopterNode->createChildSceneNode(rotorType + " " + getActorID()));
	gameActorNode->setPosition(position);
	gameActorNode->attachObject(rotor);
	gameActorNode->showBoundingBox(false);
}

/**************************************************************************************************************/

/*Updates the rotor actor.*/
void Rotor::updateActor(float dt)
{
	/*set the rotor to spin*/
	rotateRotor(dt);
}