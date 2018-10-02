//
//  AABB.cpp
//  Minecraft_CPP
//
//  Created by Shun Sato on 8/18/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#include "AABB.hpp"


AABB::AABB(int height, int width, int length)
:height(height)
,width(width)
,length(length)
{
}

AABB::~AABB() {
    
}

void AABB::setCoord(const vec3d& coord) {
    updateVertices(coord);
}

const std::array<vec3d, 8>& AABB::getVertices() const {
    return vertices;
}

void AABB::updateVertices(const vec3d& coord) {
    vertices[0].x = coord.x;
    vertices[0].y = coord.y;
    vertices[0].z = coord.z;
    
    vertices[1].x = coord.x + width;
    vertices[1].y = coord.y;
    vertices[1].z = coord.z;
    
    vertices[2].x = coord.x + width;
    vertices[2].y = coord.y;
    vertices[2].z = coord.z + length;
    
    vertices[3].x = coord.x;
    vertices[3].y = coord.y;
    vertices[3].z = coord.z + length;
    
    vertices[4].x = coord.x;
    vertices[4].y = coord.y + height;
    vertices[4].z = coord.z;
    
    vertices[5].x = coord.x + width;
    vertices[5].y = coord.y + height;
    vertices[5].z = coord.z;
    
    vertices[6].x = coord.x + width;
    vertices[6].y = coord.y + height;
    vertices[6].z = coord.z + length;
    
    vertices[7].x = coord.x;
    vertices[7].y = coord.y + height;
    vertices[7].z = coord.z + length;
}
