//
//  main.cpp
//  OpenGLPractice1
//
//  Created by Shun Sato on 8/15/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#include "OpenGL.hpp"

int main()
{
    OpenGL::get().setup(640, 480, "Minecraft_CPP");
    OpenGL::get().run();
    return 0;
}
