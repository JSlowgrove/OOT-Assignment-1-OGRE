#include "stdafx.h"
#include "Projectile.h"

/**************************************************************************************************************/

/*Constructs the Projectile object.*/
Projectile::Projectile(Ogre::Vector3 position, Ogre::Vector3 orientation, Ogre::Real scale, 
					   std::shared_ptr<Ogre::SceneNode> parentNode, Ogre::Vector3 initalVelocity) 
	: GameActor(position, orientation, scale)
{
	/*initialise the projectile*/
	projectile.reset(new ProjectileObject(initalVelocity));
	/*load the variables*/
	this->parentNode = parentNode;
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
	gameActorNode.reset(parentNode->createChildSceneNode("Projectile " + getActorID()));
	gameActorNode->setInheritScale(false);
	gameActorNode->setScale(Ogre::Vector3(scale, scale, scale));
	gameActorNode->attachObject(particle);
	gameActorNode->showBoundingBox(false);
	gameActorNode->attachObject(sphere);
	gameActorNode->translate(position, Ogre::Node::TS_LOCAL);
}

/**************************************************************************************************************/

/*Updates the Projectile actor.*/
void Projectile::updateActor(float dt)
{
	/*update the projectile motion*/
	updateProjectile(dt);

	/*update the position*/
	gameActorNode->translate(getProjectileDisplacement(), Ogre::Node::TS_WORLD);
}