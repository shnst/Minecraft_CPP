//
//  Shader.hpp
//  Minecraft_CPP
//
//  Created by Shun Sato on 8/17/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <string>
#include <unordered_map>
#include <vector>

#include "ResourceManager.hpp"

class Shader {
public:
    Shader(const std::string& programName, const std::vector<std::string>& uniforms, const std::vector<std::string>&  attributes);
    ~Shader();
    
    unsigned int getAttribute(const std::string& attributeName) const;
    
    unsigned int getUniform(const std::string& uniformName) const;
    
    unsigned int getID() const;
    
    void use() const;
    
private:
    unsigned int loadShaders(const char * vertex_file_path,const char * fragment_file_path);
    
    friend class ResourceManager;
    
    unsigned int id;
    std::unordered_map<std::string, unsigned int> uniformID;
    std::unordered_map<std::string, unsigned int> attributeID;
};

#endif /* Shader_hpp */
