//
//  ScriptComponent.cpp
//  Island
//
//  Created by Bas Roding on 27-04-13.
//  Copyright (c) 2013 Bas Roding. All rights reserved.
//

#include "ScriptComponent.h"

ScriptSystem* ScriptComponent::scriptSystem;

ScriptComponent::ScriptComponent() : Component(COMPONENT_SCRIPT, "Script", scriptSystem)
{
    script = 0;
}

ScriptComponent::~ScriptComponent()
{
    delete script;
}

void ScriptComponent::FillXML(pugi::xml_node &node)
{
    pugi::xml_node dataNode;
    
    dataNode = node.append_child("data");
    dataNode.append_attribute("type").set_value("position");
    dataNode.append_attribute("value").set_value(145);
    
    dataNode = node.append_child("data");
    dataNode.append_attribute("type").set_value("velocity");
    dataNode.append_attribute("value").set_value(145);
}

void ScriptComponent::UpdateFromXML(pugi::xml_node node)
{
    
}