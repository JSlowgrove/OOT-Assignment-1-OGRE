#include "stdafx.h"
#include "TurretBarrel.h"

/**************************************************************************************************************/

/*Constructs the TurretBarrel object.*/
TurretBarrel::TurretBarrel(Ogre::Vector3 position, Ogre::Vector3 orientation, Ogre::Real scale, 
			 std::shared_ptr<Ogre::SceneNode> turretNode, Ogre::Vector3 spawn) 
			 : GameActor(position, orientation, scale)
{
	/*initialise the targets*/
	lastTarget = target = 0.0f;
	/*initialise the time since last projectile*/
	timeSinceLastProjectile = 0.0f;
	/*initialise the magnitude*/
	magnitude = 500.0f;
	/*load the variables*/
	this->turretNode = turretNode;
	this->spawn = spawn;
}

/**************************************************************************************************************/

/*Destructs the TurretBarrel object.*/
TurretBarrel::~TurretBarrel()
{
}

/**************************************************************************************************************/

/*Sets the target of the Turret.*/
void TurretBarrel::setTarget(Ogre::Vector3 target)
{
	/*set the targets*/
	lastTarget = this->target;
	this->target = target;
}

/**************************************************************************************************************/

/*Rotates the TurretBarrel.*/
void TurretBarrel::rotateTurretBarrel()
{
	/*get the rotation in the form of a Quaternion*/
	Ogre::Quaternion orientationQ = 
		util::aim(target, lastTarget, position, Ogre::Vector3(1.0f, 0.0f, 0.0f));

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
		Ogre::Vector3(0.0f, 0.0f, 0.0f), 0.03f, gameActorNode, workOutLaunchVector()));
	projectile.back()->setUpActor(application);
}

/**************************************************************************************************************/

/*Updates the TurretBarrel actor.*/
void TurretBarrel::updateActor(float dt)
{
	/*rotate the TurretBarrel*/
	rotateTurretBarrel();
}

/**************************************************************************************************************/

/*Updates the Projectile vector.*/
void TurretBarrel::updateProjectiles(float dt, OgreApplication* application, std::shared_ptr<Helicopter> helicopter)
{
	/*update the time since last projectile*/
	timeSinceLastProjectile += dt;

	/*if the time since the last projectile was more than a second ago*/
	if (timeSinceLastProjectile > 1.0f)
	{
		/*initialise a new projectile*/
		projectile.push_back(make_shared<Projectile>(Ogre::Vector3(0.0f, 5.0f, 0.0f),
			Ogre::Vector3(0.0f, 0.0f, 0.0f), 0.03f, gameActorNode, workOutLaunchVector()));
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

	/*loop through all of the projectiles*/
	for (unsigned int i = 0; i < projectile.size(); i++)
	{
		/*test if the projectile collides with the helicopter*/
		if (projectile[i]->collisionTest(projectile[i]->getWorldPosition(), target))
		{
			/*remove the projectile*/
			projectile.erase(projectile.begin() + i);
			
			/*decrease the health of the helicopter*/
			helicopter->takeDamage();

			/*check if the helicopter is destroyed*/
			if (helicopter->getHealth() == 0)
			{
				/*reset the helicopter*/
				helicopter->resetHelicopter();
			}
		}
	}

	/*if there is more than 10 projectiles in the vector*/
	if (projectile.size() > 10)
	{
		/*remove the projectile at the front*/
		projectile.erase(projectile.begin());
	}
}


/**************************************************************************************************************/

/*Work out the launch vector of the projectile.*/
Ogre::Vector3 TurretBarrel::workOutLaunchVector()
{
	/*work out the direction vector*/
	Ogre::Vector3 launchVector = target - (spawn + Ogre::Vector3(0.0f, 5.0f, 0.0f));

	/*normalise the launch vector*/
	launchVector.normalise();

	/*increase the launch vector by the magnitude of the projectile*/
	launchVector *= magnitude;
	
	/*Add a magic number to account for projectile motion*/
	launchVector.y += 10.0f;

	/*return the launch vector of the projectile*/
	return launchVector;
}
