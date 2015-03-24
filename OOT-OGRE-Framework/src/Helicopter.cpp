#include "stdafx.h"
#include "Helicopter.h"

/**************************************************************************************************************/

/*Constructs the Helicopter object.*/
Helicopter::Helicopter(Ogre::Vector3 position, Ogre::Vector3 orientation, Ogre::Real scale) 
	: GameActor(position, orientation, scale)
{
	/*initialise the user commands to false*/
	up = down = left = right = forwards = backwards = rotateUp = rotateDown = rotateLeft = rotateRight = false;

	/*initialise the helicopter speed*/
	speed = Ogre::Vector3(0.0f, 0.0f, 0.0f);

	/*initialise the rotate speeds*/
	rotateSpeed = Ogre::Vector3(0.0f, 0.0f, 0.0f);
}

/**************************************************************************************************************/

/*Destructs the Helicopter object.*/
Helicopter::~Helicopter()
{
}

/**************************************************************************************************************/

/*Gets the speed of the Helicopter.*/
Ogre::Vector3 Helicopter::getSpeed()
{
	/*return the speed*/
	return speed;
}

/**************************************************************************************************************/

/*Sets the speed of the Helicopter.*/
void Helicopter::setSpeed(Ogre::Vector3 speed)
{
	/*set the speed*/
	this->speed = speed;
}

/**************************************************************************************************************/

/*Sets the x speed of the Helicopter.*/
void Helicopter::setXSpeed(float xSpeed)
{
	/*set the x speed*/
	speed = Ogre::Vector3(xSpeed, speed.y, speed.z);
}

/**************************************************************************************************************/

/*Sets the y speed of the Helicopter.*/
void Helicopter::setYSpeed(float ySpeed)
{
	/*set the y speed*/
	speed = Ogre::Vector3(speed.x, ySpeed, speed.z);
}

/**************************************************************************************************************/

/*Sets the z speed of the Helicopter.*/
void Helicopter::setZSpeed(float zSpeed)
{
	/*set the x speed*/
	speed = Ogre::Vector3(speed.x, speed.y, zSpeed);
}

/**************************************************************************************************************/

/*Gets the rotate speed of the Helicopter.*/
Ogre::Vector3 Helicopter::getRotateSpeed()
{
	/*return the rotate speed*/
	return rotateSpeed;
}

/**************************************************************************************************************/

/*Sets the rotate speed of the Helicopter.*/
void Helicopter::setRotateSpeed(Ogre::Vector3 rotateSpeed)
{
	/*set the rotate speed*/
	this->rotateSpeed = rotateSpeed;
}

/**************************************************************************************************************/

/*Sets the x rotate speed of the Helicopter.*/
void Helicopter::setXRotateSpeed(float xRotateSpeed)
{
	/*set the x rotate speed*/
	rotateSpeed = Ogre::Vector3(xRotateSpeed, rotateSpeed.y, rotateSpeed.z);
}

/**************************************************************************************************************/

/*Sets the y rotate speed of the Helicopter.*/
void Helicopter::setYRotateSpeed(float yRotateSpeed)
{
	/*set the y rotate speed*/
	rotateSpeed = Ogre::Vector3(rotateSpeed.x, yRotateSpeed, rotateSpeed.z);
}

/**************************************************************************************************************/

/*Sets the z rotate speed of the Helicopter.*/
void Helicopter::setZRotateSpeed(float zRotateSpeed)
{
	/*set the x rotate speed*/
	rotateSpeed = Ogre::Vector3(rotateSpeed.x, rotateSpeed.y, zRotateSpeed);
}

/**************************************************************************************************************/

/*Gets the last rotation of the Helicopter.*/
Ogre::Vector3 Helicopter::getLastRotation()
{
	/*return the last rotation*/
	return lastRotation;
}

/**************************************************************************************************************/

