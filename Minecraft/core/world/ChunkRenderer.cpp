//
//  ChunkRenderer.cpp
//  Minecraft_cpp
//
//  Created by Shun Sato on 8/14/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#include "ChunkRenderer.hpp"

#include <iostream>

#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "BasicTexture.hpp"
#include "Camera.hpp"
#include "Chunk.hpp"
#include "GameContext.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Time.hpp"
#include "Utils.hpp"
#include "World.hpp"

ChunkRenderer::ChunkRenderer()
:mesh(new Mesh())
{
    texture = new BasicTexture();
    texture->load("blocks.dds");
    
    shader = new Shader("test", {"MVP", "sampler"}, {});
    
    glGenBuffers(1, &vertexBuffer); //バッファを作成
    glGenBuffers(1, &uvBuffer); //バッファを作成
}

ChunkRenderer::~ChunkRenderer() {
    Utils::SafeDelete(texture);
    Utils::SafeDelete(shader);
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &uvBuffer);
}

void ChunkRenderer::updateMesh(const std::unordered_map<vec3n, Chunk*>& chunks) {
    std::cout << "ChunkRenderer::updateMesh" << std::endl;
    mesh->clear();
    for (const auto& chunk : chunks) {
        const auto& chunkMesh = chunk.second->getMesh();
        mesh->vertices.insert(std::end(mesh->vertices), chunkMesh.vertices.begin(), chunkMesh.vertices.end());
        mesh->textureCoords.insert(std::end(mesh->textureCoords), chunkMesh.textureCoords.begin(), chunkMesh.textureCoords.end());
//        std::copy(mesh.vertices.begin(), mesh.vertices.end(), std::back_inserter(vertices));
//        std::copy(mesh.textureCoords.begin(), mesh.textureCoords.end(), std::back_inserter(textureCoords));
    }
}

void ChunkRenderer::render(const Camera& camera, const World& world, const std::unordered_map<vec3n, Chunk*>& chunks) const {
    auto startTime = Time::now_ms();

    GLuint vertexArrayID;
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);
    
    // Use our shader
    shader->use();
    
    glUniformMatrix4fv(shader->getUniform("MVP"), 1, GL_FALSE, &camera.getMVPMatrix()[0][0]);
    
    texture->bind();
    
    glUniform1i(shader->getUniform("sampler"), 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(mesh->vertices.front()), &mesh->vertices.front(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, mesh->textureCoords.size() * sizeof(mesh->textureCoords.front()), &mesh->textureCoords.front(), GL_STATIC_DRAW);


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
    
    auto numTriangles = mesh->vertices.size() / 3;
    
    // Draw the triangle
    glDrawArrays(GL_TRIANGLES, 0, numTriangles); // 12*3 indices starting at 0 -> 12 triangles
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    
    // Cleanup VBO and shader
    glDeleteVertexArrays(1, &vertexArrayID);
    
//    std::cout << "ChunkRenderer::render time:" << Time::now_ms() - startTime << " vertices:" << numTriangles <<  std::endl;
}
