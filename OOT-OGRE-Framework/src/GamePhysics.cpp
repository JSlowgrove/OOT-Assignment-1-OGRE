#include "stdafx.h"
#include "GamePhysics.h"

/**************************************************************************************************************/

/*Constructs the GamePhysics object.*/
GamePhysics::GamePhysics()
{
}

/**************************************************************************************************************/

/*Destructs the GamePhysics object.*/
GamePhysics::~GamePhysics()
{
}

/**************************************************************************************************************/

/*Updates the projectile.*/
void GamePhysics::updateProjectile(float dt)
{
	/*set the time to the change in time since last loop*/
	projectile->time = dt;
	/*set the initial velocity to the velocity from the last loop*/
	projectile->initalVelocity = projectile->velocity;

	/*set the x and z velocity to the initial velocity as it does not change*/
	projectile->velocity.x = projectile->initalVelocity.x;
	projectile->velocity.z = projectile->initalVelocity.z;
	/*work out the new y velocity using its SUVAT equation*/
	projectile->velocity.y = getVfromUAT(projectile->initalVelocity.y, projectile->acceleration, projectile->time);

	/*set the x and z displacement to the velocity multiplied by the time*/
	projectile->displacement.x = projectile->velocity.x * dt;
	projectile->displacement.z = projectile->velocity.z * dt;

	/*work out the new y displacement using its SUVAT equation*/
	projectile->displacement.y = getSfromVAT(projectile->velocity.y, projectile->acceleration, projectile->time);
}

/**************************************************************************************************************/

/*Gets the displacement of the projectile.*/
Ogre::Vector3 GamePhysics::getProjectileDisplacement()
{
	/*returns the displacement*/
	return projectile->displacement;
}

/**************************************************************************************************************/

/*SUVAT equation v=u+at.*/
Ogre::Real GamePhysics::getVfromUAT(Ogre::Real u, Ogre::Real a, Ogre::Real t)
{
	/*Works out the velocity from the initial velocity, the acceleration and the time.*/
	Ogre::Real v = u + (a*t);

	/*return the velocity*/
	return v;
}

/**************************************************************************************************************/

/*SUVAT equation s=ut+(1/2)a(t^2).*/
Ogre::Real GamePhysics::getSfromUAT(Ogre::Real u, Ogre::Real a, Ogre::Real t)
{
	/*Works out the displacement from the initial velocity, the acceleration and the time.*/
	Ogre::Real s = (u*t) + (0.5f * a * (t*t));

	/*return the displacement*/
	return s;
}

/**************************************************************************************************************/

/*SUVAT equation s=(1/2)(u+v)t*/
Ogre::Real GamePhysics::getSfromUVT(Ogre::Real u, Ogre::Real v, Ogre::Real t)
{
	/*works out the displacement from the initial velocity, the displacement and the time*/
	Ogre::Real s = 0.5f * (u+v) * t;

	/*returns the displacement*/
	return s;
}

/**************************************************************************************************************/

/*SUVAT equation v^2=u^2+2as*/
Ogre::Real GamePhysics::getVSquaredfromUAS(Ogre::Real u, Ogre::Real a, Ogre::Real s)
{
	/*works out the velocity squared from the initial velocity, the acceleration and the displacement*/
	Ogre::Real vSquared = (u*u) + (2*a*s);

	/*return the velocity squared*/
	return vSquared;
}

/**************************************************************************************************************/

/*SUVAT equation s=vt-(1/2)a(t^2)*/
Ogre::Real GamePhysics::getSfromVAT(Ogre::Real v, Ogre::Real a, Ogre::Real t)
{
	/*works out the displacement from the velocity, the acceleration and the time*/
	Ogre::Real s = (v*t) - (0.5f * a * (t*t));

	/*return the displacement*/
	return s;
}


/**************************************************************************************************************/

/*Test if there is a collision*/
bool GamePhysics::collisionTest(Ogre::Vector3 position, Ogre::Vector3 testPosition)
{
	/*get the distance between the two vectors*/
	Ogre::Real dist = position.distance(testPosition);

	/*check if within 100.0f of the target*/
	if (dist <= 50.0f)
	{
		/*collision is true*/
		return true;
	}

	/*collision is false*/
	return false;
}