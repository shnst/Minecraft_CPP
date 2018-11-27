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
#include "Constants.hpp"
#include "Entity.hpp"
#include "JsonParser.hpp"
#include "Utils.hpp"
#include "World.hpp"

FieldMode::FieldMode()
:world(new World())
{
    setupUDP();
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

void FieldMode::notify(const std::string& message) {
//    std::cout << "received message:" << message << std::endl;
    
    vec3d lookAt;
    auto lookAtString = JsonParser::get<picojson::object>(message, "lookat", picojson::object());
    lookAt.x = JsonParser::get<double>(lookAtString, "x", 0);
    lookAt.y = JsonParser::get<double>(lookAtString, "y", 0);
    lookAt.z = JsonParser::get<double>(lookAtString, "z", 0);
    
    vec3d position;
    auto positionString = JsonParser::get<picojson::object>(message, "position", picojson::object());
    position.x = JsonParser::get<double>(positionString, "x", 0);
    position.y = JsonParser::get<double>(positionString, "y", 0);
    position.z = JsonParser::get<double>(positionString, "z", 0);
    
//    std::cout << "position x:" << position.x << " y:" << position.y << " z:" << position.z << std::endl;
//    std::cout << "lookAt x:" << lookAt.x << " y:" << lookAt.y << " z:" << lookAt.z << std::endl;
    
    position *= 10;
    lookAt *= 10;
    
    int CAMERA_OFFSET = 50;
    
    position.x += CAMERA_OFFSET;
    position.y += CAMERA_OFFSET;
    position.z += CAMERA_OFFSET;
    lookAt.x += CAMERA_OFFSET;
    lookAt.y += CAMERA_OFFSET;
    lookAt.z += CAMERA_OFFSET;
    
    auto camera = world->getCamera();
    camera->setLookat(lookAt);
    camera->setPosition(position);
    
    auto resetWorld = JsonParser::get<std::string>(message, "resetWorld", "");
    if (resetWorld == "true") {
        world->clearAllBlocks();
    }           
    
    auto hitTestJsonObject = JsonParser::get<picojson::object>(message, "hitTest", picojson::object());
    if (!hitTestJsonObject.empty()) {
        vec3d hitObjectCoord;
        hitObjectCoord.x = JsonParser::get<double>(hitTestJsonObject, "x", 0);
        hitObjectCoord.y = JsonParser::get<double>(hitTestJsonObject, "y", 0);
        hitObjectCoord.z = JsonParser::get<double>(hitTestJsonObject, "z", 0);
        
        hitObjectCoord *= 10;
        
        hitObjectCoord.x += CAMERA_OFFSET;
        hitObjectCoord.y += CAMERA_OFFSET;
        hitObjectCoord.z += CAMERA_OFFSET;
        
        std::cout << "position x:" << position.x << " y:" << position.y << " z:" << position.z << std::endl;
        std::cout << "hitCoord x:" << hitObjectCoord.x << " y:" << hitObjectCoord.y << " z:" << hitObjectCoord.z << std::endl;
        
        // place oject
//        world->setBlock(hitObjectCoord.x, hitObjectCoord.y ,hitObjectCoord.z, Blocks::Wood);
//        world->setBlock(lookAt.x, lookAt.y ,lookAt.z, Blocks::Wood);
        world->setHitBlock(position, hitObjectCoord);
    }
    
    auto distance = JsonParser::get<double>(message, "distance", 0);
    if (distance != 0) {
        std::cout << "distance:" << distance << std::endl;
    }
}

void FieldMode::setupUDP() {
    UDP::get().startReceiving("10.0.0.18", 8889);
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
