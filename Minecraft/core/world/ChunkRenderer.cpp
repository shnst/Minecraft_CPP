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

ChunkRenderer::ChunkRenderer()
:mesh(new Mesh())
{
    glGenBuffers(1, &verticesVBO); //バッファを作成
    glGenBuffers(1, &textureVBO); //バッファを作成
}

ChunkRenderer::~ChunkRenderer() {
    
}

void ChunkRenderer::createMesh(const Chunk& chunk) {
    auto blocks = chunk.getBlocks();
    
    auto xSize = blocks.size();
    auto ySize = blocks[0].size();
    auto zSize = blocks[0][0].size();
    
    mesh->vertices.clear();
    mesh->textureCoords.clear();
    
    auto chunkCoords = chunk.getCoords();
    
    for (int x=0; x<xSize; ++x) {
        for (int y=0; y<ySize; ++y) {
            for (int z=0; z<zSize; ++z) {
                if (!chunk.isBlocked(x, y+1, z)) {
//                    std::cout << "1" << std::endl;
                    mesh->addFace(
                                  chunkCoords.x + x, chunkCoords.y + y+1, chunkCoords.z + z,
                                  chunkCoords.x + x+1, chunkCoords.y + y+1, chunkCoords.z + z,
                                  chunkCoords.x + x, chunkCoords.y + y+1, chunkCoords.z + z+1,
                                  chunkCoords.x + x+1, chunkCoords.y + y+1, chunkCoords.z + z+1,
                                  48.0/256.0, 0, 16.0/256.0, 16.0/16.0);
                }
                
                
                if (!chunk.isBlocked(x, y-1, z)) {
//                    std::cout << "2" << std::endl;
                    mesh->addFace(
                                  chunkCoords.x + x, chunkCoords.y + y, chunkCoords.z + z,
                                  chunkCoords.x + x+1, chunkCoords.y + y, chunkCoords.z + z,
                                  chunkCoords.x + x, chunkCoords.y + y, chunkCoords.z + z+1,
                                  chunkCoords.x + x+1, chunkCoords.y + y, chunkCoords.z + z+1,
                                  16.0/256.0, 0, 16.0/256.0, 16.0/16.0);
                }
//
//
                if (!chunk.isBlocked(x-1, y, z)) {
//                    std::cout << "3" << std::endl;
                    mesh->addFace(
                                  chunkCoords.x + x, chunkCoords.y + y+1, chunkCoords.z + z+1,
                                  chunkCoords.x + x, chunkCoords.y + y+1, chunkCoords.z + z,
                                  chunkCoords.x + x, chunkCoords.y + y, chunkCoords.z + z+1,
                                  chunkCoords.x + x, chunkCoords.y + y, chunkCoords.z + z,
                                  32.0/256.0, 0, 16.0/256.0, 16.0/16.0);
                }
//
//
                if (!chunk.isBlocked(x+1, y, z)) {
//                    std::cout << "4" << std::endl;
                    mesh->addFace(
                                  chunkCoords.x + x+1, chunkCoords.y + y+1, chunkCoords.z + z,
                                  chunkCoords.x + x+1, chunkCoords.y + y+1, chunkCoords.z + z+1,
                                  chunkCoords.x + x+1, chunkCoords.y + y, chunkCoords.z + z,
                                  chunkCoords.x + x+1, chunkCoords.y + y, chunkCoords.z + z+1,
                                  32.0/256.0, 0, 16.0/256.0, 16.0/16.0);
                }
//
                if (!chunk.isBlocked(x, y, z-1)) {
//                    std::cout << "5" << std::endl;
                    mesh->addFace(
                                  chunkCoords.x + x, chunkCoords.y + y+1, chunkCoords.z + z,
                                  chunkCoords.x + x+1, chunkCoords.y + y+1, chunkCoords.z + z,
                                  chunkCoords.x + x, chunkCoords.y + y, chunkCoords.z + z,
                                  chunkCoords.x + x+1, chunkCoords.y + y, chunkCoords.z + z,
                                  32.0/256.0, 0, 16.0/256.0, 16.0/16.0);
                }
//
                if (!chunk.isBlocked(x, y, z+1)) {
//                    std::cout << "6" << std::endl;
                    mesh->addFace(
                                  chunkCoords.x + x+1, chunkCoords.y + y+1, chunkCoords.z + z+1,
                                  chunkCoords.x + x, chunkCoords.y + y+1, chunkCoords.z + z+1,
                                  chunkCoords.x + x+1, chunkCoords.y + y, chunkCoords.z + z+1,
                                  chunkCoords.x + x, chunkCoords.y + y, chunkCoords.z + z+1,
                                  32.0/256.0, 0, 16.0/256.0, 16.0/16.0);
                }
            }
        }
    }
}

