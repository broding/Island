//
//  Core.cpp
//  Island
//
//  Created by Bas Roding on 18-03-13.
//  Copyright (c) 2013 Bas Roding. All rights reserved.
//

#include <math.h>
#include "Core.h"

#include "RenderSystem.h"
#include "TransformSystem.h"
#include "PhysicsSystem.h"
#include "PlayerInputSystem.h"
#include "NetworkSystem.h"
#include "CollisionSystem.h"
#include "HealthSystem.h"
#include "WeaponSystem.h"
#include "ScriptSystem.h"
#include "DamageSystem.h"

#include "RenderComponent.h"
#include "TransformComponent.h"
#include "PhysicsComponent.h"
#include "PlayerInputComponent.h"
#include "NetworkComponent.h"
#include "CameraComponent.h"
#include "BoxCollisionComponent.h"
#include "SphereCollisionComponent.h"
#include "HealthComponent.h"
#include "WeaponComponent.h"
#include "ScriptComponent.h"
#include "DamageComponent.h"

#include "ConnectScene.h"
#include "DebugText.h"

#include "Entity.h"
#include "ResourcePath.hpp"
#include "GameConfig.h"

Core::Core(sf::RenderWindow* window) : _renderWindow(window)
{
    GUIObject::window = window;
    _currentScene = 0;
    _deletedScene = 0;
    
    InitializeSubSystems();
    SwitchScene(new ConnectScene());
}

Core::~Core()
{
    for (std::vector<SubSystem*>::const_iterator it = _subSystems.begin(), end = _subSystems.end(); it != end; ++it)
        delete *it;
}

void Core::InitializeSubSystems()
{
    RenderSystem* renderSystem = new RenderSystem(_renderWindow);
    TransformSystem* transformSystem = new TransformSystem();
    PhysicsSystem* physicsSystem = new PhysicsSystem();
    PlayerInputSystem* playerInputSystem = new PlayerInputSystem(_renderWindow);
    NetworkSystem* networkSystem = new NetworkSystem();
    _cameraSystem = new CameraSystem(_renderWindow);
    CollisionSystem* collisionSystem = new CollisionSystem();
    HealthSystem* healthSystem = new HealthSystem();
    WeaponSystem* weaponSystem = new WeaponSystem();
    ScriptSystem* scriptSystem = new ScriptSystem();
    DamageSystem* damageSystem = new DamageSystem();
    
    AddSubSystem(_cameraSystem);
    AddSubSystem(scriptSystem);
    AddSubSystem(playerInputSystem);
    AddSubSystem(transformSystem);
    AddSubSystem(collisionSystem);
    AddSubSystem(healthSystem);
    AddSubSystem(weaponSystem);
    AddSubSystem(physicsSystem);
    AddSubSystem(renderSystem);
    AddSubSystem(networkSystem);
    AddSubSystem(damageSystem);
    
    // setup subsystems in components
    RenderComponent::renderSystem = renderSystem;
    TransformComponent::transformSystem = transformSystem;
    PhysicsComponent::physicsSystem = physicsSystem;
    PlayerInputComponent::playerInputSystem = playerInputSystem;
    NetworkComponent::networkSystem = networkSystem;
    CameraComponent::cameraSystem = _cameraSystem;
    BoxCollisionComponent::collisionSystem = collisionSystem;
    SphereCollisionComponent::collisionSystem = collisionSystem;
    HealthComponent::healthSystem = healthSystem;
    WeaponComponent::weaponSystem = weaponSystem;
    ScriptComponent::scriptSystem = scriptSystem;
    DamageComponent::damageSystem = damageSystem;
}

void Core::AddSubSystem(SubSystem *subSystem)
{
    _subSystems.push_back(subSystem);
}

void Core::Update(float lastFrameTime)
{
    if(_deletedScene != 0)
    {
       delete _deletedScene;
        _deletedScene = 0;
    }
    
    for (std::vector<SubSystem*>::const_iterator iterator = _subSystems.begin(), end = _subSystems.end(); iterator != end; ++iterator)
    {
		if(!(*iterator)->runInEditor && GameConfig::GetInstance()->GetFlagConfig("editorMode"))
			continue;
			
		(*iterator)->ProcessGameTick(lastFrameTime, (*iterator)->GetValidComponents());
    }
    
    if(GameConfig::GetInstance()->GetFlagConfig("debugMode"))
    {
        for (std::vector<SubSystem*>::const_iterator iterator = _subSystems.begin(), end = _subSystems.end(); iterator != end; ++iterator)
        {
            (*iterator)->DrawDebug(_renderWindow);
        }
    }
    
    if(_currentScene != NULL)
    {
        sf::View oldView = _renderWindow->getView();
        
        sf::View view(sf::Vector2f(400,300), sf::Vector2f(800,600));
        _renderWindow->setView(view);
        _currentScene->Update(lastFrameTime);
        _currentScene->Draw(_renderWindow);
        
        _renderWindow->setView(oldView);
    }
}

void Core::SwitchScene(Scene* scene)
{
    if(_currentScene != 0)
        _deletedScene = _currentScene;
    
    _currentScene = scene;
    _currentScene->SetCore(this);
    _currentScene->AddGUIObject(DebugText::GetInstance());
}