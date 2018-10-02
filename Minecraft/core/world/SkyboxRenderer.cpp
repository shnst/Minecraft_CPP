//
//  SkyboxRenderer.cpp
//  Minecraft_CPP
//
//  Created by Shun Sato on 8/16/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#include "SkyboxRenderer.hpp"

#include <iostream>

#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Block.hpp"
#include "Camera.hpp"
#include "GameContext.hpp"
#include "Mesh.hpp"
#include "Skybox.hpp"
#include "SkyboxTexture.hpp"
#include "Shader.hpp"
#include "Utils.hpp"

SkyboxRenderer::SkyboxRenderer()
{
    mesh = new Mesh();
    
    shader = new Shader("skybox", {"MVP", "sampler"}, {});
    
    texture = new SkyboxTexture();
    texture->load("skybox");
    
    glGenBuffers(1, &vertexBuffer); //バッファを作成
    glGenBuffers(1, &uvBuffer); //バッファを作成
}

SkyboxRenderer::~SkyboxRenderer() {
    Utils::SafeDelete(mesh);
    Utils::SafeDelete(texture);
    Utils::SafeDelete(shader);
}

void SkyboxRenderer::createMesh(const Skybox& skybox) {
    auto size = skybox.getSize();
    
//    std::cout << "SkyboxRenderer::createMesh x:" << coord.x << " y:" << coord.y << " size:" << size << std::endl;
    
    mesh->vertices.clear();
    mesh->textureCoords.clear();

    // side2
    mesh->addFace(
                  size, size, -size,
                  size, size, size,
                  size, - size, -size,
                  size, - size, size,
                  1.0, 1.0, 1.0, 1.0);

    // side4
    mesh->addFace(
                       - size, size, size,
                       - size, size, - size,
                       - size, - size, size ,
                       - size, - size, - size,
                       1.0, 1.0, 1.0, 1.0);
    
    // top
    mesh->addFace(
                  - size, size, - size,
                  - size, size, size,
                  size, size, - size,
                  size, size, size,
                  1.0, 1.0, 1.0, 1.0);


    // bottom
    mesh->addFace(
                       - size, - size, size,
                       size, - size, size,
                       - size, - size, - size,
                       size, - size, - size,
                       1.0, 1.0, 1.0, 1.0);

    // side3
    mesh->addFace(
                  size, size, size,
                  - size, size, size,
                  size, - size, size,
                  - size, - size, size,
                  1.0, 1.0, 1.0, 1.0);

    // side1
    mesh->addFace(
                       - size, size, - size,
                       size, size, - size,
                       - size, - size, - size,
                       size, - size, - size,
                       1.0, 1.0, 1.0, 1.0);
}

void SkyboxRenderer::render(const Camera& camera, const Skybox& skybox) {
//    std::cout << "SkyboxRenderer::render vertices:" << mesh->vertices.size() / 3 << std::endl;
    
    static bool hasMeshCreated = false;
    if (!hasMeshCreated) {
        createMesh(skybox);
        hasMeshCreated = true;
    }

    // Use our shader
    shader->use();

    glUniformMatrix4fv(shader->getUniform("MVP"), 1, GL_FALSE, &camera.getMVPMatrixForCubeMap()[0][0]);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(mesh->vertices.front()), &mesh->vertices.front(), GL_STATIC_DRAW);

    texture->bind();

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

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, mesh->vertices.size() / 3); // 12*3 indices starting at 0 -> 12 triangles

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    // Cleanup VBO and shader
    glDeleteVertexArrays(1, &vao);
}
