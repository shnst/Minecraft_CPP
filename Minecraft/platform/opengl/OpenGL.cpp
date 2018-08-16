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

void keyboardInput(GLFWwindow* window, int key, int scancode, int action, int mods) {
//    if (key == GLFW_KEY_E && action == GLFW_PRESS)
//        activate_airship();
    auto camera = GameContext::get().getCamera();
    switch (key) {
        case GLFW_KEY_W:
            camera->forward();
            break;
        case GLFW_KEY_A:
            camera->left();
            break;
        case GLFW_KEY_S:
            camera->back();
            break;
        case GLFW_KEY_D:
            camera->right();
            break;
        default: break;
    }
}

static void mouseInput(GLFWwindow* window, double x, double y) {
    static bool didSetPosition = false;
    if (didSetPosition) {
        didSetPosition = false;
//        return;
    }
    
    auto camera = GameContext::get().getCamera();
    
    camera->mouseInput(x, y);
    
    auto windowSize = getWindowSize();
    didSetPosition = true;
//    glfwSetCursorPos(window, windowSize.width/2, windowSize.height/2);
    
}


bool OpenGL::setup(int windowWidth, int windowHeight, const std::string& windowName) {
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return -1;
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
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
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
    
    ResourceManager::get().loadShader("test", {"MVP", "myTextureSampler"}, {});
    ResourceManager::get().loadTexture("blocks.dds");
    
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
    
}

void OpenGL::render() {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    auto shader = ResourceManager::get().getShader("test");
    
    // Use our shader
    glUseProgram(shader->id);
    
//    // Send our transformation to the currently bound shader,
//    // in the "MVP" uniform
//    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
//    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
//    // Camera matrix
//    glm::mat4 View       = glm::lookAt(
//                                       glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
//                                       glm::vec3(0,0,0), // and looks at the origin
//                                       glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
//                                       );
//    // Model matrix : an identity matrix (model will be at the origin)
//    glm::mat4 Model      = glm::mat4(1.0f);
//    // Our ModelViewProjection : multiplication of our 3 matrices
//    glm::mat4 MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around
    
    auto camera = GameContext::get().getCamera();
    glUniformMatrix4fv(shader->getUniform("MVP"), 1, GL_FALSE, &camera->getMVPMatrix()[0][0]);
    
    
    Drawer::get().draw();
    
    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
}
