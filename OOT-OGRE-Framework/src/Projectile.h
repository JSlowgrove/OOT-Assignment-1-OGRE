#pragma once

#include "stdafx.h"
#include <iostream>
#include <memory>
#include "OgreApplication.h"
#include "MyUtils.h"
#include "GameActor.h"

/**
@brief A class for a Projectile object that inherits GameActor.
*/
class Projectile : public GameActor
{
private:
public:
	/**
	Constructs the Projectile object.
	@param Ogre::Vector3 The position of the Projectile.
	@param Ogre::Vector3 The orientation of the Projectile.
	@param Ogre::Real The scale of the Projectile.
	*/
	Projectile(Ogre::Vector3 position, Ogre::Vector3 orientation, Ogre::Real scale);

	/**
	Destructs the Projectile object.
	*/
	~Projectile();

	/**
	Sets up the actor for the Projectile.
	@param OgreApplication A pointer to the application.
	*/
	void setUpActor(OgreApplication* application);

	/**
	Updates the Projectile actor.
	@param float The delta time.
	*/
	void updateActor(float dt);
};