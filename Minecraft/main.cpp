//
//  main.cpp
//  OpenGLPractice1
//
//  Created by Shun Sato on 8/15/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#include "OpenGL.hpp"

#include "GameContext.hpp"

#include "Constants.hpp"

int main()
{
    OpenGL::get().setup(WINDOW_WIDTH, WINDOW_HEIGHT, "Minecraft_CPP");
    
    GameContext::get().goTitle();
    OpenGL::get().run();
    return 0;
}