/*Sets the actor for the Helicopter.*/
void Helicopter::setUpActor(OgreApplication* application)
{
	/*initialise helicopter rotation*/
	Ogre::Matrix3 rotateXMat;
	float angle = util::convertAngleToRadian(orientation.x);
	rotateXMat = util::RotationMatrixXYZ(Ogre::Vector3(angle, 0.f, 0.f));
	Ogre::Quaternion orientationQ;
	orientationQ.FromRotationMatrix(rotateXMat);

	/*load the mesh and material (original model & texture from http://www.turbosquid.com/FullPreview/Index.cfm/ID/863905) */
	auto helicopter = application->GetSceneManager()->createEntity("helicopter" + std::to_string(actorID),"helicopter.mesh");

	/*set the lighting*/
	helicopter->setCastShadows(false);

	/*initialise the helicopter node*/
	gameActorNode.reset(application->GetSceneManager()->getRootSceneNode()
		->createChildSceneNode(std::to_string(actorID) + "Helicopter "));
	gameActorNode->setScale(Ogre::Vector3(scale, scale, scale));
	gameActorNode->setOrientation(orientationQ);
	gameActorNode->setPosition(position);
	gameActorNode->attachObject(helicopter);
	gameActorNode->showBoundingBox(false);

	/*initialise the main rotor*/
	Ogre::Vector3 initialRotorPosition = Ogre::Vector3(-0.35f, 39.0f, -4.85f);
	mainRotor.reset(new Rotor(initialRotorPosition, orientation, scale, gameActorNode, "topRotor"));
	mainRotor->setUpActor(application);

	/*initialise the side rotor*/
	initialRotorPosition = Ogre::Vector3(8.0f, 43.0f, -110.5f);
	sideRotor.reset(new Rotor(initialRotorPosition, orientation, scale, gameActorNode, "aftRotor"));
	sideRotor->setUpActor(application);
}

/**************************************************************************************************************/

/*Handles the user input*/
void Helicopter::handleInput(OIS::Keyboard* keyboard)
{
	/*set the user commands to false*/
	up = down = left = right = forwards = backwards = rotateUp = rotateDown = rotateLeft = rotateRight = false;

	/*if W is pressed*/
	if (keyboard->isKeyDown(OIS::KC_W))
	{
		/*set the forward user command to be true*/
		forwards = true;
	}
	/*if S is pressed*/
	else if (keyboard->isKeyDown(OIS::KC_S))
	{
		/*set the backwards user command to be true*/
		backwards = true;
	}

	/*if D is pressed*/
	if (keyboard->isKeyDown(OIS::KC_D))
	{
		/*set the right user command to be true*/
		right = true;
	}
	/*if A pressed*/
	else if (keyboard->isKeyDown(OIS::KC_A))
	{
		/*set the left user command to be true*/
		left = true;
	}

	/*if Q is pressed*/
	if (keyboard->isKeyDown(OIS::KC_Q))
	{
		/*set the up user command to be true*/
		up = true;
	}
	/*if E pressed*/
	else if (keyboard->isKeyDown(OIS::KC_E))
	{
		/*set the down user command to be true*/
		down = true;
	}

	/*if Up is pressed*/
	if (keyboard->isKeyDown(OIS::KC_UP))
	{
		/*set the rotate up user command to be true*/
		rotateUp = true;
	}
	/*if Down is pressed*/
	else if (keyboard->isKeyDown(OIS::KC_DOWN))
	{
		/*set the rotate down user command to be true*/
		rotateDown = true;
	}

	/*if right is pressed*/
	if (keyboard->isKeyDown(OIS::KC_RIGHT))
	{
		/*set the rotate right user command to be true*/
		rotateRight = true;
	}
	/*if left pressed*/
	else if (keyboard->isKeyDown(OIS::KC_LEFT))
	{
		/*set the rotate left user command to be true*/
		rotateLeft = true;
	}
}

/**************************************************************************************************************/

