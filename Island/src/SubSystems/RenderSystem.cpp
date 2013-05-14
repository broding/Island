//
//  RenderSystem.cpp
//  Island
//
//  Created by Bas Roding on 19-03-13.
//  Copyright (c) 2013 Bas Roding. All rights reserved.
//

#include "RenderSystem.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include <SFML/Graphics.hpp>

RenderSystem::RenderSystem(sf::RenderWindow* renderWindow) : _renderWindow(renderWindow)
{
}

RenderSystem::~RenderSystem()
{
    
}

void RenderSystem::ProcessGameTick(float lastFrameTime, std::list<Component*> components)
{
    for (std::list<Component*>::const_iterator iterator = components.begin(), end = components.end(); iterator != end; ++iterator)
    {
        RenderComponent* renderComponent = static_cast<RenderComponent*>(*iterator);
        TransformComponent* transformComponent = static_cast<TransformComponent*>(renderComponent->GetNeighbourComponent(COMPONENT_TRANSFORM));
        
        if(transformComponent != NULL)
        {
            renderComponent->sprite.setPosition(transformComponent->position);
            renderComponent->sprite.setScale(transformComponent->scale);
            renderComponent->sprite.setRotation(transformComponent->rotation);
            renderComponent->sprite.setOrigin(transformComponent->origin);
        }
        
        if(renderComponent->currentAnimation != 0)
        {
            Animation* animation = renderComponent->currentAnimation;
            animation->currentFrameTime += lastFrameTime;
            
            if(animation->currentFrameTime > renderComponent->currentAnimation->frames[animation->currentFrame].time)
            {
                if(animation->currentFrame >= animation->frames.size() - 1 && animation->looping)
                    animation->currentFrame = 0;
                else if(animation->currentFrame < animation->frames.size())
                    animation->currentFrame++;
                
                animation->currentFrameTime = 0;
            }
            
            renderComponent->textureRect.left = renderComponent->textureRect.width * animation->currentFrame;
            renderComponent->sprite.setTextureRect(renderComponent->textureRect);
        }
        
        float spriteX = renderComponent->sprite.getPosition().x;
        float spriteY = renderComponent->sprite.getPosition().y;
        float spriteWidth = renderComponent->sprite.getScale().x * renderComponent->sprite.getTextureRect().width;
        float spriteHeight = renderComponent->sprite.getScale().y * renderComponent->sprite.getTextureRect().height;
        
        for(unsigned int x = 0; x < renderComponent->tiling.x; x++)
        {
            for(unsigned int y = 0; y < renderComponent->tiling.y; y++)
            {
                
                renderComponent->sprite.setPosition(spriteX + spriteWidth * x, spriteY + spriteHeight * y);
                _renderWindow->draw(renderComponent->sprite);
            }
        }
    }
}

