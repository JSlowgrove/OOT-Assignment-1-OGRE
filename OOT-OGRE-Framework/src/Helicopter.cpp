#include "Helicopter.h"

/**************************************************************************************************************/

/*Constructs the Helicopter object.*/
Helicopter::Helicopter(Ogre::Vector3 position, Ogre::Vector3 orientation, Ogre::Real scale) 
	: GameActor(position, orientation, scale)
{
}

/**************************************************************************************************************/

/*Destructs the Helicopter object.*/
Helicopter::~Helicopter()
{
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

/*Sets the rotation speed of the main rotor.*/
void Helicopter::setMainRotorRotateSpeed(float mainRotorRotateSpeed)
{
	/*set the rotor speed*/
	this->mainRotorRotateSpeed = mainRotorRotateSpeed;
}

/**************************************************************************************************************/

/*Sets the rotation speed of the side rotor.*/
void Helicopter::setSideRotorRotateSpeed(float sideRotorRotateSpeed)
{
	/*set the rotor speed*/
	this->sideRotorRotateSpeed = sideRotorRotateSpeed;
}

/**************************************************************************************************************/

/*Sets the actor for the Helicopter.*/
void Helicopter::setUpActor(OgreApplication* application)
{
	/*initialise variables*/
	mainRotorRotateSpeed = 0.0f;
	sideRotorRotateSpeed = 0.0f;

	/*initialise helicopter rotation*/
	Ogre::Matrix3 rotateXMat;
	float angle = orientation.x * 3.141596f / 180.0f;
	rotateXMat = util::RotationMatrixXYZ(Ogre::Vector3(angle, 0.f, 0.f));
	Ogre::Quaternion orientationQ;
	orientationQ.FromRotationMatrix(rotateXMat);

	/*load the helicopter green texture*/
	Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create("GreenTexture", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	Ogre::Technique* firstTechnique = material->getTechnique(0);
	Ogre::Pass* firstPass = firstTechnique->getPass(0);
	Ogre::TextureUnitState* textureUnit = firstPass->createTextureUnitState();
	textureUnit->setTextureName("Green.png", Ogre::TEX_TYPE_2D);
	textureUnit->setTextureCoordSet(0);
	const Ogre::String& materialName = "GreenTexture";

	/*load the meshes*/
	auto helicopter = application->GetSceneManager()->createEntity("helicopter.mesh");
	auto mainRotor = application->GetSceneManager()->createEntity("topRotor.mesh");
	auto sideRotor = application->GetSceneManager()->createEntity("aftRotor.mesh");

	/*set the lighting*/
	helicopter->setCastShadows(false);
	mainRotor->setCastShadows(false);
	sideRotor->setCastShadows(false);

	/*set the materials*/
	helicopter->setMaterialName(materialName);
	mainRotor->setMaterialName(materialName);
	sideRotor->setMaterialName(materialName);

	/*initialise the helicopter node*/
	helicopterNode.reset(application->GetSceneManager()->getRootSceneNode()->createChildSceneNode(std::to_string(actorID) + "Helicopter "));
	helicopterNode->setScale(Ogre::Vector3(scale, scale, scale));
	helicopterNode->setOrientation(orientationQ);
	helicopterNode->setPosition(position);
	helicopterNode->attachObject(helicopter);
	helicopterNode->showBoundingBox(false);

	/*initialise the main rotor node*/
	Ogre::Vector3 initialRotorPosition = Ogre::Vector3(0.0f, 0.0f,-0.045f);
	mainRotorNode.reset(helicopterNode->createChildSceneNode("mainRotor"));
	mainRotorNode->setPosition(initialRotorPosition);
	mainRotorNode->attachObject(mainRotor);
	mainRotorNode->showBoundingBox(false);

	/*initialise the side rotor node*/
	initialRotorPosition = Ogre::Vector3(-0.015f, -0.11f, -0.004f);
	sideRotorNode.reset(helicopterNode->createChildSceneNode("sideRotor"));
	sideRotorNode->setPosition(initialRotorPosition);
	sideRotorNode->attachObject(sideRotor);
	sideRotorNode->showBoundingBox(false);
}

/**************************************************************************************************************/

/*Updates the Helicopter actor.*/
void Helicopter::updateActor(float dt, OIS::Keyboard* keyboard)
{
	/*set the helicopter speed*/
	speed = Ogre::Vector3(10.0f, 10.0f, 10.0f);
	/*set the rotors speed*/
	mainRotorRotateSpeed = sideRotorRotateSpeed = 10.0f;

	/*update the helicopter position*/
	float updatedX = position.x + (speed.x * dt);
	float updatedY = position.y + (speed.y * dt);
	float updatedZ = position.z + (speed.z * dt);
	position = Ogre::Vector3(updatedX, updatedY, updatedZ); 
	helicopterNode->setPosition(position);
	
	/*set the side rotor to spin*/
	Ogre::Matrix3 rotateXMat;
	float rotateAngle = sideRotorRotateSpeed * 3.141596f / 180.0f;
	rotateXMat = util::RotationMatrixXYZ(Ogre::Vector3(rotateAngle, 0.0f, 0.0f));
	Ogre::Quaternion orientationQ;
	orientationQ.FromRotationMatrix(rotateXMat);
	sideRotorNode->rotate(orientationQ);

	/*set the main rotor to spin*/
	rotateAngle = mainRotorRotateSpeed * 3.141596f / 180.0f;
	rotateXMat = util::RotationMatrixXYZ(Ogre::Vector3(0.0f, 0.0f, rotateAngle));
	orientationQ.FromRotationMatrix(rotateXMat);
	mainRotorNode->rotate(orientationQ);
}