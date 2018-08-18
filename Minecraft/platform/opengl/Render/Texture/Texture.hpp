//
//  Texture.hpp
//  Minecraft_CPP
//
//  Created by Shun Sato on 8/17/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <string>

class Texture {
public:
    virtual void load(const std::string& fileName) = 0;
    virtual void bind() = 0;
};

#endif /* Texture_hpp */
