//
//  Entity.hpp
//  Minecraft_CPP
//
//  Created by Shun Sato on 8/17/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#ifndef Entity_hpp
#define Entity_hpp

#include "InputHandleable.hpp"
#include "Vector3d.hpp"

class AABB;

class Entity: public InputHandleable {
public:
    Entity();
    virtual ~Entity();
    
    const AABB* getAABB() const;
    virtual void handleInput(const Input::Data& input) override = 0;
    virtual vec3d getFacePosition() const = 0;
    virtual vec3d getLookat() const = 0;
    virtual void setPosition(const vec3d& position) = 0;
protected:
    AABB* aabb;
};

#endif /* Entity_hpp */
