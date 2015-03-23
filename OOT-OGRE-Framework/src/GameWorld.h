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
#include "Helicopter.h"
#include "TerrainManager.h"
#include "Camera.h"

class GameWorld : public OgreBites::SdkTrayListener
{
private:
										
	void UpdateGame(float dt);
	void UpdateScene(Ogre::Vector3 &pos, Ogre::Quaternion &q);
	Ogre::Matrix3 rotateX(float angle);

	std::shared_ptr<Camera> camera;
	std::shared_ptr<Helicopter> helicopter;
	std::shared_ptr<TerrainManager> terrain;

	OgreBites::ParamsPanel* paramPanel;
	void CreateGUI();

	// on screen panel 
	shared_ptr<OgreBites::SdkTrayManager> trayManager; 
	Ogre::FrameEvent frameEvent; 
	OgreBites::InputContext inputContext;
	
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
	void Update(float dt, OIS::Keyboard* keyboard);
	void Reset();

};

#endif // End of _GAME_WORLD_H_
