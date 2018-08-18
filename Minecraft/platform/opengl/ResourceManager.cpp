//
//  ResourceManager.cpp
//  OpenGLPractice1
//
//  Created by Shun Sato on 8/15/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#include "ResourceManager.hpp"

#include <iostream>
#include <sstream>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.hpp"
#include "Texture.hpp"

#include "ShaderHelper.hpp"
#include "TextureHelper.hpp"
#include "Utils.hpp"

ResourceManager::ResourceManager() {
    
}

ResourceManager::~ResourceManager() {
    for (auto it=shaders.begin(); it!=shaders.end(); ++it) {
        Utils::SafeDelete((*it).second);
    }
    
    for (auto it=textures.begin(); it!=textures.end(); ++it) {
        glDeleteTextures(1, &(*it).second);
    }
}

void ResourceManager::loadShader(const std::string& name, const std::vector<std::string>& uniforms, const std::vector<std::string>&  attributes) {
    //     Create and compile our GLSL program from the shaders
    unsigned int shaderID = LoadShaders((name+".vert").c_str(), (name+".frag").c_str());
    
    if (shaderID == -1) {
        std::cout << "failed to load shader:" << name << std::endl;
        return;
    }
    
    auto shader = new Shader();
    shader->id = shaderID;
    
    // Get a handle for our "MVP" uniform
    for (auto it=uniforms.begin(); it!=uniforms.end(); ++it) {
        shader->uniformID[(*it)] = glGetUniformLocation(shaderID, (*it).c_str());
    }
    
    for (auto it=attributes.begin(); it!=attributes.end(); ++it) {
        shader->attributeID[(*it)] = glGetUniformLocation(shaderID, (*it).c_str());
    }
    
    shaders[name] = shader;
}

void ResourceManager::loadTexture(const std::string& name) {
    auto textureID = loadDDS(name.c_str());
    
    if (textureID == -1) {
        std::cout << "failed to load texture:" << name << std::endl;
        return;
    }
    
    textures[name] = textureID;
}

const Shader* ResourceManager::getShader(const std::string& name) {
    if (!isShaderLoaded(name)) {
        return nullptr;
    }
    return shaders.at(name);
}

unsigned int ResourceManager::getShaderUniform(const std::string& shaderName, const std::string& uniformName) {
    if (!isShaderLoaded(shaderName)) {
        return -1;
    }
    return shaders.at(shaderName)->uniformID.at(uniformName);
}

unsigned int ResourceManager::getShaderAttribute(const std::string& shaderName, const std::string& attributeName) {
    if (!isShaderLoaded(shaderName)) {
        return -1;
    }
    return shaders.at(shaderName)->attributeID.at(attributeName);
}

unsigned int ResourceManager::getTexture(const std::string& name) {
    if (!isTextureLoaded(name)) {
        std::cout << "failed to get texture:" << name << std::endl;
        return -1;
    }
    return textures.at(name);
}

bool ResourceManager::isShaderLoaded(const std::string& name) const{
    if (shaders.find(name) == shaders.end()) {
        return false;
    }
    return true;
}

bool ResourceManager::isTextureLoaded(const std::string& name) const {
    if (textures.find(name) == textures.end()) {
        return false;
    }
    return true;
}