/*Updates the Helicopter actor.*/
void Helicopter::updateActor(float dt)
{
	/*set the rotors speed*/
	mainRotor->setRotateSpeed(500.0f);
	sideRotor->setRotateSpeed(500.0f);

	/*update the helicopter speeds depending on the user commands*/
	updateSpeed();
	updateRotate();

	/*get the translate of the helicopter*/
	Ogre::Real translationX = speed.x * dt;
	Ogre::Real translationY = speed.y * dt;
	Ogre::Real translationZ = speed.z * dt;

	/*translate the helicopter against it local position*/
	gameActorNode->translate(translationX, translationY, translationZ, Ogre::Node::TS_LOCAL);

	/*store the new position*/
	position = gameActorNode->getPosition();

	/*create a rotation vector 3 from the speed*/
	Ogre::Vector3 radianRotation = Ogre::Vector3(util::convertAngleToRadian(rotateSpeed.x * dt), 
		util::convertAngleToRadian(rotateSpeed.y *dt), util::convertAngleToRadian(rotateSpeed.z * dt));

	/*get the rotation in the form of a Quaternion*/
	Ogre::Quaternion orientationQ = util::covertRotateToQuaternion(radianRotation);

	/*rotate the helicopter*/
	gameActorNode->rotate(orientationQ);

	/*create a rotation vector 3 from the speed*/
	lastRotation = Ogre::Vector3((rotateSpeed.x * dt), (rotateSpeed.y *dt), (rotateSpeed.z * dt));

	/*work out and store the x new orientation*/
	orientation.x = util::angleCheck(orientation.x, (rotateSpeed.x * dt));
	/*work out and store the y new orientation*/
	orientation.y = util::angleCheck(orientation.y, (rotateSpeed.y * dt));
	/*work out and store the z new orientation*/
	orientation.z = util::angleCheck(orientation.z, (rotateSpeed.z * dt));

	/*set the main rotor to spin*/
	mainRotor->setRotateAxis(Ogre::Vector3(0.0f,1.0f,0.0f));
	mainRotor->updateActor(dt);
	
	/*set the side rotor to spin*/
	sideRotor->setRotateAxis(Ogre::Vector3(1.0f,0.0f,0.0f));
	sideRotor->updateActor(dt);
}

/**************************************************************************************************************/

/*Updates the speeds of the helicopter using the user commands.*/
void Helicopter::updateSpeed()
{
	/*x axis*/
	if (left)
	{
		/*set the speed to cause the the helicopter to move left*/
		setXSpeed(100.0f);
	}
	else if (right)
	{
		/*set the speed to cause the the helicopter to move right*/
		setXSpeed(-100.0f);
	}
	else
	{
		/*set the speed to cause the the helicopter to stay still along the x axis*/
		setXSpeed(0.0f);
	}

	/*y axis*/
	if (up)
	{
		/*set the speed to cause the the helicopter to move up*/
		setYSpeed(100.0f);
	}
	else if (down)
	{
		/*set the speed to cause the the helicopter to move down*/
		setYSpeed(-100.0f);
	}
	else
	{
		/*set the speed to cause the the helicopter to stay still along the y axis*/
		setYSpeed(0.0f);
	}

	/*z axis*/
	if (forwards)
	{
		/*set the speed to cause the the helicopter to move forwards*/
		setZSpeed(100.0f);
	}
	else if (backwards)
	{
		/*set the speed to cause the the helicopter to move backwards*/
		setZSpeed(-100.0f);
	}
	else
	{
		/*set the speed to cause the the helicopter to stay still along the z axis*/
		setZSpeed(0.0f);
	}
}

/**************************************************************************************************************/

/*Updates the rotate speeds of the helicopter using the user commands.*/
void Helicopter::updateRotate()
{
	/*x axis*/
	if (rotateUp)
	{
		/*set the speed to cause the the helicopter to rotate down*/
		setXRotateSpeed(100.0f);
	}
	else if (rotateDown)
	{
		/*set the speed to cause the the helicopter to rotate up*/
		setXRotateSpeed(-100.0f);
	}
	else
	{
		/*set the speed to cause the the helicopter to stay still along the x axis*/
		setXRotateSpeed(0.0f);
	}

	/*y axis*/	
	if (rotateLeft)
	{
		/*set the speed to cause the the helicopter to rotate left*/
		setYRotateSpeed(100.0f);
	}
	else if (rotateRight)
	{
		/*set the speed to cause the the helicopter to rotate right*/
		setYRotateSpeed(-100.0f);
	}
	else
	{
		/*set the speed to cause the the helicopter to stay still along the y axis*/
		setYRotateSpeed(0.0f);
	}
}