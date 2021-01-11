//
// Created by SilverJun on 2021-01-11.
//

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GLGraphicsAPI.h"
#include "GameApp.h"

void Graphics<GraphicsAPI::OpenGL>::Init(GLFWwindow* window) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_SAMPLES, 8);

    auto* gameApp = GameApp::GetInstance();

    _window = glfwCreateWindow(gameApp->_width, gameApp->_height, u8"꿀벌대소동", nullptr, nullptr);
    if (!_window)
        exit(EXIT_FAILURE);

    glfwMakeContextCurrent(_window);

    glewExperimental = GL_TRUE;
    GLenum errorCode = glewInit();
    if (GLEW_OK != errorCode) {
        std::cerr << "Error: GLEW Init failed! " << glewGetErrorString(errorCode) << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
    glCullFace(GL_BACK);
}

void Graphics<GraphicsAPI::OpenGL>::PreRender() {
    glClearColor(51/255.0f, 204 / 255.0f, 255 / 255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1, 1);
}

void Graphics<GraphicsAPI::OpenGL>::Render() {

}

void Graphics<GraphicsAPI::OpenGL>::PostRender() {
    glDisable(GL_POLYGON_OFFSET_FILL);

    glFlush();

    glfwSwapBuffers(_window);
}

void Graphics<GraphicsAPI::OpenGL>::RegisterMaterial(Material &&material) {

}

void Graphics<GraphicsAPI::OpenGL>::LoadTexture(Material &material) {

}

void Graphics<GraphicsAPI::OpenGL>::LoadShaders(Material &material) {

}
