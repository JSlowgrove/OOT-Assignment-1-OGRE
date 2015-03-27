#pragma once

#include "stdafx.h"
#include <iostream>
#include <memory>
#include "OgreApplication.h"
#include "MyUtils.h"
#include "GameActor.h"
#include "GamePhysics.h"

/**
@brief A class for a Projectile object that inherits GameActor and GamePhysics.
*/
class Projectile : public GameActor, public GamePhysics
{
private:
	/**The parent node of the projectile*/
	std::shared_ptr<Ogre::SceneNode> parentNode;
public:
	/**
	Constructs the Projectile object.
	@param Ogre::Vector3 The position of the Projectile.
	@param Ogre::Vector3 The orientation of the Projectile.
	@param Ogre::Real The scale of the Projectile.
	@param std::shared_ptr<Ogre::SceneNode> A shared pointer to the parent node.
	@param Ogre::Vector3 The inital velocity of the Projectile.
	*/
	Projectile(Ogre::Vector3 position, Ogre::Vector3 orientation, Ogre::Real scale, 
		std::shared_ptr<Ogre::SceneNode> parentNode, Ogre::Vector3 initalVelocity);

	/**
	Destructs the Projectile object.
	*/
	~Projectile();

	/**
	Getter # Gets the world position of the Projectile.
	@returns Ogre::Vector3 The world position of the Projectile.
	*/
	Ogre::Vector3 getWorldPosition();

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