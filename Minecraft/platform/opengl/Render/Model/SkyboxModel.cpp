//
//  SkyboxModel.cpp
//  Minecraft_CPP
//
//  Created by Shun Sato on 8/17/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#include "SkyboxModel.hpp"

#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Mesh.hpp"
#include "ResourceManager.hpp"
#include "Shader.hpp"
#include "Skybox.hpp"
#include "SkyboxTexture.hpp"
#include "Utils.hpp"

SkyboxModel::SkyboxModel(Skybox* skybox)
{
    for (auto it=meshes.begin(); it!=meshes.end(); ++it) {
        (*it) = new Mesh();
    }
    
    for (int i=0; i<textures.size(); ++i) {
        textures[i] = new SkyboxTexture();
        textures[i]->load("skybox");
    }
    
    glGenBuffers(1, &vertexBuffer); //バッファを作成
    glGenBuffers(1, &uvBuffer); //バッファを作成
}

SkyboxModel::~SkyboxModel() {
    for (auto it=meshes.begin(); it!=meshes.end(); ++it) {
        Utils::SafeDelete(*it);
    }
    
    for (auto it=textures.begin(); it!=textures.end(); ++it) {
        Utils::SafeDelete(*it);
    }
}

void SkyboxModel::createMesh() {
    auto coord = skybox->getCoords();
    auto size = skybox->getSize();
    
    //    std::cout << "SkyboxRenderer::createMesh x:" << coord.x << " y:" << coord.y << " size:" << size << std::endl;
    
    for (auto it=meshes.begin(); it!=meshes.end(); ++it) {
        (*it)->vertices.clear();
        (*it)->textureCoords.clear();
    }
    
    // side2
    meshes[3]->addFace(
                       coord.x + size, coord.y + size, coord.z - size,
                       coord.x + size, coord.y + size, coord.z + size,
                       coord.x + size, coord.y - size, coord.z - size,
                       coord.x + size, coord.y - size, coord.z + size,
                       1.0, 1.0, 1.0, 1.0);
    
    
    // side4
    meshes[5]->addFace(
                       coord.x - size, coord.y + size, coord.z + size,
                       coord.x - size, coord.y + size, coord.z - size,
                       coord.x - size, coord.y - size, coord.z + size ,
                       coord.x - size, coord.y - size, coord.z - size,
                       1.0, 1.0, 1.0, 1.0);
    
    // top
    meshes[0]->addFace(
                       coord.x - size, coord.y + size, coord.z - size,
                       coord.x - size, coord.y + size, coord.z + size,
                       coord.x + size, coord.y + size, coord.z - size,
                       coord.x + size, coord.y + size, coord.z + size,
                       1.0, 1.0, 1.0, 1.0);
    
    // bottom
    meshes[1]->addFace(
                       coord.x - size, coord.y - size, coord.z + size,
                       coord.x + size, coord.y - size, coord.z + size,
                       coord.x - size, coord.y - size, coord.z - size,
                       coord.x + size, coord.y - size, coord.z - size,
                       1.0, 1.0, 1.0, 1.0);
    
    // side3
    meshes[4]->addFace(
                       coord.x + size, coord.y + size, coord.z + size,
                       coord.x - size, coord.y + size, coord.z + size,
                       coord.x + size, coord.y - size, coord.z + size,
                       coord.x - size, coord.y - size, coord.z + size,
                       1.0, 1.0, 1.0, 1.0);
    
    // side1
    meshes[2]->addFace(
                       coord.x - size, coord.y + size, coord.z - size,
                       coord.x + size, coord.y + size, coord.z - size,
                       coord.x - size, coord.y - size, coord.z - size,
                       coord.x + size, coord.y - size, coord.z - size,
                       1.0, 1.0, 1.0, 1.0);
}

void SkyboxModel::render() {
    static bool hasMeshCreated = false;
    if (!hasMeshCreated) {
        createMesh();
        hasMeshCreated = true;
    }
    
    auto skyboxSize = skybox->getSize();
    
    for (auto it=meshes.begin(); it!=meshes.end(); ++it) {
        auto mesh = (*it);
        GLuint vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(mesh->vertices.front()), &mesh->vertices.front(), GL_STATIC_DRAW);
        
        glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
        glBufferData(GL_ARRAY_BUFFER, mesh->textureCoords.size() * sizeof(mesh->textureCoords.front()), &mesh->textureCoords.front(), GL_STATIC_DRAW);
        
        auto shader = ResourceManager::get().getShader("test");
        
        // Bind our texture in Texture Unit 0
        //        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, ResourceManager::get().getTexture(mesh->textureName));
        //
        //        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        //        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        //        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        //
        //        //Define all 6 faces
        //        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + it-meshes.begin(), 0, GL_RGBA8, skyboxSize, skyboxSize, 0, GL_BGRA, GL_UNSIGNED_BYTE, ResourceManager::get().getTexture(mesh->textureName));
        
        glUniform1i(shader->getUniform("sampler"), 0);
        
        // 1st attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glVertexAttribPointer(
                              0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
                              3,                  // size
                              GL_FLOAT,           // type
                              GL_FALSE,           // normalized?
                              0,                  // stride
                              (void*)0            // array buffer offset
                              );
        
        // 2nd attribute buffer : UVs
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
        glVertexAttribPointer(
                              1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
                              2,                                // size : U+V => 2
                              GL_FLOAT,                         // type
                              GL_FALSE,                         // normalized?
                              0,                                // stride
                              (void*)0                          // array buffer offset
                              );
        
        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, mesh->vertices.size() / 3); // 12*3 indices starting at 0 -> 12 triangles
        
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        
        
        // Cleanup VBO and shader
        glDeleteVertexArrays(1, &vao);
    }
}
