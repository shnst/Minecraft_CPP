//
//  SkyboxTexture.hpp
//  Minecraft_CPP
//
//  Created by Shun Sato on 8/17/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#ifndef SkyboxTexture_hpp
#define SkyboxTexture_hpp

#include "Texture.hpp"
#include <array>

class SkyboxTexture: public Texture {
public:
    enum Direction {
        Side2 = 0, // positive x
        Side4, // negative x
        Top, // top
        Bottom, // bottom
        Side3, // positive z
        Side1, // negative z
    };
    
    SkyboxTexture();
    ~SkyboxTexture();
    
    void load(const std::string& skyboxName) override;
    void bind() override;
private:
    void loadDDS(const std::string& skyboxName);
    void loadTextureOnMemory(const std::string& fileName, Direction direction);
    
    unsigned int textureID;
};

#endif /* SkyboxTexture_hpp */
