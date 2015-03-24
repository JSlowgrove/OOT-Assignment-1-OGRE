#pragma once

#include "stdafx.h"
#include <iostream>
#include <memory>
#include <string>
#include "OgreApplication.h"
#include "MyUtils.h"

/**
@brief A class for a GameActor object.
*/
class GameActor
{
private:

protected:
	/**A pointer to the GameActor node.*/
	std::shared_ptr<Ogre::SceneNode> gameActorNode;
	/**The position of the GameActor.*/
	Ogre::Vector3 position;
	/**The orientation of the GameActor.*/
	Ogre::Vector3 orientation;
	/**The scale of the GameActor*/
	Ogre::Real scale;
	/**A static member variable for the GameActor id generation*/
	static unsigned int actorIDGenerator;
	/**A the GameActor id*/
	unsigned int actorID;

public:
	/**
	Constructs the GameActor object.
	@param Ogre::Vector3 The position of the GameActor.
	@param Ogre::Vector3 The orientation of the GameActor.
	@param Ogre::Real The scale of the GameActor.
	*/
	GameActor(Ogre::Vector3 position, Ogre::Vector3 orientation, Ogre::Real scale);

	/**
	A virtual destructor for the GameActor object.
	*/
	virtual ~GameActor();

	/**
	A pure virtual function for setting up the GameActor.
	@param OgreApplication A pointer to the application.
	*/
	virtual void setUpActor(OgreApplication* application) = 0;

	/**
	A pure virtual function for updating the GameActor.
	@param float The delta time.
	*/
	virtual void updateActor(float dt) = 0;

	/**
	Getter # Gets the actorID of the GameActor.
	@returns std::string The actorID of the GameActor.
	*/
	std::string getActorID();

	/**
	Getter # Gets the position of the GameActor.
	@returns Ogre::Vector3 The position of the GameActor.
	*/
	Ogre::Vector3 getPosition();

	/**
	Setter # Sets the position of the GameActor.
	@param Ogre::Vector3 The new position of the GameActor.
	*/
	void setPosition(Ogre::Vector3 position);

	/**
	Setter # Sets the x position of the GameActor.
	@param float The new x position of the GameActor.
	*/
	void setX(float x);

	/**
	Setter # Sets the y position of the GameActor.
	@param float The new y position of the GameActor.
	*/
	void setY(float y);

	/**
	Setter # Sets the z position of the GameActor.
	@param float The new z position of the GameActor.
	*/
	void setZ(float z);

	/**
	Getter # Gets the orientation of the GameActor.
	@returns Ogre::Vector3 The orientation of the GameActor.
	*/
	Ogre::Vector3 getOrientation();

	/**
	Setter # Sets the orientation of the GameActor.
	@param Ogre::Vector3 The new orientation of the GameActor.
	*/
	void setOrientation(Ogre::Vector3 orientation);
	
	/**
	Setter # Sets the x orientation of the GameActor.
	@param float The new x orientation of the GameActor.
	*/
	void setXOrientation(float xOrientation);

	/**
	Setter # Sets the y orientation of the GameActor.
	@param float The new y orientation of the GameActor.
	*/
	void setYOrientation(float yOrientation);

	/**
	Setter # Sets the z orientation of the GameActor.
	@param float The new z orientation of the GameActor.
	*/
	void setZOrientation(float zOrientation);

	/**
	Getter # Gets the scale of the GameActor.
	@returns Ogre::Real The scale of the GameActor.
	*/
	Ogre::Real getScale();

	/**
	Setter # Sets the scale of the GameActor.
	@param Ogre::Real The new scale of the GameActor.
	*/
	void setScale(Ogre::Real scale);	

	/**
	Changes the position of the GameActor.
	@param Ogre::Vector3 The new position of the GameActor.
	*/
	void changePosition(Ogre::Vector3 position);
};