//
// Created by SilverJun on 2021-01-11.
//
#pragma once

#include <GLFW/glfw3.h>

enum class GraphicsAPI
{
    OpenGL,
    Vulkan,
    DX11,
};

template<GraphicsAPI T>
class Graphics final
{
public:
    Graphics() = default;
    virtual ~Graphics() = default;

    void Init(GLFWwindow* window);
    void PreRender();
    void Render();
    void PostRender();

private:
    GLFWwindow* _window;
};
