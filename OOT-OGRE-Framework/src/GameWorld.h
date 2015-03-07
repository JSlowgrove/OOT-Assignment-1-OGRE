//
//  GameWorld.h
// This class is the interface class between your game to Ogre.
// The access point is the pointer to OgreApplication class 
//  OOT Tutorial Ogre Framework Demo.
//  Created by Wen Tang on 19/01/15.
//

#pragma once
#ifndef _GAME_WORLD_H_
#define _GAME_WORLD_H_

#include "stdafx.h"
#include <iostream>
#include "OgreApplication.h"

class GameWorld
{
private:
										
	void UpdateGame(float dt);
	void UpdateScene(Ogre::Vector3 &pos, Ogre::Quaternion &q);
	Ogre::Matrix3 rotateX(float angle);
	
	std::shared_ptr<Ogre::SceneNode> cubeNode;
	std::shared_ptr<Ogre::SceneNode> greenCubeNode;
	std::shared_ptr<Ogre::SceneNode> atheneNode;
	Ogre::Vector3 atheneVelocity;
	Ogre::Vector3 athenePosition;
	Ogre::Vector3 initial_position;
	OgreApplication* application;
	
public:

	GameWorld(OgreApplication* application_);
	~GameWorld();
					
	void Run();
	void InitilaiseScene();
	void CreateEnviroment();
	void CreateLights();
	void CreateEntities();
	void Update(float dt);
	void Reset();

};

#endif // End of _GAME_WORLD_H_
