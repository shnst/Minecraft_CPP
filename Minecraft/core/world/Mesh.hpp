//
//  Mesh.hpp
//  Minecraft_cpp
//
//  Created by Shun Sato on 8/15/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <string>
#include <vector>

struct Mesh {
    void addPoint(float x, float y, float z, float u, float v) {
        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(z);
        textureCoords.push_back(u);
        textureCoords.push_back(v);
    }
    
    void addFace(float x, float y, float z, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float u, float v, float width, float height) {
        addPoint(x, y, z, u + width, v);
        addPoint(x1, y1, z1, u, v);
        addPoint(x2, y2, z2, u + width, v + height);
        
        addPoint(x1, y1, z1, u, v);
        addPoint(x2, y2, z2, u + width, v + height);
        addPoint(x3, y3, z3, u, v + height);
    }
    
    void addVertices(const std::vector<double>& vertices) {
        for (auto it=vertices.begin(); it!=vertices.end(); ++it) {
            this->vertices.push_back(*it);
        }
    }
    
    std::vector<float> vertices;
    std::vector<float> textureCoords;
};

#endif /* Mesh_hpp */
