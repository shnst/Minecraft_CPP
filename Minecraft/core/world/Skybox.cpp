//
//  Skybox.cpp
//  Minecraft_CPP
//
//  Created by Shun Sato on 8/16/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#include "Skybox.hpp"

#include "Camera.hpp"
#include "GameContext.hpp"

Skybox::Skybox(double size)
:size(size)
{
}

Skybox::~Skybox() {
    
}

void Skybox::update() {
    auto cameraPosition = GameContext::get().getCamera()->getPosition();
    coords.set(cameraPosition.x, cameraPosition.y, cameraPosition.z);
}

const vec3d& Skybox::getCoords() const {
    return coords;
}

double Skybox::getSize() const {
    return size;
}
