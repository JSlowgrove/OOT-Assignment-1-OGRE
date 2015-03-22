#include "stdafx.h"
#include "Helicopter.h"

/**************************************************************************************************************/

/*Constructs the Helicopter object.*/
Helicopter::Helicopter(Ogre::Vector3 position, Ogre::Vector3 orientation, Ogre::Real scale) 
	: GameActor(position, orientation, scale)
{
	/*initialise the user commands to false*/
	up = down = left = right = rotateUp = rotateDown = rotateLeft = rotateRight = false;
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

/*Sets the actor for the Helicopter.*/
void Helicopter::setUpActor(OgreApplication* application)
{
	/*initialise helicopter rotation*/
	Ogre::Matrix3 rotateXMat;
	float angle = orientation.x * 3.141596f / 180.0f;
	rotateXMat = util::RotationMatrixXYZ(Ogre::Vector3(angle, 0.f, 0.f));
	Ogre::Quaternion orientationQ;
	orientationQ.FromRotationMatrix(rotateXMat);

	/*load the helicopter green texture*/
	Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create("GreenTexture", 
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	Ogre::Technique* firstTechnique = material->getTechnique(0);
	Ogre::Pass* firstPass = firstTechnique->getPass(0);
	Ogre::TextureUnitState* textureUnit = firstPass->createTextureUnitState();
	textureUnit->setTextureName("Green.png", Ogre::TEX_TYPE_2D);
	textureUnit->setTextureCoordSet(0);
	const Ogre::String& materialName = "GreenTexture";

	/*load the mesh*/
	auto helicopter = application->GetSceneManager()->createEntity("helicopter.mesh");

	/*set the lighting*/
	helicopter->setCastShadows(false);

	/*set the materials*/
	helicopter->setMaterialName(materialName);

	/*initialise the helicopter node*/
	helicopterNode.reset(application->GetSceneManager()->getRootSceneNode()
		->createChildSceneNode(std::to_string(actorID) + "Helicopter "));
	helicopterNode->setScale(Ogre::Vector3(scale, scale, scale));
	helicopterNode->setOrientation(orientationQ);
	helicopterNode->setPosition(position);
	helicopterNode->attachObject(helicopter);
	helicopterNode->showBoundingBox(false);

	/*initialise the main rotor*/
	Ogre::Vector3 initialRotorPosition = Ogre::Vector3(0.0f, 0.0f,-0.045f);
	mainRotor.reset(new Rotor(initialRotorPosition, orientation, scale, helicopterNode, "topRotor"));
	mainRotor->setUpActor(application);

	/*initialise the side rotor*/
	initialRotorPosition = Ogre::Vector3(-0.015f, -0.11f, -0.004f);
	sideRotor.reset(new Rotor(initialRotorPosition, orientation, scale, helicopterNode, "aftRotor"));
	sideRotor->setUpActor(application);
}

/**************************************************************************************************************/

/*Handles the user input*/
void Helicopter::handleInput(OIS::Keyboard* keyboard)
{
}

/**************************************************************************************************************/

/*Updates the Helicopter actor.*/
void Helicopter::updateActor(float dt)
{
	/*set the helicopter speed*/
	speed = Ogre::Vector3(10.0f, 10.0f, 10.0f);

	/*set the rotors speed*/
	mainRotor->setRotateSpeed(10.0f);
	sideRotor->setRotateSpeed(10.0f);

	/*update the helicopter position*/
	float updatedX = position.x + (speed.x * dt);
	float updatedY = position.y + (speed.y * dt);
	float updatedZ = position.z + (speed.z * dt);
	position = Ogre::Vector3(updatedX, updatedY, updatedZ); 
	helicopterNode->setPosition(position);

	/*set the main rotor to spin*/
	mainRotor->setRotateAxis(Ogre::Vector3(0.0f,0.0f,1.0f));
	mainRotor->updateActor(dt);
	
	/*set the side rotor to spin*/
	sideRotor->setRotateAxis(Ogre::Vector3(1.0f,0.0f,0.0f));
	sideRotor->updateActor(dt);
}