//
//  GameWorld.cpp
//  OOT Tutorial Ogre Framework Demo.
//  Created by Wen Tang on 19/01/15.
//
#include "stdafx.h"
#include "GameWorld.h"

#include <string>
#include <iostream>
#include <sstream>

#define STEP_LENGTH 0.03

GameWorld::GameWorld(OgreApplication* application_) 
{
	application = application_;
	initial_position = Ogre::Vector3(0.0f, 0.0f, 0.0f); 
	trayManager = nullptr; 
	frameEvent= Ogre::FrameEvent();
}


GameWorld::~GameWorld()
{
}

void GameWorld::InitilaiseScene()
{
	CreateEnviroment();
	CreateLights();
	CreateEntities();
	CreateGUI();
}

void GameWorld::CreateEntities()
{
	/*initialise a helicopter*/
	helicopter.reset(new Helicopter(Ogre::Vector3(200.0f, 600.0f, 1800.0f), Ogre::Vector3(0.0f, 0.0f, 0.0f), 1.0f));
	helicopter->setUpActor(application);

	/*initialise a turret*/
	turret.reset(new Turret(Ogre::Vector3(224.30f, 443.20f, 1985.0f), Ogre::Vector3(0.0f, 0.0f, 0.0f), 10.0f));
	turret->setUpActor(application);
}

// Create a ogre world environment with a predefined geometry and a texture
void GameWorld::CreateEnviroment()
{
	/*initialise the terrain*/
	terrain.reset(new TerrainManager());
	terrain->Create(application->GetSceneManager());
	terrain->Loaded();

	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 100);
	application->GetSceneManager()->setSkyDome(true, "Examples/CloudySky", 10, 8, 100);
	
}

//Create light in the scene
void GameWorld::CreateLights()
{
	
	// create a spot light
	Ogre::String tempName = "SpotLight";
    Ogre::Light* spotLight = application->GetSceneManager()->createLight(tempName);
	spotLight->setType(Ogre::Light::LT_POINT);

	//Set light colour 
	spotLight->setDiffuseColour(0.8f, 0.8f, 0.8f); 
	spotLight->setSpecularColour(0.5f, 0.5f, 0.5f);
	//set the spot light corn beam width
	spotLight->setSpotlightRange(Ogre::Degree(20), Ogre::Degree(50));

	//Create a childSceneNode of the RootSceneNode
	//Attach the light to it
	Ogre::SceneNode* lightNode =  application->GetSceneManager()->getRootSceneNode()->createChildSceneNode(tempName.append("Node"));
	lightNode->attachObject(spotLight);
	lightNode->setDirection(1.0f, 1.0f, 0.0f);
	lightNode->setPosition(Ogre::Vector3(80.0, 80.0, 0.0));

	Ogre::ColourValue ambientColour(0.2f, 0.2f, 0.2f, 1.0f);
	application->GetSceneManager()->setAmbientLight(ambientColour);

}

