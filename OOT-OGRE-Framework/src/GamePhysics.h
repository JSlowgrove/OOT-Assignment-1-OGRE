#pragma once

#include "stdafx.h"
#include <iostream>
#include <memory>
#include "MyUtils.h"

/**A definition of gravity*/
#define GRAVITY 98.1f

/**
@brief A class for the GamePhysics.
*/
class GamePhysics
{
private:
	/**
	A structure for game objects that need projectile motion.
	For use with SUVAT equations.
	*/
	struct ProjectileObject
	{
		/**The displacement of the object*/
		Ogre::Vector3 displacement;
		/**The initial velocities of the object*/
		Ogre::Vector3 initalVelocity;
		/**The velocities of the object*/
		Ogre::Vector3 velocity;
		/**The acceleration of the object*/
		Ogre::Real acceleration;
		/**The time taken by the object*/
		Ogre::Real time;

		/**
		Constructs the ProjectileObject.
		@param Ogre::Vector3 The inital velocity of the object.
		*/
		ProjectileObject(Ogre::Vector3 initalVelocity)
		{
			/*initialise the variables*/
			this->initalVelocity = velocity = initalVelocity;
			acceleration = -GRAVITY;
			time = 0.0f;
			displacement = 0.0f;
		}

		/**
		Constructs the ProjectileObject.
		@param Ogre::Real The inital x velocity of the object.
		@param Ogre::Real The inital y velocity of the object.
		@param Ogre::Real The inital z velocity of the object.
		*/
		ProjectileObject(Ogre::Real initalXVelocity, Ogre::Real initalYVelocity, Ogre::Real initalZVelocity)
		{
			/*initialise the variables*/
			this->initalVelocity = velocity = Ogre::Vector3(initalXVelocity, initalYVelocity, initalZVelocity);
			acceleration = -GRAVITY;
			time = 0.0f;
			displacement = 0.0f;
		}
	};

	/**The projectile object*/
	ProjectileObject* projectile;

public:
	/**
	Constructs the GamePhysics.
	@param Ogre::Vector3 The inital velocity of the projectile object.
	*/
	GamePhysics(Ogre::Vector3 initalVelocity);

	/**
	Constructs the GamePhysics.
	@param Ogre::Real The inital x velocity of the projectile object.
	@param Ogre::Real The inital y velocity of the projectile object.
	@param Ogre::Real The inital z velocity of the projectile object.
	*/
	GamePhysics(Ogre::Real initalXVelocity, Ogre::Real initalYVelocity, Ogre::Real initalZVelocity);

	/**
	Destructs the GamePhysics object.
	*/
	~GamePhysics();

	/**
	Updates the projectile.
	@param float The delta time.
	*/
	void updateProjectile(float dt);

	/**
	Getter # Gets the displacement of the Helicopter.
	@returns Ogre::Vector3 The displacement of the Helicopter.
	*/
	Ogre::Vector3 getProjectileDisplacement();

	/**
	SUVAT equation v=u+at.
	Works out the velocity from the initial velocity, the acceleration and the time.
	@param Ogre::Real The initial velocity.
	@param Ogre::Real The acceleration.
	@param Ogre::Real The time.
	@returns Ogre::Real The velocity.
	*/
	Ogre::Real getVfromUAT(Ogre::Real u, Ogre::Real a, Ogre::Real t);

	/**
	SUVAT equation s=ut+(1/2)a(t^2).
	Works out the displacement from the initial velocity, the acceleration and the time.
	@param Ogre::Real The initial velocity.
	@param Ogre::Real The acceleration.
	@param Ogre::Real The time.
	@returns Ogre::Real The displacement.
	*/
	Ogre::Real getSfromUAT(Ogre::Real u, Ogre::Real a, Ogre::Real t);

	/**
	SUVAT equation s=(1/2)(u+v)t.
	Works out the displacement from the initial velocity, the displacement and the time.
	@param Ogre::Real The initial velocity.
	@param Ogre::Real The displacement.
	@param Ogre::Real The time.
	@returns Ogre::Real The displacement.
	*/
	Ogre::Real getSfromUVT(Ogre::Real u, Ogre::Real v, Ogre::Real t);

	/**
	SUVAT equation v^2=u^2+2as.
	Works out the velocity squared from the initial velocity, the acceleration and the displacement.
	@param Ogre::Real The initial velocity.
	@param Ogre::Real The acceleration.
	@param Ogre::Real The displacement.
	@returns Ogre::Real The velocity squared.
	*/
	Ogre::Real getVSquaredfromUAS(Ogre::Real u, Ogre::Real a, Ogre::Real s);

	/**
	SUVAT equation s=vt-(1/2)a(t^2).
	Works out the displacement from the velocity, the acceleration and the time.
	@param Ogre::Real The velocity.
	@param Ogre::Real The acceleration.
	@param Ogre::Real The time.
	@returns Ogre::Real The displacement.
	*/
	Ogre::Real getSfromVAT(Ogre::Real v, Ogre::Real a, Ogre::Real t);
};