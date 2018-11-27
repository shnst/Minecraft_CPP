//
//  OpenGL.cpp
//  OpenGLPractice1
//
//  Created by Shun Sato on 8/15/18.
//  Copyright © 2018 ShunSato. All rights reserved.
//

#include "OpenGL.hpp"

// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;


#include "Camera.hpp"
#include "Coordinates.hpp"
#include "Drawer.hpp"
#include "GameContext.hpp"
#include "ResourceManager.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Updater.hpp"

void keyboardInput(GLFWwindow* window, int key, int scancode, int action, int mods) {
    auto input = Input::Data();
    switch (key) {
        case GLFW_KEY_W:
            input.addKeyboardEvent(Keyboard::W);
            break;
        case GLFW_KEY_A:
            input.addKeyboardEvent(Keyboard::A);
            break;
        case GLFW_KEY_S:
            input.addKeyboardEvent(Keyboard::S);
            break;
        case GLFW_KEY_D:
            input.addKeyboardEvent(Keyboard::D);
            break;
        case GLFW_KEY_SPACE:
            input.addKeyboardEvent(Keyboard::SPACE);
            break;
        default: break;
    }
    GameContext::get().handleInput(input);
}

static void mouseInput(GLFWwindow* window, double x, double y) {
    static bool didSetPosition = false;
    if (didSetPosition) {
        didSetPosition = false;
//        return;
    }
    
    auto input = Input::Data();
    input.addMouseMoveEvent(x, y);
    GameContext::get().handleInput(input);
    
    auto windowSize = getWindowSize();
    didSetPosition = true;
//    glfwSetCursorPos(window, windowSize.width/2, windowSize.height/2);
}

static void mouseButtonInput(GLFWwindow* window, int button, int action, int mods) {
    auto input = Input::Data();
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        input.addMouseButtonEvent(MouseButton::Right);
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        input.addMouseButtonEvent(MouseButton::Left);
    }
    GameContext::get().handleInput(input);
}


bool OpenGL::setup(int windowWidth, int windowHeight, const std::string& windowName) {
    // Initialise GLFW
    if( !glfwInit() ) {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return false;
    }
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Open a window and create its OpenGL context
    window = glfwCreateWindow(windowWidth, windowHeight, windowName.c_str(), NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);
    
    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return false;
    }
    
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    
    glfwSetCursorPosCallback(window, mouseInput);
    glfwSetKeyCallback(window, keyboardInput);
    glfwSetMouseButtonCallback(window, mouseButtonInput);
    return true;
}

void OpenGL::run() {
    
    do{
        update();
        render();
    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
          glfwWindowShouldClose(window) == 0 );
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
}

void OpenGL::update() {
    Updater::get().update(0.0333333333, false);
}

void OpenGL::render() {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    Drawer::get().draw();
    
    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
}
