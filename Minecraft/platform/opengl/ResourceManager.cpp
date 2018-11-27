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
    for (auto& shader : shaders) {
        Utils::SafeDelete(shader.second);
    }
    
    for (auto& texture : textures) {
        glDeleteTextures(1, &texture.second);
    }
}

void ResourceManager::loadShader(const std::string& name, const std::vector<std::string>& uniforms, const std::vector<std::string>&  attributes) {
    if (isShaderLoaded(name)) {
        std::cout << "shader already loaded name:" << name << std::endl;
        return;
    }
    shaders[name] = new Shader(name, uniforms, attributes);
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
        std::cout << "failed to get shader:" << name << std::endl;
        return nullptr;
    }
    return shaders.at(name);
}

unsigned int ResourceManager::getShaderUniform(const std::string& shaderName, const std::string& uniformName) {
    if (!isShaderLoaded(shaderName)) {
        std::cout << "failed to get shader:" << shaderName << std::endl;
        return -1;
    }
    return shaders.at(shaderName)->uniformID.at(uniformName);
}

unsigned int ResourceManager::getShaderAttribute(const std::string& shaderName, const std::string& attributeName) {
    if (!isShaderLoaded(shaderName)) {
        std::cout << "failed to get shader:" << shaderName << std::endl;
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
