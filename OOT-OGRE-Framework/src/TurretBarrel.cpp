#include "stdafx.h"
#include "TurretBarrel.h"

/**************************************************************************************************************/

/*Constructs the TurretBarrel object.*/
TurretBarrel::TurretBarrel(Ogre::Vector3 position, Ogre::Vector3 orientation, Ogre::Real scale, 
			 std::shared_ptr<Ogre::SceneNode> turretNode) 
			 : GameActor(position, orientation, scale)
{
	/*initialise rotate speed*/
	rotateSpeed = 0.0f;
	/*initialise the time since last projectile*/
	timeSinceLastProjectile = 0.0f;
	/*load the variables*/
	this->turretNode = turretNode;
}

/**************************************************************************************************************/

/*Destructs the TurretBarrel object.*/
TurretBarrel::~TurretBarrel()
{
}

/**************************************************************************************************************/

/*Sets the rotation speed of the TurretBarrel.*/
void TurretBarrel::setRotateSpeed(float rotateSpeed)
{
	/*set the rotor speed*/
	this->rotateSpeed = rotateSpeed;
}

/**************************************************************************************************************/

/*Rotates the TurretBarrel.*/
void TurretBarrel::rotateTurretBarrel(float dt)
{
	/*get the rotation in the form of a Quaternion*/
	Ogre::Quaternion orientationQ = util::covertRotateToQuaternion(
		Ogre::Vector3(util::convertAngleToRadian(rotateSpeed * dt), 0.0f, 0.0f));

	/*rotate the TurretBarrel*/
	gameActorNode->rotate(orientationQ, Ogre::Node::TS_LOCAL);
}

/**************************************************************************************************************/

/*Sets the actor for the TurretBarrel.*/
void TurretBarrel::setUpActor(OgreApplication* application)
{
	/*load the mesh and material*/
	auto rotor = application->GetSceneManager()->createEntity("Barrel " + getActorID(), "turretBarrel.mesh");

	/*set the lighting*/
	rotor->setCastShadows(false);

	/*initialise the rotor node*/
	gameActorNode.reset(turretNode->createChildSceneNode("Barrel " + getActorID()));
	gameActorNode->setPosition(position);
	gameActorNode->attachObject(rotor);
	gameActorNode->showBoundingBox(false);

	/*initialise the projectile*/
	projectile.push_back(make_shared<Projectile>(Ogre::Vector3(0.0f, 5.0f, 0.0f),
		Ogre::Vector3(0.0f, 0.0f, 0.0f), 0.03f, gameActorNode, Ogre::Vector3(100.0f, 100.0f, 100.0f)));
	projectile.back()->setUpActor(application);
}

/**************************************************************************************************************/

/*Updates the TurretBarrel actor.*/
void TurretBarrel::updateActor(float dt)
{
	/*rotate the TurretBarrel*/
	rotateTurretBarrel(dt);
}

/**************************************************************************************************************/

/*Updates the Projectile vector.*/
void TurretBarrel::updateProjectiles(float dt, OgreApplication* application)
{
	/*update the time since last projectile*/
	timeSinceLastProjectile += dt;

	/*if the time since the last projectile was more than a second ago*/
	if (timeSinceLastProjectile > 1.0f)
	{
		/*initialise a new projectile*/
		projectile.push_back(make_shared<Projectile>(Ogre::Vector3(0.0f, 5.0f, 0.0f),
			Ogre::Vector3(0.0f, 0.0f, 0.0f), 0.03f, gameActorNode, Ogre::Vector3(100.0f, 100.0f, 100.0f)));
		projectile.back()->setUpActor(application);
		
		/*reset the time since the last projectile*/
		timeSinceLastProjectile = 0.0f;
	}

	/*loop through all of the projectiles*/
	for (auto currentProjectile : projectile)
	{
		/*update the projectile*/
		currentProjectile->updateActor(dt);
	}

	/*if there is more than 10 projectiles in the vector*/
	if (projectile.size() > 10)
	{
		/*remove the projectile at the front*/
		projectile.erase(projectile.begin());
	}
}