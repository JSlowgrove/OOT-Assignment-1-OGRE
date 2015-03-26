#pragma once

#include "stdafx.h"
#include <iostream>
#include <memory>
#include "OgreApplication.h"
#include "MyUtils.h"
#include "GameActor.h"
#include "Projectile.h"

/**
@brief A class for a TurretBarrel object that inherits GameActor.
*/
class TurretBarrel : public GameActor
{
private:
	/**A pointer to the Turret node.*/
	std::shared_ptr<Ogre::SceneNode> turretNode;
	/**The amount of time it has been since the last projectile was fired.*/
	Ogre::Real timeSinceLastProjectile;
	/**A vector of Projectiles.*/
	std::vector<std::shared_ptr<Projectile>> projectile;
	/**Projectile magnitude*/
	Ogre::Real magnitude;
	/**The target vector of the Projectile*/
	Ogre::Vector3 target;
	/**The last target vector of the Projectile*/
	Ogre::Vector3 lastTarget;
	/**The world position of the Projectile spawn*/
	Ogre::Vector3 spawn;

	/**
	Rotates the TurretBarrel. 
	*/
	void rotateTurretBarrel();

	/**
	Work out the launch vector of the projectile.
	@returns Ogre::Vector3 The launch vector of the projectile.
	*/
	Ogre::Vector3 workOutLaunchVector();

public:
	/**
	Constructs the TurretBarrel object.
	@param Ogre::Vector3 The position of the TurretBarrel.
	@param Ogre::Vector3 The orientation of the TurretBarrel.
	@param Ogre::Real The scale of the TurretBarrel.
	@param std::shared_ptr<Ogre::SceneNode> A shared pointer to the Turret node.
	@param Ogre::Vector3 The world position of the projectile spawn.
	*/
	TurretBarrel(Ogre::Vector3 position, Ogre::Vector3 orientation, Ogre::Real scale, 
		std::shared_ptr<Ogre::SceneNode> turretNode, Ogre::Vector3 spawn);

	/**
	Destructs the TurretBarrel object.
	*/
	~TurretBarrel();

	/**
	Setter # Sets the target of the TurretBarrel.
	@param Ogre::Vector3 The new target of the TurretBarrel.
	*/
	void setTarget(Ogre::Vector3 target);

	/**
	Sets up the actor for the TurretBarrel.
	@param OgreApplication * A pointer to the application.
	*/
	void setUpActor(OgreApplication* application);

	/**
	Updates the TurretBarrel actor.
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