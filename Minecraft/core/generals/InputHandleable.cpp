//
//  InputHandleable.cpp
//  Minecraft_CPP
//
//  Created by Shun Sato on 8/18/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#include "InputHandleable.hpp"

#include "Utils.hpp"

Input::Data::~Data() {
    Utils::SafeDelete(mouseMoveEvent);
    Utils::SafeDelete(keyboardEvent);
    Utils::SafeDelete(mouseButtonEvent);
}

void Input::Data::addMouseMoveEvent(double x, double y) {
    mouseMoveEvent = new MouseMoveEvent(x, y);
}

void Input::Data::addKeyboardEvent(Keyboard::Types key) {
    keyboardEvent = new KeyboardEvent(key);
}

void Input::Data::addMouseButtonEvent(MouseButton::Types button) {
    mouseButtonEvent = new MouseButtonEvent(button);
}