void GameWorld::Run()
{
	//Create the game world
	InitilaiseScene();

	// Create a camera
	Ogre::String cameraName = "MainCamera";
	Ogre::Vector3 cameraOffset = Ogre::Vector3(0.0f, 80.0f, -180.0f);
	Ogre::Vector3 cameraOffsetRotation = Ogre::Vector3(0.0f, 0.0f, 0.0f);
	auto cameraNode = application->CreateCamera(cameraName);
	cameraNode->setPosition(helicopter->getPosition() + cameraOffset);
	static_cast<Ogre::Camera*>(cameraNode->getAttachedObject("MainCamera"))
		->lookAt(helicopter->getPosition() + Ogre::Vector3(0.0f, 40.0f, 0.0f));
	shared_ptr<Ogre::MovableObject> cameraObject;
	cameraObject.reset(cameraNode->getAttachedObject("MainCamera"));
	camera.reset(new Camera(cameraNode, cameraObject, cameraOffsetRotation, 
		cameraOffset, helicopter->getPosition(), helicopter->getOrientation()));
	camera->setRotation(cameraOffsetRotation);

	//Create input device listeners 
	application->CreateIOS();
	auto keyboard = application->GetKeyboard();
	auto mouse = application->GetMouse();

	// Create Timer
	auto timer = application->CreateTimer();
	timer->reset();
    unsigned long lastTime = timer->getMilliseconds();
	unsigned long deltaTime = 0;
	float deltaTime_s = 0.0f;
    application->GetOgreWrapper().GetRoot()->clearEventTimes();
    double timeToUpdate = 0.0;
    unsigned int index = 0;
    float elapsedTime = 0.0f;

	//Game loop
	while (!application->GetOgreWrapper().GetWindow()->isClosed())
	{
		//display the frame stats
		trayManager->showFrameStats((OgreBites::TL_BOTTOMLEFT));

		//Update helicopter stats
		char buffer[256];
		Ogre::SceneNode *helicopterNode = application->GetSceneManager()->getSceneNode(helicopter->getActorID() + "Helicopter ");
		Ogre::Vector3 vValue = helicopter->getPosition();
		sprintf_s(buffer, 256, "%4.2f %4.2f %4.2f", vValue.x, vValue.y, vValue.z);
		paramPanel->setParamValue(0, buffer);
		vValue = helicopter->getOrientation();
		sprintf_s(buffer, 256, "%4.2f %4.2f %4.2f", vValue.x, vValue.y, vValue.z);
		paramPanel->setParamValue(1, buffer);

		//Evaluate the current time and the time elapsed since last frame 
		//Prepare the next iteration. 	
		unsigned long currentTime = timer->getMilliseconds();
		deltaTime = currentTime - lastTime;
		if(deltaTime == 0)  continue;

		lastTime = currentTime;
		deltaTime_s = 0.001f * float(deltaTime);

		keyboard->capture();
		mouse->capture();

		float coeff = 200.0f * deltaTime_s;
		Ogre::Vector3 translation(Ogre::Vector3::ZERO);

		if (keyboard->isKeyDown(OIS::KC_ESCAPE))
		{
			break;
		}
		else if (keyboard->isKeyDown(OIS::KC_V)){
			auto camera = static_cast<Ogre::Camera*>(cameraNode->getAttachedObject("MainCamera"));
			camera->setPolygonMode(Ogre::PM_WIREFRAME);
		}
		else if (keyboard->isKeyDown(OIS::KC_B))
		{
			auto camera = static_cast<Ogre::Camera*>(cameraNode->getAttachedObject("MainCamera"));
			camera->setPolygonMode(Ogre::PM_POINTS);
		}
		else if (keyboard->isKeyDown(OIS::KC_N))
		{
			auto camera = static_cast<Ogre::Camera*>(cameraNode->getAttachedObject("MainCamera"));
			camera->setPolygonMode(Ogre::PM_SOLID);
		}
		if (keyboard->isKeyDown(OIS::KC_R))
		{
			Reset();
		}

		//Update Ogre
		frameEvent.timeSinceLastFrame = deltaTime;
		trayManager->frameRenderingQueued(frameEvent);
		
		const OIS::MouseState& mouseState = mouse->getMouseState();

		elapsedTime += deltaTime;
		if (elapsedTime > 100)
		{
			// do something
			elapsedTime = 0;
		}

		timeToUpdate += deltaTime_s;
		unsigned int numOfUpdates = 0;

		while (timeToUpdate > STEP_LENGTH && numOfUpdates < 60)
		{
			timeToUpdate -= STEP_LENGTH;
			Update(deltaTime_s, dynamic_cast<OIS::Keyboard*>(keyboard.get()));

			numOfUpdates++;
		}
		
		// Update window false
		bool updateWin = false;
		bool verticalSynchro = true;
		application->Run(updateWin, verticalSynchro);

		Ogre::WindowEventUtilities::messagePump();
	}

	application->CleanUp();
 
}

void GameWorld::Reset()
{

}

void GameWorld::UpdateGame(float dt)
{
	// Implement ...... 

}

void GameWorld::UpdateScene(Ogre::Vector3 &pos, Ogre::Quaternion &q )
{
	// show updated position in Ogre
}

void GameWorld::Update(float dt, OIS::Keyboard* keyboard)
{
	UpdateGame(dt);

	helicopter->handleInput(keyboard);
	helicopter->updateActor(dt);
	camera->update(helicopter->getPosition(), helicopter->getLastRotation());
}

//a function to rotate an object around the x axis
Ogre::Matrix3 GameWorld::rotateX(float angle) 
{ 
	Ogre::Matrix3 matX, rotateY, rotateZ; 
	matX = Ogre::Matrix3( 
		1.0, 0.0, 0.0, 
		0.0, std::cos(angle), -std::sin(angle),
		0.0, std::sin(angle), std::cos(angle) 
		);
	return matX; 
}

void GameWorld::CreateGUI()
{
	OgreBites::InputContext inputContext;
	inputContext.mKeyboard = application->GetKeyboard().get();
	inputContext.mMouse = application->GetMouse().get();
	trayManager = make_shared<OgreBites::SdkTrayManager>("GUI", application->GetRenderWindow(), inputContext, this);

	//Create a parameter panel
	Ogre::StringVector parameters;
	parameters.push_back("Helicopter Position");
	parameters.push_back("Helicopter Orientation");
	paramPanel = trayManager->createParamsPanel(OgreBites::TL_TOPLEFT, "Parameter Panel", 350, parameters);

	trayManager->showLogo(OgreBites::TL_BOTTOMRIGHT);
	trayManager->hideCursor(); 
}