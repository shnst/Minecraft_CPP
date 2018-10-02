//
//  AABB.hpp
//  Minecraft_CPP
//
//  Created by Shun Sato on 8/18/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#ifndef AABB_hpp
#define AABB_hpp

#include <array>

#include "Vector3d.hpp"

class AABB {
public:
    AABB(int height, int width, int length);
    ~AABB();
    
    void setCoord(const vec3d& coord);

    const std::array<vec3d, 8>& getVertices() const;
private:
    void updateVertices(const vec3d& coord);
    
    std::array<vec3d, 8> vertices;
    
    int height;
    int width;
    int length;
};

#endif /* AABB_hpp */
