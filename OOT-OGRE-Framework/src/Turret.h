#pragma once

#include "stdafx.h"
#include <iostream>
#include <memory>
#include "OgreApplication.h"
#include "MyUtils.h"
#include "GameActor.h"
#include "TurretBarrel.h"

/**
@brief A class for a Turret object that inherits GameActor.
*/
class Turret : public GameActor
{
private:
	/**The speed of the Turret rotation.*/
	float rotateSpeed;
	/**A pointer to the TurretBarrel*/
	std::shared_ptr<TurretBarrel> barrel;
	/**The target vector of the Projectile*/
	Ogre::Vector3 target;
	
	/**
	Rotates the Turret. 
	@param float The delta time.
	*/
	void rotateTurret(float dt);

public:
	/**
	Constructs the Turret object.
	@param Ogre::Vector3 The position of the Turret.
	@param Ogre::Vector3 The orientation of the Turret.
	@param Ogre::Real The scale of the Turret.
	*/
	Turret(Ogre::Vector3 position, Ogre::Vector3 orientation, Ogre::Real scale);

	/**
	Destructs the Turret object.
	*/
	~Turret();

	/**
	Setter # Sets the target of the Turret.
	@param Ogre::Vector3 The new target of the Turret.
	*/
	void setTarget(Ogre::Vector3 target);

	/**
	Setter # Sets the rotation speed of the Turret.
	@param float The new rotation speed of the Turret.
	*/
	void setRotateSpeed(float rotateSpeed);

	/**
	Sets up the actor for the Turret.
	@param OgreApplication A pointer to the application.
	*/
	void setUpActor(OgreApplication* application);

	/**
	Updates the Turret actor.
	@param float The delta time.
	*/
	void updateActor(float dt);

	/**
	Updates the Projectiles.
	@param float The delta time.
	@param OgreApplication * A pointer to the application.
	*/
	void updateProjectiles(float dt, OgreApplication* application);
};