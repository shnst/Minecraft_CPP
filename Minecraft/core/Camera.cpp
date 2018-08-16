//
//  Camera.cpp
//  Minecraft_cpp
//
//  Created by Shun Sato on 8/10/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#include "Camera.hpp"


#include <GL/glew.h>
#include <GLUT/glut.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/noise.hpp>

#include <cmath>

Camera::Camera()
:yaw(0)
,coords(0, 0, 0)
,angle(0, -0.5, 0)
{
}

Camera::~Camera() {
    
}

void Camera::setCoords(const vec3d& coords) {
    this->coords = coords;
}

const vec3d& Camera::getCoords() const {
    return coords;
}

void Camera::setYaw(double yaw) {
    this->yaw = yaw;
}

const double& Camera::getYaw() const {
    return yaw;
}

void Camera::setAngle(const vec3d& angle) {
    this->angle = angle;
}

const vec3d& Camera::getAngle() const {
    return angle;
}

vec3d Camera::getForward() const {
    return vec3d(sin(angle.x), 0, cos(angle.x));
}

vec3d Camera::getRight() const {
    return vec3d(-cos(angle.x), 0, sin(angle.x));
}

vec3d Camera::getLookat() const {
    return vec3d(sin(angle.x) * cos(angle.y), sin(angle.y), cos(angle.x) * cos(angle.y));
}

// Calculate the forward, right and lookat vectors from the angle vector
void Camera::updateVectors() {
    forward.x = sin(angle.x);
    forward.y = 0;
    forward.z = cos(angle.x);
    
    right.x = -cos(angle.x);
    right.y = 0;
    right.z = sin(angle.x);
    
    lookat.x = sin(angle.x) * cos(angle.y);
    lookat.y = sin(angle.y);
    lookat.z = cos(angle.x) * cos(angle.y);
    
    
}
