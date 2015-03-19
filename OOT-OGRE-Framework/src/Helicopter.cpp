#include "Helicopter.h"

/**************************************************************************************************************/

/*Constructs the Helicopter object.*/
Helicopter::Helicopter(int iD)
{
	/*set the value of ID*/
	this->iD = iD;
}

/**************************************************************************************************************/

/*Destructs the Helicopter object.*/
Helicopter::~Helicopter()
{

}

/**************************************************************************************************************/

/*Sets the position of the Helicopter.*/
void Helicopter::setPosition(Ogre::Vector3 position)
{
	/*set the position*/
	this->position = position;
}

/**************************************************************************************************************/

/*Sets the x position of the Helicopter.*/
void Helicopter::setX(float x)
{
	/*set the x position*/
	position = Ogre::Vector3(x, position.y, position.z);
}

/**************************************************************************************************************/

/*Sets the y position of the Helicopter.*/
void Helicopter::setY(float y)
{
	/*set the y position*/
	position = Ogre::Vector3(position.x, y, position.z);
}

/**************************************************************************************************************/

/*Sets the z position of the Helicopter.*/
void Helicopter::setZ(float z)
{
	/*set the x position*/
	position = Ogre::Vector3(position.x, position.y, z);
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

/*Sets the angle of the Helicopter.*/
void Helicopter::setAngle(Ogre::Vector3 angle)
{
	/*set the angle*/
	this->angle = angle;
}

/**************************************************************************************************************/

/*Sets the x angle of the Helicopter.*/
void Helicopter::setXAngle(float xAngle)
{
	/*set the x angle*/
	angle = Ogre::Vector3(xAngle, angle.y, angle.z);
}

/**************************************************************************************************************/

/*Sets the y angle of the Helicopter.*/
void Helicopter::setYAngle(float yAngle)
{
	/*set the y angle*/
	angle = Ogre::Vector3(angle.x, yAngle, angle.z);
}

/**************************************************************************************************************/

/*Sets the z angle of the Helicopter.*/
void Helicopter::setZAngle(float zAngle)
{
	/*set the x angle*/
	angle = Ogre::Vector3(angle.x, angle.y, zAngle);
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
void Helicopter::setActor(OgreApplication* application)
{
	/*initialise variables*/
	Ogre::Real scale = 200.0f;
	Ogre::Vector3 initialPosition;

	/*initialise rotation*/
	Ogre::Matrix3 rotateXMat;
	float angle = 90.0f *3.141596f / 180.0f;
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
	initialPosition = Ogre::Vector3(0.0f, 10.0f, 0.0f);
	helicopterNode.reset(application->GetSceneManager()->getRootSceneNode()->createChildSceneNode("Helicopter " + std::to_string(iD) + " "));
	helicopterNode->setScale(Ogre::Vector3(scale, scale, scale));
	helicopterNode->setOrientation(orientationQ);
	helicopterNode->setPosition(initialPosition);
	helicopterNode->attachObject(helicopter);
	helicopterNode->showBoundingBox(false);

	/*initialise the main rotor node*/
	initialPosition = Ogre::Vector3(0.0f, 0.0f,-0.045f);
	mainRotorNode.reset(helicopterNode->createChildSceneNode("mainRotor"));
	mainRotorNode->setPosition(initialPosition);
	mainRotorNode->attachObject(mainRotor);
	mainRotorNode->showBoundingBox(false);

	/*initialise the side rotor node*/
	initialPosition = Ogre::Vector3(-0.015f, -0.11f, -0.004f);
	sideRotorNode.reset(helicopterNode->createChildSceneNode("sideRotor"));
	sideRotorNode->setPosition(initialPosition);
	sideRotorNode->attachObject(sideRotor);
	sideRotorNode->showBoundingBox(false);
}

/**************************************************************************************************************/

/*Updates the Helicopter actor.*/
void Helicopter::updateActor(float dt)
{
	
}