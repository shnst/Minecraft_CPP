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

class Camera {
public:
    Camera();
    ~Camera();
    
    void setCoords(const vec3d& coords);
    const vec3d& getCoords() const;
    void setYaw(double yaw);
    const double& getYaw() const;
    
    void setAngle(const vec3d& angle);
    const vec3d& getAngle() const;
    vec3d getForward() const;
    vec3d getRight() const;
    vec3d getLookat() const;
    
private:
    void updateVectors();
    
    double yaw;//カメラの回転（Ｙ軸中心）
    
    vec3d coords;
    vec3d angle;
    vec3d forward;
    vec3d right;
    vec3d up;
    vec3d lookat;
};

#endif /* Camera_hpp */
