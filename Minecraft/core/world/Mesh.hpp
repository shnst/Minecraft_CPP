//
//  Mesh.hpp
//  Minecraft_cpp
//
//  Created by Shun Sato on 8/15/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <iostream>
#include <string>
#include <vector>

#include "Constants.hpp"

struct Mesh {
    void addPoint(float x, float y, float z, float u, float v) {
        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(z);
        textureCoords.push_back(u);
        textureCoords.push_back(v);
    }
    
    void addFace(float x, float y, float z, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float u, float v, float width, float height) {
        x *=  TILE_SIZE_IN_POINT;
        y *=  TILE_SIZE_IN_POINT;
        z *=  TILE_SIZE_IN_POINT;
        
        x1 *=  TILE_SIZE_IN_POINT;
        y1 *=  TILE_SIZE_IN_POINT;
        z1 *=  TILE_SIZE_IN_POINT;
        
        x2 *=  TILE_SIZE_IN_POINT;
        y2 *=  TILE_SIZE_IN_POINT;
        z2 *=  TILE_SIZE_IN_POINT;
        
        x3 *=  TILE_SIZE_IN_POINT;
        y3 *=  TILE_SIZE_IN_POINT;
        z3 *=  TILE_SIZE_IN_POINT;
        
        addPoint(x, y, z, u + width, v);
        addPoint(x1, y1, z1, u, v);
        addPoint(x2, y2, z2, u + width, v + height);
        
        addPoint(x1, y1, z1, u, v);
        addPoint(x2, y2, z2, u + width, v + height);
        addPoint(x3, y3, z3, u, v + height);
    }
    
    void addMesh(const Mesh& mesh) {
        vertices.insert(std::end(vertices), mesh.vertices.begin(), mesh.vertices.end());
        textureCoords.insert(std::end(textureCoords), mesh.textureCoords.begin(), mesh.textureCoords.end());
    }
    
    void clear() {
        vertices.clear();
        textureCoords.clear();
    }
    
    void reserve(int numberOfVertices) {
        vertices.reserve(numberOfVertices * 3);
        textureCoords.reserve(numberOfVertices * 2);
    }
    
    std::vector<float> vertices;
    std::vector<float> textureCoords;
};

#endif /* Mesh_hpp */
