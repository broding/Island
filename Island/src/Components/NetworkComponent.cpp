//
//  NetworkComponent.cpp
//  Island
//
//  Created by Bas Roding on 25-03-13.
//  Copyright (c) 2013 Bas Roding. All rights reserved.
//

#include "NetworkComponent.h"

NetworkSystem* NetworkComponent::networkSystem;

NetworkComponent::NetworkComponent()
{
    _type = COMPONENT_PLAYERINPUT;
    _subSystem = networkSystem;
    networkSystem->AddComponent(this);
    
    this->AddComponentSubscription(COMPONENT_NETWORK);
}

NetworkComponent::~NetworkComponent()
{
    networkSystem->RemoveComponent(this);
}