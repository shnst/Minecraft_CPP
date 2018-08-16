//
//  FieldMode.cpp
//  tetris
//
//  Created by Shun Sato on 8/4/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#include "FieldMode.hpp"

#include <iostream>

#include "JsonParser.hpp"
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

void FieldMode::handleKeyboardInput(Keyboard::Types key) {
    const double delta = 1.0;
    switch (key) {
        case Keyboard::LEFT:
            break;
        case Keyboard::UP:
            break;
        case Keyboard::DOWN:
            break;
        case Keyboard::RIGHT:
            break;
        default: break;
    }
}
