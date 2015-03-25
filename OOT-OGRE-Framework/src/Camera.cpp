#include "stdafx.h"
#include "Camera.h"

/**************************************************************************************************************/

/*Constructs the Camera object.*/
Camera::Camera(std::shared_ptr<Ogre::SceneNode> sceneNode, std::shared_ptr<Ogre::MovableObject> camera, 
			   Ogre::Vector3 rotationOffset, Ogre::Vector3 positonOffset)
{
	/*initialise the variables*/
	this->sceneNode = sceneNode;
	this->camera = camera;
	this->rotationOffset = rotationOffset;
	this->positonOffset = positonOffset;
}

/**************************************************************************************************************/

/*Destructs the Camera object.*/
Camera::~Camera()
{
}

/**************************************************************************************************************/

/*Updates the Camera.*/
void Camera::update(float dt)
{
}