#include "stdafx.h"
#include "Projectile.h"

/**************************************************************************************************************/

/*Constructs the Projectile object.*/
Projectile::Projectile(Ogre::Vector3 position, Ogre::Vector3 orientation, Ogre::Real scale) 
	: GameActor(position, orientation, scale)
{
	motion.reset(new GamePhysics(100.0f,100.0f,100.0f));
}

/**************************************************************************************************************/

/*Destructs the Projectile object.*/
Projectile::~Projectile()
{
}

/**************************************************************************************************************/

/*Sets the actor for the Projectile.*/
void Projectile::setUpActor(OgreApplication* application)
{
	/*load the material for the projectile*/
	Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create("PROJECTILE", 
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	Ogre::Technique* firstTechnique = material->getTechnique(0);
	Ogre::Pass* firstPass = firstTechnique->getPass(0);
	Ogre::TextureUnitState* textureUnit = firstPass->createTextureUnitState();
	textureUnit->setTextureName("projectileTexture.png", Ogre::TEX_TYPE_2D);
	textureUnit->setTextureCoordSet(0);
	const Ogre::String& materialName = "PROJECTILE";

	/*load the mesh*/
	auto sphere = application->GetSceneManager()->createEntity("projectile " + getActorID(), "sphere.mesh");

	/*load the particle effect*/
	auto particle = application->GetSceneManager()->createParticleSystem("particle " + getActorID(), "Space/Sun");

	/*set up the entity*/
	sphere->setCastShadows(false);
	sphere->setMaterialName("PROJECTILE");

	/*initialise the Turret node*/
	gameActorNode.reset(application->GetSceneManager()->getRootSceneNode()
		->createChildSceneNode("Projectile " + getActorID()));
	gameActorNode->setScale(Ogre::Vector3(scale, scale, scale));
	gameActorNode->setPosition(position);
	gameActorNode->attachObject(particle);
	gameActorNode->showBoundingBox(false);
	gameActorNode->attachObject(sphere);
}

/**************************************************************************************************************/

/*Updates the Projectile actor.*/
void Projectile::updateActor(float dt)
{
	/*update the projectile motion*/
	motion->updateProjectile(dt);

	/*update the position from the projectile motion*/
	position.x = position.x + motion->getProjectileDisplacement().x;
	position.y = position.y + motion->getProjectileDisplacement().y;
	position.z = position.z + motion->getProjectileDisplacement().z;

	/*update the position*/
	gameActorNode->setPosition(position);
}