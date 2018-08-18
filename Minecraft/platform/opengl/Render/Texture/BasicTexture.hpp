//
//  BasicTexture.hpp
//  Minecraft_CPP
//
//  Created by Shun Sato on 8/17/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#ifndef BasicTexture_hpp
#define BasicTexture_hpp

#include "Texture.hpp"

class BasicTexture: public Texture {
public:
    BasicTexture();
    ~BasicTexture();
    
    void load(const std::string& fileName) override;
    void bind() override;
private:
    void loadDDS(const std::string& fileName);
    
    unsigned int textureID;
};

#endif /* BasicTexture_hpp */