void ChunkRenderer::render(const Chunk& chunk) {
    createMesh(chunk);
    
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    
    // Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const std::vector<float> g_vertex_buffer_data = {
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f
    };

    // Two UV coordinatesfor each vertex. They were created with Blender.
    static const std::vector<float> g_uv_buffer_data = {
        0.000059f, 1.0f-0.000004f,
        0.000103f, 1.0f-0.336048f,
        0.335973f, 1.0f-0.335903f,
        1.000023f, 1.0f-0.000013f,
        0.667979f, 1.0f-0.335851f,
        0.999958f, 1.0f-0.336064f,
        0.667979f, 1.0f-0.335851f,
        0.336024f, 1.0f-0.671877f,
        0.667969f, 1.0f-0.671889f,
        1.000023f, 1.0f-0.000013f,
        0.668104f, 1.0f-0.000013f,
        0.667979f, 1.0f-0.335851f,
        0.000059f, 1.0f-0.000004f,
        0.335973f, 1.0f-0.335903f,
        0.336098f, 1.0f-0.000071f,
        0.667979f, 1.0f-0.335851f,
        0.335973f, 1.0f-0.335903f,
        0.336024f, 1.0f-0.671877f,
        1.000004f, 1.0f-0.671847f,
        0.999958f, 1.0f-0.336064f,
        0.667979f, 1.0f-0.335851f,
        0.668104f, 1.0f-0.000013f,
        0.335973f, 1.0f-0.335903f,
        0.667979f, 1.0f-0.335851f,
        0.335973f, 1.0f-0.335903f,
        0.668104f, 1.0f-0.000013f,
        0.336098f, 1.0f-0.000071f,
        0.000103f, 1.0f-0.336048f,
        0.000004f, 1.0f-0.671870f,
        0.336024f, 1.0f-0.671877f,
        0.000103f, 1.0f-0.336048f,
        0.336024f, 1.0f-0.671877f,
        0.335973f, 1.0f-0.335903f,
        0.667969f, 1.0f-0.671889f,
        1.000004f, 1.0f-0.671847f,
        0.667979f, 1.0f-0.335851f
    };
    
    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(mesh->vertices.front()), &mesh->vertices.front(), GL_STATIC_DRAW);
//    glBufferData(GL_ARRAY_BUFFER, g_vertex_buffer_data.size() * sizeof(g_vertex_buffer_data.front()), &g_vertex_buffer_data[0], GL_STATIC_DRAW);
    
    GLuint uvbuffer;
    glGenBuffers(1, &uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, mesh->textureCoords.size() * sizeof(mesh->textureCoords.front()), &mesh->textureCoords.front(), GL_STATIC_DRAW);
//    glBufferData(GL_ARRAY_BUFFER, g_uv_buffer_data.size() * sizeof(g_uv_buffer_data.front()), &g_uv_buffer_data[0], GL_STATIC_DRAW);
    
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
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
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
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
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
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &uvbuffer);
    glDeleteVertexArrays(1, &VertexArrayID);
    
    
//    // create vertex info
//    createMesh(chunk);
//
//    for (auto it = mesh->vertices.begin(); it!=mesh->vertices.end(); ++it) {
//        std::cout << (*it) << std::endl;
//    }
//
//    // update vbo
//    glBindBuffer(GL_ARRAY_BUFFER, verticesVBO); //GLコンテキストにvertex_vboをGL_ARRAY_BUFFERでバインド。
//    glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(mesh->vertices.front()), &mesh->vertices, GL_STATIC_DRAW); //実データを格納
//
//
//    glBindBuffer(GL_ARRAY_BUFFER, textureVBO); //GLコンテキストにvertex_vboをGL_ARRAY_BUFFERでバインド。
//    glBufferData(GL_ARRAY_BUFFER, mesh->textureCoords.size() * sizeof(mesh->vertices.front()), &mesh->textureCoords, GL_STATIC_DRAW); //実データを格納
//
//
//    // TODO: use version 330
//    // create vao from vbo and send it to shader.
//
//    // Position attribute
//    glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
//    glVertexAttribPointer(ResourceManager::get().getAttributeVertex(), 3, GL_FLOAT, GL_FALSE, 3 * sizeof(mesh->vertices.front()), 0);
//
//    // Color attribute
//    glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
//    glVertexAttribPointer(ResourceManager::get().getAttributeTexture(), 2, GL_FLOAT, GL_FALSE, 2 * sizeof(mesh->vertices.front()), 0);
//
//    glDrawArrays(GL_TRIANGLES, 0, mesh->vertices.size()/3);
//
//    std::cout << "ChunkRenderer::render vertices:" << mesh->vertices.size() << std::endl;
}
