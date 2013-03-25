//
//  NetworkSystem.cpp
//  Island
//
//  Created by Bas Roding on 25-03-13.
//  Copyright (c) 2013 Bas Roding. All rights reserved.
//

#include "NetworkSystem.h"

NetworkSystem::NetworkSystem()
{
    host = enet_host_create(NULL, 1, 2, 57600 /8, 14400 / 8);
}

NetworkSystem::~NetworkSystem()
{
    delete host;
}

void NetworkSystem::ProcessGameTick(float lastFrameTime)
{
    for (std::list<Component*>::const_iterator iterator = _components.begin(), end = _components.end(); iterator != end; ++iterator)
    {
    }
}

void NetworkSystem::ProcessEvent(Component *component, Event* event)
{
    delete event;
}