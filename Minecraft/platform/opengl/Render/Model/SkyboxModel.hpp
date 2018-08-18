//
//  SkyboxModel.hpp
//  Minecraft_CPP
//
//  Created by Shun Sato on 8/17/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#ifndef SkyboxModel_hpp
#define SkyboxModel_hpp

#include <array>

#include "Model.hpp"

class Skybox;
class Mesh;
class Shader;
class Texture;

class SkyboxModel: Model {
public:
    SkyboxModel(Skybox* skybox);
    ~SkyboxModel();
    
    void createMesh();
    void render() override;
private:
    Skybox* skybox;
    
    std::array<Mesh*, 6> meshes;
    std::array<Texture*, 6> textures;
    Shader* shader;
    
    unsigned int vertexBuffer;
    unsigned int uvBuffer;
};

#endif /* SkyboxModel_hpp */
