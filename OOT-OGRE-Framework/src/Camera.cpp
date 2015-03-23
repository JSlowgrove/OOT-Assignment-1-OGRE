#include "stdafx.h"
#include "Camera.h"

/**************************************************************************************************************/

/*Constructs the Camera object.*/
Camera::Camera(std::shared_ptr<Ogre::SceneNode> sceneNode, std::shared_ptr<Ogre::MovableObject> camera, 
			   Ogre::Vector3 rotationOffset, Ogre::Vector3 positonOffset, Ogre::Vector3 helicopterPosition)
{
	/*initialise the variables*/
	this->sceneNode = sceneNode;
	this->camera = camera;
	rotation = this->rotationOffset = rotationOffset;
	this->positonOffset = positonOffset;
	position = helicopterPosition + positonOffset;
}

/**************************************************************************************************************/

/*Destructs the Camera object.*/
Camera::~Camera()
{
}

/**************************************************************************************************************/

/*Updates the Camera.*/
void Camera::update(Ogre::Vector3 helicopterPosition, Ogre::Vector3 helicopterRotation)
{
	/*store the new position of the camera*/
	position = helicopterPosition + positonOffset;
	/*set the new position of the camera*/
	sceneNode->setPosition(position);
}

/**************************************************************************************************************/

/*Sets the rotation of the Camera.*/
void Camera::setRotation(Ogre::Vector3 rotation)
{
	/*store the new value of the rotation*/
	this->rotation = rotation;
}


/*mouse stuff*/
/*if (mouse->getMouseState().X.abs > mouse->getMouseState().width)
		return;

	if (mouse->getMouseState().Y.abs > mouse->getMouseState().height)
		return;

	const int mouseX = mouse->getMouseState().X.rel;
	const int mouseY = mouse->getMouseState().Y.rel;

	this->rotation.x += mouseX;
	this->rotation.y += mouseY;

	Ogre::Quaternion newRotationX, newRotationY;
	newRotationX.FromAngleAxis((Ogre::Radian)(this->rotation.x * -0.0017f), Ogre::Vector3::UNIT_Y);
	newRotationY.FromAngleAxis((Ogre::Radian)(this->rotation.y *  0.0017f), Ogre::Vector3::UNIT_X);*/