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
	/**The speed of the TurretBarrel rotation.*/
	float rotateSpeed;
	/**The amount of time it has been since the last projectile was fired.*/
	Ogre::Real timeSinceLastProjectile;
	/**A vector of Projectiles.*/
	std::vector<std::shared_ptr<Projectile>> projectile;

	/**
	Rotates the TurretBarrel. 
	@param float The delta time.
	*/
	void rotateTurretBarrel(float dt);

public:
	/**
	Constructs the TurretBarrel object.
	@param Ogre::Vector3 The position of the TurretBarrel.
	@param Ogre::Vector3 The orientation of the TurretBarrel.
	@param Ogre::Real The scale of the TurretBarrel.
	@param std::shared_ptr<Ogre::SceneNode> A shared pointer to the Turret node.
	*/
	TurretBarrel(Ogre::Vector3 position, Ogre::Vector3 orientation, Ogre::Real scale, 
		std::shared_ptr<Ogre::SceneNode> turretNode);

	/**
	Destructs the TurretBarrel object.
	*/
	~TurretBarrel();

	/**
	Setter # Sets the rotation speed of the TurretBarrel.
	@param float The new rotation speed of the TurretBarrel.
	*/
	void setRotateSpeed(float rotateSpeed);

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