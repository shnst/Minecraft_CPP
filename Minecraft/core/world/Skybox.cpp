//
//  Skybox.cpp
//  Minecraft_CPP
//
//  Created by Shun Sato on 8/16/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#include "Skybox.hpp"

Skybox::Skybox(double size)
:size(size)
{
}

Skybox::~Skybox() {
    
}

void Skybox::update(double delta) {
}

double Skybox::getSize() const {
    return size;
}
