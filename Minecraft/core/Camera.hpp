//
//  Camera.hpp
//  Minecraft_cpp
//
//  Created by Shun Sato on 8/10/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include "Vector3d.hpp"

#include <glm/glm.hpp>

class Camera {
public:
    Camera();
    ~Camera();
    
    void mouseInput(double x, double y);
    
    const glm::vec3& getPosition() const;
    glm::mat4 getMVPMatrix() const;
    
    void forward();
    void back();
    void left();
    void right();
private:
    void updateVectors();
    
    glm::vec3 position;
    glm::vec3 lookat;
    glm::vec3 up;
    glm::vec3 angle;
    
    glm::vec3 _forward;
    glm::vec3 _right;
    
    double previousMouseX;
    double previousMouseY;
};

#endif /* Camera_hpp */
