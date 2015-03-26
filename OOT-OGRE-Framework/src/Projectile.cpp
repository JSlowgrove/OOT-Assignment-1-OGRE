#include "stdafx.h"
#include "Projectile.h"

/**************************************************************************************************************/

/*Constructs the Projectile object.*/
Projectile::Projectile(Ogre::Vector3 position, Ogre::Vector3 orientation, Ogre::Real scale) 
	: GameActor(position, orientation, scale)
{
	test = new GamePhysics(10.0f,100.0f,100.0f);
}

/**************************************************************************************************************/

/*Destructs the Projectile object.*/
Projectile::~Projectile()
{
	delete test;
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
	test->updateProjectile(dt);
	position.x = position.x + test->getProjectileDisplacement().x;
	position.y = position.y + test->getProjectileDisplacement().y;
	position.z = position.z + test->getProjectileDisplacement().z;
	gameActorNode->setPosition(position);
}