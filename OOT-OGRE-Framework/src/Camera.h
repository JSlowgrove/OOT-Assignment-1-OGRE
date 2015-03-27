#pragma once

#include "stdafx.h"
#include <memory>
#include "myUtils.h"

/**
@brief A class for a Camera object.
@author Jamie Slowgrove
*/
class Camera
{
private:
	/**A pointer to the camera scene node.*/
	std::shared_ptr<Ogre::SceneNode> sceneNode;
	/**A pointer to the camera movable object.*/
	std::shared_ptr<Ogre::MovableObject> camera;
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
	*/
	Camera(std::shared_ptr<Ogre::SceneNode> sceneNode, std::shared_ptr<Ogre::MovableObject> camera, 
		Ogre::Vector3 rotationOffset, Ogre::Vector3 positonOffset);

	/**
	Destructs the Camera object.
	*/
	~Camera();

	/**
	Updates the Camera.
	@param float The delta time.
	*/
	void update(float dt);
};