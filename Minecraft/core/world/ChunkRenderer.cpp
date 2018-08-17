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

#include "Chunk.hpp"
#include "Mesh.hpp"
#include "ResourceManager.hpp"
#include "World.hpp"

ChunkRenderer::ChunkRenderer()
:mesh(new Mesh())
{
    glGenBuffers(1, &vertexBuffer); //バッファを作成
    glGenBuffers(1, &uvBuffer); //バッファを作成
}

ChunkRenderer::~ChunkRenderer() {
    
}

void ChunkRenderer::createMesh(const World& world, const std::vector<std::vector<std::vector<Chunk*>>>& chunks) {
    mesh->vertices.clear();
    mesh->textureCoords.clear();
    for (auto it=chunks.begin(); it!=chunks.end(); ++it) {
        for (auto it2=(*it).begin(); it2!=(*it).end(); ++it2) {
            for (auto it3=(*it2).begin(); it3!=(*it2).end(); ++it3) {
                auto chunk = *it3;
                auto blocks = chunk->getBlocks();
                
                auto xSize = blocks.size();
                auto ySize = blocks[0].size();
                auto zSize = blocks[0][0].size();
                
                
                auto chunkCoords = chunk->getCoords();
                
            //    std::cout << "ChunkRenderer::createMesh chunkX:" << offsetX << " chunkY:" << offsetY << " chunkZ:" << offsetZ << std::endl;
                
                for (int x=0; x<xSize; ++x) {
                    for (int y=0; y<ySize; ++y) {
                        for (int z=0; z<zSize; ++z) {
                            auto blockType = chunk->getBlock(x, y, z);
                            if (blockType == Blocks::Air) {
                                continue;
                            }
                            
                            
                            int offsetX = chunkCoords.x * CHUNK_SIZE;
                            int offsetY = chunkCoords.y * CHUNK_SIZE;
                            int offsetZ = chunkCoords.z * CHUNK_SIZE;
                            
                            auto texture = Blocks::blockTextures[blockType];
                            
                            // top
                            if (!world.isBlocked(offsetX + x, offsetY + y+1, offsetZ + z)) {
            //                    std::cout << "1" << std::endl;
                                mesh->addFace(
                                              offsetX + x, offsetY + y+1, offsetZ + z,
                                              offsetX + x+1, offsetY + y+1, offsetZ + z,
                                              offsetX + x, offsetY + y+1, offsetZ + z+1,
                                              offsetX + x+1, offsetY + y+1, offsetZ + z+1,
                                              texture.top[0], texture.top[1], texture.top[2], texture.top[3]);
                            }
                            
                            // bottom
                            if (!world.isBlocked(offsetX + x, offsetY + y-1, offsetZ + z)) {
                                mesh->addFace(
                                              offsetX + x, offsetY + y, offsetZ + z,
                                              offsetX + x+1, offsetY + y, offsetZ + z,
                                              offsetX + x, offsetY + y, offsetZ + z+1,
                                              offsetX + x+1, offsetY + y, offsetZ + z+1,
                                              texture.bottom[0], texture.bottom[1], texture.bottom[2], texture.bottom[3]);
                            }
            
                            // side1
                            if (!world.isBlocked(offsetX + x-1, offsetY + y, offsetZ + z)) {
                                mesh->addFace(
                                              offsetX + x, offsetY + y+1, offsetZ + z+1,
                                              offsetX + x, offsetY + y+1, offsetZ + z,
                                              offsetX + x, offsetY + y, offsetZ + z+1,
                                              offsetX + x, offsetY + y, offsetZ + z,
                                              texture.side[0], texture.side[1], texture.side[2], texture.side[3]);
                            }
                            
                            // side2
                            if (!world.isBlocked(offsetX + x+1, offsetY + y, offsetZ + z)) {
                                mesh->addFace(
                                              offsetX + x+1, offsetY + y+1, offsetZ + z,
                                              offsetX + x+1, offsetY + y+1, offsetZ + z+1,
                                              offsetX + x+1, offsetY + y, offsetZ + z,
                                              offsetX + x+1, offsetY + y, offsetZ + z+1,
                                              texture.side[0], texture.side[1], texture.side[2], texture.side[3]);
                            }
                            
                            // side3
                            if (!world.isBlocked(offsetX + x, offsetY + y, offsetZ + z-1)) {
                                mesh->addFace(
                                              offsetX + x, offsetY + y+1, offsetZ + z,
                                              offsetX + x+1, offsetY + y+1, offsetZ + z,
                                              offsetX + x, offsetY + y, offsetZ + z,
                                              offsetX + x+1, offsetY + y, offsetZ + z,
                                              texture.side[0], texture.side[1], texture.side[2], texture.side[3]);
                            }
                            
                            // side4
                            if (!world.isBlocked(offsetX + x, offsetY + y, offsetZ + z+1)) {
                                mesh->addFace(
                                              offsetX + x+1, offsetY + y+1, offsetZ + z+1,
                                              offsetX + x, offsetY + y+1, offsetZ + z+1,
                                              offsetX + x+1, offsetY + y, offsetZ + z+1,
                                              offsetX + x, offsetY + y, offsetZ + z+1,
                                              texture.side[0], texture.side[1], texture.side[2], texture.side[3]);
                            }
                        }
                    }
                }
            }
        }
    }
}

void ChunkRenderer::render(const World& world, const std::vector<std::vector<std::vector<Chunk*>>>& chunks) {
    
    static bool hasMeshCreated = false;
    if (!hasMeshCreated) {
        createMesh(world, chunks);
        hasMeshCreated = true;
    }
    
    std::cout << "ChunkRenderer::render numVertices:" << mesh->vertices.size() / 3 << std::endl;
    
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    
//    GLuint vertexbuffer;
//    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(mesh->vertices.front()), &mesh->vertices.front(), GL_STATIC_DRAW);
    
//    GLuint uvbuffer;
//    glGenBuffers(1, &uvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, mesh->textureCoords.size() * sizeof(mesh->textureCoords.front()), &mesh->textureCoords.front(), GL_STATIC_DRAW);
    
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    auto shader = ResourceManager::get().getShader("test");

    // Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, ResourceManager::get().getTexture("block.dds"));
    // Set our "myTextureSampler" sampler to use Texture Unit 0
    glUniform1i(shader->getUniform("myTextureSampler"), 0);
    
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
    glDeleteVertexArrays(1, &VertexArrayID);
}
