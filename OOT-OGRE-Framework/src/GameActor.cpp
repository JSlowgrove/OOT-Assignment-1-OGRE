#include "stdafx.h"
#include "GameActor.h"

/*
The game actor class contains a number of protected attributes that are inherited by its children. 
These all contain getters and setter, depending on whether the data needs to be accessed externally. 
The game actor class also contains some pure virtual functions, for dealing with setting up and 
updating the class. These are overwritten in its children classes.
*/

/**************************************************************************************************************/

/*initialise the actor id generator static variable*/
unsigned int GameActor::actorIDGenerator = 0;

/**************************************************************************************************************/

/*Constructs the game actor object.*/
GameActor::GameActor(Ogre::Vector3 position, Ogre::Vector3 orientation, Ogre::Real scale)
{
	/*set the position of the game actor*/
	this->position = position;
	/*set the orientation of the game actor*/
	this->orientation = orientation;
	/*set the scale of the game actor*/
	this->scale = scale;
	/*set the actor id*/
	actorID = actorIDGenerator;
	/*increase the actor id generator*/
	actorIDGenerator++;
}

/**************************************************************************************************************/

/*Destructs the game actor object.*/
GameActor::~GameActor()
{
}

/**************************************************************************************************************/

/*Gets the node of the game actor.*/
std::shared_ptr<Ogre::SceneNode> GameActor::getActorNode()
{
	/*return the actor node*/
	return gameActorNode;
}

/**************************************************************************************************************/

/*Gets the actorID of the game actor.*/
std::string GameActor::getActorID()
{
	/*return the actorID as an std::string*/
	return std::to_string(actorID);
}

/**************************************************************************************************************/

/*Gets the position of the game actor.*/
Ogre::Vector3 GameActor::getPosition()
{
	/*return the position*/
	return position;
}

/**************************************************************************************************************/

/*Sets the position of the game actor.*/
void GameActor::setPosition(Ogre::Vector3 position)
{
	/*set the position*/
	this->position = position;
}

/**************************************************************************************************************/

/*Sets the x position of the game actor.*/
void GameActor::setX(float x)
{
	/*set the x position*/
	position = Ogre::Vector3(x, position.y, position.z);
}

/**************************************************************************************************************/

/*Sets the y position of the game actor.*/
void GameActor::setY(float y)
{
	/*set the y position*/
	position = Ogre::Vector3(position.x, y, position.z);
}

/**************************************************************************************************************/

/*Sets the z position of the game actor.*/
void GameActor::setZ(float z)
{
	/*set the x position*/
	position = Ogre::Vector3(position.x, position.y, z);
}

/**************************************************************************************************************/

/*Gets the orientation of the game actor.*/
Ogre::Vector3 GameActor::getOrientation()
{
	/*return the orientation*/
	return orientation;
}

/**************************************************************************************************************/

/*Sets the orientation of the game actor.*/
void GameActor::setOrientation(Ogre::Vector3 orientation)
{
	/*set the orientation*/
	this->orientation = orientation;
}

/**************************************************************************************************************/

/*Sets the x orientation of the game actor.*/
void GameActor::setXOrientation(float xOrientation)
{
	/*set the x orientation*/
	orientation = Ogre::Vector3(xOrientation, orientation.y, orientation.z);
}

/**************************************************************************************************************/

/*Sets the y orientation of the game actor.*/
void GameActor::setYOrientation(float yOrientation)
{
	/*set the y orientation*/
	orientation = Ogre::Vector3(orientation.x, yOrientation, orientation.z);
}

/**************************************************************************************************************/

/*Sets the z orientation of the game actor.*/
void GameActor::setZOrientation(float zOrientation)
{
	/*set the x orientation*/
	orientation = Ogre::Vector3(orientation.x, orientation.y, zOrientation);
}

/**************************************************************************************************************/

/*Gets the scale of the game actor.*/
Ogre::Real GameActor::getScale()
{
	/*return the scale*/
	return scale;
}

/**************************************************************************************************************/

/*Sets the scale of the game actor.*/
void GameActor::setScale(Ogre::Real scale)
{
	/*set the scale*/
	this->scale = scale;
}

/**************************************************************************************************************/

/*changes the position of the GameActor.*/
void GameActor::changePosition(Ogre::Vector3 position)
{
	/*set the position variable*/
	setPosition(position);

	/*set the position*/
	gameActorNode->setPosition(position);
}

