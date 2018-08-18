//
//  Model.hpp
//  Minecraft_CPP
//
//  Created by Shun Sato on 8/17/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#ifndef Model_hpp
#define Model_hpp

class Mesh;
class Texture;
class Shader;

class Model {
    virtual void render() = 0;
};

#endif /* Model_hpp */
