//
//  MapProcessor.hpp
//  Mobile_Slam_CPP
//
//  Created by Shun Sato on 11/16/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#ifndef MapProcessor_hpp
#define MapProcessor_hpp

#include <unordered_map>

#include "Vector3d.hpp"

class Chunk;

class MapProcessor {
public:
    MapProcessor();
    
    void process(std::unordered_map<vec3n, Chunk*>& chunks);
};

#endif /* MapProcessor_hpp */
