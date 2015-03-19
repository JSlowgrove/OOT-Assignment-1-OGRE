#pragma once

#include "stdafx.h"
#include <iostream>
#include <memory>
#include "OgreApplication.h"
#include "MyUtils.h"
#include "GameActor.h"

/**
@brief A class for a Helicopter object that inherits GameActor.
*/
class Helicopter : public GameActor
{
private:
	/**A pointer to the Helicopter node.*/
	std::shared_ptr<Ogre::SceneNode> helicopterNode;
	/**A pointer to the main rotor node of the Helicopter.*/
	std::shared_ptr<Ogre::SceneNode> mainRotorNode;
	/**A pointer to the side rotor node of the Helicopter.*/
	std::shared_ptr<Ogre::SceneNode> sideRotorNode;
	/**The speed of the Helicopter.*/
	Ogre::Vector3 speed;
	/**The speed of the main rotors rotation.*/
	float mainRotorRotateSpeed;
	/**The speed of the side rotors rotation.*/
	float sideRotorRotateSpeed;

public:
	/**
	Constructs the Helicopter object.
	@param Ogre::Vector3 The position of the Helicopter.
	@param Ogre::Vector3 The orientation of the Helicopter.
	@param Ogre::Real The scale of the Helicopter.
	*/
	Helicopter(Ogre::Vector3 position, Ogre::Vector3 orientation, Ogre::Real scale);

	/**
	Destructs the Helicopter object.
	*/
	~Helicopter();

	/**
	Setter # Sets the speed of the Helicopter.
	@param Ogre::Vector3 The new speed of the Helicopter.
	*/
	void setSpeed(Ogre::Vector3 speed);

	
	/**
	Setter # Sets the x speed of the Helicopter.
	@param float The new x speed of the Helicopter.
	*/
	void setXSpeed(float xSpeed);

	/**
	Setter # Sets the y speed of the Helicopter.
	@param float The new y speed of the Helicopter.
	*/
	void setYSpeed(float ySpeed);

	/**
	Setter # Sets the z speed of the Helicopter.
	@param float The new z speed of the Helicopter.
	*/
	void setZSpeed(float zSpeed);

	/**
	Setter # Sets the rotation speed of the main rotor.
	@param float The new rotation speed of the main rotor.
	*/
	void setMainRotorRotateSpeed(float mainRotorRotateSpeed);

	/**
	Setter # Sets the rotation speed of the side rotor.
	@param float The new rotation speed of the side rotor.
	*/
	void setSideRotorRotateSpeed(float sideRotorRotateSpeed);

	/**
	Sets up the actor for the Helicopter.
	@param OgreApplication A pointer to the application.
	*/
	void setUpActor(OgreApplication* application);

	/**
	Updates the Helicopter actor.
	@param float The delta time.
	@param OIS::Keyboard* A pointer to the keyboard.
	*/
	void updateActor(float dt, OIS::Keyboard* keyboard);
};