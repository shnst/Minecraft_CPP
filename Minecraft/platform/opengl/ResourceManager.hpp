//
//  ResourceManager.hpp
//  OpenGLPractice1
//
//  Created by Shun Sato on 8/15/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#ifndef ResourceManager_hpp
#define ResourceManager_hpp

#include <string>
#include <unordered_map>
#include <vector>

#include "Singleton.hpp"

class Shader;

class ResourceManager: public Singleton<ResourceManager> {
public:
    ~ResourceManager();
    
    void loadShader(const std::string& name, const std::vector<std::string>& uniforms, const std::vector<std::string>&  attributes);
    void loadTexture(const std::string& name);
    
    unsigned int getShaderUniform(const std::string& shaderName, const std::string& uniformName);
    unsigned int getShaderAttribute(const std::string& shaderName, const std::string& attributeName);
    
    const Shader* getShader(const std::string& name);
    unsigned int getTexture(const std::string& name);
private:
    bool isShaderLoaded(const std::string& name) const;
    bool isTextureLoaded(const std::string& name) const;
    
    friend class Singleton<ResourceManager>;
    
    ResourceManager();
    
    std::unordered_map<std::string, Shader*> shaders;
    std::unordered_map<std::string, unsigned int> textures;
};

#endif /* ResourceManager_hpp */
