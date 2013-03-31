//
//  BoxCollisionComponent.cpp
//  Island
//
//  Created by Bas Roding on 31-03-13.
//  Copyright (c) 2013 Bas Roding. All rights reserved.
//

#include "BoxCollisionComponent.h"
#include "TransformComponent.h"
#include "Entity.h"

CollisionSystem* BoxCollisionComponent::collisionSystem;

BoxCollisionComponent::BoxCollisionComponent()
{
    _type = COMPONENT_BOXCOLLISION;
    _subSystem = collisionSystem;
    
    this->AddToSystem();
    
    center = sf::Vector2f(32,32);
    size = sf::Vector2f(64, 64);
}

void BoxCollisionComponent::DrawDebug(sf::RenderWindow *window)
{
    TransformComponent* transform = this->GetOwner()->GetComponent<TransformComponent>();
    
    if(transform != NULL)
    {
        sf::RectangleShape rect = sf::RectangleShape(size);
        rect.setFillColor(sf::Color(255, 0, 0, 100));
        rect.setOutlineThickness(2);
        rect.setPosition(transform->position);
        rect.setOrigin(center);
        rect.setOutlineColor(sf::Color::Red);
        
        window->draw(rect);
    }
    
}