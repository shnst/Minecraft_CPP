//
//  FieldMode.cpp
//  tetris
//
//  Created by Shun Sato on 8/4/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#include "FieldMode.hpp"

#include <iostream>

#include "Camera.hpp"
#include "Entity.hpp"
#include "Utils.hpp"
#include "World.hpp"


FieldMode::FieldMode()
:world(new World())
{
}

FieldMode::~FieldMode() {
    Utils::SafeDelete(world);
}

void FieldMode::start() {
}

void FieldMode::pause(bool isPaused) {
}

void FieldMode::quit() {
}

void FieldMode::handleInput(const Input::Data& input) {
    if (input.mouseButtonEvent != nullptr) {
        if (input.mouseButtonEvent->button == MouseButton::Right) {
            world->save();
        }
    }
    
    auto cameraBindedEntity = world->getCameraBinidedEntity();
    if (cameraBindedEntity == nullptr) {
        auto camera = world->getCamera();
        camera->handleInput(input);
    } else {
        cameraBindedEntity->handleInput(input);
    }
}
