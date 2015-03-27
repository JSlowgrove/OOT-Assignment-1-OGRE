#include "stdafx.h"
#include "Projectile.h"

/*
My projectile class also inherits my game physics class as well as my game actor class. This is to allow the 
projectile to access and use the projectile motion and collision physics that I have included in this class. 
*/

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

/*Gets the world position of the Projectile.*/
Ogre::Vector3 Projectile::getWorldPosition()
{
	/*return the world position*/
	return gameActorNode->convertLocalToWorldPosition(position);
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
	gameActorNode.reset(parentNode->createChildSceneNode("Projectile Local " + getActorID()));
	
	/*get the world position of the node*/
	Ogre::Vector3 worldPosition = gameActorNode->convertLocalToWorldPosition(getPosition());

	/*re-initialise the Turret node to not be a child of the turret*/
	gameActorNode.reset(application->GetSceneManager()->getRootSceneNode()->createChildSceneNode("Projectile " + getActorID()));
	gameActorNode->setScale(Ogre::Vector3(scale, scale, scale));
	gameActorNode->setPosition(worldPosition);
	gameActorNode->attachObject(particle);
	gameActorNode->showBoundingBox(false);
	gameActorNode->attachObject(sphere);
}

/**************************************************************************************************************/

/*Updates the Projectile actor.*/
void Projectile::updateActor(float dt)
{
	/*update the projectile motion*/
	updateProjectile(dt);

	/*update the value of position*/
	position += getProjectileDisplacement();

	/*update the position*/
	gameActorNode->translate(getProjectileDisplacement(), Ogre::Node::TS_WORLD);
}