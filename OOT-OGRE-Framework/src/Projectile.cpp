#include "stdafx.h"
#include "Projectile.h"

/**************************************************************************************************************/

/*Constructs the Projectile object.*/
Projectile::Projectile(Ogre::Vector3 position, Ogre::Vector3 orientation, Ogre::Real scale) 
	: GameActor(position, orientation, scale)
{
}

/**************************************************************************************************************/

/*Projectile the Projectile object.*/
Projectile::~Projectile()
{
}

/**************************************************************************************************************/

/*Sets the actor for the Projectile.*/
void Projectile::setUpActor(OgreApplication* application)
{
	/*load the particle effect*/
	auto particle = application->GetSceneManager()->createParticleSystem("projectile", "Space/Sun");

	/*initialise the Turret node*/
	gameActorNode.reset(application->GetSceneManager()->getRootSceneNode()
		->createChildSceneNode("Projectile " + getActorID()));
	gameActorNode->setScale(Ogre::Vector3(scale, scale, scale));
	gameActorNode->setPosition(position);
	gameActorNode->attachObject(particle);
	gameActorNode->showBoundingBox(false);
}

/**************************************************************************************************************/

/*Updates the Projectile actor.*/
void Projectile::updateActor(float dt)
{
}