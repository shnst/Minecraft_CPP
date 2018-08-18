//
//  Shader.cpp
//  Minecraft_CPP
//
//  Created by Shun Sato on 8/17/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#include "Shader.hpp"

#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

Shader::Shader() {
    
}

Shader::~Shader() {
    glDeleteProgram(id);
}

unsigned int Shader::getAttribute(const std::string& attributeName) const {
    return attributeID.at(attributeName);
}

unsigned int Shader::getUniform(const std::string& uniformName) const {
    return uniformID.at(uniformName);
}

unsigned int Shader::getID() const {
    return id;
}

void Shader::use() const {
    glUseProgram(id);
}
