#pragma once

#include "stdafx.h"
#include <iostream>
#include <memory>
#include "OgreApplication.h"
#include "MyUtils.h"
#include "GameActor.h"
#include "Rotor.h"

/**
@brief A class for a Helicopter object that inherits GameActor.
*/
class Helicopter : public GameActor
{
private:
	/**A pointer to the main rotor of the Helicopter.*/
	std::shared_ptr<Rotor> mainRotor;
	/**A pointer to the side rotor of the Helicopter.*/
	std::shared_ptr<Rotor> sideRotor;
	/**The spawn of the Helicopter.*/
	Ogre::Vector3 spawn;
	/**The initial direction of the Helicopter.*/
	Ogre::Vector3 direction;
	/**The speed of the Helicopter.*/
	Ogre::Vector3 speed;
	/**The max speed of the Helicopter.*/
	Ogre::Real maxSpeed;
	/**The percentage speed of the max speed that the Helicopter will target*/
	Ogre::Vector3 targetSpeedPercent;
	/**A bool for if the Helicopter should move up*/
	bool up;
	/**A bool for if the Helicopter should move down*/
	bool down;
	/**A bool for if the Helicopter should move left*/
	bool left;
	/**A bool for if the Helicopter should move right*/
	bool right;
	/**A bool for if the Helicopter should move forwards*/
	bool forwards;
	/**A bool for if the Helicopter should move backwards*/
	bool backwards;
	/**The x mouse position*/
	int mouseX;
	/**The y mouse position*/
	int mouseY;
	/**The health of the helicopter*/
	int health;

	/**
	Updates the speeds of the helicopter using the user commands.
	*/
	void updateSpeed();

	/**
	Rotates the helicopter using the user commands.
	*/
	void rotateHelicopter();

	/**
	Updates the move speed of the Helicopter.
	*/
	void updateMoveSpeed();

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
	Decrease the health of the Helicopter by 1.
	*/
	void takeDamage();

	/**
	Resets the Helicopter to it's initial values.
	*/
	void resetHelicopter();

	/**
	Getter # Gets the health of the Helicopter.
	@returns int The health of the Helicopter.
	*/
	int getHealth();

	/**
	Getter # Gets the speed of the Helicopter.
	@returns Ogre::Vector3 The speed of the Helicopter.
	*/
	Ogre::Vector3 getSpeed();

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
	Getter # Gets the last rotation of the Helicopter.
	@returns Ogre::Vector3 The last rotate of the Helicopter.
	*/
	Ogre::Vector3 getLastRotation();

	/**
	Sets up the actor for the Helicopter.
	@param OgreApplication A pointer to the application.
	*/
	void setUpActor(OgreApplication* application);

	/**
	Handles the user input.
	@param OIS::Keyboard* A pointer to the keyboard.
	*/
	void handleInput(OIS::Keyboard* keyboard, OIS::Mouse* mouse);

	/**
	Updates the Helicopter actor.
	@param float The delta time.
	*/
	void updateActor(float dt);
};