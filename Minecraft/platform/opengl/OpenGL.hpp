//
//  OpenGL.hpp
//  OpenGLPractice1
//
//  Created by Shun Sato on 8/15/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#ifndef OpenGL_hpp
#define OpenGL_hpp

#include <string>

#include "Singleton.hpp"

class GLFWwindow;

class OpenGL: public Singleton<OpenGL> {
public:
    bool setup(int windowWidth, int windowHeight, const std::string& windowName);
    void run();
private:
    void render();
    void update();
    
    GLFWwindow* window;
};

#endif /* OpenGL_hpp */
