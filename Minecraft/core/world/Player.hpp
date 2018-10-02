//
//  Player.hpp
//  Minecraft_CPP
//
//  Created by Shun Sato on 8/18/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <glm/glm.hpp>

#include "Entity.hpp"
#include "InputHandleable.hpp"

class AABB;
class World;

class Player: public Entity {
public:
    Player(World* world);
    ~Player();
    
    void handleInput(const Input::Data& input) override;
    vec3d getFacePosition() const override;
    vec3d getLookat() const override;
    void setPosition(const vec3d& position) override;
private:
    void forward();
    void back();
    void left();
    void right();
    void jump();
    
    World* world;
    
    AABB* aabb;
    
    glm::vec3 position;
    glm::vec3 lookat;
    glm::vec3 up;
    
    double previousMouseX;
    double previousMouseY;
};

#endif /* Player_hpp */
