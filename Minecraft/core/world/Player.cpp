//
//  Player.cpp
//  Minecraft_CPP
//
//  Created by Shun Sato on 8/18/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#include "Player.hpp"

#include <iostream>

#include "World.hpp"

Player::Player(World* world)
:world(world)
,position(4, 3, 3)
,up(0, 1, 0)
,lookat(0, 0, 0)
,previousMouseX(-1)
,previousMouseY(-1)
{}

Player::~Player(){
    
}

void Player::handleInput(const Input::Data& input) {
    if (input.mouseMoveEvent != nullptr) {
        auto x = input.mouseMoveEvent->x;
        auto y = input.mouseMoveEvent->y;
        
        if (previousMouseX == -1 && previousMouseY == -1) {
            previousMouseX = x;
            previousMouseY = y;
            return;
        }
        
        auto deltaX = x - previousMouseX;
        auto deltaY = y - previousMouseY;
        //    std::cout << "Camera::mouseInput x:" << x << " y:" << y << " deltaX:" << deltaX << " deltaY:" << deltaY << std::endl;
        
        lookat -= up * 0.02f * static_cast<float>(deltaY);
        lookat += glm::cross(glm::normalize(lookat-position), up) * 0.05f * static_cast<float>(deltaX);
        lookat = position + (lookat-position) * 3.0f / glm::distance(lookat, position);
        
        previousMouseX = x;
        previousMouseY = y;
    }
    
    if (input.keyboardEvent != nullptr) {
        switch (input.keyboardEvent->key) {
            case Keyboard::W:
                forward();
                break;
            case Keyboard::A:
                left();
                break;
            case Keyboard::S:
                back();
                break;
            case Keyboard::D:
                right();
                break;
            case Keyboard::SPACE:
                jump();
                break;
            default:
                break;
        }
    }
    
}

void Player::setPosition(const vec3d& position) {
    this->position.x = position.x;
    this->position.y = position.y;
    this->position.z = position.z;
}

vec3d Player::getFacePosition() const {
    return vec3d(position.x, position.y+1.75, position.z);
}

vec3d Player::getLookat() const {
    return vec3d(lookat.x, lookat.y+1.75, lookat.z);
}

void Player::jump() {
    
}

void Player::forward() {
    auto previousPosition = position;
    std::cout << "Camera::forward distance:" << glm::distance(lookat, position) << std::endl;
    auto delta = glm::normalize(lookat-position) * 0.4f;
    position += delta;
    lookat += delta;
    
    if (!world->isPassable(vec3d(position.x, position.y, position.z))) {
        position = previousPosition;
    }
}

void Player::back() {
    auto previousPosition = position;
    auto delta = glm::normalize(lookat-position) * 0.4f;
    position -= delta;
    lookat -= delta;
    
    if (!world->isPassable(vec3d(position.x, position.y, position.z))) {
        position = previousPosition;
    }
}

void Player::left() {
    auto previousPosition = position;
    auto delta = glm::cross(glm::normalize(lookat-position), up) * 0.4f;
    position -= delta;
    lookat -= delta;
    
    if (!world->isPassable(vec3d(position.x, position.y, position.z))) {
        position = previousPosition;
    }
}

void Player::right() {
    auto previousPosition = position;
    auto delta = glm::cross(glm::normalize(lookat-position), up) * 0.4f;
    position += delta;
    lookat += delta;
    
    if (!world->isPassable(vec3d(position.x, position.y, position.z))) {
        position = previousPosition;
    }
}
