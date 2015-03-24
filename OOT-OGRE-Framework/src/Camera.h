#pragma once

#include "stdafx.h"
#include <memory>
#include "myUtils.h"

/**
@brief A class for a Camera object.
*/
class Camera
{
private:
	/**A pointer to the camera scene node.*/
	std::shared_ptr<Ogre::SceneNode> sceneNode;
	/**A pointer to the camera movable object.*/
	std::shared_ptr<Ogre::MovableObject> camera;
	/**The Camera objects rotation.*/
	Ogre::Vector3 rotation;
	/**The Camera objects position.*/
	Ogre::Vector3 position;
	/**The Camera objects rotation offset.*/
	Ogre::Vector3 rotationOffset;
	/**The Camera objects position offset.*/
	Ogre::Vector3 positonOffset;

public:
	/**
	Constructs the Camera object.
	@param std::shared_ptr<Ogre::SceneNode> A pointer to the camera scene node.
	@param std::shared_ptr<Ogre::MovableObject> A pointer to the camera moveable object.
	@param Ogre::Vector3 The rotation offset of the Camera.
	@param Ogre::Vector3 The positon offset of the Camera.
	@param Ogre::Vector3 The positon of the Helicopter.
	*/
	Camera(std::shared_ptr<Ogre::SceneNode> sceneNode, std::shared_ptr<Ogre::MovableObject> camera, 
		Ogre::Vector3 rotationOffset, Ogre::Vector3 positonOffset, 
		Ogre::Vector3 helicopterPosition, Ogre::Vector3 helicopterRotation);

	/**
	Destructs the Camera object.
	*/
	~Camera();

	/**
	Updates the Camera.
	*/
	void update(Ogre::Vector3 helicopterPosition, Ogre::Vector3 helicopterRotation);

	/**
	Setter # Sets the rotation of the Camera.
	@param Ogre::Vector3 The new rotation of the Camera.
	*/
	void setRotation(Ogre::Vector3 rotation);
};