//
//  Entity.cpp
//  Minecraft_CPP
//
//  Created by Shun Sato on 8/17/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#include "Entity.hpp"

#include "AABB.hpp"

Entity::Entity()
{
}

Entity::~Entity() {
    
}

const AABB* Entity::getAABB() const {
    return aabb;
}
