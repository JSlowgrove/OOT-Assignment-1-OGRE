#pragma once

#include "stdafx.h"
#include <iostream>
#include <memory>
#include "OgreApplication.h"
#include "MyUtils.h"

/**
@brief A class for a Helicopter object.
*/
class Helicopter
{
private:
	/**A pointer to the Helicopter node.*/
	std::shared_ptr<Ogre::SceneNode> helicopterNode;
	/**A pointer to the main rotor node of the Helicopter.*/
	std::shared_ptr<Ogre::SceneNode> mainRotorNode;
	/**A pointer to the side rotor node of the Helicopter.*/
	std::shared_ptr<Ogre::SceneNode> sideRotorNode;
	/**The position of the Helicopter.*/
	Ogre::Vector3 position;
	/**The angle of the Helicopter.*/
	Ogre::Vector3 angle;
	/**The speed of the Helicopter.*/
	Ogre::Vector3 speed;
	/**The speed of the main rotors rotation.*/
	float mainRotorRotateSpeed;
	/**The speed of the side rotors rotation.*/
	float sideRotorRotateSpeed;
	/**The ID of the Helicopter*/
	int iD;	

public:
	/**
	Constructs the Helicopter object.
	@param unsigned int The ID of the helicopter
	*/
	Helicopter(int iD);

	/**
	Destructs the Helicopter object.
	*/
	~Helicopter();

	/**
	Setter # Sets the position of the Helicopter.
	@param Ogre::Vector3 The new position of the Helicopter.
	*/
	void setPosition(Ogre::Vector3 position);

	/**
	Setter # Sets the x position of the Helicopter.
	@param float The new x position of the Helicopter.
	*/
	void setX(float x);

	/**
	Setter # Sets the y position of the Helicopter.
	@param float The new y position of the Helicopter.
	*/
	void setY(float y);

	/**
	Setter # Sets the z position of the Helicopter.
	@param float The new z position of the Helicopter.
	*/
	void setZ(float z);

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
	Setter # Sets the angle of the Helicopter.
	@param Ogre::Vector3 The new angle of the Helicopter.
	*/
	void setAngle(Ogre::Vector3 angle);
	
	/**
	Setter # Sets the x angle of the Helicopter.
	@param float The new x angle of the Helicopter.
	*/
	void setXAngle(float xAngle);

	/**
	Setter # Sets the y angle of the Helicopter.
	@param float The new y angle of the Helicopter.
	*/
	void setYAngle(float yAngle);

	/**
	Setter # Sets the z angle of the Helicopter.
	@param float The new z angle of the Helicopter.
	*/
	void setZAngle(float zAngle);

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
	Setter # Sets the actor for the Helicopter.
	@param OgreApplication A pointer to the application.
	*/
	void setActor(OgreApplication* application);

	/**
	Updates the Helicopter actor.
	@param float The delta time.
	*/
	void updateActor(float dt);
};