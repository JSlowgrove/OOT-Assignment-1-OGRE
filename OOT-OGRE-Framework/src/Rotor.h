#pragma once

#include "stdafx.h"
#include <iostream>
#include <memory>
#include "OgreApplication.h"
#include "MyUtils.h"
#include "GameActor.h"

/**
@brief A class for a Rotor object that inherits GameActor.
*/
class Rotor : public GameActor
{
private:
	/**A pointer to the Helicopter node.*/
	std::shared_ptr<Ogre::SceneNode> helicopterNode;
	/**The speed of the Rotor rotation.*/
	Ogre::Real rotateSpeed;
	/**The type of Rotor*/
	Ogre::String rotorType;
	/**The rotation axis of the Rotor. 
	E.g. to rotate on the x rotation axis will be (1.0f,0.0f,0.0f).*/
	Ogre::Vector3 rotationAxis;
	/**The max speed that the Rotor will rotate*/
	Ogre::Real maxRotorSpeed;
	/**The percentage speed of the max speed that the Rotor will target*/
	Ogre::Real targetRotateSpeedPercent;

	/**
	Rotates the Rotor. 
	@param float The delta time.
	*/
	void rotateRotor(float dt);

public:
	/**
	Constructs the Rotor object.
	@param Ogre::Vector3 The position of the Rotor.
	@param Ogre::Vector3 The orientation of the Rotor.
	@param Ogre::Real The scale of the Rotor.
	@param std::shared_ptr<Ogre::SceneNode> A shared pointer to the Helicopter node.
	@param Ogre::String The type of the Rotor (aftRotor or topRotor).
	*/
	Rotor(Ogre::Vector3 position, Ogre::Vector3 orientation, Ogre::Real scale, 
		std::shared_ptr<Ogre::SceneNode> helicopterNode, Ogre::String rotorType);

	/**
	Destructs the Rotor object.
	*/
	~Rotor();

	/**
	Updates the rotation speed of the rotor.
	*/
	void updateRotateSpeed();

	/**
	Setter # Sets the target percent of the rotation speed of the rotor.
	@param Ogre::Real The new target percentage rotation speed of the rotor.
	*/
	void setTargetRotateSpeedPercent(Ogre::Real targetRotateSpeedPercent);

	/**
	Setter # Sets the rotation axis of the rotor.
	@param Ogre::Vector3 The rotation axis of the Rotor. 
	E.g. to rotate on the x rotation axis will be (1.0f,0.0f,0.0f)..
	*/
	void setRotateAxis(Ogre::Vector3 rotationAxis);

	/**
	Sets up the actor for the Rotor.
	@param OgreApplication A pointer to the application.
	*/
	void setUpActor(OgreApplication* application);

	/**
	Updates the Rotor actor.
	@param float The delta time.
	*/
	void updateActor(float dt);
};