//
//  PlayerInputSystem.cpp
//  Island
//
//  Created by Bas Roding on 20-03-13.
//  Copyright (c) 2013 Bas Roding. All rights reserved.
//

#include "PlayerInputSystem.h"

#include <SFML/Window/Keyboard.hpp>
#include "PlayerInputComponent.h"
#include "PhysicsComponent.h"
#include "TransformComponent.h"
#include "GUIObject.h"
#include <math.h>

void PlayerInputSystem::ProcessGameTick(float lastFrameTime)
{
    for (std::list<Component*>::const_iterator iterator = _components.begin(), end = _components.end(); iterator != end; ++iterator)
    {
        PlayerInputComponent* inputComponent = static_cast<PlayerInputComponent*>(*iterator);
        PhysicsComponent* physicsComponent = static_cast<PhysicsComponent*>(inputComponent->GetNeighbourComponent(COMPONENT_PHYSICS));
        TransformComponent* transformComponent = static_cast<TransformComponent*>(inputComponent->GetNeighbourComponent(COMPONENT_TRANSFORM));
        
        if(physicsComponent != 0)
        {
            physicsComponent->velocity = sf::Vector2f(0,0);
            
            if(sf::Keyboard::isKeyPressed(inputComponent->up))
                physicsComponent->velocity += sf::Vector2f(0, -200);
            
            if(sf::Keyboard::isKeyPressed(inputComponent->down))
                physicsComponent->velocity += sf::Vector2f(0, 200);
            
            if(sf::Keyboard::isKeyPressed(inputComponent->left))
                physicsComponent->velocity += sf::Vector2f(-200, 0);
            
            if(sf::Keyboard::isKeyPressed(inputComponent->right))
                physicsComponent->velocity += sf::Vector2f(200, 0);
        }
        
        if(transformComponent != 0)
        {
            sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(*GUIObject::window).x, sf::Mouse::getPosition(*GUIObject::window).y);
            
            sf::Vector2f mouseDelta = mousePosition - transformComponent->position;
            
            const double degreesPerRadian = 57.2957;
            transformComponent->rotation = atan2(mouseDelta.x, -mouseDelta.y) * degreesPerRadian;
        }
    }
}

void PlayerInputSystem::ProcessEvent(Component *component, Event* event)
{
    delete event;
}