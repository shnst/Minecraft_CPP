//
//  SkyboxRenderer.hpp
//  Minecraft_CPP
//
//  Created by Shun Sato on 8/16/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#ifndef SkyboxRenderer_hpp
#define SkyboxRenderer_hpp

#include <array>

class Camera;
class Mesh;
class Shader;
class Skybox;
class Texture;

class SkyboxRenderer {
public:
    SkyboxRenderer();
    ~SkyboxRenderer();
    
    void createMesh(const Skybox& skybox);
    void render(const Camera& camera, const Skybox& skybox);
private:
    Mesh* mesh;
    Texture* texture;
    Shader* shader;

    unsigned int vertexBuffer;
    unsigned int uvBuffer;
};

#endif /* SkyboxRenderer_hpp */
