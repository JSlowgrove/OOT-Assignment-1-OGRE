#include "stdafx.h"
#include "Helicopter.h"

/**************************************************************************************************************/

/*Constructs the Helicopter object.*/
Helicopter::Helicopter(Ogre::Vector3 position, Ogre::Vector3 orientation, Ogre::Real scale) 
	: GameActor(position, orientation, scale)
{
	/*initialise the user commands to false*/
	up = down = left = right = forwards = backwards = false;
	mouseX = mouseY = 0;

	/*initialise the helicopter speeds*/
	maxSpeed = 1000.0f;
	targetSpeedPercent = Ogre::Vector3(0.0f, 0.0f, 0.0f);
	speed = maxSpeed * (targetSpeedPercent * 0.01f);

	/*initialise health*/
	health = 3;

	/*initialise the spawn and direction*/
	spawn = position;
	direction = orientation;
}

/**************************************************************************************************************/

/*Destructs the Helicopter object.*/
Helicopter::~Helicopter()
{
}

/**************************************************************************************************************/

/*Decrease the health of the Helicopter by 1.*/
void Helicopter::takeDamage()
{
	/*decrease the health*/
	health--;
}

/**************************************************************************************************************/

/*reset the helicopter*/
void Helicopter::resetHelicopter()
{
	/*reset the health, direction and position*/
	health = 3;
	gameActorNode->setPosition(spawn);
	gameActorNode->setOrientation(util::covertRotateToQuaternion(direction));
}

/**************************************************************************************************************/

