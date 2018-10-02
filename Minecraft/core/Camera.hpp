//
//  Camera.hpp
//  Minecraft_cpp
//
//  Created by Shun Sato on 8/10/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <glm/glm.hpp>

#include "Vector3d.hpp"
#include "InputHandleable.hpp"

class Camera: public InputHandleable {
public:
    Camera();
    ~Camera();
    
    void handleInput(const Input::Data& input) override;
    
    void setPosition(const vec3d& position);
    void setLookat(const vec3d& lookat);
    
    const glm::vec3& getPosition() const;
    glm::mat4 getMVPMatrix() const;
    glm::mat4 getMVPMatrixForCubeMap() const;
    
    void forward();
    void back();
    void left();
    void right();
private:
    
    glm::vec3 position;
    glm::vec3 lookat;
    glm::vec3 up;
    
    glm::vec3 skyboxLookat;
    const glm::vec3 skyboxOrigin;
    
    double previousMouseX;
    double previousMouseY;
};

#endif /* Camera_hpp */