/*Gets the health of the Helicopter.*/
int Helicopter::getHealth()
{
	/*return the health*/
	return health;
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
	auto helicopter = application->GetSceneManager()->createEntity("helicopter" + getActorID(),"helicopter.mesh");

	/*set the lighting*/
	helicopter->setCastShadows(false);

	/*initialise the helicopter node*/
	gameActorNode.reset(application->GetSceneManager()->getRootSceneNode()
		->createChildSceneNode("Helicopter " + getActorID() + " "));
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
void Helicopter::handleInput(OIS::Keyboard* keyboard, OIS::Mouse* mouse)
{
	/*set the user commands to false*/
	up = down = left = right = forwards = backwards = false;

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
	
	/*check if the mouse is off the screen on the x axis*/
	if (mouse->getMouseState().X.abs > mouse->getMouseState().width)
	{
		/*quit the function to not store the mouse position*/
		return;
	}

	/*check if the mouse is off the screen on the y axis*/
	if (mouse->getMouseState().Y.abs > mouse->getMouseState().height)
	{
		/*quit the function to not store the mouse position*/
		return;
	}

	/*store the mouse position*/
	mouseX = mouse->getMouseState().X.rel;
	mouseY = mouse->getMouseState().Y.rel;
}

/**************************************************************************************************************/

/*Updates the Helicopter actor.*/
void Helicopter::updateActor(float dt)
{
	/*update the rotors speed*/
	mainRotor->updateRotateSpeed();
	sideRotor->updateRotateSpeed();

	/*update the helicopter speeds depending on the user commands*/
	updateSpeed();
	updateMoveSpeed();

	/*get the translate of the helicopter*/
	Ogre::Real translationX = speed.x * dt;
	Ogre::Real translationY = speed.y * dt;
	Ogre::Real translationZ = speed.z * dt;

	/*translate the helicopter against it local position*/
	gameActorNode->translate(translationX, translationY, translationZ, Ogre::Node::TS_LOCAL);

	/*store the new position*/
	position = gameActorNode->getPosition();

	/*rotate the helicopter*/
	rotateHelicopter();

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
	/*set the target speed of both the rotors to 45%*/
	mainRotor->setTargetRotateSpeedPercent(45.0f);
	sideRotor->setTargetRotateSpeedPercent(25.0f);

	/*set the target speed to cause the the helicopter to stay still*/
	targetSpeedPercent = 0.0f;

	/*x axis*/
	if (left)
	{
		/*set the target speed to cause the the helicopter to move left*/
		targetSpeedPercent.x = 100.0f;

		/*set the target speed of the side rotor to 100%*/
		sideRotor->setTargetRotateSpeedPercent(100.0f);
	}
	else if (right)
	{
		/*set the target speed to cause the the helicopter to move right*/
		targetSpeedPercent.x = -100.0f;

		/*set the target speed of the side rotor to 100%*/
		sideRotor->setTargetRotateSpeedPercent(-100.0f);
	}

	/*y axis*/
	if (up)
	{
		/*set the target speed to cause the the helicopter to move up*/
		targetSpeedPercent.y = 100.0f;

		/*set the target speed of the main rotor to 100%*/
		mainRotor->setTargetRotateSpeedPercent(100.0f);
	}
	else if (down)
	{
		/*set the target speed to cause the the helicopter to move down*/
		targetSpeedPercent.y = -100.0f;

		/*set the target speed of the main rotor to 35%*/
		mainRotor->setTargetRotateSpeedPercent(35.0f);
	}

	/*z axis*/
	if (forwards)
	{
		/*set the target speed to cause the the helicopter to move forwards*/
		targetSpeedPercent.z = 100.0f;

		/*set the target speed of both the rotors to 100%*/
		mainRotor->setTargetRotateSpeedPercent(100.0f);
		sideRotor->setTargetRotateSpeedPercent(100.0f);
	}
	else if (backwards)
	{
		/*set the target speed to cause the the helicopter to move backwards*/
		targetSpeedPercent.z = -100.0f;

		/*set the target speed of both the rotors to 100%*/
		mainRotor->setTargetRotateSpeedPercent(100.0f);
		sideRotor->setTargetRotateSpeedPercent(-100.0f);
	}
}

/**************************************************************************************************************/

/*Updates the move speeds of the Helicopter.*/
void Helicopter::updateMoveSpeed()
{
	/*test if the speed is less than the target speed*/
	if (speed.x < maxSpeed * (targetSpeedPercent.x * 0.01f))
	{
		/*increase the speed*/
		speed.x += (0.01f * maxSpeed);
	}

	/*test if the speed is greater than the target speed*/
	if (speed.x > maxSpeed * (targetSpeedPercent.x * 0.01f))
	{
		/*decrease the speed*/
		speed.x -= (0.01f * maxSpeed);
	}

	/*test if the speed is less than the target speed*/
	if (speed.y < maxSpeed * (targetSpeedPercent.y * 0.01f))
	{
		/*increase the speed*/
		speed.y += (0.01f * maxSpeed);
	}

	/*test if the speed is greater than the target speed*/
	if (speed.y > maxSpeed * (targetSpeedPercent.y * 0.01f))
	{
		/*decrease the speed*/
		speed.y -= (0.01f * maxSpeed);
	}

	/*test if the speed is less than the target speed*/
	if (speed.z < maxSpeed * (targetSpeedPercent.z * 0.01f))
	{
		/*increase the speed*/
		speed.z += (0.01f * maxSpeed);
	}

	/*test if the speed is greater than the target speed*/
	if (speed.z > maxSpeed * (targetSpeedPercent.z * 0.01f))
	{
		/*decrease the speed*/
		speed.z -= (0.01f * maxSpeed);
	}
}

/**************************************************************************************************************/

/*Rotates the helicopter using the user commands*/
void Helicopter::rotateHelicopter()
{
	/*A magic number to slow down the rotation speed*/
	Ogre::Real slowDown = 0.0017f;

	/*increase the orientation as related to the mouse position*/
	orientation.x += mouseX;
	orientation.y += mouseY;

	/*convert the orientation into two quaternions*/
	Ogre::Quaternion newRotationX, newRotationY;
	newRotationX.FromAngleAxis((Ogre::Radian)(orientation.x * -slowDown), Ogre::Vector3::UNIT_Y);
	newRotationY.FromAngleAxis((Ogre::Radian)(orientation.y *  slowDown), Ogre::Vector3::UNIT_X);

	/*set the orientation of the helicopter*/
	gameActorNode->setOrientation(newRotationX * newRotationY);
}